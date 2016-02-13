#include <iostream>
#include <list>
#include <cctype>
#include "Production.h"
using namespace std;
class Grammar{
	private:
		list <Production> productions;
		list <char> nonterminals;
		list <char> terminals;
		char initialSimbol;

	public:
		Grammar(char );
		Production addProduction(Production);
		list <Production> getProductions();
		void addNonterminal(char);
		list <char> getNonterminals();
		void addTerminal(char);
		list <char> getTerminals();
		char getInitialSimbol( );
		list <Production> getProductionsOf(char );
		string first(Production ,size_t);
		short calculateFirsts();
};
Grammar::Grammar(char _initialSimbol){
	initialSimbol=_initialSimbol;
}
Production Grammar::addProduction(Production production){
	productions.push_back(production);
	return production;
}
list <Production> Grammar::getProductions(){
	return productions;
}
void Grammar::addNonterminal(char nonterminal){
	nonterminals.push_back(nonterminal);
}
list <char> Grammar::getNonterminals(){
	return nonterminals;
}
void Grammar::addTerminal(char terminal){
	terminals.push_back(terminal);
}
list<char> Grammar::getTerminals(){
	return terminals;
}
char Grammar::getInitialSimbol(){
	return initialSimbol;
}
list <Production> Grammar::getProductionsOf(char nonterminal){
	list <Production> :: iterator i=productions.begin();
	list <Production> productionsOf;
	while(i!=productions.end()){
		if((*i).getNonterminal()==nonterminal){
			productionsOf.push_back((*i));
		}
		i++;
	}
	return productionsOf;
}
string Grammar::first(Production production,size_t indexOfProduction){
	if(production.getIsCalculatedFirst()){
		cout << "first calculated of production " << production.getNonterminal() << ":" << production.getProduction() << "\n";
		return "";
	}
	production.setIsCalculatedFirst(true);
	if(islower(production.getProduction()[indexOfProduction])){
		cout << "is lower " << production.getNonterminal() << ":" << production.getProduction() << "\n";
		cout << "is lower first: "<< (production.getProduction())[indexOfProduction] << "\n";
		return (""+(production.getProduction())[indexOfProduction]);
	}
	string calculeteFirst="";
	list <Production> productionsOf=getProductionsOf(production.getProduction()[indexOfProduction]);
	list <Production> :: iterator i=productionsOf.begin();
	while(i!=productionsOf.end()){
		production.setFirst(""+first(*i,0));
		cout << "production.setFirst " << production.getNonterminal() << ":" << production.getProduction() << " first:" << production.getFirst() <<"\n";
		calculeteFirst+=(production.getFirst());
//		calculeteFirst+=(""+first(*i,0));
		i++;
	}
	if(calculeteFirst=="" and (indexOfProduction < production.getProduction().size())){
		production.setIsCalculatedFirst(false);
		production.setFirst(first(production,indexOfProduction+1));
		cout << "if and" << production.getNonterminal() << ":" << production.getProduction() << "first:" << production.getFirst() <<"\n";
		return production.getFirst();
	}
	return calculeteFirst;
}
short Grammar::calculateFirsts(){
	list <Production> :: iterator i=productions.begin();
	while(i!=productions.end()){
		if((*i).getIsCalculatedFirst()==false){
			(*i).setFirst(first(*i,0));
		}
		i++;
	}
	return 0;
}
/*int Grammar::indexOfProduction(char nontermial){
	int position=0;
	list <Production> :: iterator i;
	i=productions.begin();
	while(i!=productions.end()){
		if((*i).nonterminal==nonterminal){
			return position;
		}
		i++;
		position++;
	}
	return -1;
}
list<Production> :: iterator Grammar::indexOfProduction(char nontermial){
	list <Production> :: iterator i;
	i=productions.begin();
	while(i!=productions.end()){
		if((*i).nonterminal==nonterminal){
			return i;
		}
		i++;
	}
	return i;
}
*/
