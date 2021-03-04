#include <iostream>
using namespace std;

class Solution {
public:
    int addDigits(int num=0);

private:
    int num;
};

int Solution::addDigits(int num) {
    int sum = num;//�Ƚ���ʼֵ�������sum

    while (sum > 9)//����9����м��㣬��������ֱ�ӷ��س�ʼֵsum
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