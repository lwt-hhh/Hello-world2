#include<iostream>
#include "md5.h"
#include<stdlib.h>

void   menu()
{
	printf("#####################################################\n");
	printf("#####################################################\n");
	printf("################测文件    请输入：1    ##############\n");
	printf("################测字符串  请输入：2    ##############\n");
	printf("#####################################################\n");
	printf("#####################################################\n");
}

int main(int argc, char* argv[])
{
	menu();
	MD5 md5;
	printf("请输入：");
	if (argc != 3)
	{
		std::cout << argv[0] << "请正确输入" << std::endl;
		return 0;
	}
	/*int input;
	std::cin >> input >> std::endl;*/
	switch (*argv[1])
	{
	case '1':
		std::cout << md5.getFileMd5(argv[2]) << std::endl;
		break;
	case '2':
		std::cout << md5.getStringMd5(argv[2]) << std::endl;
		break;
	default:
		printf("输入有误！");
		break;
	}
	system("pause");
	return 0;
}
