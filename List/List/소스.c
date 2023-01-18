#include <stdio.h>
#include <malloc.h>

#define MAX_POLYS 100
#define BUFFER_LENGTH 100

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

int eval(Polynomial* poly, int x)							//���׽��� ���� ����ϴ� �Լ�
{
	int result = 0;
	Term* t = poly->first;									//���׽� poly�� ù��° �� : t
	while (t != NULL)
	{
		result += eval(t, x);								//������ ���� ���� ����Ͽ� ���Ѵ�
		t = t->next;
	}
	return result;
}

int eval(Term* term, int x)									//�ϳ��� ���� ���� ����ϴ� �Լ�
{
	int result = term->coef;
	for (int i = 0; i < term->expo; i++)					//result�� x�� ���ϴ� ���� e�� ����
	{
		result *= x;
	}
	return result;
}

void print_poly(Polynomial* p)
{
	printf("%c=", p->name);
	Term* t = p->first;
	while (t != NULL)
	{
		print_term(t);
		printf("+");
		t = t->next;
	}
}

void print_term(Term* pTerm)
{
	printf("%dx^%d", pTerm->coef, pTerm->expo);				//�����ؾ� ��.
}

void process_command()
{
	char command_line[BUFFER_LENGTH];
	char copied[BUFFER_LENGTH];
	char* command, * arg1, * arg2;

	while (1)
	{
		printf("$ ");
		if (read_line(stdin, command_line, BUFFER_LENGTH) <= 0)
			continue;
		strcpy(copied, command_line);
		command = strtok(command_line, " ");
		if (strcmp(command, "print") == 0)
		{
			arg1 = strtok(NULL, " ");
			if (arg1 == NULL)
			{
				printf("Invalid arguments.\n");
				continue;
			}
			handle_print(arg1[0]);							//char Ÿ������ �Ű����� �ѱ�
		}
		else if (strcmp(command, "calc") == 0)				//calc�� calc f 1 �̷��� �Ǿ��ֱ� ������ ��ū 2�� ����� ��.
		{
			arg1 = strtok(NULL, " ");
			if (arg1 == NULL)
			{
				printf("Invalid arguments.\n");
				continue;
			}
			arg2 = strtok(NULL, " ");
			if (arg2 == NULL)
			{
				printf("Invalid arguments.\n");
				continue;
			}
			handle_calc(arg1[0], arg2);						//ù��° �Ű������� �Լ� �̸�, �ι�°�� x ��
		}
		else if (strcmp(command, "exit") == 0)
			break;
		else
			handle_definition(copied);						//���׽��� �Է¹޾� �����ϴ� �Լ�
	}
}

void handle_print(char name) //12-2�� 10:00
{

}

void handle_calc(char name, char* x_str)
{

}

void erase_blanks(char* expression)
{

}

void handle_definition(char* expression)
{
	erase_blanks(expression);

	char* f_name = strtok(expression, "=");
	if (f_name == NULL || strlen(f_name) != 1)
	{
		printf("Unsupported command.");
		return;
	}
	char* exp_body = strtok(NULL, "=");
	if (exp_body == NULL || strlen(exp_body) <= 0)
	{
		printf("Invalid expression format.--");
		return;
	}
	if (exp_body[0] >= 'a' && exp_body[0] <= 'z' && exp_body[0] != 'x')
	{
		char* former = strtok(exp_body, "+");
		if (former == NULL || strlen(former) != 1)
		{
			printf("Invalid expression format.");
			return;
		}
		char* later = strtok(NULL, "+");
		if (later == NULL || strlen(later) != 1)
		{
			printf("Invalid expression format.\n");
			return;
		}
		Polynomial* pol = create_by_add_two_polynomials(f_name[0], former[0], later[0]);
		if (pol == NULL)
		{
			printf("Invalid expression format.");
			return;
		}
		insert_polynomial(pol);
	}
	else
	{
		Polynomial* pol = create_by_parse_polynomial(f_name[0], exp_body);
		if (pol == NULL)
		{
			printf("Invalid expression format.");
			return;
		}
		insert_polynomial(pol);
	}
}

Polynomial* create_by_parse_polynomial(char name, char* body)		//body�� ���� ���׽Ŀ� �ش��ϴ� �κ�
{
	Polynomial* ptr_poly = create_polynomial_instance(name);
	int i = 0, begin_term = 0;
	while (i < strlen(body) && body[i] != '+' && body[i] != '-')
	{
		i++;
		int result = parse_and_add_term(body, begin_term, i, ptr_poly);
		if (result == 0)
		{
			destroy_polynomial(ptr_poly);
			return NULL;
		}
		begin_term = i;
	}
	return ptr_poly;
}

Term* parse_and_add_term(char* expr, int begin, int end, Polynomial* p_poly)	//expr : ���ڿ�, begin : ������ġ, end : ����ġ �ٷ� ����
{
	int i = begin;
	int sign_coef = 1, coef = 0, expo = 1;										//sign_coef : ����� ��ȣ
	if (expr[i] == '+')
		i++;
	else if (expr[i] == '-')
	{
		sign_coef = -1;
		i++;
	}
	while (i < end && expr[i] >= '0' && expr[i] <= '9')
	{
		coef = coef * 10 + (int)(expr[i] - '0');
		i++;
	}
	if (coef == 0)
		coef = sign_coef;
	else
		coef *= sign_coef;

	if (i >= end)
	{
		add_term(coef, 0, p_poly);
		return 1;
	}
	if (expr[i] != 'x')
		return 0;
	i++;
	if (i >= end)
	{
		add_term(coef, 1, p_poly);
		return 1;
	}
	if (expr[i] != '^')
		return 0;
	i++;

	expo = 0;
	while (i < end && expr[i] >= '0' && expr[i] <= '9')
	{
		expo = expo * 10 + (int)(expr[i] - '0');
		i++;
	}
	add_term(coef, expo, p_poly);
	return 1;
}

void insert_polynomial(Polynomial* ptr_poly)									//���ο� ���׽�  �߰�
{
	for (int i = 0; i < n; i++)
	{
		if (polys[i]->name == ptr_poly->name)
		{
			destroy(polys[i]);													//���׽��� ��� ��쿡�� ������ ���׽� ��ü�� free������� ��.
			polys[i] = ptr_poly;
			return;
		}
	}
	polys[n++] = ptr_poly;
}

void destroy_polynomial(Polynomial* ptr_poly)
{
	if (ptr_poly == NULL)
		return;
	Term* t = ptr_poly->first, * tmp;
	while (t != NULL)
	{
		tmp = t;
		t = t->next;
		free(tmp);
	}
	free(ptr_poly);
}

Polynomial* create_by_add_two_polynomials(char name, char f, char g)
{

}

int main(void)
{
	
	
}