#include <stdio.h>
#include <malloc.h>

struct node
{
	char* data; //������ �ʵ�
	struct node* next; //��ũ �ʵ� = �ڱ������� ����ü
};

typedef struct node Node;
Node* head = NULL; //���Ḯ��Ʈ�� ù��° ����� �ּҸ� ������ �����͸� ���� head, first ������ ��.

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

	Node* p = head; //head�� ����� ���� p�� ��� �� p�� ù��° ��带 ����Ŵ
	while (p != NULL)
	{
		printf("%s\n", p->data); 
		p = p->next; //Monday �� Tuesday�� �Ѿ�� �ϴ� ����
	}
}