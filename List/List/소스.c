#include <stdio.h>
#include <malloc.h>

#define MAX_POLYS 100

typedef struct term
{
	int coef;												//���
	int expo;												//����
	struct term* next;
}Term;

typedef struct polynomial
{
	char name;												//���׽��� �̸� f, g, h ��
	Term* first;											//���׽��� �����ϴ� ù��° ���� �ּ�
	int size;												//���� ����
} Polynomial;

Polynomial* polys[MAX_POLYS];
int n = 0;													//����� ���׽��� ����

Term* create_term_instance()								//�ʱ�ȭ ���ִ� �Լ�
{
	Term* t = (Term*)malloc(sizeof(Term));					//Term ��ü ���� �� �ʱ�ȭ. �ʱ�ȭ �� ������ϴµ� �Ź� �ϱ� �������� �Լ� ����
	t->coef = 0;
	t->expo = 0;
	return t;												//�ּ� ����
}

Polynomial* create_polynomial_instance(char name)			//���� ��ü �ʱ�ȭ���ִ� �Լ�. name�� ���׽��� �̸�
{
	Polynomial* ptr_poly = (Polynomial*)malloc(sizeof(Polynomial));
	ptr_poly->name = name;
	ptr_poly->size = 0;
	ptr_poly->first = NULL;
	return ptr_poly;
}

void add_term(int c, int e, Polynomial* poly)				//cx^e
{
	if(c == 0) return;

	Term* p = poly->first, * q = NULL;						//p, q �����ϴµ�, p�� ù�κп��� ����. q�� �� ��
	while (p != NULL && p->expo > e)						//p�� ������ ���� ������ �������� ũ�� �ڷ�(���� ���� ��������) �̵�
	{
		q = p;
		p = p->next;
	}
	if (p != NULL && p->expo == e)							//���� ������ ������ �����ϸ�
		p->coef += c;										//����� c ���ϱ�

	if (p->coef == 0)										//��� ���ߴµ� 0�̸�
	{
		if (q == NULL)										//q == NULL �� p�� ù��° ���� ���
			poly->first = p->next;							//ù��° ��� ����(= ù��°�� �ڸ��� p ������ �ּҰ� �Է� �� p�� ù��°�� ��)
		else
			q->next = p->next;								//p �ǳʶٱ�
		poly->size--;
		free(p);											//p�� ���� ���������� �޸� �Ҵ� ���� 
	}
	
	Term* term = create_term_instance();
	term->coef = c;
	term->expo = e;

	if (q == NULL)
	{
		term->next = poly->first;
		poly->first = term;
	}
	else
	{
		term->next = p;
		q->next = term;
	}
	poly->size++;
}

int main(void)
{
	
	
}