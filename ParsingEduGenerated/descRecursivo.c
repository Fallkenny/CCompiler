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

int Program();

int Main_func();

int Compound_statement();

int Compound_statement1Linha();

int Block_item_list();

int Block_item_list1Hash();

int Block_item();

int Declaration();

int Declaration1Linha();

int Declaration_specifiers();

int Declaration_specifiers1Linha();

int Type_specifier();

int Init_declarator_list();

int Init_declarator_list1Hash();

int Init_declarator();

int Init_declarator1Linha();

int Assignment_expression();

int Assignment_expression1Linha();

int Logical_or_expression();

int Logical_or_expression1Hash();

int Logical_and_expression();

int Logical_and_expression1Hash();

int Equality_expression();

int Equality_expression1Hash();

int Relational_expression();

int Relational_expression1Hash();

int Relational_operator();

int Additive_expression();

int Additive_expression1Hash();

int Multiplicative_expression();

int Multiplicative_expression1Hash();

int Unary_expression();

int Unary_operator();

int Postfix_expression();

int Postfix_expression1Hash();

int Primary_expression();

int Constant();

int Assignment_operator();

int Statement();

int Expression_statement();

int Expression();

int Expression1Hash();

int If_statement();

int If_statement1Linha();

int Iteration_statement();

int While_statement();

int Do_while_statement();

int For_statement();

int For_statement2Linha();

int For_statement3Linha();

int For_statement1Linha();

int Jump_statement();

// <*********** INICIO DO ANALISADOR SINTÁTICO DESCENDENTE RECURSIVO SEM RETROCESSO ***********>

//Implemente aqui a sua função getToken()

void getToken() {
	tk = 0;
	tklinha = 0;
	tkcoluna = 0;
}

//Program -> Main_func 
int Program(){
	if (Main_func()){
		return 1;
	}
	else{return 0;}
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
					else{return 0;}
				}
				else{return 0;}
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else{return 0;}
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

