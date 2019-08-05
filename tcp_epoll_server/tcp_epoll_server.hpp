#pragma once
#include <vector>
#include <functional>
#include <sys/epoll.h>
#include "tcp_socket.hpp"

// 相当于 接口 Interface
// class Base {
// public:
//   virtual void Add(const TcpSocket& ) = 0;
//   virtual void Del(const TcpSocket& ) = 0;
//   virtual void Wait(std::vector<TcpSocket>* output) = 0;
// };

// Epoll 这个类就对标 Selector 这个类
class Epoll {
public:
  Epoll() {
    epoll_fd_ = epoll_create(10);
  }

  ~Epoll() {
    close(epoll_fd_);
  }

  // 只有新客户端链接过来了才调用. 调用频率远低于 select 
  // 也就意味着 epoll 拷贝数据就远没有 select 拷贝的那么频繁
  void Add(const TcpSocket& sock, bool is_et = false) {
    printf("[Epoll::Add] %d\n", sock.GetFd());
    epoll_event event;
    event.events = EPOLLIN;
    if (is_et) {
      event.events |= EPOLLET;
    }
    // 此处 epoll add 的时候插入的是键值对. 
    // fd 在键和值之中都出现了. 这件事情是迫不得已(
    // 这也是epoll一个小小的槽点)
    event.data.fd = sock.GetFd();
    epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, sock.GetFd(), &event);
  }

  void Del(const TcpSocket& sock) {
    printf("[Epoll::Del] %d\n", sock.GetFd());
    epoll_ctl(epoll_fd_, EPOLL_CTL_DEL, sock.GetFd(), NULL);
  }

  void Wait(std::vector<TcpSocket>* output) {
    output->clear();
    // 等待文件描述符就绪
    epoll_event events[100];
    // 最后一个参数表示阻塞等待
    // 返回之后, 就有若干个文件描述符就绪, 保存在 events 数组之中
    // 返回值结果就是在描述数组中有几个有效元素
    // epoll_wait 返回的内容只是键值对的值
    // 如果不加任何处理的话, 用户不知道对应文件描述符是谁. 
    // 迫不得已, 只能在插入的时候, 把 socket 往值里也存一份
    int nfds = epoll_wait(epoll_fd_, events, 100, -1);
    if (nfds < 0) {
      perror("epoll_wait");
      return;
    }
    // 依次处理每个就绪的文件描述符
    for (int i = 0; i < nfds; ++i) {
      int sock = events[i].data.fd;
      output->push_back(TcpSocket(sock));
    }
  }

private:
  int epoll_fd_;  // 通过这个 epoll_fd_ 找到内核中的对象, 从而进行文件描述符的管理
};

typedef std::function<void (const std::string&, std::string*)> Handler;

#define CHECK_RET(exp) \
  if (!exp) {\
    return false;\
  }

// Nginx 非常知名的使用 Epoll 的开源项目
// NodeJs 

class TcpEpollServer {
public:
  bool Start(const std::string& ip, uint16_t port,
      Handler handler) {
    // 1. 创建 socket
    TcpSocket listen_sock;
    CHECK_RET(listen_sock.Socket());
    // 2. 绑定端口号
    CHECK_RET(listen_sock.Bind(ip, port));
    // 3. 监听 socket
    CHECK_RET(listen_sock.Listen());
    // 4. 创建 Epoll 对象, 并把 listen_sock 用 Epoll 管理起来
    Epoll epoll;
    epoll.Add(listen_sock);
    // 5. 进入主循环
    while (true) {
      // 6. 使用 Epoll::Wait 等待文件描述符就绪
      std::vector<TcpSocket> output;
      epoll.Wait(&output);
      // 7. 循环处理每个就绪的文件描述符, 也是分成两种情况
      for (auto sock : output) {
        if (sock.GetFd() == listen_sock.GetFd()) {
          //  a) listen_sock 就调用 Accept
          TcpSocket client_sock;
          sock.Accept(&client_sock);
          epoll.Add(client_sock);
        } else {
          //  b) 非 listen_sock, 就调用 Recv
          std::string req;
          // ET 模式下必须采用非阻塞的方式进行读写
          int n = sock.Recv(&req);
          if (n < 0) {
            continue;
          }
          if (n == 0) {
            // 对端关闭
            printf("[client %d] disconnected!\n", sock.GetFd());
            sock.Close();
            epoll.Del(sock);
            continue;
          }
          printf("[client %d] %s\n", sock.GetFd(), req.c_str());
          // 正确读取的情况
          std::string resp;
          handler(req, &resp);
          sock.Send(resp);
        }  // end else
      }  // end for
    }  // end while (true)
  }  // end function Start
};
