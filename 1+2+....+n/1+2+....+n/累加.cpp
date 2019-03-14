
#include<iostream>
#include<windows.h>
using namespace std;
class Solution {
public:
	class sum
	{
	public:
		sum()
		{
			_sum += _i;
			++_i;
		}
	};
	int Sum_Solution(int n) {
		_sum = 0;
		_i = 1;
		sum arr[100];
		return _sum;
	}
private:
	static int _sum;
	static int _i;
};
int Solution::_sum = 0;
int Solution::_i = 1;

int main()
{
	Solution d;
	cout << d.Sum_Solution(100) << endl;
	system("pause");
	return 0;
}