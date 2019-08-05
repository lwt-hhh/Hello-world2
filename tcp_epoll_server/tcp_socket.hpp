#pragma once
#include <cstdio>
#include <cstring>
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class TcpSocket {
public:
  TcpSocket() : fd_(-1) {

  }

  TcpSocket(int fd) : fd_(fd) {

  }

  bool Socket() {
    // 和 UDP 不同的是, 第二个参数
    fd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (fd_ < 0) {
      perror("socket");
      return false;
    }
    return true;
  }

  // 给服务器使用
  bool Bind(const std::string& ip, uint16_t port) {
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip.c_str());
    addr.sin_port = htons(port);
    int ret = bind(fd_, (sockaddr*)&addr, sizeof(addr));
    if (ret < 0) {
      perror("bind");
      return false;
    }
    return true;
  }

  // 给服务器使用
  bool Listen() {
    // listen 进入监听状态
    int ret = listen(fd_, 10);
    if (ret < 0) {
      perror("listen");
      return false;
    }
    return true;
  }

  // 给服务器使用
  bool Accept(TcpSocket* peer, std::string* ip = NULL,
      uint16_t* port = NULL) {
    // accept 从连接队列中取一个连接到用户代码中
    // 如果队列中没有连接, 就会阻塞(默认行为)
    sockaddr_in peer_addr;
    socklen_t len = sizeof(peer_addr);
    // 返回值也是一个 socket 
    int client_sock = accept(fd_, (sockaddr*)&peer_addr, &len);
    if (client_sock < 0) {
      perror("accept");
      return false;
    }
    peer->fd_ = client_sock;
    if (ip != NULL) {
      *ip = inet_ntoa(peer_addr.sin_addr);
    }
    if (port != NULL) {
      *port = ntohs(peer_addr.sin_port);
    }
    return true;
  }

  // 客户端和服务器都会使用
  int Recv(std::string* msg) {
    msg->clear();
    char buf[1024 * 10] = {0};
    ssize_t n = recv(fd_, buf, sizeof(buf) - 1, 0);
    // recv 的返回值: 如果读取成功, 返回结果为读到的字节数
    // 如果读取失败, 返回结果为 -1
    // 如果对端关闭了 socket 返回结果为 0
    if (n < 0) {
      perror("recv");
      return -1;
    } else if (n == 0) {
      // 需要考虑到 返回 0 的情况
      return 0;
    }
    msg->assign(buf);
    return 1;
  }

  // 客户端和服务器都会使用
  bool Send(const std::string& msg) {
    ssize_t n = send(fd_, msg.c_str(), msg.size(), 0);
    if (n < 0) {
      perror("send");
      return false;
    }
    return true;
  }

  // 给客户端使用
  bool Connect(const std::string& ip, uint16_t port) {
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip.c_str());
    addr.sin_port = htons(port);
    int ret = connect(fd_, (sockaddr*)&addr, sizeof(addr));
    if (ret < 0) {
      perror("connet");
      return false;
    }
    return true;
  }

  bool Close() {
    if (fd_ != -1) {
      close(fd_);
    }
    return true;
  }

  int GetFd() const {
    return fd_;
  }

  bool SetNoBlock() {
    // 获取到 fd_ 这个文件描述符的相关标志位
    // 这些标志位也是通过一个位图的方式来反应的, 保存在 fl 这个 int 中
    int fl = fcntl(fd_, F_GETFL);
    if (fl < 0) {
      perror("fcntl F_GETFL");
      return false;
    }
    int ret = fcntl(fd_, F_SETFL, fl | O_NONBLOCK);
    if (ret < 0) {
      perror("fcntl F_SETFL");
      return false;
    }
    return true;
  }

  int RecvNoBlock(std::string* msg) const {
    msg->clear();
    // 这是一个近似的写法, 不够严谨, 没有考虑粘包问题
    // 如果 TCP 的接受缓冲区为空, 此时会读不到数据, 但是 recv 同样也会返回. errno 会被设置成 EAGAIN 或者 EWOULDBLOCK
    // 如果当前读到的数据长度比设定的用户缓冲区长度一样, 就持续往下读
    // 如果当前读到的数据长度已经比缓冲区长度短了, 就认为暂时读完了
    char tmp[1024 * 10] = {0};
    while (true) {
      ssize_t n = recv(fd_, tmp, 1024 * 10 - 1, 0);
      if (n < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
          // 此时缓冲区已经没数据了, 还是继续尝试读
          continue;
        }
        // 如果是其他原因导致的读失败, 退出函数
        return -1;
      }
      if (n == 0) {
        // 对端关闭
        return 0;
      }
      tmp[n] = '\0';
      // 把这个数据追加到 输出参数 中
      msg->append(tmp); // 相当于 +=
      if (n < (ssize_t)sizeof(tmp) - 1) {
        // 这一次读取没有填充完整个缓冲区, 我们认为当前缓冲区里应该就暂时没数据了
        break;
      }
    }
    return msg->size();
  }

  bool SendNoBlock(const std::string& msg) const {
    // 这个相比于 Recv 更简单一点
    // 当实际发送数据长度和 msg 的长度一样的时候, 就发送完了
    // 这样写是比较有风险. 
    // 由于当前是非阻塞 IO, 如果发送缓冲区已经满了, 函数一调用就返回, 可能会出现发送失败的情况 
    // 更严谨的情况, 应该是小块小块数据发送, 每次发一个数据之后, 
    // 都检查自己发了多少数据, 累加发送成功的数据达到 msg 的长度的时候
    // 才最终发送完成
    send(fd_, msg.c_str(), msg.size(), 0);
    // TODO
    return true;
  }

private:
  int fd_;
};
