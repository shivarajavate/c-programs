#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int data;
	struct node *next;
} node_t;

void push(node_t **head, int data) {
	node_t *temp = (node_t *)malloc(sizeof(node_t));
	temp->data = data;
	temp->next = *head;
	*head = temp;
}

void insert(node_t **head, int data, int position) {
	int index = 1;
	node_t *curr, *prev = (*head);
	
	node_t *temp = (node_t *)malloc(sizeof(node_t));
	temp->data = data;
	temp->next = NULL;
	
	while(prev && prev->next && index==(position-1)) {
			prev = prev->next;
			index++;
	}
	curr = prev->next;
	prev->next = temp;
	temp->next = curr;
}

void insertAfter(node_t *prev, int data) {
	node_t *curr;

	node_t *temp = (node_t *)malloc(sizeof(node_t));
	temp->data = data;
	temp->next = NULL;
	
	if(!prev)
		return;

	curr = prev->next;
	prev->next = temp;
	temp->next = curr;
}

void append(node_t **head, int data) {
	node_t *last = *head;

	node_t *temp = (node_t *)malloc(sizeof(node_t));
	temp->data = data;
	temp->next = NULL;
	
	if(!(*head)) {
		*head = temp;
		return;	
	}

	while(last->next) {
			last = last->next;
	}
	last->next = temp;
}

void display(node_t *node) {	
	while(node) {
		printf("%d ", node->data);
		node = node->next;
	}
	printf("\n");
}

int main(int argc, char *argv[]) {
	node_t *head = NULL;
	append(&head, 6);
  	push(&head, 7);
  	push(&head, 1);
  	append(&head, 4);
  	insert(&head, 9, 2);
	insertAfter(head->next, 8);
	printf("\nCreated Linked list is: ");
	display(head);
	return 0;
}
