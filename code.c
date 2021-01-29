include<stdio.h>

int sum(int number)
{
  int rt=0;
  for(int i=0;i<number;i++){
      rt += i;
  }
  return rt;
}

int main()
{
  int result=sum(100);
  printf("%d\n ",result);
  return 0;
}
