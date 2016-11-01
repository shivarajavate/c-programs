#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int data;
	int rank;
	struct node *next;
	struct node *repr;
} node_t;

int getIndex(node_t *head[], int n, int data) {
	int i;
	node_t *h;
	for(i=0; i<n; ++i) {
		h = head[i];
		while(h) {
			if(h->data==data)
				return i;
			else
				h = h->next;
		}
	}
	return -1;
}

node_t *getRepr(node_t *head[], int n, int data) {
	int i;
	node_t *h;
	for(i=0; i<n; ++i) {
		h = head[i];
		while(h) {
			if(h->data==data)
				return head[i];
			else
				h = h->next;
		}
	}
	return NULL;
}

int setsize(node_t *root) {
	int count = 0;
	while(root) {
		root = root->next;
		count++;
	}
	return count;
}

void unionset(node_t *head[], int n) {
	int index1, index2, data1, data2, size1, size2;
	node_t *root1, *root2, *temp1, *temp2;
	scanf("%d%d", &data1, &data2);
	index1 = getIndex(head, n, data1);
	index2 = getIndex(head, n, data2);
	root1 = getRepr(head, n, data1);
	root2 = getRepr(head, n, data2);
	temp1 = root1;
	temp2 = root2;
	size1 = setsize(temp1);
	size2 = setsize(temp2);

	if(!root1 || !root2 || index1==-1 || index2==-1 || index1==index2 )
		return;

	if(size1>=size2) {
		while(temp1->next) {
			++(temp1->rank);
			temp1 = temp1->next;
		}
		++(temp1->rank);
		temp1->next = root2;
		
		while(temp2) {
			temp2->repr = root1;
			temp2->rank = root1->rank;
			temp2 = temp2->next;
		}

		head[index2] = NULL;
	}
	else {
		while(temp2->next) {
			++(temp2->rank);
			temp2 = temp2->next;
		}
		++(temp2->rank);
		temp2->next = root1;
		
		while(temp1) {
			temp1->repr = root2;
			temp1->rank = root2->rank;
			temp1 = temp1->next;
		}

		head[index1] = NULL;
	}
}

void display(node_t *head[], int n) {
	int i;
	node_t *h;
	printf("\nSETS\n");
	for(i=0; i<n; ++i) {
		h = head[i];
		printf("{");
		while(h) {
			printf("%d", h->data);
			if(h->next)
				printf(", ");
			else
				printf(": RANK %d", h->rank);
			h = h->next;
		}
		printf("}\n");
	}
	printf("--x--\n\n");
}

node_t *makeset(int data) {
	node_t *newset;
	node_t *newnode = (node_t *)malloc(sizeof(node_t));
	newnode->data = data;
	newnode->rank = 0;
	newnode->next = NULL;
	newnode->repr = newnode;	
	newset = newnode;
	return newset;
}

int main(int argc, char *argv[]) {
	
	int n, i, data;
	printf("Enter the head size: ");
	scanf("%d", &n);
	node_t *head[n];
	for(i=0; i<n; ++i) {
		scanf("%d", &data);
		head[i] = makeset(data);
	}
	display(head, n);
	
	int u, j;
	printf("Enter no. of union operations: ");
	scanf("%d", &u);
	for(j=0; j<u; ++j) {
		unionset(head, n);
		display(head, n);
	}

	return 0;
}
