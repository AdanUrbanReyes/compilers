#include "list.h"
void printList(Node *head){
	while(head!=NULL){
	   printf("|%s|%s|->",head->word,head->token);
	   head=head->next;
	   if(head==NULL)
	      printf("NULL\n");
	}
}
Node *getNode(char *word,char *token,Node *next, Node *previus){
	Node *node=(Node *)malloc(sizeof(Node));
	if(node==NULL)
		return node;
	node->word=word;
	node->token=token;
	node->next=next;
	node->previus=previus;
	return node;
}
Node *addNode(Node **head,Node *toAdd){
	if(*head==NULL){
		*head=toAdd;
	}else{
		Node *auxiliary=*head;
		while(auxiliary->next!=NULL){
			auxiliary=auxiliary->next;
		}
		auxiliary->next=toAdd;
		toAdd->previus=auxiliary;
	}
	return toAdd;
}
Node *removeNode(Node **toRemove){
	if(*toRemove==NULL){
		return NULL;
	}
	Node *auxiliary=*toRemove;
	if((*toRemove)->previus==NULL){//then (*toRemove) is head of list then need move pointer head to start list (*toRemove)->next;
		*toRemove=(*toRemove)->next;//move toRemove (header of list) to next elemente 
		(*toRemove)->previus=NULL;//set pointer previus with null (head->previus=NULL)
	}else{
		if(auxiliary->next!=NULL){//if next not is null
			(auxiliary->next)->previus=auxiliary->previus;//set previus of next element of auxiliary with previus element of auxiliary
		}
		if(auxiliary->previus!=NULL){//if previus not is null
			(auxiliary->previus)->next=auxiliary->next;//set next of previus element of auxiliary with next element of auxiliary
		}
	}
	auxiliary->next=auxiliary->previus=NULL;//set null pointer of auxiliary (here is where remove element :D)
	return auxiliary;//return element droped
}
