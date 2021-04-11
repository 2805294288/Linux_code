#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>

#define SIZE 128

int main()
{
  close(1);
  int fd = open("log.txt",O_CREAT|O_TRUNC|O_RDWR,0644);
  if(fd<0)
  {
      perror("open error!");
      return 1;
  }


  const char* str="Hello World 1!\n";
  const char* str1="Hello World 2!\n";
  const char* str2="Hello World 3!\n";
  write(1,str,strlen(str));
  printf(str1);
  fprintf(stdout,str2);

  fflush(stdout);
  close(fd);

  return 0;
}
