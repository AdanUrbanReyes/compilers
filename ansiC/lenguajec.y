%{
#include <stdlib.h>
#include <stdio.h>
extern FILE *yyin;
char *idRecognized;
%}
%token IDENTIFIER CONSTANT STRING_LITERAL SIZEOF
%token PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP
%token AND_OP OR_OP MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN
%token SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN
%token XOR_ASSIGN OR_ASSIGN TYPE_NAME

%token TYPEDEF EXTERN STATIC AUTO REGISTER
%token CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE CONST VOLATILE VOID
%token STRUCT UNION ENUM ELLIPSIS

%token CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN

%start translation_unit
%%

primary_expression
	: IDENTIFIER 
	| CONSTANT
	| STRING_LITERAL
	| '(' expression ')'
	;

postfix_expression
	: primary_expression
	| postfix_expression '[' expression ']'
	| postfix_expression '(' ')'
	| postfix_expression '(' argument_expression_list ')'
	| postfix_expression '.' IDENTIFIER
	| postfix_expression PTR_OP IDENTIFIER
	| postfix_expression INC_OP
	| postfix_expression DEC_OP
	;

argument_expression_list
	: assignment_expression
	| argument_expression_list ',' assignment_expression
	;

unary_expression
	: postfix_expression
	| INC_OP unary_expression
	| DEC_OP unary_expression
	| unary_operator cast_expression
	| SIZEOF unary_expression
	| SIZEOF '(' type_name ')'
	;

unary_operator
	: '&'
	| '*'
	| '+'
	| '-'
	| '~'
	| '!'
	;

cast_expression
	: unary_expression
	| '(' type_name ')' cast_expression
	;

multiplicative_expression
	: cast_expression
	| multiplicative_expression '*' cast_expression
	| multiplicative_expression '/' cast_expression
	| multiplicative_expression '%' cast_expression
	;

additive_expression
	: multiplicative_expression
	| additive_expression '+' multiplicative_expression
	| additive_expression '-' multiplicative_expression
	;

shift_expression
	: additive_expression
	| shift_expression LEFT_OP additive_expression
	| shift_expression RIGHT_OP additive_expression
	;

relational_expression
	: shift_expression
	| relational_expression '<' shift_expression
	| relational_expression '>' shift_expression
	| relational_expression LE_OP shift_expression
	| relational_expression GE_OP shift_expression
	;

equality_expression
	: relational_expression
	| equality_expression EQ_OP relational_expression
	| equality_expression NE_OP relational_expression
	;

and_expression
	: equality_expression
	| and_expression '&' equality_expression
	;

exclusive_or_expression
	: and_expression {printf("exclusive_or_expression|and_expression %s\n",idRecognized);}
	| exclusive_or_expression '^' and_expression {printf("exclusive_or_expression|exclusive_or_expression|^|and_expression %s\n",idRecognized);}
	;

inclusive_or_expression
	: exclusive_or_expression {printf("inclusive_or_expresion|exclusive_or_expression %s\n",idRecognized);}
	| inclusive_or_expression '|' exclusive_or_expression {printf("inclusive_or_expression|inclusive_or_expression|exclusive_or_expression %s\n",idRecognized);}
	;

logical_and_expression
	: inclusive_or_expression {printf("logical_and_expression|inclusive_or_expression %s\n",idRecognized);}
	| logical_and_expression AND_OP inclusive_or_expression {printf("logical_and_expression|logical_and_expression|AND_OP|inclusive_or_expression %s\n",idRecognized);}
	;

logical_or_expression
	: logical_and_expression {printf("logical_or_expression|logical_and_expression %s\n",idRecognized);}
	| logical_or_expression OR_OP logical_and_expression {printf("logical_or_expression|logical_or_expression|OR_OP|logical_and_expression %s\n",idRecognized);}
	;

conditional_expression
	: logical_or_expression {printf("conditional_expressiion|logical_or_expression %s\n",idRecognized);}
	| logical_or_expression '?' expression ':' conditional_expression {printf("logical_or_expression|?|expression|:|conditional_expression %s\n",idRecognized);}
	;

assignment_expression
	: conditional_expression
	| unary_expression assignment_operator assignment_expression
	;

assignment_operator
	: '='
	| MUL_ASSIGN
	| DIV_ASSIGN
	| MOD_ASSIGN
	| ADD_ASSIGN
	| SUB_ASSIGN
	| LEFT_ASSIGN
	| RIGHT_ASSIGN
	| AND_ASSIGN
	| XOR_ASSIGN
	| OR_ASSIGN
	;

expression
	: assignment_expression
	| expression ',' assignment_expression
	;

