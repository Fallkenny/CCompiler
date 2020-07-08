#include <stdio.h>
#include <stdlib.h>

char exp[10]="3+2";
int pos=0;

typedef struct tnodo {char tipo; 
                      struct tnodo *fesq; 
                      struct tnodo *fdir;
                      int val;} tnodo; // tipo: 'I':identificador  
                                       //       'C':constante

tnodo *gerafolha(char tipo, int val)
{
    tnodo *naux=(tnodo *)malloc(sizeof(tnodo));
    naux->val=val;
    naux->tipo=tipo;
    return naux; 
}

tnodo *geranodo(char tipo, tnodo *nesq, tnodo *ndir)
{
    tnodo *naux=(tnodo *)malloc(sizeof(tnodo));
    naux->tipo=tipo;
    naux->fesq=nesq;
    naux->fdir=ndir;
    return naux;
}

int R(tnodo **Rs, tnodo *Rh);

int T(tnodo **Tptr);

int E(tnodo **Eptr)
   {
   tnodo *Rs,*Rh,*Tptr;
   if (T(&Tptr))
      {
      Rh=Tptr;
      if (R(&Rs, Rh))
         {
         *Eptr=Rs;
         return 1;
         }
      }
   return 0;
   }     
  
void Desaloca(tnodo *Raiz)
{
    if (Raiz->tipo=='C') free(Raiz);
    else
       {
           Desaloca(Raiz->fesq);
           Desaloca(Raiz->fdir);
       }
  }  
   
int R(tnodo **Rs, tnodo *Rh)
   {
   tnodo *Tptr,*R1h,*R1s;
   if (exp[pos]=='+')
      {
      pos++;
      if (T(&Tptr))
         {
         R1h=geranodo('+',Rh,Tptr);
         if (R(&R1s,R1h))
            {
            *Rs=R1s;
            return 1;
            }
            else 
            {
            Desaloca(R1s);
            return 0;
            }
         }
     else return 0;
     }
  else
     {
     *Rs=Rh;
     return 1;
     }    
}

int T(tnodo **Tptr)
   {
   tnodo *Eptr;
   if (exp[pos]=='(')
      {
      pos++;
      if (E(&Eptr))
         if (exp[pos]==')')
            {
            pos++;
            *Tptr=Eptr;
            return 1;
            }
         else return 0;
      else return 0;
      }
   else if (exp[pos]>='a' && exp[pos]<='z')
           {
           char id=exp[pos];
           pos++;
           *Tptr=gerafolha('I',id);
           return 1;
           }
        else if (exp[pos]>='0' && exp[pos]<='9')
                {
                int val=exp[pos]-'0';
                pos++;
            *Tptr=gerafolha('C',val);
                return 1;
                }
             else return 0;
   }             

int avalia(tnodo *Eraiz)
{
if (Eraiz->tipo=='C') return Eraiz->val;
if (Eraiz->tipo=='+') return avalia(Eraiz->fesq)+avalia(Eraiz->fdir);
}

int main()
{
//scanf("%s",exp);
tnodo *Eraiz;
if (E(&Eraiz))
   printf("O valor � %d\n",avalia(Eraiz));
else printf("Erro!!!! pos=%d\n",pos);
system("pause");
}
