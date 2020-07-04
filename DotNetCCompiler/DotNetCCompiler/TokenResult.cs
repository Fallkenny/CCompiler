using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Text;

namespace DotNetCCompiler
{
    public class TokenResult
    {
        public TokenResult(eToken token, string label, int line, int column)
        {
            Token = token;
            Label = label;
            Line = line;
            Column = column;
        }

        public eToken Token { get; set; }
        public string Label { get; set; }
        public int Line { get; set; }
        public int Column { get; set; }

        public void Write()
        {
            LexicalAnalyzer.OutStreamWriter.WriteLine(
                $"{Line},{Column - Label.Length}-{Line},{Column}\t {Token} \t {Label} ");

            Debug.WriteLine($"{Line},{Column - Label.Length}-{Line},{Column}\t {Token} \t {Label} ");
        }
    }
}
