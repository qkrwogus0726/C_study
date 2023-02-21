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

	//① 읽을 비트 가져오기
	for (int i = index_num; i >= remainder; i--)
	{ 
		line = line << 8;
		line += a[i];
	}

	//② 읽은 바이트 &연산할 것 만들기
	for (int i = 0; i < len; i++)
	{
		L += pow(2, i);
	}

	//③ start bit로 위치 설정
	line = line >> start_bit % 8;
	result = line & L;


	return result;
}