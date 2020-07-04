#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// DEFINE TOKENS

#define tkCONSTANT 1 // constant
#define tkIDENTIFIER 2 // identifier
#define tkMAIN 3 // main
#define tkOPEN_BRACE 4 // {
#define tkCLOSE_BRACE 5 // }
#define tkSEMICOLON 6 // ;
#define tkCOMMA 7 // ,
#define tkASSIGNENT 8 // =
#define tkOPEN_BRACKET 9 // [
#define tkCLOSE_BRACKET 10 // ]
#define tkDOT 11 // .
#define tkLOGICAL_NOT 12 // !
#define tkLOGICAL_OR 13 // ||
#define tkLOGICAL_AND 14 // &&
#define tkEQUALS 15 // ==
#define tkNOT_EQUALS 16 // !=
#define tkLESS 17 // <
#define tkGREATER 18 // >
#define tkPLUS 19 // +
#define tkMINUS 20 // -
#define tkPRODUCT 21 // *
#define tkDIVISION 22 // /
#define tkMODULE 23 // %
#define tkINCREMENT 24 // ++
#define tkDECREMENT 25 // --
#define tkOPEN_PARENTHESIS 26 // (
#define tkCLOSE_PARENTHESIS 27 // )
#define tkPRODUCT_ASSIGNMENT 28 // *=
#define tkDIVISION_ASSIGNMENT 29 // /=
#define tkMODULE_ASSIGNENT 30 // %=
#define tkPLUS_ASSIGNENT 31 // +=
#define tkMINUS_ASSIGNENT 32 // -=
#define tkFOR 33 // for
#define tkWHILE 34 // while
#define tkIF 35 // if
#define tkDO 36 // do
#define tkELSE 37 // else
#define tkINT 38 // int
#define tkFLOAT 39 // float
#define tkCONTINUE 40 // continue
#define tkBREAK 41 // break

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

int Compound_statement'();

int Block_item_list();

int Block_item_list1Hash();

int Block_item();

int Declaration();

int Declaration'();

int Declaration_specifiers();

int Declaration_specifiers'();

int Type_specifier();

int Init_declarator_list();

int Init_declarator_list1Hash();

int Init_declarator();

int Init_declarator'();

int Initializer();

int Initializer'();

int Initializer_list();

int Initializer_list1Hash();

int Initializer_list1Hash();

int Assignment_expression();

int Designation();

int Designator_list();

int Designator_list1Hash();

int Designator();

int Conditional_expression();

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

//Main_func -> int main Compound_statement 
int Main_func(){
	if(tk == tkINT){// int
		getToken();
		if(tk == tkMAIN){// main
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

//Compound_statement -> { Compound_statement' 
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

//Declaration -> Declaration_specifiers Declaration' 
int Declaration(){
	if (Declaration_specifiers()){
	}
}

//Declaration_specifiers -> Type_specifier Declaration_specifiers' 
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

//Init_declarator -> identifier Init_declarator' 
int Init_declarator(){
	if(tk == tkIDENTIFIER){// identifier
		getToken();
		marcaPosToken(); // FUNÇÃO NECESSÁRIA CASO SEJA NECESSÁRIO RESTAURAR O TOKEN ANTERIOR
		if(tk == tkASSIGNENT){// =
			getToken();
			if (Initializer()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
{return 1;}
		}
	}
}

//Initializer -> { Initializer_list Initializer' | Assignment_expression 
int Initializer(){
	if(tk == tkOPEN_BRACE){// {
		getToken();
		if (Initializer_list()){
		}
		else if (Assignment_expression()){
		return 1;
	}
	else {return 0;}
}

//Initializer_list -> Designation Initializer Initializer_list1Hash | Initializer Initializer_list1Hash 
int Initializer_list(){
	if (Designation()){
		if (Initializer()){
			if (Initializer_list1Hash()){
				return 1;
			}
			else {return 0;}
		}
		else {return 0;}
	}
	else if (Initializer()){
		if (Initializer_list1Hash()){
			return 1;
		}
		else {return 0;}
	}
	else {return 0;}
}

//Initializer_list1Hash -> , Initializer_list1Hash | ? 
int Initializer_list1Hash(){
	if(tk == tkCOMMA){// ,
		getToken();
		marcaPosToken(); // FUNÇÃO NECESSÁRIA CASO SEJA NECESSÁRIO RESTAURAR O TOKEN ANTERIOR
		if (Designation()){
			if (Initializer()){
				if (Initializer_list1Hash()){
					return 1;
				}
				else{return 0;}
			}
			else{return 0;}
		}
		else{return 0;}
if (Initializer()){
					if (Initializer_list1Hash()){
						return 1;
					}
					else{return 0;}
				}
				else{return 0;}
			}
			else{return 0;}
		}
		else{return 0;}
				}
			}
		}
	}
	else {return 1;}
}

//Assignment_expression -> Conditional_expression | Unary_expression Assignment_operator Assignment_expression 
int Assignment_expression(){
	if (Conditional_expression()){
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

//Designation -> Designator_list = 
int Designation(){
	if (Designator_list()){
		if(tk == tkASSIGNENT){// =
			getToken();
			return 1;
		}
		else {return 0;}
	}
	else {return 0;}
}

//Designator_list -> Designator Designator_list1Hash 
int Designator_list(){
	if (Designator()){
		if (Designator_list1Hash()){
			return 1;
		}
		else {return 0;}
	}
	else {return 0;}
}

//Designator_list1Hash -> Designator Designator_list1Hash | ? 
int Designator_list1Hash(){
	if (Designator()){
		if (Designator_list1Hash()){
			return 1;
		}
		else {return 0;}
	}
	else {return 1;}
}

//Designator -> [ Conditional_expression ] | . identifier 
int Designator(){
	if(tk == tkOPEN_BRACKET){// [
		getToken();
		if (Conditional_expression()){
			if(tk == tkCLOSE_BRACKET){// ]
				getToken();
				return 1;
			}
			else {return 0;}
		}
		else {return 0;}
	}
	else if(tk == tkDOT){// .
		getToken();
		if(tk == tkIDENTIFIER){// identifier
			getToken();
			return 1;
		}
		else {return 0;}
	}
	else {return 0;}
}

//Conditional_expression -> Logical_or_expression 
int Conditional_expression(){
	if (Logical_or_expression()){
		return 1;
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