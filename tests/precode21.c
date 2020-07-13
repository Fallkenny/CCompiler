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
#define tkEOF 41 // eof

// Variáveis Globais <o>

int tk;
int tklinha = 0;
int tkcoluna = 0;

// <*********** INICIO DO ANALISADOR LÉXICO ***********>

// Implemente aqui seu analisador Léxico

// <*********** FIM DO ANALISADOR LÉXICO ***********>

// Protótipo das Funções do Analisador Sintático

int For_statement();

int For_statement2Linha();

int For_statement3Linha();

int For_statement1Linha();

// <*********** INICIO DO ANALISADOR SINTÁTICO DESCENDENTE RECURSIVO SEM RETROCESSO ***********>

//Implemente aqui a sua função getToken()

void getToken() {
	tk = 0;
	tklinha = 0;
	tkcoluna = 0;
}

//For_statement -> for ( For_statement2Linha 
int For_statement(){
	if(tk == tkFOR){// for
		getToken(); 
		if(tk == tkOPEN_PARENTHESIS){// (
			getToken();
			if (For_statement2Linha()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else{return 0;}
}

//For_statement2Linha -> Expression_statement Expression_statement For_statement1Linha | Declaration Expression_statement For_statement3Linha 
int For_statement2Linha(){
	if(Expression_statement()){
		if (Expression_statement()){
			if (For_statement1Linha()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else if(Declaration()){
		if (Expression_statement()){
			if (For_statement3Linha()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else{return 0;}
}

//For_statement3Linha -> ) Statement | Expression ) Statement 
int For_statement3Linha(){
	if(tk == tkCLOSE_PARENTHESIS){// )
		getToken(); 
		if (Statement()){
			return 1;
		}
		else{return 0;}
	}
	else if(Expression()){
		if(tk == tkCLOSE_PARENTHESIS){// )
			getToken();
			if (Statement()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else{return 0;}
}

//For_statement1Linha -> ) Statement | Expression ) Statement 
int For_statement1Linha(){
	if(tk == tkCLOSE_PARENTHESIS){// )
		getToken(); 
		if (Statement()){
			return 1;
		}
		else{return 0;}
	}
	else if(Expression()){
		if(tk == tkCLOSE_PARENTHESIS){// )
			getToken();
			if (Statement()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else{return 0;}
}

// <*********** FIM DO ANALISADOR SINTÁTICO DESCENDENTE RECURSIVO SEM RETROCESSO ***********>

int main(){
}