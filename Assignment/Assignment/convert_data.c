#include "convert_data.h"
#include <math.h>
#include <stdlib.h>


long convert_data(unsigned char a[], int start_bit, int len)
{
	long long L = 0;
	int index_num, remainder;
	long result = 0;
	unsigned char* b = malloc(sizeof(unsigned char));
	long long line = 0;

	index_num = ((start_bit + (len - 1)) / 8);
	remainder = start_bit / 8;

	//�� ���� ��Ʈ ��������
	for (int i = index_num; i >= remainder; i--)
	{ 
		line = line << 8;
		line += a[i];
	}

	//�� ���� ����Ʈ &������ �� �����
	for (int i = 0; i < len; i++)
	{
		L += pow(2, i);
	}

	//�� start bit�� ��ġ ����
	line = line >> start_bit % 8;
	result = line & L;


	return result;
}