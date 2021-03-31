#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>

#define SIZE 128

int main()
{

  int fd = open("log.txt",O_CREAT|O_TRUNC|O_RDWR,0644);
  if(fd<0)
  {
      perror("open error!");
      return 1;
  }

  const char* str1="Hello World 2!\n";
  write(fd,str1,strlen(str1));
  dup2(fd,1);
  printf(str1);
  
  fflush(stdout);
  close(fd);

  return 0;
}