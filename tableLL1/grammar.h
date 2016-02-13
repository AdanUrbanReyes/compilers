//#include <fstream>
#include <cstdio>
#include <iostream>
using namespace std;
void readGrammar(char *pathFile){
	FILE *file=fopen(pathFile ,"r");
	char cr;
	while((cr=fgetc(file))!=EOF){
		cout << cr << endl;
	}
}
/*typedef struct grammar{
	/
		private static int numberProductions;
		private static char *symbolsTerminals, *symbolsNonterminals;
		private static char initialSymbol;
	/
	char nonterminal
	char *production;
}*/
/*
void loadGrammar(char *file){
	ifstream sl(file);//start lexema
	ifstream el(file);//end lexema
	if(sl==NULL || el==NULL){
		return ;
	}
	char cr;//character readed
	while((el >> cr)!=EOF){
		while(cr != '\n' && cr != EOF){
			el >> cr;
		}

	}
}
*/
