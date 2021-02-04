#include<iostream>
using namespace std;
//求三位数字的水仙花数。
int main()
{
int number = 100;
do {
  int a = 0;
  int b = 0;
  int c = 0;
  int sum = 0;
  a = number % 10;
  b = number / 10 % 10;
  c = number / 100;
  sum = a * a * a + b * b * b + c * c * c;
  if (sum== number) {
    cout << sum<< endl;
  }
  number++;
}while (number < 1000);
}

