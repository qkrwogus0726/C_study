#include <stdio.h>

typedef struct list
{
	char name;
	List* next;													//�̴ϼȿ� ���� �з��ؼ� �ܹ��� ���Ḯ��Ʈ�� ����� ����
	List* head;
	List* tail
}List;