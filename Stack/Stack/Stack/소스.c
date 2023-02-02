#include <stdio.h>
#include <stdlib.h>
#include "stackADT.h"
#define MAX_LENGTH 100

typedef struct node
{
	char* data;
	struct node* next;
}Node;

Node* top = NULL;
Stack operand_stack;													//피연산자들을 저장할 스택

static char OPERATORS[] = "+-*/()";
static int PRECEDENCE[] = { 1, 1, 2, 2, -1, -1 };

Stack operator_stack;

int top = -1;

void push(char *item)
{
	Node* p = (Node*)malloc(sizeof(Node));
	p->data = item;
	p->next = top;
	top = p;
}
char pop()
{
	if (is_empty())
		return NULL;
	char* result = top->data;
	top = top->next;
	return result;
}
char peek()
{
	if (is_empty())
		return NULL;
	return top->data;
}
int is_empty()
{
	return top == NULL;
}
int is_full()
{
	return top == MAX_LENGTH - 1;
}
void handle_exception(const char* err_msg)
{
	printf("%s\n", err_msg);
	exit(1);
}

char* convert(char* infix)
{
	operator_stack = create();

	char* postfix = (char*)malloc(strlen(infix) + 1);
	char* pos = postfix;

	char* token = strtok(infix, " ");

	while (token != NULL)
	{
		if (token[0] >= '0' && token[0] <= '9')							//token이 비연산자인 경우
		{
			sprintf(pos, "%s ", token);
			pos += (strlen(token) + 1);
		}
		else if (is_operator(token[0] > -1))							//연산자인 경우
		{
			pos = process_op(token[0], pos);
		}
		else
			handle_exception("Syntax Error : invalid character ecountered. line 77\n");
		token = strtok(NULL, " ");
	}

	while (!is_empty(operator_stack))
	{
		char op = (char)pop(operator_stack);
		if(op == '(')
			handle_exception("Unmatched parethesis. line 86\n");
		sprintf(pos, "%c ", op);
		pos += 2;
	}
	*pos = '\0';
	return postfix;
}

char* process_op(char op, char* pos)
{
	if (is_empty(operator_stack) || op == '(')										//operator_stack이 비어있을 떄
		push(operator_stack, op);
	else
	{
		char top_op = peek(operator_stack);
		if (precedence(op) > precedence(top_op))
			push(operator_stack, op);
		else
		{
			while (!is_empty(operator_stack) && precedence(op) <= precedence(top_op))
			{
				pop(operator_stack);
				if (top_op == '(')
					break;
				sprintf(pos, "%c ", top_op);
				pos += 2;
				if (!is_empty(operator_stack))
					top_op = (char)peek(operator_stack);
			}
			if(op != ')')
				push(operator_stack, op);
		}
	}
	return pos;
}

int precedence(char op)
{
	return PRECEDENCE[is_operator(op)];
}

int is_operator(char ch)												//ch가 연산자인지 검사하는 함수
{
	for (int i = 0; i < strlen(OPERATORS); i++)
	{
		if (OPERATORS[i] == ch)											//+이면 0, -이면 1, *이면 2, /이면 3 리턴
			return i;
		return -1;
	}
}

int eval(char* expr)													//후위표기식이 문자열의 형태로 주어졌을 때 계산하는 함수
{
	operand_stack = create();											//스택 생성 후 operand_stack에 주소 저장
	char* token = strtok(expr, " ");									//모든 연산자, 피연산자가 공백문자로 구분되어 있다고 가정
	while (token != NULL)
	{
		if (token[0] >= '0' && token[0] <= '9')							//token이 피연산자인 경우
		{
			int value = atoi(token);
			push(operand_stack, value);
		}
		else if (is_operator(token[0] > -1))							//token이 연산자인 경우
		{
			int result = eval_op(token[0]);
			push(operand_stack, result);
		}
		else
			handle_exception("Syntax Error : invalid character encountered. line 34\n");
		token = strtok(NULL, " ");
	}

	if(is_empty(operand_stack))
		handle_exception("Syntax Error : Stack empty in eval_op. line 39\n");
	int answer = pop(operand_stack);
	if (is_empty(operand_stack))
		return answer;
	else
	{
		handle_exception("Syntax Error : Stack should be empty. line 45\n");
		return -1;
	}
}

int eval_op(char op)
{
	if (is_empty(operand_stack))
		handle_exception("Syntax Error. Stack empty in eval_op. line 42\n");
	int rhs = pop(operand_stack);
	if (is_empty(operand_stack))
		handle_exception("Syntax Error. Stack empty in eval_op. line 45\n");
	int lhs = pop(operand_stack);
	int result = 0;
	switch (op) {
	case '+': result = lhs + rhs; break;
	case '-': result = lhs - rhs; break;
	case '*': result = lhs * rhs; break;
	case '/': result = lhs / rhs; break;
	}
	return result;
}

int main(void)
{
	char infix[MAX_LENGTH];
	read_line(stdin, infix, MAX_LENGTH);

	printf(" %s := ", infix);
	char* postfix = convert(infix);
	printf("%d\n", eval(postfix));

}