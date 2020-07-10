using System;
using System.IO;
using System.Text;

namespace ParsingEduCodeCSharpConverter
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");
            //var filetext = File.OpenText(@"C:\GitHub\CCompiler\ParsingEduGenerated\descRecursivo.c");
            var filetext = File.OpenText(@"C:\GitHub\CCompiler\tests\precode4.c");
            var line = filetext.ReadLine();
            var stringBuilder = new StringBuilder();
            //var sStart = "//Program -> Main_func ";
            var sStart = "//Unary_expression -> Unary_operator Unary_expression | Postfix_expression ";
            var sEnd = "// <*********** FIM DO ANALISADOR SINT";

            while (!line.Contains(sStart))
            {
                line = filetext.ReadLine();
                continue;
            }
            while (!line.Contains(sEnd))
            {
                stringBuilder.AppendLine(line);
                line = filetext.ReadLine();
            }
                       
            var syntactic = stringBuilder.ToString()
                .Replace("return 1", "return true")
                .Replace("return 0", "return false")
                .Replace("int ", "bool ")
                .Replace("tk == tk", "_token == eToken.")
                .Replace("getToken()", "GetToken()");
                
        }
    }
}
