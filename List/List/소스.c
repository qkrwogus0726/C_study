#include <stdio.h>
#include <malloc.h>

struct node
{
	char* data; //데이터 필드
	struct node* next; //링크 필드 = 자기참조형 구조체
};

typedef struct node Node;
Node* head = NULL; //연결리스트의 첫번째 노드의 주소를 저장할 포인터를 보통 head, first 등으로 씀.

int main(void)
{
	Node* head = (Node*)malloc(sizeof(Node));
	head->data = "Monday";
	head->next = NULL;

	Node* q = (Node*)malloc(sizeof(Node));
	q->data = "Tuesday";
	q->next = NULL;
	head->next = q;

	q = (Node*)malloc(sizeof(Node));
	q->data = "Monday";
	q->next = head;
	head = q;

	Node* p = head; //head에 저장된 값을 p에 써라 → p도 첫번째 노드를 가리킴
	while (p != NULL)
	{
		printf("%s\n", p->data); 
		p = p->next; //Monday → Tuesday로 넘어가게 하는 문장
	}
}