#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<sys/types.h>
#include<fcntl.h>
#include<ctype.h>
#include<sys/stat.h>
#include<wait.h>

#define SIZE 128

void redirect( char *cmd)
{
  int fd =  -1;
  char *ptr = cmd;
  char *file = NULL;
  int count = 0;
  while(*ptr)
  {
    if(*ptr == '>')
    {
      *ptr++ = '\0';
      count++;
      if(*ptr == '>')
      {
        *ptr++ ='\0';
        count++;
      }
      while(*ptr != '\0' && isspace(*ptr))
      {
        ptr++;
      }
      file=ptr;
      while(*ptr != '\0' && !isspace(*ptr))
      {
        ptr++;
      }
      *ptr = '\0';

      if(count == 1)
      {
        fd = open(file,O_CREAT|O_TRUNC|O_RDWR,0644);
      }
      else if(count == 2)
      {
        fd = open(file,O_CREAT|O_APPEND|O_RDWR,0644);
      }
      else 
      {
        perror("command error");
      }

      dup2(fd,1);
      close(fd);
    }
    ptr++;
  }
}


int main()
{
  while(1)
  {
    printf("[myshell@VM-8-16-centos shell]$ ");
    char str[SIZE]={0};

    fgets(str,SIZE,stdin);
    str[strlen(str)-1]='\0';
    
    pid_t id=fork();
    if(id<0)
    {
      perror("fork error!");
        return 1;
    }
    if(id == 0)
    {
      redirect(str);

    char *arg[SIZE]={0};

    arg[0]=strtok(str," ");

    int i=1;

    do 
    {
      arg[i]=strtok(NULL," ");
      if(!arg[i])
      {
        break;
      }
    i++;
    }while(1);

      execvp(arg[0],arg);

      printf("comman not error!\n");
      exit(1);
    }

    int st;
    waitpid(id,&st,0);

    printf("state is:%d \n",(st>>8)&0xff);
  }

  return 0;
}
