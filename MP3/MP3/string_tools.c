#include "string_tools.h"

int read_line(FILE*fp, char str[], int n)						//n : �迭�� ũ��
{
	int ch;
	int i = 0;

	while ((ch=fgetc(fp)) != '\n' && ch != EOF)								//�� ������ ���̳� ������ ���� �����ϸ� while �� ��������
		if (i < n - 1)
			str[i++] = ch;
	str[i] = '\0';
	return i;													//������ ����ڸ� �о������� ���ϵ�
}