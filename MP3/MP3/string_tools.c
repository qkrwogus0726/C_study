#include "string_tools.h"

int read_line(FILE*fp, char str[], int n)						//n : 배열의 크기
{
	int ch;
	int i = 0;

	while ((ch=fgetc(fp)) != '\n' && ch != EOF)								//한 라인의 끝이나 파일의 끝에 도달하면 while 문 빠져나옴
		if (i < n - 1)
			str[i++] = ch;
	str[i] = '\0';
	return i;													//실제로 몇글자를 읽었는지가 리턴됨
}