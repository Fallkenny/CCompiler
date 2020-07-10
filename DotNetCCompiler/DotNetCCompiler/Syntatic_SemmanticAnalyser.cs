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
            _tokenEnumerator.MoveNext();
            _currentToken = _tokenEnumerator.Current;
            _token = _currentToken.Token;
        }

        bool Program()
        {
            if (Additive_expression(out string place, out string code))
            {
                return true;
            }
            else
            {
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
                    if(_unToken == eToken.PLUS||
                        _unToken == eToken.MINUS||
                        _unToken == eToken.LOGICAL_NOT)
                    unExpPlace = newUnaryPlace;
                    return true;
                }
                else { return false; }
            }
            else if (Primary_expression(out string primExpPlace, out string primExpCode)) // trocar para Postfix_expression
            {
                unExpPlace = primExpPlace;
                unExpCode = primExpCode;
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

        //Postfix_expression -> Primary_expression Postfix_expression1Hash
        bool Postfix_expression(out string postFixExpressionPlace, out string postFixExpressionCode)
        {
            postFixExpressionPlace = "";
            postFixExpressionCode = "";
            if (Primary_expression(out postFixExpressionPlace, out postFixExpressionCode))
            {
                if (Postfix_expression1Hash(out postFixExpressionPlace, out postFixExpressionCode))
                {
                    return true;
                }
                else { return false; }
            }
            else { return false; }
        }

        //Postfix_expression1Hash -> ++ Postfix_expression1Hash | -- Postfix_expression1Hash | ? 
        bool Postfix_expression1Hash(out string postFixExpressionPlace, out string postFixExpressionCode)
        {
            postFixExpressionPlace = "";
            postFixExpressionCode = "";
            if (_token == eToken.INCREMENT)
            {// ++
                GetToken();
                if (Postfix_expression1Hash(out postFixExpressionPlace, out postFixExpressionCode))
                {
                    return true;
                }
                else { return false; }
            }
            else if (_token == eToken.DECREMENT)
            {// --
                GetToken();
                if (Postfix_expression1Hash(out postFixExpressionPlace, out postFixExpressionCode))
                {
                    return true;
                }
                else { return false; }
            }
            else { return true; }
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
        //bool Expression_statement()
        //{
        //    if (_token == eToken.SEMICOLON)
        //    {// ;
        //        GetToken();
        //        return true;
        //    }
        //    else if (Expression())
        //    {
        //        if (_token == eToken.SEMICOLON)
        //        {// ;
        //            GetToken();
        //            return true;
        //        }
        //        else { return false; }
        //    }
        //    else { return false; }
        //}

        //Expression -> Postfix_expression Expression1Hash 
        //bool Expression()
        //{
        //    if (Postfix_expression())
        //    {
        //        if (Expression1Hash())
        //        {
        //            return true;
        //        }
        //        else { return false; }
        //    }
        //    else { return false; }
        //}

        ////Expression1Hash -> , Postfix_expression Expression1Hash | ? 
        //bool Expression1Hash()
        //{
        //    if (_token == eToken.COMMA)
        //    {// ,
        //        GetToken();
        //        if (Postfix_expression())
        //        {
        //            if (Expression1Hash())
        //            {
        //                return true;
        //            }
        //            else { return false; }
        //        }
        //        else { return false; }
        //    }
        //    else { return true; }
        //}


    }
}
