using System;
using System.IO;

namespace DotNetCCompiler
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");
            //test();
            var testFile = @"C:\GitHub\CCompiler\code\testinprogress.c";
            Console.WriteLine($"Iniciando análise sintática: {testFile}");
            var fileStream = File.OpenRead(testFile);
            var lexical = new LexicalAnalyzer(fileStream);
            lexical.Analyze();
            Console.WriteLine($"Verifique o arquivo de saida gerado em: {(LexicalAnalyzer.OutStreamWriter.BaseStream as FileStream).Name}");

            var syntactic = new Syntatic_SemmanticAnalyser(lexical.TokenResultList);
            syntactic.Analyze();
        }

        static void test()
        {
            int a = 2;
            int b = 3;
            int c = a;
            float devil = 6.66f;
            if (a > b)
            {
                c = b;
            }
            else if (b >= a)
            {
                a = c++;
                b = ++c;
            }
            if (devil < a + b + c)
            {
                a = 6 * 100;
                b = 6 * 10;
                c = 6 * 1;
            }

            while (devil != a + b + c)
            {
                devil *= 10;
            }

            int i;
            int anotherDevil = 1;
            for (i = 0; i <= 2; i++)
            {
                anotherDevil = 1;
                do
                {
                    anotherDevil++;
                }
                while (anotherDevil < 6);
                int hellMultiplier = i;
                while (hellMultiplier-- != 0)
                {
                    anotherDevil = anotherDevil * 10;
                }
            }

            while (anotherDevil != 0 || devil != 0)
            {
                if (anotherDevil != 0)
                {
                    anotherDevil--;
                    continue;
                }

                if (devil != 0)
                {
                    devil--;
                    continue;
                }
            }
            int theEvilWasDefeated = 0;

            if (anotherDevil + devil == 0)
            {
                theEvilWasDefeated = 1;
            }
            while (theEvilWasDefeated!=0)
            {
                break;
            }

        }
    }
}
