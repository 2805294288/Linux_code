#pragma once 

#include<iostream>
#include<string>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<cstdlib>
#include<cstdio>
#include<map>

class udpServer
{
  public:
    udpServer(int _port=8080)
     // :ip(_ip)
      :port(_port)
    {
       dict.insert(std::pair<std::string,std::string>("apple","苹果"));
       dict.insert(std::pair<std::string,std::string>("banana","香蕉"));
       dict.insert(std::pair<std::string,std::string>("string","字符串"));
       dict.insert(std::pair<std::string,std::string>("int","整形"));
       dict.insert(std::pair<std::string,std::string>("float","浮点型"));
    }
    void initServer()
    {
      sock = socket(AF_INET,SOCK_DGRAM,0);
      std::cout<<"sock"<<sock<<std::endl;
      struct sockaddr_in local;
      local.sin_family = AF_INET;
      local.sin_port = htons(port);
      local.sin_addr.s_addr = INADDR_ANY;
    
    
       if(bind(sock,(struct sockaddr*)&local,sizeof(local)) < 0)
       {
          std::cerr<<"bind error!\n"<<std::endl;
          exit(1);
       }
    }

    void start()
    {
      char msg[64];
      while(1)
      {
          msg[0]='\0';
          struct sockaddr_in end_point;
          socklen_t len = sizeof(end_point);
          ssize_t s=recvfrom(sock,msg,sizeof(msg)-1,0,(struct sockaddr*)&end_point,&len);
          if(s>0)
          {
            char buff[16];
            sprintf(buff,"%d",ntohs(end_point.sin_port));

            std::string cli = inet_ntoa(end_point.sin_addr);
            cli += ":";
            cli += buff;

            msg[s]='\0';
            std::cout<<cli<< ":"<< msg <<std::endl;

            //std::string echo_string = msg;
            std::string echo = "unknow";
            auto it = dict.find(msg);
            if(it != dict.end())
            {
              echo = dict[msg];
            }
            //echo_string += " [server echo!]";
            sendto(sock,echo.c_str(),echo.size(),0,(struct sockaddr*)&end_point,len);
          }
      }
    }
    ~udpServer()
    {
      close(sock);
    }
  private:
   // std::string ip;
    int port;
    int sock;
    std::map<std::string,std::string> dict;
};
