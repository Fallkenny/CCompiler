using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace DotNetCCompiler
{
    class SyntacticAnalyzer
    {
        eToken _token;
        TokenResult _currentToken;

        private LinkedList<TokenResult> _linkedList;
        private LinkedList<TokenResult>.Enumerator _tokenEnumerator;

        public SyntacticAnalyzer(List<TokenResult> tokenResultList)
        {
            this._linkedList = new LinkedList<TokenResult>(tokenResultList);
            this._tokenEnumerator = _linkedList.GetEnumerator();
        }

        public void Analyze()
        {
            GetToken();
            var passed = Program();
        }

        void GetToken()
        {
            _tokenEnumerator.MoveNext();
            _currentToken = _tokenEnumerator.Current;
            _token = _currentToken.Token;
        }

        //Program -> Main_func 
        bool Program()
        {
            if (Main_func())
            {
                return true;
            }
            else { return false; }
        }

        //Main_func -> bool identifier ( ) Compound_statement 
        bool Main_func()
        {
            if (_token == eToken.INT)
            {// int
                GetToken();
                if (_token == eToken.IDENTIFIER)
                {// identifier
                    GetToken();
                    if (_token == eToken.OPEN_PARENTHESIS)
                    {// (
                        GetToken();
                        if (_token == eToken.CLOSE_PARENTHESIS)
                        {// )
                            GetToken();
                            if (Compound_statement())
                            {
                                return true;
                            }
                            else { return false; }
                        }
                        else { return false; }
                    }
                    else { return false; }
                }
                else { return false; }
            }
            else { return false; }
        }

        //Compound_statement -> { Compound_statement1Linha 
        bool Compound_statement()
        {
            if (_token == eToken.OPEN_BRACE)
            {// {
                GetToken();
                if (Compound_statement1Linha())
                {
                    return true;
                }
                else { return false; }
            }
            else { return false; }
        }

        //Compound_statement1Linha -> } | Block_item_list } 
        bool Compound_statement1Linha()
        {
            if (_token == eToken.CLOSE_BRACE)
            {// }
                GetToken();
                return true;
            }
            else if (Block_item_list())
            {
                if (_token == eToken.CLOSE_BRACE)
                {// }
                    GetToken();
                    return true;
                }
                else { return false; }
            }
            else { return false; }
        }

        //Block_item_list -> Block_item Block_item_list1Hash 
        bool Block_item_list()
        {
            if (Block_item())
            {
                if (Block_item_list1Hash())
                {
                    return true;
                }
                else { return false; }
            }
            else { return false; }
        }

        //Block_item_list1Hash -> Block_item Block_item_list1Hash | ? 
        bool Block_item_list1Hash()
        {
            if (Block_item())
            {
                if (Block_item_list1Hash())
                {
                    return true;
                }
                else { return false; }
            }
            else { return true; }
        }

        //Block_item -> Declaration | Statement 
        bool Block_item()
        {
            if (Declaration())
            {
                return true;
            }
            else if (Statement())
            {
                return true;
            }
            else { return false; }
        }

        //Declaration -> Declaration_specifiers Declaration1Linha 
        bool Declaration()
        {
            if (Declaration_specifiers())
            {
                if (Declaration1Linha())
                {
                    return true;
                }
                else { return false; }
            }
            else { return false; }
        }

        //Declaration1Linha -> ; | Init_declarator_list ; 
        bool Declaration1Linha()
        {
            if (_token == eToken.SEMICOLON)
            {// ;
                GetToken();
                return true;
            }
            else if (Init_declarator_list())
            {
                if (_token == eToken.SEMICOLON)
                {// ;
                    GetToken();
                    return true;
                }
                else { return false; }
            }
            else { return false; }
        }

        //Declaration_specifiers -> Type_specifier Declaration_specifiers1Linha 
        bool Declaration_specifiers()
        {
            if (Type_specifier())
            {
                if (Declaration_specifiers1Linha())
                {
                    return true;
                }
                else { return false; }
            }
            else { return false; }
        }

        //Declaration_specifiers1Linha -> Declaration_specifiers | ? 
        bool Declaration_specifiers1Linha()
        {
            if (Declaration_specifiers())
            {
                return true;
            }
            else { return true; }
        }

        //Type_specifier -> bool | float 
        bool Type_specifier()
        {
            if (_token == eToken.INT)
            {// int
                GetToken();
                return true;
            }
            else if (_token == eToken.FLOAT)
            {// float
                GetToken();
                return true;
            }
            else { return false; }
        }

        //Init_declarator_list -> Init_declarator Init_declarator_list1Hash 
        bool Init_declarator_list()
        {
            if (Init_declarator())
            {
                if (Init_declarator_list1Hash())
                {
                    return true;
                }
                else { return false; }
            }
            else { return false; }
        }

        //Init_declarator_list1Hash -> , Init_declarator Init_declarator_list1Hash | ? 
        bool Init_declarator_list1Hash()
        {
            if (_token == eToken.COMMA)
            {// ,
                GetToken();
                if (Init_declarator())
                {
                    if (Init_declarator_list1Hash())
                    {
                        return true;
                    }
                    else { return false; }
                }
                else { return false; }
            }
            else { return true; }
        }

        //Init_declarator -> identifier Init_declarator1Linha 
        bool Init_declarator()
        {
            if (_token == eToken.IDENTIFIER)
            {// identifier
                GetToken();
                if (Init_declarator1Linha())
                {
                    return true;
                }
                else { return false; }
            }
            else { return false; }
        }

        //Init_declarator1Linha -> = Assignment_expression | ? 
        bool Init_declarator1Linha()
        {
            if (_token == eToken.ASSIGNENT)
            {// =
                GetToken();
                if (Assignment_expression())
                {
                    return true;
                }
                else { return false; }
            }
            else { return true; }
        }

        //Assignment_expression -> Logical_or_expression | Unary_expression Assignment_operator Assignment_expression 
        bool Assignment_expression()
        {
            if (Logical_or_expression())
            {
                return true;
            }
            else if (Unary_expression())
            {
                if (Assignment_operator())
                {
                    if (Assignment_expression())
                    {
                        return true;
                    }
                    else { return false; }
                }
                else { return false; }
            }
            else { return false; }
        }

        //Logical_or_expression -> Logical_and_expression Logical_or_expression1Hash 
        bool Logical_or_expression()
        {
            if (Logical_and_expression())
            {
                if (Logical_or_expression1Hash())
                {
                    return true;
                }
                else { return false; }
            }
            else { return false; }
        }

        //Logical_or_expression1Hash -> ii Logical_and_expression Logical_or_expression1Hash | ? 
        bool Logical_or_expression1Hash()
        {
            if (_token == eToken.LOGICAL_OR)
            {// ii
                GetToken();
                if (Logical_and_expression())
                {
                    if (Logical_or_expression1Hash())
                    {
                        return true;
                    }
                    else { return false; }
                }
                else { return false; }
            }
            else { return true; }
        }

        //Logical_and_expression -> Equality_expression Logical_and_expression1Hash 
        bool Logical_and_expression()
        {
            if (Equality_expression())
            {
                if (Logical_and_expression1Hash())
                {
                    return true;
                }
                else { return false; }
            }
            else { return false; }
        }

        //Logical_and_expression1Hash -> && Equality_expression Logical_and_expression1Hash | ? 
        bool Logical_and_expression1Hash()
        {
            if (_token == eToken.LOGICAL_AND)
            {// &&
                GetToken();
                if (Equality_expression())
                {
                    if (Logical_and_expression1Hash())
                    {
                        return true;
                    }
                    else { return false; }
                }
                else { return false; }
            }
            else { return true; }
        }

        //Equality_expression -> Relational_expression Equality_expression1Hash 
        bool Equality_expression()
        {
            if (Relational_expression())
            {
                if (Equality_expression1Hash())
                {
                    return true;
                }
                else { return false; }
            }
            else { return false; }
        }

        //Equality_expression1Hash -> == Relational_expression Equality_expression1Hash | != Relational_expression Equality_expression1Hash | ? 
        bool Equality_expression1Hash()
        {
            if (_token == eToken.EQUALS)
            {// ==
                GetToken();
                if (Relational_expression())
                {
                    if (Equality_expression1Hash())
                    {
                        return true;
                    }
                    else { return false; }
                }
                else { return false; }
            }
            else if (_token == eToken.NOT_EQUALS)
            {// !=
                GetToken();
                if (Relational_expression())
                {
                    if (Equality_expression1Hash())
                    {
                        return true;
                    }
                    else { return false; }
                }
                else { return false; }
            }
            else { return true; }
        }

        //Relational_expression -> Additive_expression Relational_expression1Hash 
        bool Relational_expression()
        {
            if (Additive_expression())
            {
                if (Relational_expression1Hash())
                {
                    return true;
                }
                else { return false; }
            }
            else { return false; }
        }

        //Relational_expression1Hash -> Relational_operator Additive_expression Relational_expression1Hash | ? 
        bool Relational_expression1Hash()
        {
            if (Relational_operator())
            {
                if (Additive_expression())
                {
                    if (Relational_expression1Hash())
                    {
                        return true;
                    }
                    else { return false; }
                }
                else { return false; }
            }
            else { return true; }
        }

        //Relational_operator -> > | < | >= | <= 
        bool Relational_operator()
        {
            if (_token == eToken.GREATER)
            {// >
                GetToken();
                return true;
            }
            else if (_token == eToken.LESS)
            {// <
                GetToken();
                return true;
            }
            else if (_token == eToken.GREATER_OR_EQUAL)
            {// >=
                GetToken();
                return true;
            }
            else if (_token == eToken.LESS_OR_EQUAL)
            {// <=
                GetToken();
                return true;
            }
            else { return false; }
        }

        //Additive_expression -> Multiplicative_expression Additive_expression1Hash 
        bool Additive_expression()
        {
            if (Multiplicative_expression())
            {
                if (Additive_expression1Hash())
                {
                    return true;
                }
                else { return false; }
            }
            else { return false; }
        }

        //Additive_expression1Hash -> + Multiplicative_expression Additive_expression1Hash | - Multiplicative_expression Additive_expression1Hash | ? 
        bool Additive_expression1Hash()
        {
            if (_token == eToken.PLUS)
            {// +
                GetToken();
                if (Multiplicative_expression())
                {
                    if (Additive_expression1Hash())
                    {
                        return true;
                    }
                    else { return false; }
                }
                else { return false; }
            }
            else if (_token == eToken.MINUS)
            {// -
                GetToken();
                if (Multiplicative_expression())
                {
                    if (Additive_expression1Hash())
                    {
                        return true;
                    }
                    else { return false; }
                }
                else { return false; }
            }
            else { return true; }
        }

        //Multiplicative_expression -> Unary_expression Multiplicative_expression1Hash 
        bool Multiplicative_expression()
        {
            if (Unary_expression())
            {
                if (Multiplicative_expression1Hash())
                {
                    return true;
                }
                else { return false; }
            }
            else { return false; }
        }

        //Multiplicative_expression1Hash -> * Unary_expression Multiplicative_expression1Hash | / Unary_expression Multiplicative_expression1Hash | % Unary_expression Multiplicative_expression1Hash | ? 
        bool Multiplicative_expression1Hash()
        {
            if (_token == eToken.PRODUCT)
            {// *
                GetToken();
                if (Unary_expression())
                {
                    if (Multiplicative_expression1Hash())
                    {
                        return true;
                    }
                    else { return false; }
                }
                else { return false; }
            }
            else if (_token == eToken.DIVISION)
            {// /
                GetToken();
                if (Unary_expression())
                {
                    if (Multiplicative_expression1Hash())
                    {
                        return true;
                    }
                    else { return false; }
                }
                else { return false; }
            }
            else if (_token == eToken.MODULE)
            {// %
                GetToken();
                if (Unary_expression())
                {
                    if (Multiplicative_expression1Hash())
                    {
                        return true;
                    }
                    else { return false; }
                }
                else { return false; }
            }
            else { return true; }
        }

        //Unary_expression -> Postfix_expression | ++ Unary_expression | -- Unary_expression | Unary_operator Unary_expression 
        bool Unary_expression()
        {
            if (Postfix_expression())
            {
                return true;
            }
            else if (_token == eToken.INCREMENT)
            {// ++
                GetToken();
                if (Unary_expression())
                {
                    return true;
                }
                else { return false; }
            }
            else if (_token == eToken.DECREMENT)
            {// --
                GetToken();
                if (Unary_expression())
                {
                    return true;
                }
                else { return false; }
            }
            else if (Unary_operator())
            {
                if (Unary_expression())
                {
                    return true;
                }
                else { return false; }
            }
            else { return false; }
        }

        //Unary_operator -> + | - | ! 
        bool Unary_operator()
        {
            if (_token == eToken.PLUS)
            {// +
                GetToken();
                return true;
            }
            else if (_token == eToken.MINUS)
            {// -
                GetToken();
                return true;
            }
            else if (_token == eToken.LOGICAL_NOT)
            {// !
                GetToken();
                return true;
            }
            else { return false; }
        }

        //Postfix_expression -> Primary_expression Postfix_expression1Hash 
        bool Postfix_expression()
        {
            if (Primary_expression())
            {
                if (Postfix_expression1Hash())
                {
                    return true;
                }
                else { return false; }
            }
            else { return false; }
        }

        //Postfix_expression1Hash -> ++ Postfix_expression1Hash | -- Postfix_expression1Hash | ? 
        bool Postfix_expression1Hash()
        {
            if (_token == eToken.INCREMENT)
            {// ++
                GetToken();
                if (Postfix_expression1Hash())
                {
                    return true;
                }
                else { return false; }
            }
            else if (_token == eToken.DECREMENT)
            {// --
                GetToken();
                if (Postfix_expression1Hash())
                {
                    return true;
                }
                else { return false; }
            }
            else { return true; }
        }

        //Primary_expression -> identifier | Constant | ( Expression ) 
        bool Primary_expression()
        {
            if (_token == eToken.IDENTIFIER)
            {// identifier
                GetToken();
                return true;
            }
            else if (Constant())
            {
                return true;
            }
            else if (_token == eToken.OPEN_PARENTHESIS)
            {// (
                GetToken();
                if (Expression())
                {
                    if (_token == eToken.CLOSE_PARENTHESIS)
                    {// )
                        GetToken();
                        return true;
                    }
                    else { return false; }
                }
                else { return false; }
            }
            else { return false; }
        }

        //Constant -> int_constant | float_constant 
        bool Constant()
        {
            if (_token == eToken.INTEGER_CONSTANT)
            {// int_constant
                GetToken();
                return true;
            }
            else if (_token == eToken.FLOATING_POINT_CONSTANT)
            {// float_constant
                GetToken();
                return true;
            }
            else { return false; }
        }

        //Assignment_operator -> = | *= | /= | %= | += | -= 
        bool Assignment_operator()
        {
            if (_token == eToken.ASSIGNENT)
            {// =
                GetToken();
                return true;
            }
            else if (_token == eToken.PRODUCT_ASSIGNMENT)
            {// *=
                GetToken();
                return true;
            }
            else if (_token == eToken.DIVISION_ASSIGNMENT)
            {// /=
                GetToken();
                return true;
            }
            else if (_token == eToken.MODULE_ASSIGNENT)
            {// %=
                GetToken();
                return true;
            }
            else if (_token == eToken.PLUS_ASSIGNENT)
            {// +=
                GetToken();
                return true;
            }
            else if (_token == eToken.MINUS_ASSIGNENT)
            {// -=
                GetToken();
                return true;
            }
            else { return false; }
        }

        //Statement -> Compound_statement | Expression_statement | If_statement | Iteration_statement | Jump_statement 
        bool Statement()
        {
            if (Compound_statement())
            {
                return true;
            }
            else if (Expression_statement())
            {
                return true;
            }
            else if (If_statement())
            {
                return true;
            }
            else if (Iteration_statement())
            {
                return true;
            }
            else if (Jump_statement())
            {
                return true;
            }
            else { return false; }
        }

        //Expression_statement -> ; | Expression ; 
        bool Expression_statement()
        {
            if (_token == eToken.SEMICOLON)
            {// ;
                GetToken();
                return true;
            }
            else if (Expression())
            {
                if (_token == eToken.SEMICOLON)
                {// ;
                    GetToken();
                    return true;
                }
                else { return false; }
            }
            else { return false; }
        }

        //Expression -> Assignment_expression Expression1Hash 
        bool Expression()
        {
            if (Assignment_expression())
            {
                if (Expression1Hash())
                {
                    return true;
                }
                else { return false; }
            }
            else { return false; }
        }

        //Expression1Hash -> , Assignment_expression Expression1Hash | ? 
        bool Expression1Hash()
        {
            if (_token == eToken.COMMA)
            {// ,
                GetToken();
                if (Assignment_expression())
                {
                    if (Expression1Hash())
                    {
                        return true;
                    }
                    else { return false; }
                }
                else { return false; }
            }
            else { return true; }
        }

        //If_statement -> if ( Expression ) Statement If_statement1Linha 
        bool If_statement()
        {
            if (_token == eToken.IF)
            {// if
                GetToken();
                if (_token == eToken.OPEN_PARENTHESIS)
                {// (
                    GetToken();
                    if (Expression())
                    {
                        if (_token == eToken.CLOSE_PARENTHESIS)
                        {// )
                            GetToken();
                            if (Statement())
                            {
                                if (If_statement1Linha())
                                {
                                    return true;
                                }
                                else { return false; }
                            }
                            else { return false; }
                        }
                        else { return false; }
                    }
                    else { return false; }
                }
                else { return false; }
            }
            else { return false; }
        }

        //If_statement1Linha -> else Statement | ? 
        bool If_statement1Linha()
        {
            if (_token == eToken.ELSE)
            {// else
                GetToken();
                if (Statement())
                {
                    return true;
                }
                else { return false; }
            }
            else { return true; }
        }

        //Iteration_statement -> While_statement | Do_while_statement | For_statement 
        bool Iteration_statement()
        {
            if (While_statement())
            {
                return true;
            }
            else if (Do_while_statement())
            {
                return true;
            }
            else if (For_statement())
            {
                return true;
            }
            else { return false; }
        }

        //While_statement -> while ( Expression ) Statement 
        bool While_statement()
        {
            if (_token == eToken.WHILE)
            {// while
                GetToken();
                if (_token == eToken.OPEN_PARENTHESIS)
                {// (
                    GetToken();
                    if (Expression())
                    {
                        if (_token == eToken.CLOSE_PARENTHESIS)
                        {// )
                            GetToken();
                            if (Statement())
                            {
                                return true;
                            }
                            else { return false; }
                        }
                        else { return false; }
                    }
                    else { return false; }
                }
                else { return false; }
            }
            else { return false; }
        }

        //Do_while_statement -> do Statement while ( Expression ) ; 
        bool Do_while_statement()
        {
            if (_token == eToken.DO)
            {// do
                GetToken();
                if (Statement())
                {
                    if (_token == eToken.WHILE)
                    {// while
                        GetToken();
                        if (_token == eToken.OPEN_PARENTHESIS)
                        {// (
                            GetToken();
                            if (Expression())
                            {
                                if (_token == eToken.CLOSE_PARENTHESIS)
                                {// )
                                    GetToken();
                                    if (_token == eToken.SEMICOLON)
                                    {// ;
                                        GetToken();
                                        return true;
                                    }
                                    else { return false; }
                                }
                                else { return false; }
                            }
                            else { return false; }
                        }
                        else { return false; }
                    }
                    else { return false; }
                }
                else { return false; }
            }
            else { return false; }
        }

        //For_statement -> for ( For_statement2Linha 
        bool For_statement()
        {
            if (_token == eToken.FOR)
            {// for
                GetToken();
                if (_token == eToken.OPEN_PARENTHESIS)
                {// (
                    GetToken();
                    if (For_statement2Linha())
                    {
                        return true;
                    }
                    else { return false; }
                }
                else { return false; }
            }
            else { return false; }
        }

        //For_statement2Linha -> Expression_statement Expression_statement For_statement1Linha | Declaration Expression_statement For_statement3Linha 
        bool For_statement2Linha()
        {
            if (Expression_statement())
            {
                if (Expression_statement())
                {
                    if (For_statement1Linha())
                    {
                        return true;
                    }
                    else { return false; }
                }
                else { return false; }
            }
            else if (Declaration())
            {
                if (Expression_statement())
                {
                    if (For_statement3Linha())
                    {
                        return true;
                    }
                    else { return false; }
                }
                else { return false; }
            }
            else { return false; }
        }

        //For_statement3Linha -> ) Statement | Expression ) Statement 
        bool For_statement3Linha()
        {
            if (_token == eToken.CLOSE_PARENTHESIS)
            {// )
                GetToken();
                if (Statement())
                {
                    return true;
                }
                else { return false; }
            }
            else if (Expression())
            {
                if (_token == eToken.CLOSE_PARENTHESIS)
                {// )
                    GetToken();
                    if (Statement())
                    {
                        return true;
                    }
                    else { return false; }
                }
                else { return false; }
            }
            else { return false; }
        }

        //For_statement1Linha -> ) Statement | Expression ) Statement 
        bool For_statement1Linha()
        {
            if (_token == eToken.CLOSE_PARENTHESIS)
            {// )
                GetToken();
                if (Statement())
                {
                    return true;
                }
                else { return false; }
            }
            else if (Expression())
            {
                if (_token == eToken.CLOSE_PARENTHESIS)
                {// )
                    GetToken();
                    if (Statement())
                    {
                        return true;
                    }
                    else { return false; }
                }
                else { return false; }
            }
            else { return false; }
        }

        //Jump_statement -> continue ; | break ; 
        bool Jump_statement()
        {
            if (_token == eToken.CONTINUE)
            {// continue
                GetToken();
                if (_token == eToken.SEMICOLON)
                {// ;
                    GetToken();
                    return true;
                }
                else { return false; }
            }
            else if (_token == eToken.BREAK)
            {// break
                GetToken();
                if (_token == eToken.SEMICOLON)
                {// ;
                    GetToken();
                    return true;
                }
                else { return false; }
            }
            else { return false; }
        }




    }
}
