using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace DotNetCCompiler
{
    public class LexicalAnalyzer
    {
        #region Fields
        private enum State
        {
            Initial,
            Word,
            Number,
        }

        private char _char;
        private State _state = State.Initial;
        private string _lexical = string.Empty;
        private bool _hasPoint;
        private string _stringLine;
        private int _currentLine;
        private int _currentColumn;
        private bool EndOfFile;

        private readonly Dictionary<string, eToken> KeyWords = new Dictionary<string, eToken>()
        {
            {"for", eToken.FOR},
            {"while", eToken.WHILE},
            {"if", eToken.IF},
            {"do", eToken.DO},
            {"else", eToken.ELSE},
            {"int", eToken.INT},
            {"float", eToken.FLOAT},
            {"continue", eToken.CONTINUE},
            {"break", eToken.BREAK},
        };

        private StreamReader InStreamReader { get; }

        #endregion

        internal static StreamWriter OutStreamWriter { get; set; }
        public List<TokenResult> TokenResultList { get; private set; } = new List<TokenResult>();

        #region Constructor
        public LexicalAnalyzer(Stream fileStream)
        {
            InStreamReader = new StreamReader(fileStream);

            string path = Path.Combine(Path.GetDirectoryName((fileStream as FileStream).Name), "Saida.lex");

            OutStreamWriter = File.CreateText(path);
        }
        #endregion

        private void NextLine()
        {
            ReadLine();
        }

        private void ReadLine()
        {
            _stringLine = InStreamReader.ReadLine();
            if (_stringLine == null) 
                EndOfFile = true;
            _stringLine += '\n';
            _currentLine++;
        }


        private void GetChar()
        {
            if (string.IsNullOrEmpty(_stringLine) || _currentColumn >= _stringLine.Length)
            {
                NextLine();
                _currentColumn = 0;
                _char = _stringLine[_currentColumn++];
                return;
            }


            _char = _stringLine[_currentColumn++];
        }

        public void Analyze()
        {
            GetChar();
            while (!EndOfFile)
            {
                TokenResult tokenResult = GetToken();
                if (tokenResult == null) continue;

                LexicalErase();
                tokenResult.Write();
                TokenResultList.Add(tokenResult);
            }
            var finalTokenResult = new TokenResult(eToken.EOF, "", _currentLine, _currentColumn);
            finalTokenResult.Write();
            TokenResultList.Add(finalTokenResult);
            OutStreamWriter.Close();
        }

        private TokenResult GetToken()
        {
            _lexical += _char;
            switch (_state)
            {
                case State.Initial:
                    if (_char == ' ' || _char == '\t' || _char == '\n')
                    {
                        LexicalErase();
                        GetChar();
                        return null;
                    }

                    if (char.IsLetter(_char) || _char == '_')
                    {
                        GetChar();
                        _state = State.Word;
                        return null;
                    }

                    if (char.IsDigit(_char))
                    {
                        GetChar();
                        _state = State.Number;
                        return null;
                    }

                    if (_char == '(')
                    {
                        SaveContextGetCharLexicalErase(out int line, out int column, out string lexical);
                        return new TokenResult(eToken.OPEN_PARENTHESIS, lexical, line, column);
                    }
                    if (_char == ')')
                    {
                        SaveContextGetCharLexicalErase(out int line, out int column, out string lexical);
                        return new TokenResult(eToken.CLOSE_PARENTHESIS, lexical, line, column);
                    }
                    if (_char == '{')
                    {
                        SaveContextGetCharLexicalErase(out int line, out int column, out string lexical);
                        return new TokenResult(eToken.OPEN_BRACE, lexical, line, column);
                    }
                    if (_char == '}')
                    {
                        SaveContextGetCharLexicalErase(out int line, out int column, out string lexical);
                        return new TokenResult(eToken.CLOSE_BRACE, lexical, line, column);
                    }
                    if (_char == ';')
                    {
                        SaveContextGetCharLexicalErase(out int line, out int column, out string lexical);
                        return new TokenResult(eToken.SEMICOLON, lexical, line, column);
                    }
                    if (_char == ',')
                    {
                        SaveContextGetCharLexicalErase(out int line, out int column, out string lexical);
                        return new TokenResult(eToken.COMMA, lexical, line, column);
                    }
                    if (_char == '=')
                    {
                        GetChar();
                        if (_char == '=')
                        {
                            _lexical += _char;
                            SaveContextGetCharLexicalErase(out int line, out int column, out string lexical);
                            return new TokenResult(eToken.EQUALS, lexical, line, column);
                        }
                        else
                        {
                            UndoGetChar();
                            SaveContextGetCharLexicalErase(out int line, out int column, out string lexical);
                            return new TokenResult(eToken.ASSIGNENT, lexical, line, column);
                        }
                    }
                    if (_char == '!')
                    {
                        GetChar();
                        if (_char == '=')
                        {
                            _lexical += _char;
                            SaveContextGetCharLexicalErase(out int line, out int column, out string lexical);
                            return new TokenResult(eToken.NOT_EQUALS, lexical, line, column);
                        }
                        else
                        {
                            UndoGetChar();
                            SaveContextGetCharLexicalErase(out int line, out int column, out string lexical);
                            return new TokenResult(eToken.LOGICAL_NOT, lexical, line, column);
                        }
                    }

                    if (_char == '>')
                    {
                        GetChar();
                        if (_char == '=')
                        {
                            _lexical += _char;
                            SaveContextGetCharLexicalErase(out int line, out int column, out string lexical);
                            return new TokenResult(eToken.GREATER_OR_EQUAL, lexical, line, column);
                        }                     
                        else
                        {
                            UndoGetChar();
                            SaveContextGetCharLexicalErase(out int line, out int column, out string lexical);
                            return new TokenResult(eToken.GREATER, lexical, line, column);
                        }
                    }

                    if (_char == '<')
                    {
                        GetChar();
                        if (_char == '=')
                        {
                            _lexical += _char;
                            SaveContextGetCharLexicalErase(out int line, out int column, out string lexical);
                            return new TokenResult(eToken.LESS_OR_EQUAL, lexical, line, column);
                        }                    
                        else
                        {
                            UndoGetChar();
                            SaveContextGetCharLexicalErase(out int line, out int column, out string lexical);
                            return new TokenResult(eToken.LESS, lexical, line, column);
                        }
                    }

                    if (_char == '+')
                    {
                        GetChar();
                        if (_char == '=')
                        {
                            _lexical += _char;
                            SaveContextGetCharLexicalErase(out int line, out int column, out string lexical);
                            return new TokenResult(eToken.PLUS_ASSIGNENT, lexical, line, column);
                        }
                        if (_char == '+')
                        {
                            _lexical += _char;
                            SaveContextGetCharLexicalErase(out int line, out int column, out string lexical);
                            return new TokenResult(eToken.INCREMENT, lexical, line, column);
                        }
                        else
                        {
                            UndoGetChar();
                            SaveContextGetCharLexicalErase(out int line, out int column, out string lexical);
                            return new TokenResult(eToken.PLUS, lexical, line, column);
                        }
                    }

                    if (_char == '-')
                    {
                        GetChar();
                        if (_char == '=')
                        {
                            _lexical += _char;
                            SaveContextGetCharLexicalErase(out int line, out int column, out string lexical);
                            return new TokenResult(eToken.MINUS_ASSIGNENT, lexical, line, column);
                        }
                        if (_char == '-')
                        {
                            _lexical += _char;
                            SaveContextGetCharLexicalErase(out int line, out int column, out string lexical);
                            return new TokenResult(eToken.DECREMENT, lexical, line, column);
                        }
                        else
                        {
                            UndoGetChar();
                            SaveContextGetCharLexicalErase(out int line, out int column, out string lexical);
                            return new TokenResult(eToken.MINUS, lexical, line, column);
                        }
                    }

                    if (_char == '*')
                    {
                        GetChar();
                        if (_char == '=')
                        {
                            _lexical += _char;
                            SaveContextGetCharLexicalErase(out int line, out int column, out string lexical);
                            return new TokenResult(eToken.PRODUCT_ASSIGNMENT, lexical, line, column);
                        }
                        
                        else
                        {
                            UndoGetChar();
                            SaveContextGetCharLexicalErase(out int line, out int column, out string lexical);
                            return new TokenResult(eToken.PRODUCT, lexical, line, column);
                        }
                    }

                    if (_char == '/')
                    {
                        GetChar();
                        if (_char == '=')
                        {
                            _lexical += _char;
                            SaveContextGetCharLexicalErase(out int line, out int column, out string lexical);
                            return new TokenResult(eToken.DIVISION_ASSIGNMENT, lexical, line, column);
                        }

                        else
                        {
                            UndoGetChar();
                            SaveContextGetCharLexicalErase(out int line, out int column, out string lexical);
                            return new TokenResult(eToken.DIVISION, lexical, line, column);
                        }
                    }

                    if (_char == '%')
                    {
                        GetChar();
                        if (_char == '=')
                        {
                            _lexical += _char;
                            SaveContextGetCharLexicalErase(out int line, out int column, out string lexical);
                            return new TokenResult(eToken.MODULE_ASSIGNENT, lexical, line, column);
                        }

                        else
                        {
                            UndoGetChar();
                            SaveContextGetCharLexicalErase(out int line, out int column, out string lexical);
                            return new TokenResult(eToken.MODULE, lexical, line, column);
                        }
                    }

                    if (_char == '|')
                    {
                        GetChar();
                        if (_char == '|')
                        {
                            _lexical += _char;
                            SaveContextGetCharLexicalErase(out int line, out int column, out string lexical);
                            return new TokenResult(eToken.LOGICAL_OR, lexical, line, column);
                        }

                        else
                        {
                            UndoGetChar();
                            SaveContextGetCharLexicalErase(out int line, out int column, out string lexical);
                            return new TokenResult(eToken.LEXICAL_ERROR, lexical, line, column);
                        }
                    }

                    if (_char == '&')
                    {
                        GetChar();
                        if (_char == '&')
                        {
                            _lexical += _char;
                            SaveContextGetCharLexicalErase(out int line, out int column, out string lexical);
                            return new TokenResult(eToken.LOGICAL_AND, lexical, line, column);
                        }

                        else
                        {
                            UndoGetChar();
                            SaveContextGetCharLexicalErase(out int line, out int column, out string lexical);
                            return new TokenResult(eToken.LEXICAL_ERROR, lexical, line, column);
                        }
                    }

                    break;

                case State.Word:
                    if (IsLetter() || _char == '_' || char.IsDigit(_char)) return NextChar();
                    else
                    {
                        BackSpaceUndoGetChar();
                        SaveContextGetCharLexicalErase(out int line, out int column, out string lexical);
                        _state = State.Initial;

                        eToken token;
                        if (KeyWords.ContainsKey(lexical))
                            token = KeyWords[lexical];
                        else token = eToken.IDENTIFIER;

                        return new TokenResult(token, lexical, line, column);
                    }

                case State.Number:
                    if (char.IsDigit(_char))
                    {
                        GetChar();
                        return null;
                    }
                    else if (_char == '.' && !_hasPoint)
                    {
                        GetChar();
                        _hasPoint = true;
                        return null;
                    }
                    else if (_char == '.' && _hasPoint)
                    {
                        _state = State.Initial;
                        SaveContextGetCharLexicalErase(out int line, out int column, out string lexical);
                        return new TokenResult(eToken.LEXICAL_ERROR, lexical, line, column);
                    }
                    else
                    {
                        _state = State.Initial;
                        BackSpaceUndoGetChar();
                        SaveContextGetCharLexicalErase(out int line, out int column, out string lexical);

                        return int.TryParse(lexical, out _) ? new TokenResult(eToken.INTEGER_CONSTANT, lexical, line, column) :
                            float.TryParse(lexical, out _) ? new TokenResult(eToken.FLOATING_POINT_CONSTANT, lexical, line, column) :
                            new TokenResult(eToken.LEXICAL_ERROR, lexical, line, column);
                    }

                default:
                    throw new ArgumentOutOfRangeException();
            }

            return null;
        }

        private TokenResult NextChar()
        {
            GetChar();
            return null;
        }

        private void BackSpaceUndoGetChar()
        {
            BackSpace();
            UndoGetChar();
        }

        private void UndoGetChar() => _currentColumn--;

        private void SaveContextGetCharLexicalErase(out int line, out int column, out string lexical)
        {
            SaveContext(out line, out column, out lexical);
            GetChar();
            LexicalErase();
        }

        private void SaveContext(out int line, out int column, out string lexical)
        {
            line = _currentLine;
            column = _currentColumn;
            lexical = _lexical;
        }

        private void LexicalErase() => _lexical = string.Empty;

        private void SkipLine() => _currentColumn = _stringLine.Length;

        private bool IsLetter() => _char >= 'a' && _char <= 'z' || _char >= 'A' && _char <= 'Z';


        private void BackSpace() => _lexical = _lexical.Remove(_lexical.Length - 1);
    }
}