#include <stdio.h>
#include <malloc.h>

#define MAX_POLYS 100
#define BUFFER_LENGTH 100

typedef struct term
{
	int coef;												//계수
	int expo;												//지수
	struct term* next;
}Term;

typedef struct polynomial
{
	char name;												//다항식의 이름 f, g, h 등
	Term* first;											//다항식을 구성하는 첫번째 항의 주소
	int size;												//항의 개수
} Polynomial;

Polynomial* polys[MAX_POLYS];
int n = 0;													//저장된 다항식의 개수

Term* create_term_instance()								//초기화 해주는 함수
{
	Term* t = (Term*)malloc(sizeof(Term));					//Term 객체 생성 후 초기화. 초기화 꼭 해줘야하는데 매번 하기 귀찮으니 함수 생성
	t->coef = 0;
	t->expo = 0;
	return t;												//주소 리턴
}

Polynomial* create_polynomial_instance(char name)			//생성 객체 초기화해주는 함수. name은 다항식의 이름
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

	Term* p = poly->first, * q = NULL;						//p, q 생산하는데, p는 첫부분에서 시작. q는 그 앞
	while (p != NULL && p->expo > e)						//p의 지수가 내가 지정한 지수보다 크면 뒤로(작은 지수 방향으로) 이동
	{
		q = p;
		p = p->next;
	}
	if (p != NULL && p->expo == e)							//내가 지정한 지수에 도착하면
		p->coef += c;										//계수에 c 더하기

	if (p->coef == 0)										//계수 더했는데 0이면
	{
		if (q == NULL)										//q == NULL → p가 첫번째 항일 경우
			poly->first = p->next;							//첫번째 노드 삭제(= 첫번째의 자리에 p 다음꺼 주소값 입력 → p가 첫번째가 됨)
		else
			q->next = p->next;								//p 건너뛰기
		poly->size--;
		free(p);											//p는 쓸모 없어졌으니 메모리 할당 해제 
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

int eval(Polynomial* poly, int x)							//다항식의 값을 계산하는 함수
{
	int result = 0;
	Term* t = poly->first;									//다항식 poly의 첫번째 항 : t
	while (t != NULL)
	{
		result += eval(t, x);								//각각의 항의 값을 계산하여 더한다
		t = t->next;
	}
	return result;
}

int eval(Term* term, int x)									//하나의 항의 값을 계산하는 함수
{
	int result = term->coef;
	for (int i = 0; i < term->expo; i++)					//result에 x를 곱하는 것을 e번 해줌
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
	printf("%dx^%d", pTerm->coef, pTerm->expo);				//개선해야 함.
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
			handle_print(arg1[0]);							//char 타입으로 매개변수 넘김
		}
		else if (strcmp(command, "calc") == 0)				//calc는 calc f 1 이렇게 되어있기 때문에 토큰 2번 해줘야 함.
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
			handle_calc(arg1[0], arg2);						//첫번째 매개변수는 함수 이름, 두번째는 x 값
		}
		else if (strcmp(command, "exit") == 0)
			break;
		else
			handle_definition(copied);						//다항식을 입력받아 정의하는 함수
	}
}

void handle_print(char name) //12-2강 10:00
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

Polynomial* create_by_parse_polynomial(char name, char* body)		//body가 실제 다항식에 해당하는 부분
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

Term* parse_and_add_term(char* expr, int begin, int end, Polynomial* p_poly)	//expr : 문자열, begin : 시작위치, end : 끝위치 바로 다음
{
	int i = begin;
	int sign_coef = 1, coef = 0, expo = 1;										//sign_coef : 계수의 부호
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

void insert_polynomial(Polynomial* ptr_poly)									//새로운 다항식  추가
{
	for (int i = 0; i < n; i++)
	{
		if (polys[i]->name == ptr_poly->name)
		{
			destroy(polys[i]);													//다항식을 덮어쓸 경우에는 기존의 다항식 객체를 free시켜줘야 함.
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