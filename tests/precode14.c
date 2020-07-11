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

int Declaration();

int Declaration1Linha();

int Declaration_specifiers();

int Declaration_specifiers1Linha();

int Type_specifier();

int Init_declarator_list();

int Init_declarator_list1Hash();

int Init_declarator();

int Init_declarator1Linha();

// <*********** INICIO DO ANALISADOR SINTÁTICO DESCENDENTE RECURSIVO SEM RETROCESSO ***********>

//Implemente aqui a sua função getToken()

void getToken() {
	tk = 0;
	tklinha = 0;
	tkcoluna = 0;
}

//Declaration -> Declaration_specifiers Declaration1Linha 
int Declaration(){
	if(Declaration_specifiers()){
		if (Declaration1Linha()){
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//Declaration1Linha -> ; | Init_declarator_list ; 
int Declaration1Linha(){
	if(tk == tkSEMICOLON){// ;
		getToken();
		return 1;
	}
	else if(Init_declarator_list()){
		if(tk == tkSEMICOLON){// ;
			getToken();
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//Declaration_specifiers -> Type_specifier Declaration_specifiers1Linha 
int Declaration_specifiers(){
	if(Type_specifier()){
		if (Declaration_specifiers1Linha()){
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//Declaration_specifiers1Linha -> Declaration_specifiers | ? 
int Declaration_specifiers1Linha(){
	if (Declaration_specifiers()){
		return 1;
	}
	else {return 1;}
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
	else{return 0;}
}

//Init_declarator_list -> Init_declarator Init_declarator_list1Hash 
int Init_declarator_list(){
	if(Init_declarator()){
		if (Init_declarator_list1Hash()){
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//Init_declarator_list1Hash -> , Init_declarator Init_declarator_list1Hash | ? 
int Init_declarator_list1Hash(){
	if(tk == tkCOMMA){// ,
		getToken(); 
		if (Init_declarator()){
			if (Init_declarator_list1Hash()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else {return 1;}
}

//Init_declarator -> identifier Init_declarator1Linha 
int Init_declarator(){
	if(tk == tkIDENTIFIER){// identifier
		getToken(); 
		if (Init_declarator1Linha()){
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//Init_declarator1Linha -> = Assignment_expression | ? 
int Init_declarator1Linha(){
	if(tk == tkASSIGNENT){// =
		getToken(); 
		if (Assignment_expression()){
			return 1;
		}
		else{return 0;}
	}
	else {return 1;}
}

// <*********** FIM DO ANALISADOR SINTÁTICO DESCENDENTE RECURSIVO SEM RETROCESSO ***********>

int main(){
}