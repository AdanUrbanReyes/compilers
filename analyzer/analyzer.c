#include "analyzer.h"
FILE *sl=NULL,*el=NULL;//sl= pointer to the start lexema, el= pointer to the end lexema
unsigned int na=0;//na= number of atomaton
unsigned int lineNumber=1;
int cr;//character readed
char *lexema=NULL;
FILE *pfe,*pfl;//pfe= pointer file errors, pfl=pointer file lexemas
Node *lrw=NULL;//list reserved words
void setLexema(){
	long psl=ftell(sl);//psl=position start lexema
	long pel=ftell(el);//pel=position end lexema
	unsigned int it=0,lt=pel-psl;//ic=index lexema, lt=lenght lexema
	//printf("psl=%ld\tpel=%ld\nlt=%u\n",psl,pel,lt);
	lexema=(char *)malloc(sizeof(char)*lt+1);
	while(it<lt){
		lexema[it++]=(char)fgetc(sl);
	}
	lexema[it]='\0';
	//printf("cad=|%s|\n",lexema);
}
void recognizedLexema(char *token,char *value){
	setLexema();//set lexema reconocido on global variable lexema
	if(value==NULL){
		value=lexema;
	}
	fprintf(pfl,"%30s\t%30s\t%30s\n",token,lexema,value);
	na=0;
}
void failRecognizeLexema(){
	fseek(el,ftell(sl),SEEK_SET);//set pointer el(end token) to position pointed by sl(start token)      
	na++;
}
void recognizedRecervedWord(char *token,char *value){
	Node *i=lrw;
	setLexema();
	if(value==NULL){
		value=lexema;
	}
	na=0;
	while(i!=NULL){
		if(!strcmp(lexema,i->word)){
			fprintf(pfl,"%30s\t%30s\t%30s\n",i->token,lexema,value);
			return ;
		}
		i=i->next;
	}
	fprintf(pfl,"%30s\t%30s\t%30s\n",token,lexema,value);
	return;
}
void automatonForId(){
	unsigned int state=0;
	while(1){
		cr=fgetc(el);
		switch(state){
			case 0: 
				if(cr=='\t' || cr==' ' || cr=='\n'){
					fgetc(sl);
					if(cr=='\n'){//count lines
						lineNumber++;
					}
				}else{
					if(isalpha(cr)!=0){
						state=1;
					}else{
						if(cr=='_'){
							state=2;
						}else{//failure atomaton
							failRecognizeLexema();
							return ;					
						}
					}
				}
			break;
			case 1: 
				if(isalpha(cr)!=0){
					state=3;
				}else{
					if(cr=='_'){
						state=4;
					}else{
						if(isdigit(cr)!=0){
							state=5;
						}else{
							fseek(el,-1,SEEK_CUR);
							recognizedRecervedWord("IDENTIFICADOR",NULL);
							return;
						}
					}
				}
			break;
			case 2: 
				if(isalpha(cr)!=0){
					state=3;
				}else{
					if(cr=='_'){
						state=4;
					}else{
						if(isdigit(cr)!=0){
							state=5;
						}else{
							fseek(el,-1,SEEK_CUR);
							recognizedRecervedWord("IDENTIFICADOR",NULL);
							return;
						}
					}
				}
			break;
			case 3:
				if(isalpha(cr)!=0){
					state=3;
				}else{
					if(cr=='_'){
						state=4;
					}else{
						if(isdigit(cr)!=0){
							state=5;
						}else{
							fseek(el,-1,SEEK_CUR);
							recognizedRecervedWord("IDENTIFICADOR",NULL);
							return;
						}
					}
				}
			break;
			case 4: 
				if(isalpha(cr)!=0){
					state=3;
				}else{
					if(cr=='_'){
						state=4;
					}else{
						if(isdigit(cr)!=0){
							state=5;
						}else{
							fseek(el,-1,SEEK_CUR);
							recognizedRecervedWord("IDENTIFICADOR",NULL);
							return;
						}
					}
				}
			break;
			case 5: 
				if(isalpha(cr)!=0){
					state=3;
				}else{
					if(cr=='_'){
						state=4;
					}else{
						if(isdigit(cr)!=0){
							state=5;
						}else{
							fseek(el,-1,SEEK_CUR);
							recognizedRecervedWord("IDENTIFICADOR",NULL);
							return;
						}
					}
				}
			break;
		}
	}
}
void automatonForFloatNumbers(){
	unsigned int state=0;
	while(1){
		cr=fgetc(el);
		switch(state){
			case 0:
				if(cr=='\t' || cr==' ' || cr=='\n'){//remove black space, tabulator, line jump
					fgetc(sl);
					if(cr=='\n'){//count lines
						lineNumber++;
					}
				}else{
					if(isdigit(cr)!=0){
						state=1;
					}else{
						if(cr=='.'){
							state=2;
						}else{//then failure atomaton
							failRecognizeLexema();
							return ;
						}
					}
				}
			break;
			case 1:
				if(cr=='.'){
					state=3;	
				}else{
					if(isdigit(cr)!=0){
						state=1;
					}else{
						failRecognizeLexema();
						return ;
					}
				}
			break;
			case 2: 
				if(isdigit(cr)!=0){
					state=4;
				}else{//then failure atomaton
					failRecognizeLexema();
					return ;
				}
			break;
			case 3:
				if(isdigit(cr)!=0){
					state=5;
				}else{//then failure atomaton
					fseek(el,-1,SEEK_CUR);
					recognizedLexema("NUMERO FLOTANTE",NULL);
					return ;
				}
			break;
			case 4:
				if(isdigit(cr)!=0){
					state=4;
				}else{//then failure atomaton
					fseek(el,-1,SEEK_CUR);
					recognizedLexema("NUMERO FLOTANTE",NULL);
					return ;
				}
			break;
			case 5:
				if(isdigit(cr)!=0){
					state=5;
				}else{//then failure atomaton
					fseek(el,-1,SEEK_CUR);
					recognizedLexema("NUMERO FLOTANTE",NULL);
					return ;
				}
			break;
		}
	}
}
void automatonForIntegersNumber(){
	unsigned int state=0;
	while(1){
		cr=fgetc(el);//read character of file
		switch(state){
			case 0: 
				if(cr=='\t' || cr==' ' || cr=='\n'){//remove black space, tabulator, line jump
					fgetc(sl);
					if(cr=='\n'){//count lines
						lineNumber++;
					}
				}else{
					if(isdigit(cr)!=0){
						state=1;
					}else{// then this automaton failurefor this character
						failRecognizeLexema();
						return ;
					}
				}
			break;
			case 1://when is state is beause reconozing number 
				if(isdigit(cr)!=0){
					state=1;
				}else{
					fseek(el,-1,SEEK_CUR);
					recognizedLexema("NUMERO ENTERO",NULL);
					return;
				}
			break;
		}
	}
}
void automatonForOperatorsArithmeticAssignmentIncrement(){
	unsigned int state=0;
	while(1){
		cr=fgetc(el);
		switch(state){
			case 0: 
				if(cr=='\t' || cr==' ' || cr=='\n'){//remove black space, tabulator, line jump
					fgetc(sl);
					if(cr=='\n'){//count lines
						lineNumber++;
					}
				}else{
					if(cr=='+'){
						state=1;
					}else{
						if(cr=='-'){
							state=2;
						}else{
							if(cr=='*'){
								state=3;
							}else{
								if(cr=='/'){
									state=4;
								}else{
									if(cr=='%'){
										recognizedLexema("OPERADOR-ARITMETICO","MODULO");
										return;
									}else{
										failRecognizeLexema();
										return ;
									}
								}
							}
						}
					}
				}
			break;
			case 1:
				if(cr=='+'){
					recognizedLexema("INCREMENTO","INCREMENTO-POSITIVO");
					return;
				}else{
					if(cr=='='){
						recognizedLexema("ASIGNACION","SUMA-ASIGNACION");
						return ;
					}else{
						fseek(el,-1,SEEK_CUR);
						recognizedLexema("OPERADOR ARITMETICO","SUMA");
						return;
					}
				}
			break;
			case 2:
				if(cr=='-'){
					recognizedLexema("INCREMENTO","INCREMENTO-NEGATIVO");
					return ;
				}else{
					if(cr=='='){
						recognizedLexema("ASIGNACION","RESTA-ASIGNACION");
						return;
					}else{
						fseek(el,-1,SEEK_CUR);
						recognizedLexema("OPERADOR ARITMETICO","RESTA");
						return ;
					}
				}
			break;
			case 3:
				if(cr=='='){
					recognizedLexema("ASIGNACION","MULTIPLICACION-ASIGNACION");
					return ;
				}else{
					fseek(el,-1,SEEK_CUR);
					recognizedLexema("OPERADOR ARITMETICO","MULTIPLICACION");
					return ;
				}
			break;
			case 4:
				if(cr=='='){
					recognizedLexema("ASIGNACION","DIVISION-ASIGNACION");
					return ;
				}else{
						fseek(el,-1,SEEK_CUR);
						recognizedLexema("OPERADOR ARITMETICO","DIVISION");
						return ;
				}
			break;
		}
	}
}
void automatonForOperatorLogic(){
	unsigned int state=0;
	while(1){
		cr=fgetc(el);//read character of file
		switch(state){
			case 0:
				if(cr=='\t' || cr==' ' || cr=='\n'){//remove black space, tabulator, line jump
					fgetc(sl);
					if(cr=='\n'){//count lines
						lineNumber++;
					}
				}else{
					if(cr=='&'){
						state=1;
					}else{
						if(cr=='|'){
							state=2;
						}else{
							if(cr=='!'){
								state=3;
							}else{
								failRecognizeLexema();
								return;
							}
						}
					}
				}
			break;
			case 1:
				if(cr=='&'){
					recognizedLexema("OPERADOR LOGICO","Y");
					return;
				}else{
					failRecognizeLexema();
					return;
				}
			break;
			case 2:
				if(cr=='|'){
					recognizedLexema("OPERADOR LOGICO","O");
					return;
				}else{
					failRecognizeLexema();
					return;
				}
			break;
			case 3:
				if(cr=='='){
					recognizedLexema("OPERADOR LOGICO","DIFERENTE");
					return;
				}else{
					fseek(el,-1,SEEK_CUR);
					recognizedLexema("OPERADOR LOGICO","NEGACION");
					return;
				}
			break;
		}
	}
}

