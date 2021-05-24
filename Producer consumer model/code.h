#ifndef __QUEUE_BLOCK_H__
#define __QUEUE_BLOCK_H__
#include<unistd.h>
#include<iostream>
#include<pthread.h>
#include<queue>
using namespace std;
class Task
{
public:
  int x;
  int y;
public:
  Task(int _x,int _y):x(_x),y(_y)
  {}
  Task()
  {}
  int Run()
  {
    return x+y;
  }
  ~Task()
  {}
};
class BlockQueue
{
private:
  queue<Task> q;
  size_t cap;
  pthread_mutex_t lock;
  pthread_cond_t c_cond;
  pthread_cond_t p_cond;
public:
  //判满
  bool IsFull()
  {
    return q.size()>=cap;
  }
  //判空
  bool IsEmpty()
  {
    return q.empty();
  }
  //解锁
  void UnlockQueue()
  {
    pthread_mutex_unlock(&lock);
  }
  //唤醒消费者
  void WakeUpConsumer()
  {
    cout<<"WakeUpConsumer"<<endl;
    pthread_cond_signal(&c_cond);
  }
  //唤醒生产者
  void WakeUpProductor()
  {
    cout<<"WakeUpProductor"<<endl;
    pthread_cond_signal(&p_cond);
  }
  //pthread_cond_wait传入lock参数：
  //在条件满足时，消费者or生产者持有锁进入临界区执行，当判断条件不满足时，调用对应的wait函数
  //在消费者or生产者等待时，调用对应的Wait函数，自动释放lock
  //消费者等待，必须解锁，让另一个角色持有锁，以保证线程之间友好，在
  void ConsumerWait()
  {
    cout<<"ConsumerWait"<<endl;
    pthread_cond_wait(&c_cond,&lock);
  }
  //生产者等待
  void ProductWait()
  {
    cout<<"ProductWait"<<endl;
    pthread_cond_wait(&p_cond,&lock);
  }
public:
    BlockQueue(int _cap):cap(_cap)
    {
      pthread_mutex_init(&lock,nullptr);
      pthread_cond_init(&c_cond,nullptr);
      pthread_cond_init(&p_cond,nullptr);
    }
    ~BlockQueue()
    {
      pthread_mutex_destroy(&lock);
      pthread_cond_destroy(&p_cond);
      pthread_cond_destroy(&c_cond);
    }
    //消费者消费，拿取or执行队列中的数据以及任务并执行
    void Put(Task in)
    {
      UnlockQueue();
      if(IsFull())
      {
        WakeUpConsumer();
        ProductWait();
      }
      q.push(in);
      UnlockQueue();
    }
    //生产者生产，向队列中塞数据或者任务
    void Get(Task &out)
    {
      UnlockQueue();
      if(IsEmpty())
      {
        WakeUpProductor();
        ConsumerWait();
      }
      out=q.front();
      q.pop();
      UnlockQueue();
    }
};
#endif
