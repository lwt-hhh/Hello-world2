#include<iostream>
#include "md5.h"
#include<stdlib.h>

void   menu()
{
	printf("#####################################################\n");
	printf("#####################################################\n");
	printf("################���ļ�    �����룺1    ##############\n");
	printf("################���ַ���  �����룺2    ##############\n");
	printf("#####################################################\n");
	printf("#####################################################\n");
}

int main(int argc, char* argv[])
{
	menu();
	MD5 md5;
	printf("�����룺");
	if (argc != 3)
	{
		std::cout << argv[0] << "����ȷ����" << std::endl;
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
		printf("��������");
		break;
	}
	system("pause");
	return 0;
}
