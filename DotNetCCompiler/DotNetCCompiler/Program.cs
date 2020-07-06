using System;
using System.IO;

namespace DotNetCCompiler
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");

            var testFile = @"C:\GitHub\CCompiler\code\testfile.c";
            Console.WriteLine($"Iniciando análise sintática: {testFile}");
            var fileStream = File.OpenRead(testFile);
            var lexical = new LexicalAnalyzer(fileStream);
            lexical.Analyze();
            Console.WriteLine($"Verifique o arquivo de saida gerado em: {(LexicalAnalyzer.OutStreamWriter.BaseStream as FileStream).Name}");

            var syntactic = new SyntacticAnalyzer(lexical.TokenResultList);
            syntactic.Analyze();


        }
    }
}
