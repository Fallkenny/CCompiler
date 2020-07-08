//avaliador de expressoes de soma recursivo a direita

#include <stdio.h>
#include <stdlib.h>

int pos=0;
char exp[20];

int T(int *Tval)
{
	if (exp[pos]>='0'&&exp[pos]<='9')
	   {
	   	*Tval=exp[pos]-'0';
	   	pos++;
	   	return 1;
	   }
	return 0;
}

/*******************************************************************************************************************/
/*******************************************************************************************************************/
int E( int *Eval){
	int Tval,E1val;
	
	if (T(&Tval))
		if(exp[pos]=='+')
		   {
            pos++;
			if(E(&E1val))
				{
				*Eval = E1val+Tval;
				return 1;
			}
			else return 0;
		}
		else
		{
			*Eval=Tval;
			return 1;
		}
	else return 0;
	
}
/*******************************************************************************************************************/
/*******************************************************************************************************************/
int main()
{
	int Eval;
	printf("Digite a expressao:");
	scanf("%s",exp);
 	if (E(&Eval))  printf("\nExpressão correta vale %d\n",Eval);
	else printf("Erro na posição %d\n",pos);
	system("pause");
}
/*******************************************************************************************************************/