void automatonForOperatorsAssignmentRelational(){
	unsigned int state=0;
	while(1){
		cr=fgetc(el);//read character of file
		switch(state){
			case 0:
				if(cr=='\t' || cr==' ' || cr=='\n'){//remove black space, tabulator, line jump
					fgetc(sl);
					if(cr=='\n'){//count lines
						lineNumber++;
					}
				}else{
					if(cr=='>'){
						state=1;
					}else{
						if(cr=='<'){
							state=2;
						}else{
							if(cr=='='){
								state=3;
							}else{
								failRecognizeLexema();
								return;
							}
						}
					}
				}
			break;
			case 1:
				if(cr=='='){
					recognizedLexema("OPERADOR RELACIONAL","MAYOR-IGUAL");
					return;				
				}else{
					fseek(el,-1,SEEK_CUR);
					recognizedLexema("OPERADOR RELACIONAL","MAYOR");
					return;
				}
			break;
			case 2:
				if(cr=='='){
					recognizedLexema("OPERADOR RELACIONAL","MENOR-IGUAL");
					return;
				}else{
					fseek(el,-1,SEEK_CUR);
					recognizedLexema("OPERADOR RELACIONAL","MENOR");
					return;
				}
			break;
			case 3:
				if(cr=='='){
					recognizedLexema("OPERADOR RELACIONAL","IGUAL");
					return;
				}else{
					fseek(el,-1,SEEK_CUR);
					recognizedLexema("ASIGNACION","ASIGNACION");
					return;
				}
			break;
		}
	}
}
void automatonForSpecialSymbol(){
	unsigned int state=0;
	while(1){
		cr=fgetc(el);//read character of file
		switch(state){
			case 0:
				if(cr=='\t' || cr==' ' || cr=='\n'){//remove black space, tabulator, line jump
					fgetc(sl);
					if(cr=='\n'){//count lines
						lineNumber++;
					}
				}else{
					if(cr=='('){
						recognizedLexema("SIMBOLO ESPECIAL","PARENTESIS ABIERTO");
						return;
					}else{
						if(cr==')'){
							recognizedLexema("SIMBOLO ESPECIAL","PARENTESIS CERRADO");
							return;
						}else{
							if(cr=='{'){
								recognizedLexema("SIMBOLO ESPECIAL","LLAVE ABIERTA");
								return;
							}else{
								if(cr=='}'){
									recognizedLexema("SIMBOLO ESPECIAL","LLAVE CERRADA");
									return;
								}else{
									if(cr=='['){
										recognizedLexema("SIMBOLO ESPECIAL","CORCHETE ABIERTO");
										return;
									}else{
										if(cr==']'){
											recognizedLexema("SIMBOLO ESPECIAL","CORCHETE CERRADO");
											return;
										}else{
											if(cr==';'){
												recognizedLexema("SIMBOLO ESPECIAL","PUNTO Y COMA");
												return;
											}else{
												if(cr==','){
													recognizedLexema("SIMBOLO ESPECIAL","COMA");
													return;
												}else{
													if(cr=='.'){
														recognizedLexema("SIMBOLO ESPECIAL","PUNTO");
														return;
													}else{
														if(cr==':'){
															recognizedLexema("SIMBOLO ESPECIAL","DOS PUNTOS");
															return;
														}else{
															if(cr=='#'){
																recognizedLexema("SIMBOLO ESPECIAL","NUMERAL");
																return;
															}else{
																if(cr=='\''){
																	recognizedLexema("SIMBOLO ESPECIAL","COMILLA-SIMPLE");
																	return;
																}else{
																	if(cr=='\"'){
																		recognizedLexema("SIMBOLO ESPECIAL","COMILLA-DOBLE");
																		return ;
																	}else{
																		failRecognizeLexema();
																		return;
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			break;
		}
	}
}
Node *getListOfReservedWords(char *fptrw){//fptrw= file path to reserved words
	Node *lrw=NULL;//list reserved words
	char *word,*token;
	if((el=fopen(fptrw,"r"))==NULL){
		return NULL;
	}
	sl=fopen(fptrw,"r");
	while((cr=fgetc(el))!=EOF){
		while(cr!='\n' && cr!=EOF){
			cr=fgetc(el);
		}
		fseek(el,-1,SEEK_CUR);
		setLexema();//set lexema reconocido on global variable lexema
		fgetc(el);
		fseek(sl,ftell(el),SEEK_SET);
		word=strdup(strtok(lexema,"|"));
		token=strdup(strtok(NULL,"|"));
		//printf("word= |%s|\n",word);
		//printf("token= |%s|\n",token);
		addNode(&lrw,getNode(word,token,NULL,NULL));
	}
	fclose(sl);
	fclose(el);
	return lrw;
}
short startAnalyzer(char *fpta,char *fptsl,char *fptse,char *fptrw){//fpta=file path to analyzer,fptse=file path to save errors, fptsl= file path to save lexemas, fptrw= file path to reserved words
	lrw=getListOfReservedWords(fptrw);//list recerved words
//	printList(lrw);
	if((el=fopen(fpta,"r"))==NULL){
		return -1;
	}
	if((pfe=fopen(fptse,"w+"))==NULL){
		return -2;
	}
	if((pfl=fopen(fptsl,"w+"))==NULL){
		return -3;
	}
	sl=fopen(fpta,"r");//is imposibol this line failure because pass if((el=fopen(filePath,"r"))!=NULL)
	cr='s';//start cr
	lineNumber=1;
	na=0;//here can change the automaton with el cual will start
	while(cr!=EOF){
		switch(na){
			case 0: automatonForId(); break;
			case 1: automatonForFloatNumbers(); break;
			case 2: automatonForIntegersNumber(); break;
			case 3: automatonForOperatorsArithmeticAssignmentIncrement();break;
			case 4: automatonForOperatorsAssignmentRelational();break;
			case 5: automatonForOperatorLogic();break;
			case 6: automatonForSpecialSymbol();break;
			default:	fprintf(pfe,"linea %u: %c\n",lineNumber,cr); fgetc(sl); fgetc(el); na=0; break;
		}
	}
	fclose(el);
	fclose(pfe);
	fclose(pfl);
	fclose(sl);
	return 0;
}
