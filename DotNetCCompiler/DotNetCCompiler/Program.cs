using System;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Threading;

namespace DotNetCCompiler
{
    public class Program
    {
        public static void Main(string[] args)
        {
            Console.Clear();
            DrawText();
            Console.ForegroundColor = ConsoleColor.Gray;
            string testFile = (!args.Any() && Debugger.IsAttached) 
                              ? @"C:\GitHub\CCompiler\code\testfile.c"
                              :args[0];

            Console.WriteLine($"Iniciando análise léxica: {testFile}");
            Console.Write("...\n");
            var fileStream = File.OpenRead(testFile);
            var lexical = new LexicalAnalyzer(fileStream);
            lexical.Analyze();
            Console.WriteLine($"Verifique o arquivo de saida gerado em: {(LexicalAnalyzer.OutStreamWriter.BaseStream as FileStream).Name}");
            Console.Write("...\n");
            Console.WriteLine($"Iniciando análise sintática + semântica + compilação: {testFile}");
            Console.Write("...\n");
            var syntactic = new Syntactic_SemmanticAnalyser(lexical.TokenResultList);
            if (syntactic.Compile(out string _3adressCode))
            {
                var copiledPath = Path.Combine(Path.GetDirectoryName(testFile), $"compiled_{Path.GetFileNameWithoutExtension(testFile)}.3addrCode");
                var file = File.CreateText(copiledPath);
                file.Write(_3adressCode);
                file.Close();
                Console.ForegroundColor = ConsoleColor.Green;
                Console.WriteLine($"Verifique o arquivo de saida gerado em: {copiledPath}");
                Console.Write(".\n.\n.\n");
                Console.ForegroundColor = ConsoleColor.Red;
                Console.Write("Para selecionar outro arquivo, use o diálogo principal");
                Console.Write("...\n");
                
            }
        }

        private static void DrawText()
        {
            Console.ForegroundColor = ConsoleColor.DarkBlue;
            Console.WriteLine("=======================================================================================================");
            Console.WriteLine("=======================================================================================================");
            Console.WriteLine("=======================================================================================================");
            Console.ForegroundColor = ConsoleColor.DarkGreen;
            Console.WriteLine("░░░███╗░░██╗███████╗████████╗  ░█████╗░  ░█████╗░░█████╗░███╗░░░███╗██████╗░██╗██╗░░░░░███████╗██████╗░");
            Console.WriteLine("░░░████╗░██║██╔════╝╚══██╔══╝  ██╔══██╗  ██╔══██╗██╔══██╗████╗░████║██╔══██╗██║██║░░░░░██╔════╝██╔══██╗");
            Console.WriteLine("░░░██╔██╗██║█████╗░░░░░██║░░░  ██║░░╚═╝  ██║░░╚═╝██║░░██║██╔████╔██║██████╔╝██║██║░░░░░█████╗░░██████╔╝");
            Console.WriteLine("░░░██║╚████║██╔══╝░░░░░██║░░░  ██║░░██╗  ██║░░██╗██║░░██║██║╚██╔╝██║██╔═══╝░██║██║░░░░░██╔══╝░░██╔══██╗");
            Console.WriteLine("██╗██║░╚███║███████╗░░░██║░░░  ╚█████╔╝  ╚█████╔╝╚█████╔╝██║░╚═╝░██║██║░░░░░██║███████╗███████╗██║░░██║");
            Console.WriteLine("╚═╝╚═╝░░╚══╝╚══════╝░░░╚═╝░░░  ░╚════╝░  ░╚════╝░░╚════╝░╚═╝░░░░░╚═╝╚═╝░░░░░╚═╝╚══════╝╚══════╝╚═╝░░╚═╝");
            Console.ForegroundColor = ConsoleColor.DarkBlue;
            Console.WriteLine("=======================================================================================================");
            Console.WriteLine("=======================================================================================================");
            Console.WriteLine("=======================================================================================================");
            Console.ForegroundColor = ConsoleColor.DarkGray;
            Console.WriteLine("=======================================================================================================");
            Console.WriteLine("=======================================================================================================");
            Console.WriteLine("=============█▀▀ █▀▀ █░░ █ █▀█ █▀▀   █▀▀ █ █▀ █▀▀ █░█ █▀▀ █▀█   █▀▄ ▄▀█   █▀ █ █░░ █░█ ▄▀█=============");
            Console.WriteLine("=============█▀░ ██▄ █▄▄ █ █▀▀ ██▄   █▀░ █ ▄█ █▄▄ █▀█ ██▄ █▀▄   █▄▀ █▀█   ▄█ █ █▄▄ ▀▄▀ █▀█=============");
            Console.WriteLine("=======================================================================================================");
            Console.WriteLine("=======================================================================================================");
            Console.Write(".\n...\n");
          
        }
    }
}
