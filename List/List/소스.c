#include <stdio.h>
#include <malloc.h>

struct node
{
	char* data;												//������ �ʵ�
	struct node* next;										//��ũ �ʵ� = �ڱ������� ����ü
};

typedef struct node Node;
Node* head = NULL;											//���Ḯ��Ʈ�� ù��° ����� �ּҸ� ������ �����͸� ���� head, first ������ ��.

void add_first(Node** ptr_head, char* item)					//add_first(&head, item_to_store) head�� �ּҸ� �޾ƾ� �ܺο��� head ���� �ٲ� �� �ִ�.
{
	Node* temp = (Node*)malloc(sizeof(Node));				//104
	temp->data = item;
	temp->next = *ptr_head;									//���� head�� �ּҸ� ����Ŵ(next -> 100)
	*ptr_head = temp;										//head�� �ּҸ� 104�� �ٲ�
}

void add_after(Node* prev, char* item)
{
	if (prev == NULL)
		return 0;

	Node* tmp = (Node*)malloc(sizeof(Node));
	tmp->data = item;
	tmp->next = prev->next;
	prev->next = tmp;
}

Node* remove_after(Node* prev)								//���ڷ� ���� prev�� ���� ��带 �����ϴ� �Լ�
{
	Node* tmp = prev->next;									//tmp�� ��������� ���� �ּҸ� ����
	if (tmp == NULL)
	{
		return NULL;
	}
	else
	{
		prev->next = tmp->next;								 //prev�� next�� �� ĭ �ǳʶٰ� �ٴ���ĭ�� �ּ� ����
		return tmp;
	}
}

Node* remove_first()
{
	if (head == NULL)
		return NULL;
	else
	{
		Node* tmp = head;
		head = head->next;
		return tmp;
	}
}

Node* findd(char *word)										//�˻��� �ܾ ����
{
	Node* p = head;
	while (p != NULL)
	{
		if (strcmp(p->data, word) == 0)
			return p;
		p = p->next;
	}
	return NULL;
}

Node* get_node(int index)									//���Ḯ��Ʈ���� index��° ��带 ã�Ƽ� �������ִ� �Լ�
{
	Node* p = (Node*)malloc(sizeof(Node));
	if (index < 0) return NULL;
	for (int i = 0; i < index && p != NULL; i++)
	{
		p = p->next;
	}
	return p;
}

int add(int index, char* item)								//index��°�� ���ο� ��� ���� ����
{
	Node* prev = (Node*)malloc(sizeof(Node));
	Node* p = (Node*)malloc(sizeof(Node));

	if (index < 0) return NULL;

	for (int i = 0; i < index-1 && prev != NULL; i++)
	{
		prev = prev->next;
	} 
	
	p->data = "anything";
	p->next = prev->next;
	prev->next = p;
}

int remove(int index)
{
	Node* prev = (Node*)malloc(sizeof(Node));
	Node* p = (Node*)malloc(sizeof(Node));

	if (index < 0) return NULL;

	for (int i = 0; i < index - 1 && prev != NULL; i++)
	{
		prev = prev->next;
	}														//prev ���ϸ� �� prev�� next���� ���� ���� prev�� next�� �� �������� �ű��
	p = prev->next;
	prev->next = p->next;
}

Node* remove_item(char* item)
{
	Node* p = head;
	Node* q = NULL;
	while (p != NULL && strcmp(p->data, item) == 0)
	{
		q = p;
		p = p->next;
	}
	if (p == NULL)
		return NULL;
	if (q == NULL)											//�����ؾ� �� ��尡 ù��° ����� ���
		return remove_first();
	else return
		remove_after(q);
}

void add_to_ordered_list(char* item)
{
	Node* p = head;
	Node* q = NULL;

	while (p != NULL && strcmp(p->data, item)==0) //order ��� �� ���ִµ� ���ǿ����� �׳� �ȰŶ� �����ϰ� �Ѿ
	{
		q = p;
		p = p->data;
	}
	if (q == NULL)
		add_first(p, item);
	else
		add_after(p, q);
}

int main(void)
{
	char word = "Hello";
	char *ptr;
	ptr = word;

	Node* head = (Node*)malloc(sizeof(Node));				//head�� 100 ����Ǿ�����
	head->data = "tom";
	head->next = NULL;

	Node* p = (Node*)malloc(sizeof(Node));					//101
	p->data = "dick";
	head->next = p;
	
	Node*q = (Node*)malloc(sizeof(Node));					//102
	q->data = "harry";
	p->next = q;

	Node*tmp = (Node*)malloc(sizeof(Node));					//103
	tmp->data = "Ann";
	tmp->next = head;										//tmp next�� 100���� ����Ŵ
	head = tmp;												//head�� 103���� ����Ű���� �ٲ�

	add_after(tmp, "Hello");
															//head�� ����� ���� p�� ��� �� p�� ù��° ��带 ����Ŵ

	findd(&word, head);




	while (head != NULL)
	{
		printf("%s\n", head->data);
		head = head->next;
	}
	return 0;
}