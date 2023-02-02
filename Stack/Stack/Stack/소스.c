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
Stack operand_stack;													//�ǿ����ڵ��� ������ ����

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
		if (token[0] >= '0' && token[0] <= '9')							//token�� �񿬻����� ���
		{
			sprintf(pos, "%s ", token);
			pos += (strlen(token) + 1);
		}
		else if (is_operator(token[0] > -1))							//�������� ���
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
	if (is_empty(operator_stack) || op == '(')										//operator_stack�� ������� ��
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

int is_operator(char ch)												//ch�� ���������� �˻��ϴ� �Լ�
{
	for (int i = 0; i < strlen(OPERATORS); i++)
	{
		if (OPERATORS[i] == ch)											//+�̸� 0, -�̸� 1, *�̸� 2, /�̸� 3 ����
			return i;
		return -1;
	}
}

int eval(char* expr)													//����ǥ����� ���ڿ��� ���·� �־����� �� ����ϴ� �Լ�
{
	operand_stack = create();											//���� ���� �� operand_stack�� �ּ� ����
	char* token = strtok(expr, " ");									//��� ������, �ǿ����ڰ� ���鹮�ڷ� ���еǾ� �ִٰ� ����
	while (token != NULL)
	{
		if (token[0] >= '0' && token[0] <= '9')							//token�� �ǿ������� ���
		{
			int value = atoi(token);
			push(operand_stack, value);
		}
		else if (is_operator(token[0] > -1))							//token�� �������� ���
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