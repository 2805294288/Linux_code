#include "block.h"
using namespace std;

void *consumer_run(void *arg)
{
  //int num=(int)arg;
  pthread_mutex_t lock;
  BlockQueue *bq=(BlockQueue*)arg;
  while(true)                         
  {                            
    pthread_mutex_lock(&lock);
    //int data;
    Task t;
    bq->Get(t); 
    //t.Run();
    pthread_mutex_unlock(&lock);
    cout<<"consumer"<<t.x<<"+"<<t.y<<"="<<t.Run()<<endl;
    sleep(1); 
  }
  //pthread_mutex_unlock(&lock);
}
void *productor_run(void *arg)
{
  //int num=(int)arg;
  pthread_mutex_t lock;
  sleep(1);
  BlockQueue *bq=(BlockQueue*)arg;
  //int count=0;
  while(true)
  {
    int x=rand()%10+1;
    int y=rand()%100+1;
    pthread_mutex_lock(&lock);
    Task t(x,y);
    bq->Put(t);
    pthread_mutex_unlock(&lock);
    cout<<"productor "<<x<<"+"<<y<<"=?"<<endl;
  }
  //pthread_mutex_unlock(&lock);
}

int main()
{
  BlockQueue *bq = new BlockQueue(5);
  pthread_t con1,pro1;
  pthread_create(&con1,nullptr,consumer_run,(void*)bq);
  pthread_create(&pro1,nullptr,productor_run,(void*)bq);
  //pthread_create(&con2,nullptr,consumer_run,(void*)bq);
  //pthread_create(&pro2,nullptr,productor_run,(void*)bq);
  pthread_join(con1,nullptr);
  //pthread_join(con2,nullptr);
  pthread_join(pro1,nullptr);
  //pthread_join(pro2,nullptr);
  return 0;
}