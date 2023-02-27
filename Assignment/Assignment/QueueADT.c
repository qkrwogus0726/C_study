#include <stdio.h>
#include <stdlib.h>
#include "QueueADT.h"

Node* create_node()
{
	Node* ptr_node = (Node*)malloc(sizeof(Node));

	if (ptr_node == NULL)
	{
		printf("Error in create_node.\n");
		return;
	}
	else {
		ptr_node->date = '0';
		ptr_node->time = NULL;
		ptr_node->expression = '0';
		ptr_node->latitude = 0;
		ptr_node->longitude = 0;
		ptr_node->velocity = 0;
	}
	return ptr_node;
}

Queue* create_queue()
{
	Queue* q = (Queue*)calloc(1, sizeof(struct queue_type));
	if (q == NULL) {
		printf("Error in create\n");
	}
	q->front = NULL;
	q->rear = NULL;
	q->size = 0;
	return q;
}

void enqueue(Queue* q, double* enqueue_data, Node* enqueue_node)
{
	Node* new_node = enqueue_node;
	new_node->output_data = enqueue_data;

	if (q->front == NULL) {
		q->front = new_node;
		q->rear = new_node;
	}
	else {
		q->rear->next = new_node;
		q->rear = new_node;
	}

	q->size++;
}

void dequeue(Queue* q, FILE* dequeue_wfile, char* boot_time)
{
	Node* old_front;

	if (q == NULL) {
		printf("Error in dequeue.\n");
		return;
	}

	while (q->size != 0) {
		old_front = q->front;
		q->front = old_front->next;

		if (q->front == NULL) {
			q->rear = NULL;
			return;
		}
		fprintf(dequeue_wfile, "%s,", boot_time);
		fprintf(dequeue_wfile, "%s,", old_front->time);
		fprintf(dequeue_wfile, "%s,", old_front->latitude);
		fprintf(dequeue_wfile, "%s,", old_front->longitude);
		fprintf(dequeue_wfile, "%s,", old_front->velocity);

		for (int i = 0; i < 199; i++) {
			fprintf(dequeue_wfile, "%f,", old_front->output_data[i]);
		}

		fprintf(dequeue_wfile, "\n");
		free(old_front);
		q->size--;
	}
	return;
}