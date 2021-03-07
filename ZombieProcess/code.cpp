#include <stdio.h>                                                                                                                                                                             
#include <stdlib.h>
#include <unistd.h>

int main()
{
  printf("输入一遍\n");
  pid_t ret = fork();
  if(ret > 0)
  {
    //parent    
    while(1)    
    {    
    printf("I am parent! pid is : %d\n", getpid());    
    sleep(1);    
    }    
  }    
  else if(ret == 0)    
  {    
    /child    
    int count = 0;    
    while(count<5)    
    {    
      printf("I am child! pid is : %d, ppid: %d\n", getpid(), getppid());    
      count++;    
      sleep(2);    
    }    
    exit(0);    
  }    
  else    
  {    
    printf("fork error\n");    
  }    
  sleep(1);    
  return 0;    
}