#include <stdio.h>
#include <malloc.h>

#define MAX_POLYS 100

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

int main(void)
{
	
	
}