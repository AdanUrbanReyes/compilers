#include <stdio.h>
//https://www.circuitlab.com/editor/#?id=7pq5wm
#include "analyzer.h"
int main(int ari,char **arc){//./a.out <input file> <file path to save symbols table> <file path to save errors>
	if(ari<4){
		printf("error porfavor ejecute como %s <ruta completa del archivo de entrada> <ruta completa del archivo a guardar la tabla de simbolos> <ruta completa del archivo a guardar los errores>\n",arc[0]);
		return -1;
	}
	startAnalyzer(arc[1],arc[2],arc[3],"reservedWords.c");
	return 0;
}