constant_expression
	: conditional_expression {printf("constant_expression|conditional_expression %s\n",idRecognized);}
	;

declaration
	: declaration_specifiers ';' {printf("declaration|declaration_specifiers = %s\n",idRecognized);}
	| declaration_specifiers init_declarator_list ';'{printf("declaration|declaration_specifiers|init_declarator_list = %s\n",idRecognized);}
	;

declaration_specifiers
	: storage_class_specifier{printf("declaration_specifiers|storage_class_specifier %s\n",idRecognized);}
	| storage_class_specifier declaration_specifiers{printf("declaration_specifiers|storage_class_specifier|declaration_specifiers %s\n",idRecognized);}
	| type_specifier{printf("declaration_specifiers|type_specifier %s\n",idRecognized);}
	| type_specifier declaration_specifiers{printf("declaration_spefcifiers|type_specifier|declaration_specifiers %s\n",idRecognized);}
	| type_qualifier{printf("declaration_specifiers|type_qualifer %s\n",idRecognized);}
	| type_qualifier declaration_specifiers{printf("declaration_specifiers|type_qualifier|declaration_specifiers %s\n",idRecognized);}
	;

init_declarator_list
	: init_declarator{printf("init_declarator_list|init_declarator %s\n",idRecognized);}
	| init_declarator_list ',' init_declarator {printf("init_declarator_list|init_declarator_list| , | init_declarator %s\n",idRecognized);}
	;

init_declarator
	: declarator {printf("init_declarator|declarator %s\n",idRecognized);}
	| declarator '=' initializer {printf("init_declarator|declarator| = | initializer %s\n",idRecognized);}
	;

storage_class_specifier
	: TYPEDEF
	| EXTERN
	| STATIC
	| AUTO
	| REGISTER
	;

type_specifier
	: VOID
	| CHAR
	| SHORT 
	| INT
	| LONG
	| FLOAT
	| DOUBLE
	| SIGNED
	| UNSIGNED
	| struct_or_union_specifier
	| enum_specifier
	| TYPE_NAME
	;

struct_or_union_specifier
	: struct_or_union IDENTIFIER '{' struct_declaration_list '}'
	| struct_or_union '{' struct_declaration_list '}'
	| struct_or_union IDENTIFIER
	;

struct_or_union
	: STRUCT
	| UNION
	;

struct_declaration_list
	: struct_declaration
	| struct_declaration_list struct_declaration
	;

struct_declaration
	: specifier_qualifier_list struct_declarator_list ';'
	;

specifier_qualifier_list
	: type_specifier specifier_qualifier_list
	| type_specifier
	| type_qualifier specifier_qualifier_list
	| type_qualifier
	;

struct_declarator_list
	: struct_declarator
	| struct_declarator_list ',' struct_declarator
	;

struct_declarator
	: declarator
	| ':' constant_expression
	| declarator ':' constant_expression
	;

enum_specifier
	: ENUM '{' enumerator_list '}'
	| ENUM IDENTIFIER '{' enumerator_list '}'
	| ENUM IDENTIFIER
	;

enumerator_list
	: enumerator
	| enumerator_list ',' enumerator
	;

enumerator
	: IDENTIFIER
	| IDENTIFIER '=' constant_expression
	;

type_qualifier
	: CONST {printf("type_qualifier|CONST %s\n",idRecognized);}
	| VOLATILE {printf("type_qualifier|VOLATILE %s\n",idRecognized);}
	;

declarator
	: pointer direct_declarator {printf("declarator|pointer|direct_declarator %s\n",idRecognized);}
	| direct_declarator {printf("declarator|direct_declarator %s\n",idRecognized);}
	;

direct_declarator
	: IDENTIFIER {printf("direct_declarator|IDENTIFIER %s\n",idRecognized);}
	| '(' declarator ')' {printf("direct_declarator|(|declarator|) %s\n",idRecognized);}
	| direct_declarator '[' constant_expression ']'{printf("direct_declarator|[|constant_expression|] %s\n",idRecognized);}
	| direct_declarator '[' ']'{printf("direct_declarator| direct_declarator|[|]%s\n",idRecognized);}
	| direct_declarator '(' parameter_type_list ')'{printf("direct_declarator|(|paramter_type_list|) %s\n",idRecognized);}
	| direct_declarator '(' identifier_list ')' {printf("direct_declarator|(|identifier_list|) %s\n",idRecognized);}
	| direct_declarator '(' ')' {printf("direct_declarator|(|) %s\n",idRecognized);}
	;

pointer
	: '*' {printf("pointer|* %s\n",idRecognized);}
	| '*' type_qualifier_list {printf("pointer|type_qualifer_list %s\n",idRecognized);}
	| '*' pointer {printf("pointer|*|pointer %s\n",idRecognized);}
	| '*' type_qualifier_list pointer {printf("pointer|type_qualifier_list|pointer %s\n",idRecognized);}
	;

