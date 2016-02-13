#include <stdio.h>
int main(int ari,char **arc){
	if(ari < 2){
		printf("ERROR ejecute como %s archivoParaAnalizar\n",arc[0]);
		return 1;
	}
//	yyin(arc[1],"r");
	yyin = stdin;
	yylex();
	return 0;
}
