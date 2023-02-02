#include <stdio.h>
#include <stdlib.h>
#include "stackADT.h"

#define INIT_CAPACITY 100

struct node
{
	Item data;
	struct node* next;
};

struct stack_type
{
	struct node* top;
};

static void terminate(const char* message)
{
	printf("%s\n", message);
	exit(EXIT_FAILURE);
}

Stack create()
{
	Stack s = (Stack)malloc(sizeof(struct stack_type));
	if (s == NULL)
		terminate("Error in create : stack coult not be created. line 47\n");
	s->top = NULL;
	return s;
}

void destroy(Stack s)
{
	make_empty(s);
	free(s);
}

void make_empty(Stack s)
{
	while (!is_empty(s))
		pop(s);
}

bool is_empty(Stack s)
{
	return s->top == NULL;
}

void push(Stack s, Item i)
{
	struct node* new_node = malloc(sizeof(struct node));
	if (new_node == NULL)
		terminate("Error in push : stack is full. line 54\n");

	new_node->data = i;
	new_node->next = s->top;
	s->top = new_node;
}

Item pop(Stack s)
{
	struct node* old_top;
	Item i;

	if (is_empty(s))
		terminate("Error in pop : stack is empty. line 67\n");
	
	old_top = s->top;
	i = old_top->data;
	s->top = old_top->next;
	free(old_top);
	return i;
}

Item peek(Stack s)
{
	if (is_empty(s))
		terminate("Error in peek : stack is empty. line 79\n");
	return s->top->data;
}

void reallocate(Stack s)
{
	Item* tmp = (Item*)malloc(2 * s->size * sizeof(Item));
	if (tmp == NULL)
		terminate("Error in create : stack could not be created. line 79\n");
	for (int i = 0; i < s->size; i++)
		tmp[i] = s->contents[i];
	free(s->contents);
	s->contents = tmp;
	s->size *= 2;
}