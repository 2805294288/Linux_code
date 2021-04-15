#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void show_pending(sigset_t *pending)
{
  int sig = 1;
  for(; sig<=31; sig++){
    if(sigismember(pending, sig)){
      printf("1");
    }
    else 
    {
      printf("0");
    }
  }
  printf("\n");
}

void handler(int sig)
{
  printf("get a sig: %d\n", sig);
}

int main()
{
  signal(2, handler);

  sigset_t pending;
  
  sigset_t block,oblock;
  sigemptyset(&block);
  sigemptyset(&oblock);
  
  sigaddset(&block, 2);//阻塞信号
  
  sigprocmask(SIG_SETMASK, &block, &oblock);//屏蔽进程的信号集
  
  int count = 0;
  
  while(1){
    sigemptyset(&pending);//初始化
    sigpending(&pending);//未决信号集
    show_pending(&pending);//显示未决信号
    sleep(1);
    count++;
    if(count == 10){
      printf("recover sig mask!\n");
      sigprocmask(SIG_SETMASK, &oblock, NULL);//10s时解除屏蔽
    }
  }
   
  return 0;
}