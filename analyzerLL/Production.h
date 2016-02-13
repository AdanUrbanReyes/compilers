#include <string>
using namespace std;
class Production{
	private:
		bool isCalculatedFirst;
		bool isCalculatedNext;
		string production;
		char nonterminal;
		string first;
		string next;
	public:
		Production(char, string);
		void setProduction(string);
		string getProduction();
		void setNonterminal(char);
		char getNonterminal();
		void setIsCalculatedFirst(bool _isCalculatedFirst);
		bool getIsCalculatedFirst();
		void setIsCalculatedNext(bool _isCalculatedNext);
		bool getIsCalculatedNext();
		void setFirst(string);
		string getFirst();
		void setNext(string);
		string getNext();
};
Production::Production(char _nonterminal,string _production){
	nonterminal=_nonterminal;
	production=_production;
	isCalculatedFirst=false;
	isCalculatedNext=false;
}
void Production::setProduction(string _production){
	production=_production;
}
string Production::getProduction(){
	return production;
}
void Production::setNonterminal(char _nonterminal){
	nonterminal=_nonterminal;
}
char Production::getNonterminal(){
	return nonterminal;
}
void Production::setIsCalculatedFirst(bool _isCalculatedFirst){
	isCalculatedFirst=_isCalculatedFirst;	
}
bool Production::getIsCalculatedFirst(){
	return isCalculatedFirst;
}
void Production::setIsCalculatedNext(bool _isCalculatedNext){
	isCalculatedNext=_isCalculatedNext;
}
bool Production::getIsCalculatedNext(){
	return isCalculatedNext;
}
void Production::setFirst(string _first){
		first=first;
}
string Production::getFirst(){
	return first;
}
void Production::setNext(string _next){
	next=_next;
}
string Production::getNext(){
	return next;
}
