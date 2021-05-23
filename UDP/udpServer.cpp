#include"udpServer.hpp"
void Usage(std::string proc)
{
  std::cout<<"Usage: "<< proc <<"local_ip local_proc"<<std::endl;
}
int main(int argc,char *argv[])
{
  if(argc != 3)
  {
    Usage(argv[0]);
      exit(1);
  }
  udpServer *up = new udpServer();
  up->initServer();
  up->start();

  delete up;
}
