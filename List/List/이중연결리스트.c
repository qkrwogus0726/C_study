#include <stdio.h>

typedef struct node {
	char* data;
	Node next;
	Node prev;
}Node;

Node* head;
Node* tail;
int size = 0;

void add_after(Node* pre, char* item)								//pre�� ����Ű�� ��� �ٷ� ������ ���ο� ��� ����
{
	Node* new_node = (Node*)malloc(sizeof(Node));
	new_node->data = item;
	new_node->prev = NULL;
	new_node->next = NULL;

	if (pre == NULL && head == NULL) {								//�ƹ� ��嵵 ���� ��
		head = new_node;
		tail = new_node;
	}
	
	else if (pre == NULL)											//�� �տ� ���Ե� ��
	{
		new_node->next = head;
		head->prev = new_node;
		head = new_node;
	}
	else if (pre == tail)											//�� �ڿ� ���Ե� ��
	{
		new_node->prev = tail;
		tail->next = new_node;
		tail = new_node;
	}
	else															//�� �� �Ϲ����� ���
	{
		new_node->next = pre->next;
		new_node->prev = pre;
		pre->next->prev = new_node;
		pre->next = new_node;
	}
	size++;
}

void add_ordered_list(char* item)
{
	Node* p = tail;
	while (p != NULL && strcmp(item, p->data) < 0)
		p = p->prev;
	add_after(p, item);
}

int main(void)
{
	Node* new_node = (Node*)malloc(sizeof(Node));
	Node* p = (Node*)malloc(sizeof(Node));
	Node* q = (Node*)malloc(sizeof(Node));

	new_node->data = "Sharon"; //p, q ���̿� new_node ����
	new_node->next = p;
	new_node->prev = p->prev;
	p->prev->next = new_node;
	p->prev = new_node;

	new_node->prev->next = new_node->next; //�߰��� ���� ��� ����
	new_node->next->prev = new_node->prev;


}