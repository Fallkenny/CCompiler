using System;
using System.Collections.Generic;
using System.Text;

namespace DotNetCCompiler
{
    public class Symbol
    {
        public string Name { get; set; }
        public string VarType { get; set; }
        public bool Initialized { get; set; }

        public bool IsCompatible(Symbol anotherSymbol)
        {
            if (this.VarType == "int" && anotherSymbol.VarType == "float")
                return false;
            return true;
        }
    }
}
