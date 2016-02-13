#include <iostream>
#include <string>
#include <fstream>
#include "Grammar.h"
using namespace std;
void printGrammar(Grammar grammar){
	cout << "initial simbol: " << grammar.getInitialSimbol() << "\n";
	list <char> l=grammar.getNonterminals();
	list <char> :: iterator i;
	i=l.begin();
	cout << "nonterminals:\n";
	while(i!=l.end()){
		cout << (*i) <<"\n";
		i++;
	}
	l=grammar.getTerminals();
	i=l.begin();
	cout << "terminals:\n";
	while(i!=l.end()){
		cout << (*i) <<"\n";
		i++;
	}
	list <Production> l2=grammar.getProductions();
	list <Production> :: iterator i2=l2.begin();
	cout << "Productions:\n";
	while(i2!=l2.end()){
		cout << (*i2).getNonterminal() <<":" << (*i2).getProduction() << "\n";
		cout << "first = " << (*i2).getFirst() << "\n";
		i2++;
	}
}
Grammar loadGrammar(char *pathFile){
	size_t iterator;
	string lineReaded;
	ifstream file;
	file.open(pathFile);
	getline(file,lineReaded);
	Grammar grammar(lineReaded[0]);//past simbol initial like paramter for constructor
	getline(file,lineReaded);
	for(iterator=0;iterator<lineReaded.size();iterator++){
		grammar.addNonterminal(lineReaded[iterator]);//set the simbols terminals
	}
	getline(file,lineReaded);
	for(iterator=0;iterator<lineReaded.size();iterator++){
		grammar.addTerminal(lineReaded[iterator]);//set the simbols terminals
	}
	while(getline(file,lineReaded)>0){
		grammar.addProduction(Production(lineReaded[0],lineReaded.substr(lineReaded.find("->")+2,lineReaded.size())));
	}
	file.close();
	return grammar;
}
void change(Grammar g){
	g.setInitial();
}
int main(int ari,char **arc){
	if(ari<3){
		cout << "Error ejecute como " << arc[0] << " gramatica=<archivo donde esta la gramatica> cadena=<cadena a probar>\n";
		return -1;
	}
	Grammar grammar=loadGrammar(arc[1]);
	grammar.calculateFirsts();
	cout << "initial simbol: " << grammar.getInitialSimbol() << "\n";
	printGrammar(grammar);
	return 0;
}
