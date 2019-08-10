#include<vector>

using namespace std;

class bitset
{
public:
	bitset(size_t rang)
	{
		_bits.resize((rang >> 5) + 1);
	}
	//吧x对应的位设为1，表示存在
	void set(size_t x)
	{
		size_t index = x >> 5;  //相当于除以32  找到在数组中的位置，一个位置是一个整形  有32位
		size_t bitnum = x % 32;   //找到对应位置的哪一位
		_bits[index] |= (1 << bitnum);

	}
	//把x对应的位设为0  表示不存在
	void reset(size_t x)
	{
		size_t index = x >> 5;
		size_t bitnum = x % 32;
		_bits[index] &= (~(1 << bitnum));
	}

	//x对应的位是否为1
	bool test(size_t x)
	{
		size_t index = x >> 5;
		size_t bitnum = x % 32;
		return _bits[index] & (1 << bitnum);
	}
private:
	vector<int> _bits;
};


int main()
{

	return 0;
}