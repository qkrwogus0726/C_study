#ifndef QUEUEADT_H
#define QUEUEADT_H
#pragma once

#define row_num 199

typedef struct node Node;

typedef struct node
{
	char* expression;
	char* date;
	char* time;
	char* can_id;
	char* can_data;
	char* latitude;
	char* longitude;
	char* velocity;
	double* output_data;
	Node* next;
}Node;

typedef struct queue_type
{
	struct node* front;
	struct node* rear;
	int size;
}Queue;

Node* create_node();
Queue* create_queue();
void enqueue(Queue* q, double* enqueue_data, Node* enqueue_node);
void dequeue(Queue* q, FILE* dequeue_wfile, char* boot_time);

#endif