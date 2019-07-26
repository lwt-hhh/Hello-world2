#include<stdio.h>                                                                                 
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>


int main(int argc,char* argv[])
{

  //创建sock
  int sock=socket(AF_INET,SOCK_DGRAM,0);
  if(sock<0)
  {
    perror("sock fail");
    return 1;
  }

  //这里不需要绑定端口号，操作系统回自动分配
  //所以不用bind这一步
  
  sockaddr_in server_addr;

  server_addr.sin_family=AF_INET;
  server_addr.sin_addr.s_addr=inet_addr(argv[1]);
  server_addr.sin_port=htons(9090);

  //客户端直接发送数据即可
  while(1)
  {
    char buf[1024]={0};
    printf("请输入一段内容： ");
    fflush(stdout);
    scanf("%s\n",buf);
    sendto(sock,buf,strlen(buf),0,(sockaddr*)&server_addr,sizeof(server_addr));
    //从服务器接受一下返回结果
    char out_buf[1024]={0};

    //后两个参数填NULL,表示不关注对端地址
    recvfrom(sock,out_buf,sizeof(out_buf),0,NULL,NULL);

    printf("[server resp: ]%s\n",out_buf);

  }

  return 0;
}
