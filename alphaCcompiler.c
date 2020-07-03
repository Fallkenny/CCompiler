#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// DEFINE TOKENS

#define CONSTANT 1 // constant
#define MAIN_FUNC 2 // int main
#define OPEN_BRACE 3 // {
#define CLOSE_BRACE 4 // }
#define SEMICOLON 5 // ;
#define COMMA 6 // ,
#define ASSIGNENT 7 // =
#define OPEN_BRACKET 8 // [
#define CLOSE_BRACKET 9 // ]
#define DOT 10 // .
#define LOGICAL_NOT 11 // !
#define LOGICAL_OR 12 // ||
#define LOGICAL_AND 13 // &&
#define EQUALS 14 // ==
#define NOT_EQUALS 15 // !=
#define LESS 16 // <
#define GREATER 17 // >
#define PLUS 18 // +
#define MINUS 19 // -
#define PRODUCT 20 // *
#define DIVISION 21 // /
#define MODULE 22 // %
#define INCREMENT 23 // ++
#define DECREMENT 24 // --
#define OPEN_PARENTHESIS 25 // (
#define CLOSE_PARENTHESIS 26 // )
#define PRODUCT_ASSIGNMENT 27 // *=
#define DIVISION_ASSIGNMENT 28 // /=
#define MODULE_ASSIGNENT 29 // %=
#define PLUS_ASSIGNENT 30 // +=
#define MINUS_ASSIGNENT 31 // -=
#define FOR 32 // for
#define WHILE 33 // while
#define IF 34 // if
#define DO 35 // do
#define ELSE 36 // else
#define INT 37 // int
#define FLOAT 38 // float
#define CONTINUE 39 // continue
#define BREAK 40 // break

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

int Block_item();

int Declaration();

int Declaration_specifiers();

int Type_specifier();

int Init_declarator_list();

int Init_declarator();

int Initializer();

int Initializer_list();

int Assignment_expression();

int Designation();

int Designator_list();

int Designator();

int Conditional_expression();

int Logical_or_expression();

int Logical_and_expression();

int Equality_expression();

int Relational_expression();

int Additive_expression();

int Multiplicative_expression();

int Unary_expression();

int Unary_operator();

int Postfix_expression();

int Primary_expression();

int Assignment_operator();

int Statement();

int Expression_statement();

int Expression();

int If_statement();

int Iteration_statement();

int While_statement();

int Do_while_statement();

int For_statement();

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

