#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<sys/types.h>

void *pthread_run(void* arg)
{
  while(1)
  {
    printf("I am new %s:My pid is: %d My id is: %p \n",(char*)arg,getpid(),pthread_self());
    printf("\n");
    sleep(1);
  }
}
int main()
{ 
  pthread_t tid;
  pthread_create(&tid,NULL,pthread_run,(void*)"pthrtead");

  while(1)
  {

    printf("I am man pthread:My pid is : %d My id is: %p \n",getpid(),pthread_self());
    printf("The new pthread tid is: %p \n",tid);
    sleep(1);
  }

  return 0;
}
