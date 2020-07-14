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
    }
}
