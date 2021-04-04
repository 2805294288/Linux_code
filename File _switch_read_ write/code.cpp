#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>

#define SIZE 128

int main()
{
  //close(1);
  int fd = open("log.txt",O_CREAT|O_APPEND|O_RDWR,0644); //打开文件
  if(fd<0)
  {
      perror("open error!");
      return 1;
  }


 // const char* str1="Hello World 2!\n";
 //  write(fd,str1,strlen(str1));  //写文件 1
  
  char buf[SIZE]={0};
  read(fd,buf,15); //读文件
  printf("buf = %s",buf);

  close(fd); //关闭文件

  return 0;
  }
