#include <stdio.h>

typedef struct list
{
	char name;
	List* next;													//이니셜에 따라 분류해서 단방향 연결리스트로 만들기 위함
	List* head;
	List* tail
}List;