//Assignment_expression -> Logical_or_expression Assignment_expression1Linha 
int Assignment_expression(){
	if(Logical_or_expression()){
		if (Assignment_expression1Linha()){
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//Assignment_expression1Linha -> Assignment_operator Assignment_expression | ? 
int Assignment_expression1Linha(){
	if(Assignment_operator()){
		if (Assignment_expression()){
			return 1;
		}
		else{return 0;}
	}
	else {return 1;}
}

//Logical_or_expression -> Logical_and_expression Logical_or_expression1Hash 
int Logical_or_expression(){
	if(Logical_and_expression()){
		if (Logical_or_expression1Hash()){
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//Logical_or_expression1Hash -> ii Logical_and_expression Logical_or_expression1Hash | ? 
int Logical_or_expression1Hash(){
	if(tk == tkLOGICAL_OR){// ii
		getToken(); 
		if (Logical_and_expression()){
			if (Logical_or_expression1Hash()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else {return 1;}
}

//Logical_and_expression -> Equality_expression Logical_and_expression1Hash 
int Logical_and_expression(){
	if(Equality_expression()){
		if (Logical_and_expression1Hash()){
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//Logical_and_expression1Hash -> && Equality_expression Logical_and_expression1Hash | ? 
int Logical_and_expression1Hash(){
	if(tk == tkLOGICAL_AND){// &&
		getToken(); 
		if (Equality_expression()){
			if (Logical_and_expression1Hash()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else {return 1;}
}

//Equality_expression -> Relational_expression Equality_expression1Hash 
int Equality_expression(){
	if(Relational_expression()){
		if (Equality_expression1Hash()){
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//Equality_expression1Hash -> == Relational_expression Equality_expression1Hash | != Relational_expression Equality_expression1Hash | ? 
int Equality_expression1Hash(){
	if(tk == tkEQUALS){// ==
		getToken(); 
		if (Relational_expression()){
			if (Equality_expression1Hash()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else if(tk == tkNOT_EQUALS){// !=
		getToken(); 
		if (Relational_expression()){
			if (Equality_expression1Hash()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else {return 1;}
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

//Additive_expression -> Multiplicative_expression Additive_expression1Hash 
int Additive_expression(){
	if(Multiplicative_expression()){
		if (Additive_expression1Hash()){
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//Additive_expression1Hash -> + Multiplicative_expression Additive_expression1Hash | - Multiplicative_expression Additive_expression1Hash | ? 
int Additive_expression1Hash(){
	if(tk == tkPLUS){// +
		getToken(); 
		if (Multiplicative_expression()){
			if (Additive_expression1Hash()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else if(tk == tkMINUS){// -
		getToken(); 
		if (Multiplicative_expression()){
			if (Additive_expression1Hash()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else {return 1;}
}

//Multiplicative_expression -> Unary_expression Multiplicative_expression1Hash 
int Multiplicative_expression(){
	if(Unary_expression()){
		if (Multiplicative_expression1Hash()){
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//Multiplicative_expression1Hash -> * Unary_expression Multiplicative_expression1Hash | / Unary_expression Multiplicative_expression1Hash | % Unary_expression Multiplicative_expression1Hash | ? 
int Multiplicative_expression1Hash(){
	if(tk == tkPRODUCT){// *
		getToken(); 
		if (Unary_expression()){
			if (Multiplicative_expression1Hash()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else if(tk == tkDIVISION){// /
		getToken(); 
		if (Unary_expression()){
			if (Multiplicative_expression1Hash()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else if(tk == tkMODULE){// %
		getToken(); 
		if (Unary_expression()){
			if (Multiplicative_expression1Hash()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else {return 1;}
}

//Unary_expression -> ++ Unary_expression | -- Unary_expression | Unary_operator Unary_expression | Postfix_expression 
int Unary_expression(){
	if(tk == tkINCREMENT){// ++
		getToken(); 
		if (Unary_expression()){
			return 1;
		}
		else{return 0;}
	}
	else if(tk == tkDECREMENT){// --
		getToken(); 
		if (Unary_expression()){
			return 1;
		}
		else{return 0;}
	}
	else if(Unary_operator()){
		if (Unary_expression()){
			return 1;
		}
		else{return 0;}
	}
	else if (Postfix_expression()){
		return 1;
	}
	else{return 0;}
}

//Unary_operator -> + | - | ! 
int Unary_operator(){
	if(tk == tkPLUS){// +
		getToken();
		return 1;
	}
	else if(tk == tkMINUS){// -
		getToken();
		return 1;
	}
	else if(tk == tkLOGICAL_NOT){// !
		getToken();
		return 1;
	}
	else{return 0;}
}

//Postfix_expression -> Primary_expression Postfix_expression1Hash 
int Postfix_expression(){
	if(Primary_expression()){
		if (Postfix_expression1Hash()){
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//Postfix_expression1Hash -> ++ Postfix_expression1Hash | -- Postfix_expression1Hash | ? 
int Postfix_expression1Hash(){
	if(tk == tkINCREMENT){// ++
		getToken(); 
		if (Postfix_expression1Hash()){
			return 1;
		}
		else{return 0;}
	}
	else if(tk == tkDECREMENT){// --
		getToken(); 
		if (Postfix_expression1Hash()){
			return 1;
		}
		else{return 0;}
	}
	else {return 1;}
}

//Primary_expression -> identifier | Constant 
int Primary_expression(){
	if(tk == tkIDENTIFIER){// identifier
		getToken();
		return 1;
	}
	else if (Constant()){
		return 1;
	}
	else{return 0;}
}

//Constant -> int_constant | float_constant 
int Constant(){
	if(tk == tkINTEGER_CONSTANT){// int_constant
		getToken();
		return 1;
	}
	else if(tk == tkFLOATING_POINT_CONSTANT){// float_constant
		getToken();
		return 1;
	}
	else{return 0;}
}

//Assignment_operator -> = | *= | /= | %= | += | -= 
int Assignment_operator(){
	if(tk == tkASSIGNENT){// =
		getToken();
		return 1;
	}
	else if(tk == tkPRODUCT_ASSIGNMENT){// *=
		getToken();
		return 1;
	}
	else if(tk == tkDIVISION_ASSIGNMENT){// /=
		getToken();
		return 1;
	}
	else if(tk == tkMODULE_ASSIGNENT){// %=
		getToken();
		return 1;
	}
	else if(tk == tkPLUS_ASSIGNENT){// +=
		getToken();
		return 1;
	}
	else if(tk == tkMINUS_ASSIGNENT){// -=
		getToken();
		return 1;
	}
	else{return 0;}
}

//Statement -> Compound_statement | Expression_statement | If_statement | Iteration_statement | Jump_statement 
int Statement(){
	if (Compound_statement()){
		return 1;
	}
	else if (Expression_statement()){
		return 1;
	}
	else if (If_statement()){
		return 1;
	}
	else if (Iteration_statement()){
		return 1;
	}
	else if (Jump_statement()){
		return 1;
	}
	else{return 0;}
}

//Expression_statement -> ; | Expression ; 
int Expression_statement(){
	if(tk == tkSEMICOLON){// ;
		getToken();
		return 1;
	}
	else if(Expression()){
		if(tk == tkSEMICOLON){// ;
			getToken();
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//Expression -> Assignment_expression Expression1Hash 
int Expression(){
	if(Assignment_expression()){
		if (Expression1Hash()){
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//Expression1Hash -> , Assignment_expression Expression1Hash | ? 
int Expression1Hash(){
	if(tk == tkCOMMA){// ,
		getToken(); 
		if (Assignment_expression()){
			if (Expression1Hash()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else {return 1;}
}

//If_statement -> if ( Expression ) Statement If_statement1Linha 
int If_statement(){
	if(tk == tkIF){// if
		getToken(); 
		if(tk == tkOPEN_PARENTHESIS){// (
			getToken();
			if (Expression()){
				if(tk == tkCLOSE_PARENTHESIS){// )
					getToken();
					if (Statement()){
						if (If_statement1Linha()){
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
		else{return 0;}
	}
	else{return 0;}
}

//If_statement1Linha -> else Statement | ? 
int If_statement1Linha(){
	if(tk == tkELSE){// else
		getToken(); 
		if (Statement()){
			return 1;
		}
		else{return 0;}
	}
	else {return 1;}
}

//Iteration_statement -> While_statement | Do_while_statement | For_statement 
int Iteration_statement(){
	if (While_statement()){
		return 1;
	}
	else if (Do_while_statement()){
		return 1;
	}
	else if (For_statement()){
		return 1;
	}
	else{return 0;}
}

//While_statement -> while ( Expression ) Statement 
int While_statement(){
	if(tk == tkWHILE){// while
		getToken(); 
		if(tk == tkOPEN_PARENTHESIS){// (
			getToken();
			if (Expression()){
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
		else{return 0;}
	}
	else{return 0;}
}

//Do_while_statement -> do Statement while ( Expression ) ; 
int Do_while_statement(){
	if(tk == tkDO){// do
		getToken(); 
		if (Statement()){
			if(tk == tkWHILE){// while
				getToken();
				if(tk == tkOPEN_PARENTHESIS){// (
					getToken();
					if (Expression()){
						if(tk == tkCLOSE_PARENTHESIS){// )
							getToken();
							if(tk == tkSEMICOLON){// ;
								getToken();
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
			else{return 0;}
		}
		else{return 0;}
	}
	else{return 0;}
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

//Jump_statement -> continue ; | break ; 
int Jump_statement(){
	if(tk == tkCONTINUE){// continue
		getToken(); 
		if(tk == tkSEMICOLON){// ;
			getToken();
			return 1;
		}
		else{return 0;}
	}
	else if(tk == tkBREAK){// break
		getToken(); 
		if(tk == tkSEMICOLON){// ;
			getToken();
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

// <*********** FIM DO ANALISADOR SINTÁTICO DESCENDENTE RECURSIVO SEM RETROCESSO ***********>

int main(){
}