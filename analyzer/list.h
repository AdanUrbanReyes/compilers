#include <stdio.h>
#include <stdlib.h>
#ifndef __LIST_H__
#define __LIST_H__
typedef struct node{
	char *word;
	char *token;
	struct node *next,*previus;
}Node;
void printList(Node *);
Node *getNode(char *,char *,Node *, Node *);
Node *addNode(Node **,Node *);
Node *removeNode(Node **);
#endif
