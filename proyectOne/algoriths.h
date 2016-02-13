#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stack.h"
#ifndef __ALGORITHS_H__
#define __ALGORITHS_H__
//algorith infija to posfija
char *signs="()*+-|";
short getPrecedence(char operador){
	switch(operador){
		case ')':return 5; break;
		case '*':return 4; break;
		case '+':return 3; break;
		case '-':return 2; break;
		case '|':return 1; break;
		case '(':return 0; break;
	}
	return -1;
}
char *infijaToPosfija(char *infija){
	int i,j,li=strlen(infija);//lenght infija
	char *posfija=(char *)malloc(sizeof(char)*li);
	char operador;//auxiliary
	Stack *stack=NULL;
	for(i=0,j=0;i<li;i++){	
		if(strchr(signs,infija[i])==NULL){//if character not is character especial
			posfija[j++]=infija[i];
		}else{
			if(stack==NULL || infija[i]=='('){
				push(&stack,(void *)&infija[i]);
			}else{
				if(infija[i]==')'){//empty stack
					for(operador=*((char *)(pop(&stack)->object));operador!='(';operador=*((char *)(pop(&stack)->object))){
						posfija[j++]=operador;
					}
				}else{
					for(operador=*((char *)peek(stack));getPrecedence(operador)>=getPrecedence(infija[i]);operador=*((char *)peek(stack))){
						posfija[j++]=operador;
						pop(&stack);
						if(stack==NULL)
							break;
					}
					push(&stack,(void *)&infija[i]);
				}
			}
		}
	}
	while(peek(stack)!=NULL){//empty stack set operatores in string posfija
		posfija[j++]=*((char *)(pop(&stack)->object));
	}
	return posfija;
}
//end algorith infija to posfija
#endif
