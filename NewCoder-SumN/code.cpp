class Sum
{
public:
    Sum()
    {
        _ret += _i;
        ++_i;
    }
    
    static int GetRot()
    {
        return _ret;
     }
    static void Init()
    {
        _ret=0;
        _i=1;
    }
private:
    static int _ret;
    static int _i;
};
int Sum::_i=1;
int Sum::_ret=0;


class Solution {
public:
    int Sum_Solution(int n) {
        
        Sum::Init();
        
        Sum arr[n];
        
        return Sum::GetRot();
    }
};