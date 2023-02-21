#ifndef QUEUEADT_H
#define QUEUEADT_H
#pragma once

typedef struct node Node;


typedef struct node
{
	char* expression;

	char* date;
	char* time;
	char* CAN_ID;
	char* CAN_DATA;
	char* latitude;		//위도
	char* longitude;		//경도
	char* velocity;		//속도

	double* output_data;
	Node* next;
}Node;

typedef struct queue_type
{
	struct node* front;
	struct node* rear;
	int size;
}Queue;


Queue* create_queue();
void enqueue(Queue* q, double* output_data_, Node* enqueue_node);
void dequeue(Queue* q, FILE* dequeue_wfile, char* boot_time);

#endif