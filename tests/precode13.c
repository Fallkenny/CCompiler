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

// Vari�veis Globais <o>

int tk;
int tklinha = 0;
int tkcoluna = 0;

// <*********** INICIO DO ANALISADOR L�XICO ***********>

// Implemente aqui seu analisador L�xico

// <*********** FIM DO ANALISADOR L�XICO ***********>

// Prot�tipo das Fun��es do Analisador Sint�tico

int Compound_statement();

int Compound_statement1Linha();

int Block_item_list();

int Block_item_list1Hash();

int Block_item();

// <*********** INICIO DO ANALISADOR SINT�TICO DESCENDENTE RECURSIVO SEM RETROCESSO ***********>

//Implemente aqui a sua fun��o getToken()

void getToken() {
	tk = 0;
	tklinha = 0;
	tkcoluna = 0;
}

//Compound_statement -> { Compound_statement1Linha 
int Compound_statement(){
	if(tk == tkOPEN_BRACE){// {
		getToken(); 
		if (Compound_statement1Linha()){
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//Compound_statement1Linha -> } | Block_item_list } 
int Compound_statement1Linha(){
	if(tk == tkCLOSE_BRACE){// }
		getToken();
		return 1;
	}
	else if(Block_item_list()){
		if(tk == tkCLOSE_BRACE){// }
			getToken();
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//Block_item_list -> Block_item Block_item_list1Hash 
int Block_item_list(){
	if(Block_item()){
		if (Block_item_list1Hash()){
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//Block_item_list1Hash -> Block_item Block_item_list1Hash | ? 
int Block_item_list1Hash(){
	if(Block_item()){
		if (Block_item_list1Hash()){
			return 1;
		}
		else{return 0;}
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
	else{return 0;}
}

// <*********** FIM DO ANALISADOR SINT�TICO DESCENDENTE RECURSIVO SEM RETROCESSO ***********>

int main(){
}