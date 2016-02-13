#include <iostream>
#include "grammar.h"
#include "list.h"
using namespace std;

int main(int ari,char **arc){	
	char *grammar=arc[1];//path file to load grammar
	//char *string=arc[2];//string to test on grammar
//	loadGrammar(grammar);
	readGrammar(grammar);
/*	
	Node *head=NULL;
	int i=15;
	addNode(&head,getNode(&i,NULL,NULL));
	cout << "i = " << *((int*)(head->data)) << endl;
*/
	return 0;
}
