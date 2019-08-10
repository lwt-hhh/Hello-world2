#include<vector>

using namespace std;

class bitset
{
public:
	bitset(size_t rang)
	{
		_bits.resize((rang >> 5) + 1);
	}
	//��x��Ӧ��λ��Ϊ1����ʾ����
	void set(size_t x)
	{
		size_t index = x >> 5;  //�൱�ڳ���32  �ҵ��������е�λ�ã�һ��λ����һ������  ��32λ
		size_t bitnum = x % 32;   //�ҵ���Ӧλ�õ���һλ
		_bits[index] |= (1 << bitnum);

	}
	//��x��Ӧ��λ��Ϊ0  ��ʾ������
	void reset(size_t x)
	{
		size_t index = x >> 5;
		size_t bitnum = x % 32;
		_bits[index] &= (~(1 << bitnum));
	}

	//x��Ӧ��λ�Ƿ�Ϊ1
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