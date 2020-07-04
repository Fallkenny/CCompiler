//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//// DEFINE TOKENS
//
//#define TK1 1 // main
//#define tkCONSTANT 2 // constant
//#define tkIDENTIFIER 3 // identifier
//#define tkMAIN 4 // main
//#define tkOPEN_BRACE 5 // {
//#define tkCLOSE_BRACE 6 // }
//#define tkSEMICOLON 7 // ;
//#define tkCOMMA 8 // ,
//#define tkASSIGNENT 9 // =
//#define tkOPEN_BRACKET 10 // [
//#define tkCLOSE_BRACKET 11 // ]
//#define tkDOT 12 // .
//#define tkLOGICAL_NOT 13 // !
//#define tkLOGICAL_OR 14 // ||
//#define tkLOGICAL_AND 15 // &&
//#define tkEQUALS 16 // ==
//#define tkNOT_EQUALS 17 // !=
//#define tkLESS 18 // <
//#define tkGREATER 19 // >
//#define tkPLUS 20 // +
//#define tkMINUS 21 // -
//#define tkPRODUCT 22 // *
//#define tkDIVISION 23 // /
//#define tkMODULE 24 // %
//#define tkINCREMENT 25 // ++
//#define tkDECREMENT 26 // --
//#define tkOPEN_PARENTHESIS 27 // (
//#define tkCLOSE_PARENTHESIS 28 // )
//#define tkPRODUCT_ASSIGNMENT 29 // *=
//#define tkDIVISION_ASSIGNMENT 30 // /=
//#define tkMODULE_ASSIGNENT 31 // %=
//#define tkPLUS_ASSIGNENT 32 // +=
//#define tkMINUS_ASSIGNENT 33 // -=
//#define tkFOR 34 // for
//#define tkWHILE 35 // while
//#define tkIF 36 // if
//#define tkDO 37 // do
//#define tkELSE 38 // else
//#define tkINT 39 // int
//#define tkFLOAT 40 // float
//#define tkCONTINUE 41 // continue
//#define tkBREAK 42 // break
//
//// Variáveis Globais <o>
//
//int tk;
//int tklinha = 0;
//int tkcoluna = 0;
//
//// <*********** INICIO DO ANALISADOR LÉXICO ***********>
//
//// Implemente aqui seu analisador Léxico
//
//// <*********** FIM DO ANALISADOR LÉXICO ***********>
//
//// Protótipo das Funções do Analisador Sintático
//
//int Program();
//
//int Main_func();
//
//int Compound_statement();
//
//int Block_item_list();
//
//int Block_item();
//
//int Declaration();
//
//int Declaration_specifiers();
//
//int Type_specifier();
//
//int Init_declarator_list();
//
//int Init_declarator();
//
//int Initializer();
//
//int Initializer_list();
//
//int Assignment_expression();
//
//int Designation();
//
//int Designator_list();
//
//int Designator();
//
//int Conditional_expression();
//
//int Logical_or_expression();
//
//// <*********** INICIO DO ANALISADOR SINTÁTICO DESCENDENTE RECURSIVO COM RETROCESSO ***********>
//
////Implemente aqui a sua função getToken()
//
//void getToken() {
//	tk = 0;
//	tklinha = 0;
//	tkcoluna = 0;
//}
//
////Implemente aqui a sua função marcaPosToken()
//
//void marcaPosToken() {
//}
//
////Implemente aqui a sua função restauraPosToken()
//
//void restauraPosToken() {
//}
//
////Program -> Main_func 
//int Program()
//{
//	if (Main_func())
//	{
//		return 1;
//	}
//	else
//	{
//		return 0;
//	}
//}
//
////Main_func -> int main Compound_statement 
//int Main_func()
//{
//	if (tk == tkINT)
//	{// int
//		getToken();
//		if (tk == tkMAIN)
//		{// main
//			getToken();
//			if (Compound_statement())
//			{
//				return 1;
//			}
//			else { return 0; }
//		}
//		else { return 0; }
//	}
//	else { return 0; }
//}
//
////Compound_statement -> { } | { Block_item_list } 
//int Compound_statement()
//{
//	if (tk == tkOPEN_BRACE)
//	{// {
//		getToken();
//		marcaPosToken(); // FUNÇÃO NECESSÁRIA CASO SEJA NECESSÁRIO RESTAURAR O TOKEN ANTERIOR
//		if (tk == tkCLOSE_BRACE)
//		{// }
//			return 1;
//		}
//		else if (Block_item_list())
//		{
//			if (tk == tkCLOSE_BRACE)
//			{// }
//				return 1;
//			}
//			else { return 0; }
//		}
//	}
//}
////Block_item_list -> Block_item | Block_item_list Block_item 
//int Block_item_list()
//{
//	if (Block_item())
//	{
//		return 1;
//	}
//	else if (Block_item_list())
//	{
//		if (Block_item())
//		{
//			return 1;
//		}
//		else { return 0; }
//	}
//	else { return 0; }
//}
//
////Block_item -> Declaration | Statement 
//int Block_item()
//{
//	if (Declaration())
//	{
//		return 1;
//	}
//	else if (Statement())
//	{
//		return 1;
//	}
//	else { return 0; }
//}
//
////Declaration -> Declaration_specifiers ; | Declaration_specifiers Init_declarator_list ; 
//int Declaration()
//{
//	if (Declaration_specifiers())
//	{
//	}
//}
//
////Declaration_specifiers -> Type_specifier Declaration_specifiers | Type_specifier 
//int Declaration_specifiers() {
//	if (Type_specifier()) {
//	}
//}
//
////Type_specifier -> int | float 
//int Type_specifier() {
//	if (tk == tkINT) {// int
//		getToken();
//		return 1;
//	}
//	else if (tk == tkFLOAT) {// float
//		getToken();
//		return 1;
//	}
//	else { return 0; }
//}
//
////Init_declarator_list -> Init_declarator | Init_declarator_list , Init_declarator 
//int Init_declarator_list()
//{
//	if (Init_declarator())
//	{
//		return 1;
//	}
//	else if (Init_declarator_list())
//	{
//		if (tk == tkCOMMA)
//		{// ,
//			getToken();
//			if (Init_declarator())
//			{
//				return 1;
//			}
//			else { return 0; }
//		}
//		else { return 0; }
//	}
//	else { return 0; }
//}
//
////Init_declarator -> identifier = Initializer | identifier 
//int Init_declarator()
//{
//	if (tk == tkIDENTIFIER)
//	{// identifier
//		getToken();
//		marcaPosToken(); // FUNÇÃO NECESSÁRIA CASO SEJA NECESSÁRIO RESTAURAR O TOKEN ANTERIOR
//		if (tk == tkASSIGNENT)
//		{// =
//			getToken();
//			if (Initializer())
//			{
//				return 1;
//			}
//			else { return 0; }
//		}
//		else { return 0; }
//		{return 1; }
//	}
//}
//
////Initializer -> { Initializer_list } | { Initializer_list , } | Assignment_expression 
//int Initializer()
//{
//	if (tk == tkOPEN_BRACE) {// {
//		getToken();
//		if (Initializer_list()) {
//		}
//		else if (Assignment_expression()) {
//			return 1;
//		}
//		else { return 0; }
//	}
//}
////Initializer_list -> Designation Initializer | Initializer | Initializer_list , Designation Initializer | Initializer_list , Initializer 
//int Initializer_list()
//{
//	if (Designation())
//	{
//		if (Initializer())
//		{
//			return 1;
//		}
//		else { return 0; }
//	}
//	else if (Initializer())
//	{
//		return 1;
//	}
//	else if (Initializer_list())
//	{
//		if (tk == tkCOMMA)
//		{// ,
//			getToken();
//			marcaPosToken(); // FUNÇÃO NECESSÁRIA CASO SEJA NECESSÁRIO RESTAURAR O TOKEN ANTERIOR
//			if (Designation())
//			{
//				if (Initializer())
//				{
//					return 1;
//				}
//				else { return 0; }
//			}
//			else { return 0; }
//		}
//		else { return 0; }
//		if (Initializer())
//		{
//			return 1;
//		}
//		else
//		{
//			return 0;
//		}
//	}
//}
//
////Assignment_expression -> Conditional_expression | Unary_expression Assignment_operator Assignment_expression 
//int Assignment_expression()
//{
//	if (Conditional_expression())
//	{
//		return 1;
//	}
//	else if (Unary_expression())
//	{
//		if (Assignment_operator())
//		{
//			if (Assignment_expression())
//			{
//				return 1;
//			}
//			else { return 0; }
//		}
//		else { return 0; }
//	}
//	else { return 0; }
//}
//
////Designation -> Designator_list = 
//int Designation() {
//	if (Designator_list())
//	{
//		if (tk == tkASSIGNENT)
//		{// =
//			getToken();
//			return 1;
//		}
//		else { return 0; }
//	}
//	else { return 0; }
//}
//
////Designator_list -> Designator | Designator_list Designator 
//int Designator_list()
//{
//	if (Designator())
//	{
//		return 1;
//	}
//	else if (Designator_list())
//	{
//		if (Designator())
//		{
//			return 1;
//		}
//		else { return 0; }
//	}
//	else { return 0; }
//}
//
////Designator -> [ Conditional_expression ] | . identifier 
//int Designator() 
//{
//	if (tk == tkOPEN_BRACKET) 
//	{// [
//		getToken();
//		if (Conditional_expression()) 
//		{
//			if (tk == tkCLOSE_BRACKET) 
//			{// ]
//				getToken();
//				return 1;
//			}
//			else { return 0; }
//		}
//		else { return 0; }
//	}
//	else if (tk == tkDOT) 
//	{// .
//		getToken();
//		if (tk == tkIDENTIFIER) 
//		{// identifier
//			getToken();
//			return 1;
//		}
//		else { return 0; }
//	}
//	else { return 0; }
//}
//
////Conditional_expression -> Logical_or_expression 
//int Conditional_expression() 
//{
//	if (Logical_or_expression()) 
//	{
//		return 1;
//	}
//	else { return 0; }
//}
//
////Logical_or_expression -> Logical_and_expression | Logical_or_expression 
//int Logical_or_expression() 
//{
//	if (Logical_and_expression()) 
//	{
//		return 1;
//	}
//	else if (Logical_or_expression()) 
//	{
//		return 1;
//	}
//	else { return 0; }
//}
//
//// <*********** FIM DO ANALISADOR SINTÁTICO DESCENDENTE RECURSIVO COM RETROCESSO ***********>
//
//int main() {
//}