type_qualifier_list
	: type_qualifier {printf("type_qualifer_list|type_qualifer %s\n",idRecognized);}
	| type_qualifier_list type_qualifier {printf("type_qualifier_list|type_qualifier_list|type_qualifier %s\n",idRecognized);}
	;


parameter_type_list
	: parameter_list
	| parameter_list ',' ELLIPSIS
	;

parameter_list
	: parameter_declaration
	| parameter_list ',' parameter_declaration
	;

parameter_declaration
	: declaration_specifiers declarator
	| declaration_specifiers abstract_declarator
	| declaration_specifiers
	;

identifier_list
	: IDENTIFIER
	| identifier_list ',' IDENTIFIER
	;

type_name
	: specifier_qualifier_list
	| specifier_qualifier_list abstract_declarator
	;

abstract_declarator
	: pointer
	| direct_abstract_declarator
	| pointer direct_abstract_declarator
	;

direct_abstract_declarator
	: '(' abstract_declarator ')'
	| '[' ']'
	| '[' constant_expression ']'
	| direct_abstract_declarator '[' ']'
	| direct_abstract_declarator '[' constant_expression ']'
	| '(' ')'
	| '(' parameter_type_list ')'
	| direct_abstract_declarator '(' ')'
	| direct_abstract_declarator '(' parameter_type_list ')'
	;

initializer
	: assignment_expression {printf("initializer| assignment_expression %s\n",idRecognized);}
	| '{' initializer_list '}'{printf("initializer|{|initializer_list|} %s\n",idRecognized);}
	| '{' initializer_list ',' '}'{printf("initializer|{|initializer_list|.|} %s\n",idRecognized);}
	;

initializer_list
	: initializer {printf("initializer_list|initializer %s\n",idRecognized);}
	| initializer_list ',' initializer {printf("initializer_list|,|initializer %s\n",idRecognized);}
	;

statement
	: labeled_statement
	| compound_statement
	| expression_statement
	| selection_statement
	| iteration_statement
	| jump_statement
	;

labeled_statement
	: IDENTIFIER ':' statement
	| CASE constant_expression ':' statement
	| DEFAULT ':' statement
	;

compound_statement
	: '{' '}'
	| '{' statement_list '}'
	| '{' declaration_list '}'
	| '{' declaration_list statement_list '}'
	;

declaration_list
	: declaration
	| declaration_list declaration
	;

statement_list
	: statement
	| statement_list statement
	;

expression_statement
	: ';'
	| expression ';'
	;

selection_statement
	: IF '(' expression ')' statement
	| IF '(' expression ')' statement ELSE statement
	| SWITCH '(' expression ')' statement
	;

iteration_statement
	: WHILE '(' expression ')' statement
	| DO statement WHILE '(' expression ')' ';'
	| FOR '(' expression_statement expression_statement ')' statement
	| FOR '(' expression_statement expression_statement expression ')' statement
	;

jump_statement
	: GOTO IDENTIFIER ';'
	| CONTINUE ';'
	| BREAK ';'
	| RETURN ';'
	| RETURN expression ';'
	;

translation_unit
	: external_declaration
	| translation_unit external_declaration
	;

external_declaration
	: function_definition {printf("externar_declaration|declaration = %s\n",idRecognized);}
	| declaration {printf("externar_declaration|declaration = %s\n",idRecognized);}
	;

function_definition
	: declaration_specifiers declarator declaration_list compound_statement {printf("function_definicion|declaration_specifiers|declarator|declaration_list|compound_statement %s\n",idRecognized);}
	| declaration_specifiers declarator compound_statement{printf("function_definicion|declaration_specifiers|declarator|compound_statement %s\n",idRecognized);}
	| declarator declaration_list compound_statement {printf("function_definicion|declarator|declaration_list|compound_statement %s\n",idRecognized);}
	| declarator compound_statement {printf("function_definicion|declarator|compound_statement %s\n",idRecognized);}
	;

%%

extern char yytext[];
extern int column;

int main(int ari,char **arc){
//        if(ari < 2){
//                printf("ERROR ejecute como %s archivoParaAnalizar\n",arc[0]);
  //              return 1;
   //     }
      yyin=fopen(arc[1],"r");
     //   yyin = stdin;
     //   yylex();
	yyparse();
	printf("BIEN\n");
        return 0;
}


yyerror(s) char *s;
{
	fflush(stdout);
	printf("MAL\n");
//	printf("my error = \n%*s\n%*s\n", column, "^", column, s);
	exit(0);
}
