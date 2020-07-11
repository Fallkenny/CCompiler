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
#define tkLOGICAL_OR 10 // ii
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

int Relational_expression();

int Relational_expression1Hash();

int Relational_operator();

// <*********** INICIO DO ANALISADOR SINTÁTICO DESCENDENTE RECURSIVO SEM RETROCESSO ***********>

//Implemente aqui a sua função getToken()

void getToken() {
	tk = 0;
	tklinha = 0;
	tkcoluna = 0;
}

//Relational_expression -> Additive_expression Relational_expression1Hash 
int Relational_expression(){
	if(Additive_expression()){
		if (Relational_expression1Hash()){
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//Relational_expression1Hash -> Relational_operator Additive_expression Relational_expression1Hash | ? 
int Relational_expression1Hash(){
	if(Relational_operator()){
		if (Additive_expression()){
			if (Relational_expression1Hash()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else {return 1;}
}

//Relational_operator -> > | < | >= | <= 
int Relational_operator(){
	if(tk == tkGREATER){// >
		getToken();
		return 1;
	}
	else if(tk == tkLESS){// <
		getToken();
		return 1;
	}
	else if(tk == tkGREATER_OR_EQUAL){// >=
		getToken();
		return 1;
	}
	else if(tk == tkLESS_OR_EQUAL){// <=
		getToken();
		return 1;
	}
	else{return 0;}
}

// <*********** FIM DO ANALISADOR SINTÁTICO DESCENDENTE RECURSIVO SEM RETROCESSO ***********>

int main(){
}