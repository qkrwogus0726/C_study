#include <stdio.h>
#include <malloc.h>

struct node
{
	char* data;												//데이터 필드
	struct node* next;										//링크 필드 = 자기참조형 구조체
};

typedef struct node Node;
Node* head = NULL;											//연결리스트의 첫번째 노드의 주소를 저장할 포인터를 보통 head, first 등으로 씀.

void add_first(Node** ptr_head, char* item)					//add_first(&head, item_to_store) head의 주소를 받아야 외부에서 head 값을 바꿀 수 있다.
{
	Node* temp = (Node*)malloc(sizeof(Node));				//104
	temp->data = item;
	temp->next = *ptr_head;									//지금 head의 주소를 가리킴(next -> 100)
	*ptr_head = temp;										//head의 주소를 104로 바꿈
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

Node* remove_after(Node* prev)								//인자로 받은 prev의 다음 노드를 삭제하는 함수
{
	Node* tmp = prev->next;									//tmp에 이전노드의 다음 주소를 저장
	if (tmp == NULL)
	{
		return NULL;
	}
	else
	{
		prev->next = tmp->next;								 //prev의 next에 한 칸 건너뛰고 다다음칸의 주소 지정
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

Node* findd(char *word)										//검색할 단어를 받음
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

Node* get_node(int index)									//연결리스트에서 index번째 노드를 찾아서 리턴해주는 함수
{
	Node* p = (Node*)malloc(sizeof(Node));
	if (index < 0) return NULL;
	for (int i = 0; i < index && p != NULL; i++)
	{
		p = p->next;
	}
	return p;
}

int add(int index, char* item)								//index번째에 새로운 노드 만들어서 삽입
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
	}														//prev 구하면 → prev의 next값을 받은 이후 prev의 next를 그 다음으로 옮기기
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
	if (q == NULL)											//삭제해야 할 노드가 첫번째 노드인 경우
		return remove_first();
	else return
		remove_after(q);
}

void add_to_ordered_list(char* item)
{
	Node* p = head;
	Node* q = NULL;

	while (p != NULL && strcmp(p->data, item)==0) //order 대로 안 돼있는데 강의에서는 그냥 된거라 가정하고 넘어감
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

	Node* head = (Node*)malloc(sizeof(Node));				//head에 100 저장되어있음
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
	tmp->next = head;										//tmp next가 100번을 가리킴
	head = tmp;												//head가 103번을 가리키도록 바꿈

	add_after(tmp, "Hello");
															//head에 저장된 값을 p에 써라 → p도 첫번째 노드를 가리킴

	findd(&word, head);




	while (head != NULL)
	{
		printf("%s\n", head->data);
		head = head->next;
	}
	return 0;
}