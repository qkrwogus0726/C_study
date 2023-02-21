#ifndef STACKADT_H
#define STACKADT_H
#pragma once

#include <stdbool.h>

typedef int Item;
typedef struct stack_type* Stack; //d

Stack create();
void destroy(Stack s);
void make_empty(Stack s);
void push(Stack s, Item i);
Item pop(Stack s);
Item peek(Stack s);

#endif