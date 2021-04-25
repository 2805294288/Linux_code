#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
pthread_mutex_t lock;
pthread_cond_t cond;

void *run1(void *arg)
{
  const char *name=(char*)arg;
  while(1)
  {
    pthread_cond_wait(&cond,&lock);
    printf("%s get singal\n",name);
  }
}
void *run2(void *arg)
{
  const char *name=(char*)arg;
  while(1)
  {
    sleep(2);
    pthread_cond_signal(&cond);
    printf("%s signal done!\n",name);
  }
}
int main()
{
  pthread_mutex_init(&lock,NULL);
  pthread_cond_init(&cond,NULL);
  pthread_t t1;
  pthread_t t2;

  pthread_create(&t1,NULL,run1,"thread1");
  pthread_create(&t2,NULL,run2,"thread2");

  pthread_join(t1,NULL);
  pthread_join(t2,NULL);
  
  pthread_mutex_destroy(&lock);
  pthread_cond_destroy(&cond);

  return 0;
}
