#include<iostream>
#include<string>

using namespace std;

int main()
{
  string name[3]={"张三","李四","王五"};

  int Achievement[3][3]=
  {
    {100,98,87},
    {89,86,99},
    {95,89,88}
  };

  int sum=0;
  for(int i=0;i<3;i++){
    sum=0;
    for(int j=0;j<3;j++){
      sum += Achievement[i][j];
    }
    cout<<name[i]<<"的总成绩为："<<sum<<endl;
  }
  return 0;
}
