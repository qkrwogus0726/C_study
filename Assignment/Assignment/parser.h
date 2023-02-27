#ifndef PARSER_H
#define PARSER_H
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "QueueADT.h"

#define MAX 100
#define protocol_id_num 24

int find_index(char* id);
void tokenizer_data(Node* ptr_node);
void tokenizer_can(char* tokenize_data, Node* ptr_node);
void parser(Node* data, unsigned char* Parsed_data);

#endif