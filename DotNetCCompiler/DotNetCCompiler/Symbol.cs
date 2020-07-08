using System;
using System.Collections.Generic;
using System.Text;

namespace DotNetCCompiler
{
    public class Symbol
    {
        public string Name { get; set; }
        public eVarType VarType { get; set; }
        public object Value { get; set; }

        public bool IsCompatible(Symbol anotherSymbol)
        {
            return this.VarType == anotherSymbol.VarType;
        }

        public bool IsCompatible(eToken eToken)
        {
            switch (eToken)
            {
                case eToken.INTEGER_CONSTANT:
                    return this.VarType == eVarType.INT;
                case eToken.FLOATING_POINT_CONSTANT:
                    return this.VarType == eVarType.FLOAT;
                default:
                    return false;                
            }
        }
    }
}
