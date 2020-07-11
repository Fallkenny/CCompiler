using System;
using System.Collections.Generic;
using System.Text;

namespace DotNetCCompiler
{
    public class Syntatic_SemmanticAnalyser
    {

        eToken _token;
        TokenResult _currentToken;
        int _tempIndex = 0;
        public SymbolTable SymbolTable = new SymbolTable();

        private LinkedList<TokenResult> _linkedList;
        private LinkedList<TokenResult>.Enumerator _tokenEnumerator;

        public Syntatic_SemmanticAnalyser(List<TokenResult> tokenResultList)
        {
            this._linkedList = new LinkedList<TokenResult>(tokenResultList);
            this._tokenEnumerator = _linkedList.GetEnumerator();
        }

        private string CreateTempVar()
        {
            return string.Format($"T{_tempIndex++.ToString("D3")}");
        }

        public void Analyze()
        {
            GetToken();
            var passed = Program();
        }

        void GetToken()
        {
            var moved = _tokenEnumerator.MoveNext();
            if (moved)
            {
                _currentToken = _tokenEnumerator.Current;
                _token = _currentToken.Token;
                return;
            }
            _currentToken = null;
            _token = eToken.EOF;
        }

        bool Program()
        {
            if (Expression_statement(out string place, out string code))
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        //Assignment_expression -> Logical_or_expression Assignment_expression1Linha 
        bool Assignment_expression(out string assExpPlace, out string assExpCode)
        {
            assExpPlace = "";
            assExpCode = "";
            if (Logical_or_expression(out string logicOrExpPlace, out string logicOrExpCode))
            {
                var assExp1Hash1_IPlace = logicOrExpPlace;
                var assExp1Hash1_ICode = logicOrExpCode;
                if (Assignment_expression1Linha(assExp1Hash1_IPlace, assExp1Hash1_ICode,
                        out string assExp1Hash_SPlace, out string assExp1Hash_SCode))
                {
                    assExpPlace = assExp1Hash_SPlace;
                    assExpCode = assExp1Hash_SCode;
                    return true;
                }
                else { return false; }
            }
            else { return false; }
        }

        //Assignment_expression1Linha -> Assignment_operator Assignment_expression | ? 
        bool Assignment_expression1Linha(string assExp1Hash1_IPlace, string assExp1Hash1_ICode,
                        out string assExp1Hash_SPlace, out string assExp1Hash_SCode)
        {
            assExp1Hash_SPlace = "";
            assExp1Hash_SCode = "";
            if (Assignment_operator(out string assOperator))
            {
                if (Assignment_expression(out string assExpPlace, out string assExpCode))
                {
                    assExp1Hash_SPlace = assExp1Hash1_IPlace;
                    assExp1Hash_SCode = $"{assExp1Hash1_ICode}{assExpCode}{assExp1Hash1_IPlace}{assOperator}{assExpPlace}\n";
                    return true;
                }
                else { return false; }
            }
            else
            {
                assExp1Hash_SPlace = assExp1Hash1_IPlace;
                assExp1Hash_SCode = assExp1Hash1_ICode;
                return true;
            }
        }

        //Assignment_operator -> = | *= | /= | %= | += | -= 
        bool Assignment_operator(out string assOperator)
        {
            assOperator = "";
            switch (_token)
            {
                case eToken.ASSIGNENT:
                case eToken.PRODUCT_ASSIGNMENT:
                case eToken.DIVISION_ASSIGNMENT:
                case eToken.MODULE_ASSIGNENT:
                case eToken.PLUS_ASSIGNENT:
                case eToken.MINUS_ASSIGNENT:
                    assOperator = _currentToken.Label;
                    GetToken();
                    return true;
                default:
                    return false;
            }
        }

        //Logical_or_expression -> Logical_and_expression Logical_or_expression1Hash 
        bool Logical_or_expression(out string logicOrExpPlace, out string logicOrExpCode)
        {
            logicOrExpPlace = "";
            logicOrExpCode = "";
            if (Logical_and_expression(out string logicAndExpPlace, out string logicAndExpCode))
            {
                var logicOrExp1Hash_IPlace = logicAndExpPlace;
                var logicOrExp1Hash_ICode = logicAndExpCode;
                if (Logical_or_expression1Hash(logicOrExp1Hash_IPlace,
                    logicOrExp1Hash_ICode,
                    out string logicOrExp1Hash_SPlace, out string logicOrExp1Hash_SCode))
                {
                    logicOrExpPlace = logicOrExp1Hash_SPlace;
                    logicOrExpCode = logicOrExp1Hash_SCode;
                    return true;
                }
                else { return false; }
            }
            else { return false; }
        }

        //Logical_or_expression1Hash -> || Logical_and_expression Logical_or_expression1Hash | ? 
        bool Logical_or_expression1Hash(
            string logicOrExp1Hash_IPlace, string logicOrExp1Hash_ICode,
            out string logicOrExp1Hash_SPlace, out string logicOrExp1Hash_SCode)
        {
            logicOrExp1Hash_SPlace = "";
            logicOrExp1Hash_SCode = "";
            if (_token == eToken.LOGICAL_OR)
            {// ||
                GetToken();
                if (Logical_and_expression(out string logicAndExpPlace, out string logicAndExpCode))
                {
                    var logicOrExp1Hash1_IPlace = CreateTempVar();
                    var logicOrExp1Hash1_ICode = logicOrExp1Hash_ICode + logicAndExpCode + CreateCode("&&", logicOrExp1Hash1_IPlace, logicOrExp1Hash_IPlace, logicAndExpPlace);

                    if (Logical_or_expression1Hash(logicOrExp1Hash1_IPlace, logicOrExp1Hash1_ICode,
                        out string logicOrExp1HashPlace, out string logicOrExp1HashCode))
                    {
                        logicOrExp1Hash_SPlace = logicOrExp1HashPlace;
                        logicOrExp1Hash_SCode = logicOrExp1HashCode;

                        return true;
                    }
                    else { return false; }
                }
                else { return false; }
            }
            else
            {
                logicOrExp1Hash_SPlace = logicOrExp1Hash_IPlace;
                logicOrExp1Hash_SCode = logicOrExp1Hash_ICode;
                return true;
            }
        }

        //Logical_and_expression -> Equality_expression Logical_and_expression1Hash 
        bool Logical_and_expression(out string logicAndExpPlace, out string logicAndExpCode)
        {
            logicAndExpPlace = "";
            logicAndExpCode = "";
            if (Equality_expression(out string eqExpPlace, out string eqExpCode))
            {
                var logicAndExp1Hash_IPlace = eqExpPlace;
                var logicAndExp1Hash_ICode = eqExpCode;
                if (Logical_and_expression1Hash(logicAndExp1Hash_IPlace,
                    logicAndExp1Hash_ICode,
                    out string logicAndExp1Hash_SPlace, out string logicAndExp1Hash_SCode))
                {
                    logicAndExpPlace = logicAndExp1Hash_SPlace;
                    logicAndExpCode = logicAndExp1Hash_SCode;
                    return true;
                }
                else { return false; }
            }
            else { return false; }
        }

        //Logical_and_expression1Hash -> && Equality_expression Logical_and_expression1Hash | ? 
        bool Logical_and_expression1Hash(
            string logicAndExp1Hash_IPlace, string logicAndExp1Hash_ICode,
            out string logicAndExp1Hash_SPlace, out string logicAndExp1Hash_SCode)
        {
            logicAndExp1Hash_SPlace = "";
            logicAndExp1Hash_SCode = "";
            if (_token == eToken.LOGICAL_AND)
            {// &&
                GetToken();
                if (Equality_expression(out string eqExpPlace, out string eqExpCode))
                {
                    var logicAndExp1Hash1_IPlace = CreateTempVar();
                    var logicAndExp1Hash1_ICode = logicAndExp1Hash_ICode + eqExpCode + CreateCode("&&", logicAndExp1Hash1_IPlace, logicAndExp1Hash_IPlace, eqExpPlace);

                    if (Logical_and_expression1Hash(logicAndExp1Hash1_IPlace, logicAndExp1Hash1_ICode,
                        out string logicAndExp1HashPlace, out string logicAndExp1HashCode))
                    {
                        logicAndExp1Hash_SPlace = logicAndExp1HashPlace;
                        logicAndExp1Hash_SCode = logicAndExp1HashCode;

                        return true;
                    }
                    else { return false; }
                }
                else { return false; }
            }
            else
            {
                logicAndExp1Hash_SPlace = logicAndExp1Hash_IPlace;
                logicAndExp1Hash_SCode = logicAndExp1Hash_ICode;
                return true;
            }
        }

        //Equality_expression -> Relational_expression Equality_expression1Hash 
        bool Equality_expression(out string eqExpPlace, out string eqExpCode)
        {
            eqExpPlace = "";
            eqExpCode = "";
            if (Relational_expression(out string relExpPlace, out string relExpCode))
            {
                var eqExp1Hash_IPlace = relExpPlace;
                var eqExp1Hash_ICode = relExpCode;
                if (Equality_expression1Hash(eqExp1Hash_IPlace,
                    eqExp1Hash_ICode,
                    out string eqExp1Hash_SPlace, out string eqExp1Hash_SCode))
                {
                    eqExpPlace = eqExp1Hash_SPlace;
                    eqExpCode = eqExp1Hash_SCode;
                    return true;
                }
                else { return false; }
            }
            else { return false; }
        }

        //Equality_expression1Hash -> == Relational_expression Equality_expression1Hash | != Relational_expression Equality_expression1Hash | ? 
        bool Equality_expression1Hash(
              string eqExp1Hash_IPlace, string eqExp1Hash_ICode,
              out string eqExp1Hash_SPlace, out string eqExp1Hash_SCode)
        {
            eqExp1Hash_SPlace = "";
            eqExp1Hash_SCode = "";
            if (Equality_operator(out string eqOperator))
            {
                if (Relational_expression(out string relExpPlace, out string relExpCode))
                {
                    var eqExp1Hash1_IPlace = CreateTempVar();
                    var eqExp1Hash1_ICode = eqExp1Hash_ICode + relExpCode + CreateCode(eqOperator, eqExp1Hash1_IPlace, eqExp1Hash_IPlace, relExpPlace);

                    if (Equality_expression1Hash(eqExp1Hash1_IPlace, eqExp1Hash1_ICode,
                        out string eqExp1HashPlace, out string eqExp1HashCode))
                    {
                        eqExp1Hash_SPlace = eqExp1HashPlace;
                        eqExp1Hash_SCode = eqExp1HashCode;

                        return true;
                    }
                    else { return false; }
                }
                else { return false; }
            }
            else
            {
                eqExp1Hash_SPlace = eqExp1Hash_IPlace;
                eqExp1Hash_SCode = eqExp1Hash_ICode;
                return true;
            }
        }

        bool Equality_operator(out string eqOperator)
        {
            eqOperator = "";
            switch (_token)
            {
                case eToken.EQUALS:
                case eToken.NOT_EQUALS:
                    eqOperator = _currentToken.Label;
                    GetToken();
                    return true;
                default:
                    return false;
            }
        }

        //Relational_expression -> Additive_expression Relational_expression1Hash 
        bool Relational_expression(out string relExpPlace, out string relExpCode)
        {
            relExpPlace = "";
            relExpCode = "";
            if (Additive_expression(out string addExpPlace, out string addExpCode))
            {
                var relExp1Hash_IPlace = addExpPlace;
                var relExp1Hash_ICode = addExpCode;
                if (Relational_expression1Hash(relExp1Hash_IPlace,
                    relExp1Hash_ICode,
                    out string relExp1Hash_SPlace, out string relExp1Hash_SCode))
                {
                    relExpPlace = relExp1Hash_SPlace;
                    relExpCode = relExp1Hash_SCode;
                    return true;
                }
                else { return false; }
            }
            else { return false; }
        }


        //Relational_expression1Hash -> Relational_operator Additive_expression Relational_expression1Hash | ? 
        bool Relational_expression1Hash(
            string relExp1Hash_IPlace, string relExp1Hash_ICode,
            out string relExp1Hash_SPlace, out string relExp1Hash_SCode)
        {
            relExp1Hash_SPlace = "";
            relExp1Hash_SCode = "";
            if (Relational_operator(out string relOperator))
            {
                if (Additive_expression(out string addExpPlace, out string addExpCode))
                {
                    var relExp1Hash1_IPlace = CreateTempVar();
                    var relExp1Hash1_ICode = relExp1Hash_ICode + addExpCode + CreateCode(relOperator, relExp1Hash1_IPlace, relExp1Hash_IPlace, addExpPlace);

                    if (Relational_expression1Hash(relExp1Hash1_IPlace, relExp1Hash1_ICode,
                        out string relExp1HashPlace, out string relExp1HashCode))
                    {
                        relExp1Hash_SPlace = relExp1HashPlace;
                        relExp1Hash_SCode = relExp1HashCode;

                        return true;
                    }
                    else { return false; }
                }
                else { return false; }
            }
            else
            {
                relExp1Hash_SPlace = relExp1Hash_IPlace;
                relExp1Hash_SCode = relExp1Hash_ICode;
                return true;
            }
        }

        //Relational_operator -> > | < | >= | <= 
        bool Relational_operator(out string relOperator)
        {
            relOperator = "";

            switch (_token)
            {
                case eToken.GREATER:
                case eToken.LESS:
                case eToken.GREATER_OR_EQUAL:
                case eToken.LESS_OR_EQUAL:
                    relOperator = _currentToken.Label;
                    GetToken();
                    return true;
                default:
                    return false;
            }
        }

        //Additive_expression -> Multiplicative_expression Additive_expression1Hash 
        bool Additive_expression(out string addExpPlace, out string addExpCode)
        {
            addExpPlace = "";
            addExpCode = "";
            if (Multiplicative_expression(out string mulExpPlace, out string mulExpCode))
            {
                var addExp1Hash_IPlace = mulExpPlace;
                var addExp1Hash_ICode = mulExpCode;
                if (Additive_expression1Hash(addExp1Hash_IPlace,
                    addExp1Hash_ICode,
                    out string addExp1Hash_SPlace, out string addExp1Hash_SCode))
                {
                    addExpPlace = addExp1Hash_SPlace;
                    addExpCode = addExp1Hash_SCode;
                    return true;
                }
                else { return false; }
            }
            else { return false; }
        }

        //Additive_expression1Hash -> + Multiplicative_expression Additive_expression1Hash | - Multiplicative_expression Additive_expression1Hash | ? 
        bool Additive_expression1Hash(
            string addExp1Hash_IPlace, string addExp1Hash_ICode,
            out string addExp1Hash_SPlace, out string addExp1Hash_SCode)
        {
            addExp1Hash_SPlace = "";
            addExp1Hash_SCode = "";
            if (_token == eToken.PLUS)
            {// +
                GetToken();
                if (Multiplicative_expression(out string mulExpPlace, out string mulExpCode))
                {
                    var addExp1Hash1_IPlace = CreateTempVar();
                    var addExp1Hash1_ICode = addExp1Hash_ICode + mulExpCode + CreateCode("+", addExp1Hash1_IPlace, addExp1Hash_IPlace, mulExpPlace);

                    if (Additive_expression1Hash(addExp1Hash1_IPlace, addExp1Hash1_ICode,
                        out string addExp1HashPlace, out string addExp1HashCode))
                    {
                        addExp1Hash_SPlace = addExp1HashPlace;
                        addExp1Hash_SCode = addExp1HashCode;

                        return true;
                    }
                    else { return false; }
                }
                else { return false; }
            }
            else if (_token == eToken.MINUS)
            {// -
                GetToken();
                if (Multiplicative_expression(out string mulExpPlace, out string mulExpCode))
                {
                    var addExp1Hash1_IPlace = CreateTempVar();
                    var addExp1Hash1_ICode = addExp1Hash_ICode + mulExpCode + CreateCode("-", addExp1Hash1_IPlace, addExp1Hash_IPlace, mulExpPlace);
                    if (Additive_expression1Hash(addExp1Hash1_IPlace, addExp1Hash1_ICode,
                        out string addExp1HashPlace, out string addExp1HashCode))
                    {
                        addExp1Hash_SPlace = addExp1HashPlace;
                        addExp1Hash_SCode = addExp1HashCode;

                        return true;
                    }
                    else { return false; }
                }
                else { return false; }
            }
            else
            {
                addExp1Hash_SPlace = addExp1Hash_IPlace;
                addExp1Hash_SCode = addExp1Hash_ICode;
                return true;
            }
        }

        //Multiplicative_expression -> Primary_expression Multiplicative_expression1Hash 
        bool Multiplicative_expression(out string mulExpPlace, out string mulExpCode)
        {
            mulExpPlace = "";
            mulExpCode = "";
            if (Unary_expression(out string unExpPlace, out string unExpCode))
            {
                var mulExp1Hash_IPlace = unExpPlace;
                var mulExp1Hash_ICode = unExpCode;
                if (Multiplicative_expression1Hash(mulExp1Hash_IPlace,
                    mulExp1Hash_ICode,
                    out string mulExp1Hash_SPlace, out string mulExp1Hash_SCode))
                {
                    mulExpPlace = mulExp1Hash_SPlace;
                    mulExpCode = mulExp1Hash_SCode;
                    return true;
                }
                else { return false; }
            }
            else { return false; }
        }

        //Multiplicative_expression1Hash -> * Primary_expression Multiplicative_expression1Hash | / Primary_expression Multiplicative_expression1Hash | % Primary_expression Multiplicative_expression1Hash | ? 
        bool Multiplicative_expression1Hash(
            string mulExp1Hash_IPlace, string mulExp1Hash_ICode,
            out string mulExp1Hash_SPlace, out string mulExp1Hash_SCode)
        {
            mulExp1Hash_SPlace = "";
            mulExp1Hash_SCode = "";

            if (_token == eToken.PRODUCT)
            {// *
                GetToken();
                if (Unary_expression(out string unExpPlace, out string unExpCode))
                {
                    var mulExp1Hash1_IPlace = CreateTempVar();
                    var mulExp1Hash1_ICode = mulExp1Hash_ICode + unExpCode + CreateCode("*", mulExp1Hash1_IPlace, mulExp1Hash_IPlace, unExpPlace);
                    if (Multiplicative_expression1Hash(mulExp1Hash1_IPlace, mulExp1Hash1_ICode,
                        out string mulExp1HashPlace, out string mulExp1HashCode))
                    {
                        mulExp1Hash_SPlace = mulExp1HashPlace;
                        mulExp1Hash_SCode = mulExp1HashCode;
                        return true;
                    }
                    else { return false; }
                }
                else { return false; }
            }
            else if (_token == eToken.DIVISION)
            {// /
                GetToken();
                if (Unary_expression(out string unExpPlace, out string unExpCode))
                {
                    var mulExp1Hash1_IPlace = CreateTempVar();
                    var mulExp1Hash1_ICode = mulExp1Hash_ICode + unExpCode + CreateCode("/", mulExp1Hash1_IPlace, mulExp1Hash_IPlace, unExpPlace);
                    if (Multiplicative_expression1Hash(mulExp1Hash1_IPlace, mulExp1Hash1_ICode,
                        out string mulExp1HashPlace, out string mulExp1HashCode))
                    {
                        mulExp1Hash_SPlace = mulExp1HashPlace;
                        mulExp1Hash_SCode = mulExp1HashCode;
                        return true;
                    }
                    else { return false; }
                }
                else { return false; }
            }
            else if (_token == eToken.MODULE)
            {// %
                GetToken();
                if (Unary_expression(out string unExpPlace, out string unExpCode))
                {
                    var mulExp1Hash1_IPlace = CreateTempVar();
                    var mulExp1Hash1_ICode = mulExp1Hash_ICode + unExpCode + CreateCode("/", mulExp1Hash1_IPlace, mulExp1Hash_IPlace, unExpPlace);
                    if (Multiplicative_expression1Hash(mulExp1Hash1_IPlace, mulExp1Hash1_ICode,
                        out string mulExp1HashPlace, out string mulExp1HashCode))
                    {
                        mulExp1Hash_SPlace = mulExp1HashPlace;
                        mulExp1Hash_SCode = mulExp1HashCode;
                        return true;
                    }
                    else { return false; }
                }
                else { return false; }
            }
            else
            {
                mulExp1Hash_SPlace = mulExp1Hash_IPlace;
                mulExp1Hash_SCode = mulExp1Hash_ICode;
                return true;
            }
        }

        //Unary_expression -> Unary_operator Unary_expression | Postfix_expression 
        bool Unary_expression(out string unExpPlace, out string unExpCode)
        {
            unExpPlace = "";
            unExpCode = "";
            if (Unary_operator(out eToken _unToken))
            {
                if (Unary_expression(out unExpPlace, out string unExpCode1))
                {
                    var newUnaryPlace = CreateTempVar();
                    switch (_unToken)
                    {
                        case eToken.PLUS:
                            unExpCode = $"{unExpCode1}{newUnaryPlace} = +{unExpPlace}\n";
                            break;
                        case eToken.MINUS:
                            unExpCode = $"{unExpCode1}{newUnaryPlace} = -{unExpPlace}\n";
                            break;
                        case eToken.LOGICAL_NOT:
                            unExpCode = $"{unExpCode1}{newUnaryPlace} = !{unExpPlace}\n";
                            break;
                        case eToken.DECREMENT:
                            unExpCode = $"{unExpCode1}\n{CreateCode(" -", unExpPlace, unExpPlace, "1")}";
                            break;
                        case eToken.INCREMENT:
                            unExpCode = $"{unExpCode1}\n{CreateCode(" +", unExpPlace, unExpPlace, "1")}";
                            break;
                        default:
                            return false;
                    }
                    if (_unToken == eToken.PLUS ||
                        _unToken == eToken.MINUS ||
                        _unToken == eToken.LOGICAL_NOT)
                        unExpPlace = newUnaryPlace;
                    return true;
                }
                else { return false; }
            }
            else if (Postfix_expression(out string postFixExpPlace, out string postFixExpCode)) // trocar para Postfix_expression
            {
                unExpPlace = postFixExpPlace;
                unExpCode = postFixExpCode;
                return true;
            }
            else { return false; }
        }

        //Unary_operator -> + | - | ! | -- | ++ 
        bool Unary_operator(out eToken _unToken)
        {
            _unToken = eToken.LEXICAL_ERROR;

            switch (_token)
            {
                case eToken.PLUS:
                case eToken.MINUS:
                case eToken.LOGICAL_NOT:
                case eToken.DECREMENT:
                case eToken.INCREMENT:
                    _unToken = _token;
                    GetToken();
                    return true;
                default:
                    return false;
            }
        }

        //Postfix_expression -> Primary_expression Postfix_expression1Linha 
        bool Postfix_expression(out string postFixExpPlace, out string postFixExpCode)
        {
            postFixExpPlace = "";
            postFixExpCode = "";
            if (Primary_expression(out string primExpPlace, out string primExpCode))
            {
                var postFixExp1_IPlace = primExpPlace;
                var postFixExp1_ICode = primExpCode;
                if (Postfix_expression1Linha(postFixExp1_IPlace, postFixExp1_ICode,
                        out string postFixExp1Hash_SPlace, out string postFixExp1Hash_SCode))
                {
                    postFixExpPlace = postFixExp1Hash_SPlace;
                    postFixExpCode = postFixExp1Hash_SCode;
                    return true;
                }
                else { return false; }
            }
            else { return false; }
        }

        //Postfix_expression1Linha -> Postfix_operator | ? 
        bool Postfix_expression1Linha(string postFixExp1_IPlace, string postFixExp1_ICode,
                        out string postFixExp1Hash_SPlace, out string postFixExp1Hash_SCode)
        {
            if (Postfix_operator(out string postFixOperator))
            {
                postFixExp1Hash_SPlace = CreateTempVar();
                postFixExp1Hash_SCode = $"{postFixExp1_ICode}{postFixExp1Hash_SPlace}={postFixExp1_IPlace}\n" +
                                        CreateCode(postFixOperator, postFixExp1_IPlace, postFixExp1_IPlace, "1");
                return true;
            }
            else 
            {
                postFixExp1Hash_SPlace = postFixExp1_IPlace;
                postFixExp1Hash_SCode = postFixExp1_ICode;
                return true; 
            }
        }


        //Postfix_operator -> ++ | -- 
        bool Postfix_operator(out string postFixOperator)
        {
            postFixOperator = "";

            switch (_token)
            {
                case eToken.DECREMENT:
                    postFixOperator = "-";
                    GetToken();
                    return true;
                case eToken.INCREMENT:
                    postFixOperator = "+";
                    GetToken();
                    return true;
                default:
                    return false;
            }
        }

        //Primary_expression -> identifier | Constant | ( Expression ) 
        bool Primary_expression(out string primExpPlace, out string primExpCode)
        {
            primExpCode = "";
            primExpPlace = "";
            if (_token == eToken.IDENTIFIER)
            {// identifier
                primExpPlace = _currentToken.Label;
                primExpCode = "";
                GetToken();
                return true;
            }
            else if (Constant(out primExpPlace, out primExpCode))
            {
                return true;
            }
            //else if (_token == eToken.OPEN_PARENTHESIS)
            //{// (
            //    GetToken();
            //    if (Expression())
            //    {
            //        if (_token == eToken.CLOSE_PARENTHESIS)
            //        {// )
            //            GetToken();
            //            return true;
            //        }
            //        else { return false; }
            //    }
            //    else { return false; }
            //}
            else { return false; }
        }

        //Constant -> int_constant | float_constant 
        bool Constant(out string constantPlace, out string constantCod)
        {
            constantPlace = "";
            constantCod = "";

            if (_token == eToken.INTEGER_CONSTANT)
            {// int_constant
                constantPlace = CreateTempVar();
                constantCod = CreateCode("=", constantPlace, _currentToken.Label);
                GetToken();
                return true;
            }
            else if (_token == eToken.FLOATING_POINT_CONSTANT)
            {// float_constant
                constantPlace = CreateTempVar();
                constantCod = CreateCode("=", constantPlace, _currentToken.Label);
                GetToken();
                return true;
            }
            else { return false; }
        }
        private string CreateCode(string operation, string destiny, string left, string right)
        {
            return $"{destiny}={ left }{operation}{right}\n";
        }

        private string CreateCode(string operation, string left, string right)
        {
            return $"{ left }{operation}{right}\n";
        }

        //Expression_statement -> ; | Expression ; 
        bool Expression_statement(out string expStmtPlace, out string expStmtCode)
        {
            expStmtPlace = "";
            expStmtCode = "";
            if (_token == eToken.SEMICOLON)
            {// ;
                GetToken();
                return true;
            }
            else if (Expression(out string expPlace, out string expCode))
            {
                expStmtPlace = expPlace;
                expStmtCode = expCode;
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
        bool Expression(out string expPlace, out string expCode)
        {
            expPlace = "";
            expCode = "";
            if (Assignment_expression(out string assExpressionPlace, out string assExpressionCode))
            {
                var exp1Hash_IPlace = assExpressionPlace;
                var exp1Hash_ICode = assExpressionCode;
                if (Expression1Hash(exp1Hash_IPlace, exp1Hash_ICode,
                    out string exp1Hash_SPlace, out string exp1Hash_SCode))
                {
                    expPlace = exp1Hash_SPlace;
                    expCode = exp1Hash_SCode;
                    return true;
                }
                else { return false; }
            }
            else { return false; }
        }

        //Expression1Hash -> , Assignment_expression Expression1Hash | ? 
        bool Expression1Hash(string exp1Hash_IPlace, string exp1Hash_ICode,
                    out string exp1Hash_SPlace, out string exp1Hash_SCode)
        {
            exp1Hash_SPlace = "";
            exp1Hash_SCode = "";
            if (_token == eToken.COMMA)
            {// ,
                GetToken();
                if (Assignment_expression(out string assExpressionPlace, out string assExpressionCode))
                {
                    var exp1Hash1_IPlace = assExpressionPlace;
                    var exp1Hash1_ICode = assExpressionCode;
                    if (Expression1Hash(exp1Hash1_IPlace, exp1Hash1_ICode,
                        out string exp1Hash1_SPlace, out string exp1Hash1_SCode))
                    {
                        return true;
                    }
                    else { return false; }
                }
                else { return false; }
            }
            else 
            {
                exp1Hash_SPlace = exp1Hash_IPlace;
                exp1Hash_SCode = exp1Hash_ICode;
                return true; 
            }
        }
    }
}
