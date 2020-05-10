#pragma once
#include<string>
#define N 64

class MD5
{
public:
	MD5();
	//�����ļ�
	std::string getFileMd5(const char* filename);
	//�����ַ���
	std::string getStringMd5(const std::string& str);
private:
	void Init();//��ʼ������
	//�����64�β�����ÿ��������4���ֽڣ�32λ��Ϊ��λ����ģ�����Ҫ��size_t
	void calculateMD5(size_t* chunk);
	void calculateMD5Final();
	std::string changeHex(size_t num);
	//������Ĭ��չ��Ϊ����������
	size_t F(size_t x, size_t y, size_t z)
	{
		return (x & y) | ((~x) & z);
	}
	size_t G(size_t x, size_t y, size_t z)
	{
		return (x&z) | (y&(~z));
	}
	size_t H(size_t x, size_t y, size_t z)
	{
		return x^y^z;
	}
	size_t I(size_t x, size_t y, size_t z)
	{
		return y ^ (x | (~z));
	}
	size_t shiftLeftRotate(size_t num, size_t n)
	{
		return (num << n) | (num >> (32 - n));
	}
	size_t _a;
	size_t _b;
	size_t _c;
	size_t _d;

	size_t _k[N];
	size_t _sft[N];

	const size_t _chunkByte;
	unsigned char _chunk[N];

	size_t _lastByte;
	unsigned long long _totalByte;
};