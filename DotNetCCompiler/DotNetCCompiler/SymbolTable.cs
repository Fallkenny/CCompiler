using System;
using System.Collections.Generic;
using System.Text;

namespace DotNetCCompiler
{
    public class SymbolTable
    {
        public Symbol this[string id]
        {
            get
            {
                if (Symbols.ContainsKey(id))
                    return Symbols[id];                
                if (!(ParentContext is null))
                    return ParentContext[id];
                if (RuntimeVariables.Symbols.ContainsKey(id))
                    return RuntimeVariables.Symbols[id];
                throw new Exception($"Variavel {id} não está declarada nesse escopo");
            }
        }

        public static SymbolTable TemporaryVariables { get; set; } = new SymbolTable();

        public SymbolTable RuntimeVariables => TemporaryVariables;

        public Dictionary<string, Symbol> Symbols { get; set; } = new Dictionary<string, Symbol>();
        public SymbolTable ParentContext { get; set; } = null;

        public bool Contains(string id)
        {
            if (Symbols.ContainsKey(id))
                return true;
            if (!(ParentContext is null))
                return ParentContext.Contains(id);
            return false;
        }

        internal void Add(string id, string type)
        {
            if(this.Symbols.ContainsKey(id))
            {
                throw new Exception($"A variável {id} já existe");
            }
            this.Symbols.Add(id, new Symbol { Name = id, VarType = type });
        }
    }
}
