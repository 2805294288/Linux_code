#pragma once 

#include <iostream>
#include <string>
#include <cstdlib>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>
#include <signal.h>

#define BACKLOG 5

class tcpServer
{
  public:
    tcpServer(int _port)
      :port(_port)
      ,lsock(-1)
    {}
    void initServer()
    {
      signal(SIGCHLD,SIG_IGN);
      lsock = socket(AF_INET,SOCK_STREAM,0);
      if(lsock < 0)
      {
        std::cerr<< " socket error " <<std::endl;
        exit(2);
      }
      struct sockaddr_in local;
      local.sin_family = AF_INET;
      local.sin_port = htons(port);
      local.sin_addr.s_addr=  INADDR_ANY;

      if(bind(lsock,(struct sockaddr*)&local,sizeof(local)) < 0)
      {
          std::cerr<<"bind error "<<std::endl;
          exit(3);
      }
      if(listen(lsock,BACKLOG) < 0)
      {
        std::cerr<< "bind error " << std::endl;
        exit(4);
      }
    }
    void service(int sock)
    {
      char buffer[1024];
      while(1)
      {
        size_t s = recv(sock,buffer,sizeof(buffer)-1,0);
        if(s > 0)
        {
          buffer[s] = 0;
          std::cout << "client: "<< buffer;
          send(sock, buffer,strlen(buffer),0);
        }
        else if(s == 0)
        {
          std::cout<<" Client quit! " << std::endl;
          close(sock);
          break;
        }
        else 
        {
          std::cout<< "recv client data error !" << std::endl;
          break;
        }
      }
      close(sock);
    }
    void start()
    {
      sockaddr_in endpoint;
      while(1)
      {
        socklen_t len = sizeof(endpoint);
       int sock =  accept(lsock,(struct sockaddr*)&endpoint,&len);

       if(sock < 0)
       {
          std::cerr<<"accept error"<<std::endl;
          continue;
       }
        std::string cli_info = inet_ntoa(endpoint.sin_addr);//四字节Ip改为点分十进制
        cli_info += " : ";
        cli_info += std::to_string(ntohs(endpoint.sin_port));
        std::cout << cli_info<< std::endl;
        std::cout << "get a new link!"<< "sock: " << sock <<std::endl;

        pid_t id = fork();
        if(id == 0)
        {
          close(lsock);
          service(sock);
          exit(0);

        }
        close(sock);
        //waitpid(-1,NULL,0);
      }
    }

    ~tcpServer()
    {}

  private:
    int port;
    int lsock;
};
