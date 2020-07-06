#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// DEFINE TOKENS

#define tkINTEGER_CONSTANT 1 // int_constant
#define tkFLOATING_POINT_CONSTANT 2 // float_constant
#define tkIDENTIFIER 3 // identifier
#define tkOPEN_BRACE 4 // {
#define tkCLOSE_BRACE 5 // }
#define tkSEMICOLON 6 // ;
#define tkCOMMA 7 // ,
#define tkASSIGNENT 8 // =
#define tkLOGICAL_NOT 9 // !
#define tkLOGICAL_OR 10 // ||
#define tkLOGICAL_AND 11 // &&
#define tkEQUALS 12 // ==
#define tkNOT_EQUALS 13 // !=
#define tkLESS 14 // <
#define tkGREATER 15 // >
#define tkLESS_OR_EQUAL 16 // <=
#define tkGREATER_OR_EQUAL 17 // >=
#define tkPLUS 18 // +
#define tkMINUS 19 // -
#define tkPRODUCT 20 // *
#define tkDIVISION 21 // /
#define tkMODULE 22 // %
#define tkINCREMENT 23 // ++
#define tkDECREMENT 24 // --
#define tkOPEN_PARENTHESIS 25 // (
#define tkCLOSE_PARENTHESIS 26 // )
#define tkPRODUCT_ASSIGNMENT 27 // *=
#define tkDIVISION_ASSIGNMENT 28 // /=
#define tkMODULE_ASSIGNENT 29 // %=
#define tkPLUS_ASSIGNENT 30 // +=
#define tkMINUS_ASSIGNENT 31 // -=
#define tkFOR 32 // for
#define tkWHILE 33 // while
#define tkIF 34 // if
#define tkDO 35 // do
#define tkELSE 36 // else
#define tkINT 37 // int
#define tkFLOAT 38 // float
#define tkCONTINUE 39 // continue
#define tkBREAK 40 // break

// Variáveis Globais <o>

int tk;
int tklinha = 0;
int tkcoluna = 0;

// <*********** INICIO DO ANALISADOR LÉXICO ***********>

// Implemente aqui seu analisador Léxico

// <*********** FIM DO ANALISADOR LÉXICO ***********>

// Protótipo das Funções do Analisador Sintático

int Program();

int Main_func();

int Compound_statement();

int Block_item_list();

int Block_item_list1Hash();

int Block_item();

int Declaration();

int Declaration_specifiers();

int Type_specifier();

int Init_declarator_list();

int Init_declarator_list1Hash();

int Init_declarator();

int Assignment_expression();

int Logical_or_expression();

int Logical_or_expression1Hash();

// <*********** INICIO DO ANALISADOR SINTÁTICO DESCENDENTE RECURSIVO COM RETROCESSO ***********>

//Implemente aqui a sua função getToken()

void getToken() {
	tk = 0;
	tklinha = 0;
	tkcoluna = 0;
}

//Implemente aqui a sua função marcaPosToken()

void marcaPosToken() {
}

//Implemente aqui a sua função restauraPosToken()

void restauraPosToken() {
}

//Program -> Main_func 
int Program(){
	if (Main_func()){
		return 1;
	}
	else {return 0;}
}

//Main_func -> int identifier ( ) Compound_statement 
int Main_func(){
	if(tk == tkINT){// int
		getToken();
		if(tk == tkIDENTIFIER){// identifier
			getToken();
			if(tk == tkOPEN_PARENTHESIS){// (
				getToken();
				if(tk == tkCLOSE_PARENTHESIS){// )
					getToken();
					if (Compound_statement()){
						return 1;
					}
					else {return 0;}
				}
				else {return 0;}
			}
			else {return 0;}
		}
		else {return 0;}
	}
	else {return 0;}
}

//Compound_statement -> { } | { Block_item_list } 
int Compound_statement(){
	if(tk == tkOPEN_BRACE){// {
		getToken();
		marcaPosToken(); // FUNÇÃO NECESSÁRIA CASO SEJA NECESSÁRIO RESTAURAR O TOKEN ANTERIOR
		if(tk == tkCLOSE_BRACE){// }
			return 1;
		}
		else if (Block_item_list()){
		if(tk == tkCLOSE_BRACE){// }
			return 1;
		}
		else {return 0;}
	}
}

//Block_item_list -> Block_item Block_item_list1Hash 
int Block_item_list(){
	if (Block_item()){
		if (Block_item_list1Hash()){
			return 1;
		}
		else {return 0;}
	}
	else {return 0;}
}

//Block_item_list1Hash -> Block_item Block_item_list1Hash | ? 
int Block_item_list1Hash(){
	if (Block_item()){
		if (Block_item_list1Hash()){
			return 1;
		}
		else {return 0;}
	}
	else {return 1;}
}

//Block_item -> Declaration | Statement 
int Block_item(){
	if (Declaration()){
		return 1;
	}
	else if (Statement()){
		return 1;
	}
	else {return 0;}
}

//Declaration -> Declaration_specifiers ; | Declaration_specifiers Init_declarator_list ; 
int Declaration(){
	if (Declaration_specifiers()){
	}
}

//Declaration_specifiers -> Type_specifier Declaration_specifiers | Type_specifier 
int Declaration_specifiers(){
	if (Type_specifier()){
	}
}

//Type_specifier -> int | float 
int Type_specifier(){
	if(tk == tkINT){// int
		getToken();
		return 1;
	}
	else if(tk == tkFLOAT){// float
		getToken();
		return 1;
	}
	else {return 0;}
}

//Init_declarator_list -> Init_declarator Init_declarator_list1Hash 
int Init_declarator_list(){
	if (Init_declarator()){
		if (Init_declarator_list1Hash()){
			return 1;
		}
		else {return 0;}
	}
	else {return 0;}
}

//Init_declarator_list1Hash -> , Init_declarator Init_declarator_list1Hash | ? 
int Init_declarator_list1Hash(){
	if(tk == tkCOMMA){// ,
		getToken();
		if (Init_declarator()){
			if (Init_declarator_list1Hash()){
				return 1;
			}
			else {return 0;}
		}
		else {return 0;}
	}
	else {return 1;}
}

//Init_declarator -> identifier = Assignment_expression | identifier 
int Init_declarator(){
	if(tk == tkIDENTIFIER){// identifier
		getToken();
		marcaPosToken(); // FUNÇÃO NECESSÁRIA CASO SEJA NECESSÁRIO RESTAURAR O TOKEN ANTERIOR
		if(tk == tkASSIGNENT){// =
			getToken();
			if (Assignment_expression()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
{return 1;}
		}
	}
}

//Assignment_expression -> Logical_or_expression | Unary_expression Assignment_operator Assignment_expression 
int Assignment_expression(){
	if (Logical_or_expression()){
		return 1;
	}
	else if (Unary_expression()){
		if (Assignment_operator()){
			if (Assignment_expression()){
				return 1;
			}
			else {return 0;}
		}
		else {return 0;}
	}
	else {return 0;}
}

//Logical_or_expression -> Logical_and_expression Logical_or_expression1Hash 
int Logical_or_expression(){
	if (Logical_and_expression()){
		if (Logical_or_expression1Hash()){
			return 1;
		}
		else {return 0;}
	}
	else {return 0;}
}

//Logical_or_expression1Hash -> Logical_or_expression1Hash | ? 
int Logical_or_expression1Hash(){
	if (Logical_or_expression1Hash()){
		return 1;
	}
	else {return 1;}
}

// <*********** FIM DO ANALISADOR SINTÁTICO DESCENDENTE RECURSIVO COM RETROCESSO ***********>

int main(){
}