//Main_func -> MAIN_FUNC Compound_statement 
int Main_func(){
	if(MAIN_FUNC()){
		if (Compound_statement()){
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//Compound_statement -> OPEN_BRACE CLOSE_BRACE | OPEN_BRACE Block_item_list CLOSE_BRACE 
int Compound_statement(){
	if(OPEN_BRACE()){
		if (CLOSE_BRACE()){
			return 1;
		}
		else{return 0;}
	}
	else if(OPEN_BRACE()){
		if (Block_item_list()){
			if (CLOSE_BRACE()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else{return 0;}
}

//Block_item_list -> Block_item | Block_item_list Block_item 
int Block_item_list(){
	if (Block_item()){
		return 1;
	}
	else if(Block_item_list()){
		if (Block_item()){
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
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

//Declaration -> Declaration_specifiers SEMICOLON | Declaration_specifiers Init_declarator_list SEMICOLON 
int Declaration(){
	if(Declaration_specifiers()){
		if (SEMICOLON()){
			return 1;
		}
		else{return 0;}
	}
	else if(Declaration_specifiers()){
		if (Init_declarator_list()){
			if (SEMICOLON()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else{return 0;}
}

//Declaration_specifiers -> Type_specifier Declaration_specifiers | Type_specifier 
int Declaration_specifiers(){
	if(Type_specifier()){
		if (Declaration_specifiers()){
			return 1;
		}
		else{return 0;}
	}
	else if (Type_specifier()){
		return 1;
	}
	else{return 0;}
}

//Type_specifier -> INT | FLOAT 
int Type_specifier(){
	if (INT()){
		return 1;
	}
	else if (FLOAT()){
		return 1;
	}
	else{return 0;}
}

//Init_declarator_list -> Init_declarator | Init_declarator_list COMMA Init_declarator 
int Init_declarator_list(){
	if (Init_declarator()){
		return 1;
	}
	else if(Init_declarator_list()){
		if (COMMA()){
			if (Init_declarator()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else{return 0;}
}

//Init_declarator -> IDENTIFIER ASSIGNENT Initializer | IDENTIFIER 
int Init_declarator(){
	if(IDENTIFIER()){
		if (ASSIGNENT()){
			if (Initializer()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else if (IDENTIFIER()){
		return 1;
	}
	else{return 0;}
}

//Initializer -> OPEN_BRACE Initializer_list CLOSE_BRACE | OPEN_BRACE Initializer_list COMMA CLOSE_BRACE | Assignment_expression 
int Initializer(){
	if(OPEN_BRACE()){
		if (Initializer_list()){
			if (CLOSE_BRACE()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else if(OPEN_BRACE()){
		if (Initializer_list()){
			if (COMMA()){
				if (CLOSE_BRACE()){
					return 1;
				}
				else{return 0;}
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else if (Assignment_expression()){
		return 1;
	}
	else{return 0;}
}

//Initializer_list -> Designation Initializer | Initializer | Initializer_list COMMA Designation Initializer | Initializer_list COMMA Initializer 
int Initializer_list(){
	if(Designation()){
		if (Initializer()){
			return 1;
		}
		else{return 0;}
	}
	else if (Initializer()){
		return 1;
	}
	else if(Initializer_list()){
		if (COMMA()){
			if (Designation()){
				if (Initializer()){
					return 1;
				}
				else{return 0;}
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else if(Initializer_list()){
		if (COMMA()){
			if (Initializer()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else{return 0;}
}

//Assignment_expression -> Conditional_expression | Unary_expression Assignment_operator Assignment_expression 
int Assignment_expression(){
	if (Conditional_expression()){
		return 1;
	}
	else if(Unary_expression()){
		if (Assignment_operator()){
			if (Assignment_expression()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else{return 0;}
}

//Designation -> Designator_list ASSIGNENT 
int Designation(){
	if(Designator_list()){
		if (ASSIGNENT()){
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//Designator_list -> Designator | Designator_list Designator 
int Designator_list(){
	if (Designator()){
		return 1;
	}
	else if(Designator_list()){
		if (Designator()){
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//Designator -> OPEN_BRACKET Conditional_expression CLOSE_BRACKET | DOT IDENTIFIER 
int Designator(){
	if(OPEN_BRACKET()){
		if (Conditional_expression()){
			if (CLOSE_BRACKET()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else if(DOT()){
		if (IDENTIFIER()){
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//Conditional_expression -> Logical_or_expression 
int Conditional_expression(){
	if (Logical_or_expression()){
		return 1;
	}
	else{return 0;}
}

//Logical_or_expression -> Logical_and_expression | Logical_or_expression LOGICAL_OR Logical_and_expression 
int Logical_or_expression(){
	if (Logical_and_expression()){
		return 1;
	}
	else if(Logical_or_expression()){
		if (LOGICAL_OR()){
			if (Logical_and_expression()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else{return 0;}
}

//Logical_and_expression -> Equality_expression | Logical_and_expression LOGICAL_AND Equality_expression 
int Logical_and_expression(){
	if (Equality_expression()){
		return 1;
	}
	else if(Logical_and_expression()){
		if (LOGICAL_AND()){
			if (Equality_expression()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else{return 0;}
}

//Equality_expression -> Relational_expression | Equality_expression EQUALS Relational_expression | Equality_expression NOT_EQUALS Relational_expression 
int Equality_expression(){
	if (Relational_expression()){
		return 1;
	}
	else if(Equality_expression()){
		if (EQUALS()){
			if (Relational_expression()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else if(Equality_expression()){
		if (NOT_EQUALS()){
			if (Relational_expression()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else{return 0;}
}

//Relational_expression -> Additive_expression | Relational_expression LESS Additive_expression | Relational_expression GREATER Additive_expression 
int Relational_expression(){
	if (Additive_expression()){
		return 1;
	}
	else if(Relational_expression()){
		if (LESS()){
			if (Additive_expression()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else if(Relational_expression()){
		if (GREATER()){
			if (Additive_expression()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else{return 0;}
}

//Additive_expression -> Multiplicative_expression | Additive_expression PLUS Multiplicative_expression | Additive_expression MINUS Multiplicative_expression 
int Additive_expression(){
	if (Multiplicative_expression()){
		return 1;
	}
	else if(Additive_expression()){
		if (PLUS()){
			if (Multiplicative_expression()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else if(Additive_expression()){
		if (MINUS()){
			if (Multiplicative_expression()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else{return 0;}
}

//Multiplicative_expression -> Unary_expression | Multiplicative_expression PRODUCT Unary_expression | Multiplicative_expression DIVISION Unary_expression | Multiplicative_expression MODULE Unary_expression 
int Multiplicative_expression(){
	if (Unary_expression()){
		return 1;
	}
	else if(Multiplicative_expression()){
		if (PRODUCT()){
			if (Unary_expression()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else if(Multiplicative_expression()){
		if (DIVISION()){
			if (Unary_expression()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else if(Multiplicative_expression()){
		if (MODULE()){
			if (Unary_expression()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else{return 0;}
}

//Unary_expression -> Postfix_expression | INCREMENT Unary_expression | DECREMENT Unary_expression | Unary_operator Unary_expression; 
int Unary_expression(){
	if (Postfix_expression()){
		return 1;
	}
	else if(INCREMENT()){
		if (Unary_expression()){
			return 1;
		}
		else{return 0;}
	}
	else if(DECREMENT()){
		if (Unary_expression()){
			return 1;
		}
		else{return 0;}
	}
	else if(Unary_operator()){
		if (Unary_expression;()){
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//Unary_operator -> PLUS | MINUS | LOGICAL_NOT 
int Unary_operator(){
	if (PLUS()){
		return 1;
	}
	else if (MINUS()){
		return 1;
	}
	else if (LOGICAL_NOT()){
		return 1;
	}
	else{return 0;}
}

//Postfix_expression -> Primary_expression | Postfix_expression INCREMENT | Postfix_expression DECREMENT 
int Postfix_expression(){
	if (Primary_expression()){
		return 1;
	}
	else if(Postfix_expression()){
		if (INCREMENT()){
			return 1;
		}
		else{return 0;}
	}
	else if(Postfix_expression()){
		if (DECREMENT()){
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//Primary_expression -> IDENTIFIER | constant | OPEN_PARENTHESIS Expression CLOSE_PARENTHESIS 
int Primary_expression(){
	if (IDENTIFIER()){
		return 1;
	}
	else if(tk == CONSTANT){// constant
		getToken();
		return 1;
	}
	else if(OPEN_PARENTHESIS()){
		if (Expression()){
			if (CLOSE_PARENTHESIS()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else{return 0;}
}

//Assignment_operator -> ASSIGNENT | PRODUCT_ASSIGNMENT | DIVISION_ASSIGNMENT | MODULE_ASSIGNENT | PLUS_ASSIGNENT | MINUS_ASSIGNENT 
int Assignment_operator(){
	if (ASSIGNENT()){
		return 1;
	}
	else if (PRODUCT_ASSIGNMENT()){
		return 1;
	}
	else if (DIVISION_ASSIGNMENT()){
		return 1;
	}
	else if (MODULE_ASSIGNENT()){
		return 1;
	}
	else if (PLUS_ASSIGNENT()){
		return 1;
	}
	else if (MINUS_ASSIGNENT()){
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

//Expression_statement -> SEMICOLON | Expression SEMICOLON 
int Expression_statement(){
	if (SEMICOLON()){
		return 1;
	}
	else if(Expression()){
		if (SEMICOLON()){
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

//Expression -> Assignment_expression | Expression COMMA Assignment_expression; 
int Expression(){
	if (Assignment_expression()){
		return 1;
	}
	else if(Expression()){
		if (COMMA()){
			if (Assignment_expression;()){
				return 1;
			}
			else{return 0;}
		}
		else{return 0;}
	}
	else{return 0;}
}

//If_statement -> IF OPEN_PARENTHESIS Expression CLOSE_PARENTHESIS Statement ELSE Statement | IF OPEN_PARENTHESIS Expression CLOSE_PARENTHESIS Statement 
int If_statement(){
	if(IF()){
		if (OPEN_PARENTHESIS()){
			if (Expression()){
				if (CLOSE_PARENTHESIS()){
					if (Statement()){
						if (ELSE()){
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
		else{return 0;}
	}
	else if(IF()){
		if (OPEN_PARENTHESIS()){
			if (Expression()){
				if (CLOSE_PARENTHESIS()){
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

//While_statement -> WHILE OPEN_PARENTHESIS Expression CLOSE_PARENTHESIS Statement 
int While_statement(){
	if(WHILE()){
		if (OPEN_PARENTHESIS()){
			if (Expression()){
				if (CLOSE_PARENTHESIS()){
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

//Do_while_statement -> DO Statement WHILE OPEN_PARENTHESIS Expression CLOSE_PARENTHESIS SEMICOLON 
int Do_while_statement(){
	if(DO()){
		if (Statement()){
			if (WHILE()){
				if (OPEN_PARENTHESIS()){
					if (Expression()){
						if (CLOSE_PARENTHESIS()){
							if (SEMICOLON()){
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

//For_statement -> FOR OPEN_PARENTHESIS Expression_statement Expression_statement CLOSE_PARENTHESIS Statement | FOR OPEN_PARENTHESIS Expression_statement Expression_statement Expression CLOSE_PARENTHESIS Statement | FOR OPEN_PARENTHESIS Declaration Expression_statement CLOSE_PARENTHESIS Statement | FOR OPEN_PARENTHESIS Declaration Expression_statement Expression CLOSE_PARENTHESIS Statement 
int For_statement(){
	if(FOR()){
		if (OPEN_PARENTHESIS()){
			if (Expression_statement()){
				if (Expression_statement()){
					if (CLOSE_PARENTHESIS()){
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
	else if(FOR()){
		if (OPEN_PARENTHESIS()){
			if (Expression_statement()){
				if (Expression_statement()){
					if (Expression()){
						if (CLOSE_PARENTHESIS()){
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
		else{return 0;}
	}
	else if(FOR()){
		if (OPEN_PARENTHESIS()){
			if (Declaration()){
				if (Expression_statement()){
					if (CLOSE_PARENTHESIS()){
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
	else if(FOR()){
		if (OPEN_PARENTHESIS()){
			if (Declaration()){
				if (Expression_statement()){
					if (Expression()){
						if (CLOSE_PARENTHESIS()){
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
		else{return 0;}
	}
	else{return 0;}
}

//Jump_statement -> CONTINUE SEMICOLON | BREAK SEMICOLON 
int Jump_statement(){
	if(CONTINUE()){
		if (SEMICOLON()){
			return 1;
		}
		else{return 0;}
	}
	else if(BREAK()){
		if (SEMICOLON()){
			return 1;
		}
		else{return 0;}
	}
	else{return 0;}
}

// <*********** FIM DO ANALISADOR SINTÁTICO DESCENDENTE RECURSIVO SEM RETROCESSO ***********>

int main(){
}