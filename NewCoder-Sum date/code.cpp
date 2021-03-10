#include<iostream>
using namespace std;

void leap(int year,int *month)
{
    if((year%4==0&&year%100!=0)||year%400==0)
        {
            month[2]=29;
        }
    else
        month[2]=28;
}

int main()
{
    int m=0;
    int year=0;
    int month=1;
    int day=1;
    int number=0;
    int months[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    cin>>m;
    while(m--)
    {
        cin>>year>>month>>day>>number;
        leap(year,months);
         number=number-(months[month]-day);
        if(number>0){
            month++;
                while(number>months[month])
                {
                    number -= months[month];
                    month++;
                    if(month>12)
                    {
                        year++;
                        month=1;
                        leap(year,months);
                    }
                }
            day=number;
        }
        else
        day=number+months[month];
       printf("%d-%02d-%02d\n", year, month, day);
     }
}



