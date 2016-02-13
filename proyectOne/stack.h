#include <stdio.h>
//http://catarina.udlap.mx/u_dl_a/tales/documentos/lis/gonzalez_c_vm/capitulo2.pdf
#include <stdlib.h>
#ifndef __STACK_H__
#define __STACK_H__
typedef struct Stack{
	void *object;
	struct Stack *down;
}Stack;
int empty(Stack *header){
	int ss=0;//sizeof stack
	if(header==NULL){
		return 0;
	}else{
		Stack *auxiliary=header;
		while(auxiliary!=NULL){
			ss++;
			auxiliary=auxiliary->down;
		}
	}
	return ss;
}
Stack *push(Stack **header,void *object){
	Stack *toAdd=(Stack *)malloc(sizeof(Stack));
	toAdd->object=object;
	toAdd->down=NULL;
	if(*header!=NULL){
		toAdd->down=*header;
	}
	*header=toAdd;
	return toAdd;
}
Stack *pop(Stack **header){
	Stack *auxiliary;
	if(*header==NULL){
		return NULL;
	}else{
		auxiliary=*header;
		*header=(*header)->down;
		auxiliary->down=NULL;
	}
	return auxiliary;
}
void *peek(Stack *header){
	if(header==NULL){
		return NULL;
	}
	return header->object;
}
#endif
