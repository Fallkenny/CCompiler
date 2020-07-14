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
            var filetext = File.OpenText(@"C:\GitHub\CCompiler\tests\precode22.c");
            var line = filetext.ReadLine();
            var stringBuilder = new StringBuilder();
            
            var sEnd = "// <*********** FIM DO ANALISADOR SINT";

            while (!line.Contains("void getToken()"))
            {
                line = filetext.ReadLine();
                continue;
            }
            while (!line.Contains("}"))
            {
                line = filetext.ReadLine();
                continue;
            }

            line = filetext.ReadLine();
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
