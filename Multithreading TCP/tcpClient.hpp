#pragma once 

#include<iostream>
#include<string>
#include<sys/types.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<cstring>
class tcpClient
{
  public:
    tcpClient(std::string _ip = "127.0.0.1",int _port = 8080)
      :svr_ip(_ip)
      ,svr_port(_port)
    {}
    void initClient()
    {
      sock = socket(AF_INET, SOCK_STREAM, 0);
      if(sock < 0)
      {
        std::cerr << "sock error" << std::endl;
        exit(2);
      }
       //bind不需要 客户端！！！由系统自动进行绑定
       //也不需要监听，服务器需要监听
       //也不需要accept
       //面向链接，需要链接
       struct sockaddr_in svr;
       svr.sin_family = AF_INET;
       svr.sin_port = htons(svr_port);
       svr.sin_addr.s_addr = inet_addr(svr_ip.c_str());

      if(connect(sock,(struct sockaddr*)&svr,sizeof(svr)) !=0)
      {
        std::cout<<"connect error! "<<std::endl;
        exit(3);
      }
      //connect success！
    }
    void start()
    {
      
      char msg[64];
      while(1)
      {
          std::cout<< "Please enter:";
          fflush(stdout);
          size_t s = read(0,msg,sizeof(msg)-1);
          if(s > 0)
          {
            msg[s]=0;
            send(sock,msg,strlen(msg),0);
            size_t ss =  recv(sock,msg,sizeof(msg)-1,0);
            if(ss > 0)
            {
              msg[ss] = 0;
              std::cout<< "server echo: "<< msg << std::endl;
            }
          }
      }
    }
    ~tcpClient()
    {
      close(sock);
    }
  private:
    int svr_port;
    std::string svr_ip;
    int sock;
};
