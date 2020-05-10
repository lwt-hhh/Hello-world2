#include<cstring>
#include<math.h>
#include<fstream>
#include "md5.h"


MD5::MD5()
:_chunkByte(N)
{
	Init();
	memset(_chunk, 0, _chunkByte);
	_totalByte = _lastByte = 0;
}
//��ʼ��
void MD5::Init()
{
	//��ʼ��_a,_b,_c,_d
	_a = 0x67452301;
	_b = 0xefcdab89;
	_c = 0x98badcfe;
	_d = 0x10325476;

	size_t s[] = { 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7,
		12, 17, 22, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
		4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 6, 10,
		15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21 };

	memcpy(_sft, s, sizeof(s));
	
	for (size_t i = 0; i < 64; i++)
	{
		_k[i] = pow(2.0, 32)*abs(sin(i + 1.0));
	}
}
//��һ��16��������  ת��Ϊ��Ӧ���ַ�����ʽ num=0x23456789 --->89 67 45 23
std::string MD5::changeHex(size_t num)
{
	static std::string strMap = "0123456789abcdef";
	std::string ret;
	std::string byteStr;
	for (size_t i = 0; i < 4; i++)
	{
		byteStr = "";
		size_t b = (num >> (i * 8)) & 0xff;
		for (size_t j = 0; j < 2; j++){
			byteStr.insert(0, 1, strMap[b % 16]);//ͷ��
			b /= 16;
		}
		ret += byteStr;
	}
	return ret;
}

//�����ַ����ĺ���
std::string MD5::getStringMd5(const std::string& str)
{
	if (str.empty())   //�յ��ַ����ͷ���һ���յ��ַ���
		return "";
	else   //���� ����ǿ�
	{
		unsigned char* pstr = (unsigned char*)str.c_str();   //��stringת��Ϊc����ַ���

		//��һ�� Ҫ�ֶ��ٸ�64�ֽڣ�512bit�� �Ŀ�
		size_t numChunk = str.size() / _chunkByte;
		for (size_t i = 0; i < numChunk; i++)
		{
			_totalByte += _chunkByte;//�������ݳ���
			calculateMD5((size_t *)pstr + i*_chunkByte);//����ÿһ������ݣ�ÿ��ȥ����64���ֽ�
		}
		_lastByte = str.size() % _chunkByte;//��һ����û�в���8�ֽ�
		memcpy(_chunk, pstr + _totalByte, _lastByte);//�Ƚ����ݿ�����
		_totalByte += _lastByte;
		calculateMD5Final();//Ȼ��������ݵ�ƴ��
		return changeHex(_a) + changeHex(_b) + changeHex(_c) + changeHex(_d);//����md5��ֵȻ�󷵻�
	}
}

	//����һ�������ĵ���MD5�Ĵ�С
	std::string MD5::getFileMd5(const char* filename)
	{
		std::ifstream fin(filename, std::ifstream::binary);//��2��������ȡ
		if (fin.is_open())//�ж��ļ��Ƿ��Ѿ���
		{
			//�ж�һ���ļ��Ƿ��Ѿ��ߵ����
			while (!fin.eof())
			{
				fin.read((char*)_chunk, _chunkByte);//���ն�����ȥ������ȡ64���ֽڣ��ŵ�_chunk��
				//�ж���������ǲ������һ�����ݣ����һ�ζ��˲���64���ֽڣ�������ѭ�����е�������
				if (_chunkByte != fin.gcount())
					break;
				_totalByte += _chunkByte;//�ļ�����64���ֽڣ������ۼ�
				calculateMD5((size_t*)_chunk);//���˵Ļ���������md5
			}
			_lastByte = fin.gcount();//���һ�ζ������ļ���
			_totalByte += _lastByte;//�ۼӵ�ǰ�ĵ����ֽ����������ĵ��Ĵ�С
			calculateMD5Final();
		}
		//������תΪһ��16���̵�MD5�ַ�����Ȼ�󷵻�abcd����һ��ƴ��
		return changeHex(_a) + changeHex(_b) + changeHex(_c) + changeHex(_d);
	}
	//����ǶԲ���64���ֽڵ�ģ�飬������䵽64�ֽ�Ȼ����б���
	void MD5::calculateMD5Final()
	{
		//�������8λ������һ�����ͽ������
		//_lastByte���һ���ֽ�λ:<64byte,�����ݽ���ƫ�Ƶ����һ�����ݵĴ�С��Ȼ���¼����
		unsigned char* p = _chunk + _lastByte;
		//���λ�İ˸�bitλ��1000 0000 ox80   
		*p++ = 0x80;
		//��������Ժ�ʣ�µĳ��ȣ��ܲ��������λ�Ĵ�С��-1��ʾ�ղ������һλ
		size_t remainFillByte = _chunkByte - _lastByte - 1;
		if (remainFillByte < 8)//���ʣ�µĳ��Ȳ���8���ֽ�
		{
			memset(p, 0, remainFillByte);//������8λ����ȫ�����Ϊ0
			calculateMD5((size_t*)_chunk);//�������Ѿ���64�ֽڴ�С�Ľ���һ������
			memset(_chunk, 0, _chunkByte);//�ڽ��п���һ����512��С�����ݿ齫���ȫ�����Ϊ0
		}
		else//������ڵ���8λ���ȣ�Ȼ��ȫ�����Ϊ0
		{
			memset(p, 0, remainFillByte);
		}
		//����64bit8���ֽڴ��ԭʼ�ĵ���λ���ȣ�447~512λ
		((unsigned long long*)_chunk)[7] = _totalByte * 8;//�����䣬��ԭ�����Ϊ0�ģ���ԭʼ�ĵ����64λ���и���
		calculateMD5((size_t*)_chunk);//�����ڶ��乻64�ֽ�Ȼ����б������
	}
	//����Ƕ�64���ֽڵĽ��б���
	void MD5::calculateMD5(size_t* chunk)
	{
		//���ż�����ϣ����
		//�ڸ���ֵ�Ļ�������ȥ�����ֵ
		size_t a = _a;
		size_t b = _b;
		size_t c = _c;
		size_t d = _d;
		//f�ǹ�ϣ�����ķ���ֵ��chunk[g]
		size_t f;
		size_t g;
		//64�α仯��4�ֲ�����ÿһ�β�����16�Ӳ���
		for (size_t i = 0; i < 64; i++)
		{
			if (0 <= i&&i < 16){
				f = F(b, c, d);
				g = i;
			}
			else if (16 <= i&&i < 32){
				f = G(b, c, d);
				g = (5 * i + 1) % 16;
			}
			else if (32 <= i&&i < 48){
				f = H(b, c, d);
				g = (3 * i + 5) % 16;
			}
			else{
				f = I(b, c, d);
				g = (7 * i) % 16;
			}
			//���ĸ�ֵ�޸�64��
			size_t temp = d;
			d = c;
			c = b;
			b = b + shiftLeftRotate(a + f + _k[i] + chunk[g], _sft[i]);     //ֻ��b��������
			a = temp;    //a���ڸ���֮ǰ��	d
		}
		_a += a;       //ÿ�ν����ۼ�
		_b += b;
		_c += c;
		_d += d;        //Ȼ�����ĸ�ֵ�ڸ�һ������һ���µ�
	}