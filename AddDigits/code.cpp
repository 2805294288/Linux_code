#include <iostream>
using namespace std;

class Solution {
public:
    int addDigits(int num=0);

private:
    int num;
};

int Solution::addDigits(int num) {
    int sum = num;//先将初始值赋予变量sum

    while (sum > 9)//大于9则进行计算，不大于则直接返回初始值sum
    {
        num = sum;
        sum = 0;
        while (num)
        {
            sum += num % 10;
            num = num / 10;
        }
    }
    return sum;
}

int main()
{
    Solution solution;
    int num = 0;
    cout << "Please enter number: ";
    cin >> num;
    int number=solution.addDigits(num);
    cout << number;
    return 0;
}