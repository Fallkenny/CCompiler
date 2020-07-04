using System;
using System.Collections.Generic;
using System.Text;

namespace DotNetCCompiler
{
    public enum eToken
    {
        LEXICAL_ERROR,
        RESERVED_WORD,
        CONSTANT,// constant
        IDENTIFIER,// identifier
        MAIN,// main
        OPEN_BRACE,// {
        CLOSE_BRACE, // }
        SEMICOLON, // ;
        COMMA, // ,
        ASSIGNENT, //
        OPEN_BRACKET,// [
        CLOSE_BRACKET,// ]
        DOT,// .
        LOGICAL_NOT,// !
        LOGICAL_OR, // ||
        LOGICAL_AND,// &&
        EQUALS, // 
        NOT_EQUALS, // ! 
        LESS, // <
        GREATER,// >
        PLUS, // +
        MINUS,// -
        PRODUCT,// *
        DIVISION, // /
        MODULE, // %
        INCREMENT,// ++
        DECREMENT,// --
        OPEN_PARENTHESIS, // (
        CLOSE_PARENTHESIS,// )
        PRODUCT_ASSIGNMENT, // * 
        DIVISION_ASSIGNMENT,// / 
        MODULE_ASSIGNENT, // % 
        PLUS_ASSIGNENT, // + 
        MINUS_ASSIGNENT,// - 
        FOR,// for
        WHILE,// while
        IF, // if
        DO, // do
        ELSE, // else
        INT,// int
        FLOAT,// float
        CONTINUE, // continue
        BREAK,// break
        INTEGER_CONSTANT,
        FLOATING_POINT_CONSTANT,
        GREATER_OR_EQUAL,
        LESS_OR_EQUAL,
    }
}
