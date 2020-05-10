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
//初始化
void MD5::Init()
{
	//初始化_a,_b,_c,_d
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
//将一个16进制数字  转换为相应的字符串形式 num=0x23456789 --->89 67 45 23
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
			byteStr.insert(0, 1, strMap[b % 16]);//头插
			b /= 16;
		}
		ret += byteStr;
	}
	return ret;
}

//处理字符串的函数
std::string MD5::getStringMd5(const std::string& str)
{
	if (str.empty())   //空的字符串就返回一个空的字符串
		return "";
	else   //否则 处理非空
	{
		unsigned char* pstr = (unsigned char*)str.c_str();   //将string转换为c风格字符串

		//算一下 要分多少个64字节（512bit） 的块
		size_t numChunk = str.size() / _chunkByte;
		for (size_t i = 0; i < numChunk; i++)
		{
			_totalByte += _chunkByte;//计算数据长度
			calculateMD5((size_t *)pstr + i*_chunkByte);//处理每一块的数据，每次去处理64个字节
		}
		_lastByte = str.size() % _chunkByte;//看一下有没有不够8字节
		memcpy(_chunk, pstr + _totalByte, _lastByte);//先将数据拷过来
		_totalByte += _lastByte;
		calculateMD5Final();//然后进行数据的拼接
		return changeHex(_a) + changeHex(_b) + changeHex(_c) + changeHex(_d);//计算md5的值然后返回
	}
}

	//计算一个整个文档的MD5的大小
	std::string MD5::getFileMd5(const char* filename)
	{
		std::ifstream fin(filename, std::ifstream::binary);//将2进制流读取
		if (fin.is_open())//判断文件是否已经打开
		{
			//判断一下文件是否已经走到最后
			while (!fin.eof())
			{
				fin.read((char*)_chunk, _chunkByte);//按照二进程去读，读取64个字节，放到_chunk中
				//判断这个数据是不是最后一块数据，最近一次读了不够64个字节，则跳出循环进行单独处理
				if (_chunkByte != fin.gcount())
					break;
				_totalByte += _chunkByte;//文件数够64个字节，进行累加
				calculateMD5((size_t*)_chunk);//够了的话计算它的md5
			}
			_lastByte = fin.gcount();//最后一次读到的文件数
			_totalByte += _lastByte;//累加当前文档的字节数，整个文档的大小
			calculateMD5Final();
		}
		//把整形转为一个16进程的MD5字符串，然后返回abcd进行一个拼接
		return changeHex(_a) + changeHex(_b) + changeHex(_c) + changeHex(_d);
	}
	//这个是对不足64个字节的模块，进行填充到64字节然后进行编码
	void MD5::calculateMD5Final()
	{
		//至少填充8位，所以一进来就进行填充
		//_lastByte最后一个字节位:<64byte,将数据进行偏移到最后一块数据的大小，然后记录下来
		unsigned char* p = _chunk + _lastByte;
		//填充位的八个bit位：1000 0000 ox80   
		*p++ = 0x80;
		//计算填充以后剩下的长度，能不能在填充位的大小，-1表示刚才填充了一位
		size_t remainFillByte = _chunkByte - _lastByte - 1;
		if (remainFillByte < 8)//如果剩下的长度不够8个字节
		{
			memset(p, 0, remainFillByte);//将不够8位进行全部填充为0
			calculateMD5((size_t*)_chunk);//这里对填补已经够64字节大小的进行一个编码
			memset(_chunk, 0, _chunkByte);//在进行开辟一个新512大小的数据块将这个全部填充为0
		}
		else//如果大于等于8位长度，然后全部填充为0
		{
			memset(p, 0, remainFillByte);
		}
		//最后的64bit8个字节存放原始文档的位长度：447~512位
		((unsigned long long*)_chunk)[7] = _totalByte * 8;//这个填充，将原来最后为0的，用原始文档最后64位进行覆盖
		calculateMD5((size_t*)_chunk);//这里在对其够64字节然后进行编码操作
	}
	//这个是对64个字节的进行编码
	void MD5::calculateMD5(size_t* chunk)
	{
		//走着几个哈希函数
		//在更新值的基础上再去变这个值
		size_t a = _a;
		size_t b = _b;
		size_t c = _c;
		size_t d = _d;
		//f是哈希函数的返回值，chunk[g]
		size_t f;
		size_t g;
		//64次变化，4轮操作，每一次操作：16子操作
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
			//这四个值修改64次
			size_t temp = d;
			d = c;
			c = b;
			b = b + shiftLeftRotate(a + f + _k[i] + chunk[g], _sft[i]);     //只有b参与运算
			a = temp;    //a等于更新之前的	d
		}
		_a += a;       //每次进行累加
		_b += b;
		_c += c;
		_d += d;        //然后将这四个值在给一个赋给一个新的
	}