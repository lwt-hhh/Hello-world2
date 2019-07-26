#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>


int main()
{

  //创建socket
  int sock=socket(AF_INET,SOCK_DGRAM,0);
  if(sock<0)
  {
    perror("socket fail");
    return 1;
  }

  sockaddr_in addr;
  addr.sin_family=AF_INET;
  addr.sin_addr.s_addr=inet_addr("0.0.0.0");
  addr.sin_port=htons(9090);
   

  //绑定
  int ret=bind(sock,(sockaddr*)&addr,sizeof(addr));
  printf("服务器启动成功\n");


  while(1)
  {
    //接受客户端请求
    sockaddr_in peer;
    socklen_t len=sizeof(peer);
    char buf[1024]={0};
    ssize_t n=recvfrom(sock,buf,sizeof(buf)-1,0,(sockaddr*)&peer,&len);
    if(n<0)
    {
      perror("recvfrom fail");
      return 1;
    }
  buf[n]='\0';


  //计算响应    （这里不需要计算响应，因为我们实现的是回显服务器,客户端发什么服务器返回什么）
  
  //向客户端返回（发送）计算结果
  
  n=sendto(sock,buf,sizeof(buf),0,(sockaddr*)&peer,len);
  if(n<0)
  {
    perror("sendto fail");
    continue;
  }

  printf("[%s:%d] buf: %s\n",inet_ntoa(peer.sin_addr),ntohs(peer.sin_port),buf);
}

  close(sock);
  return 0;
}
