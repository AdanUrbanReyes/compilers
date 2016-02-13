#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "list.h"
#include <unistd.h>
//http://es.aliexpress.com/w/wholesale-american-style-hoodies.html
#ifndef __ANALYZER_H__
#define __ANALYZER_H__
void setLexema();
void recognizedLexema(char *,char *);//receive token, value of token
void failRecognizeLexema();
void automatonForId();
void automatonForFloatNumbers();
void automatonForIntegersNumber();
void automatonForOperatorsArithmeticAssignmentIncrement();
void automatonForOperatorLogic();
void automatonForOperatorsAssignmentRelational();
void automatonForSpecialSymbol();
Node *getListOfReservedWords(char *);//receive file path to reserved words
short startAnalyzer(char *,char *,char *,char *);//receive file path to analyzer, file path to save errors, file path to save lexemas,file path to recerved words 
#endif
