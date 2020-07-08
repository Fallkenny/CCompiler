#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#define TK_int 1
#define TK_float 2
#define TK_char 3
#define TK_struct 4
#define TK_if 5
#define TK_else 6

#define TK_id 7
#define TK_Abre_Colch 8
#define TK_Fecha_Colch 9
#define TK_Abre_Chaves 10
#define TK_Fecha_Chaves 11
#define TK_Fim_Arquivo 12
#define TK_Atrib 13
#define TK_Const_Int 14
#define TK_Mais 15
#define TK_Menos 16
#define TK_Mult 17
#define TK_Abre_Par 18
#define TK_Fecha_Par 19
#define TK_virgula 20
#define TK_pv 21
#define TK_Maior 22
#define TK_Menor 23
#define TK_Menor_Igual 24
#define TK_Maior_Igual 25
#define TK_Igual 26
#define TK_Diferente 27


/***********************************************************************************/
/*                                                                                 */
/*  INÍCIO DO LÉXICO - Não entre a não ser que tenha interesse pessoal em léxicos  */
/*                                                                                 */
/***********************************************************************************/

int linlex=0,collex=1;

char tokens[][20]={"","TK_int",
                      "TK_float",
					  "TK_char",
					  "TK_struct",
					  "TK_if",
					  "TK_else",
					  "TK_id",
					  "TK_Abre_Colch",
					  "TK_Fecha_Colch",
					  "TK_Abre_Chaves",
					  "TK_Fecha_Chaves",
					  "TK_Fim_Arquivo",
					  "TK_Atrib",
					  "TK_Const_Int",
					  "TK_Mais",
					  "TK_Menos",
					  "TK_Mult",
					  "TK_Abre_Par",
					  "TK_Fecha_Par",
					  "TK_virgula",
					  "TK_pv",
					  "TK_Maior",
					  "TK_Menor",
					  "TK_Menor_Igual",
					  "TK_Maior_Igual",
					  "TK_Igual",
					  "TK_Diferente"
					  };

char reservadas[][20]={"","int","float","char","struct","if","else","fim"};

FILE *arqin;
int token;
char lex[20];

char le_char()
{
char c;

if (fread(&c,1,1,arqin)==0) return -1;
if (c=='\n') {linlex++;collex=1;}
else collex++;
return c;
};

int pal_res(char lex[])
{
int tk=0;
while (strcmp(reservadas[tk],"fim")!=0)
   {
   	if (strcmp(lex,reservadas[tk])==0) return tk;
	tk++; 
   }
return TK_id;	
}

int le_token()
{
static int pos=0;
static int estado=0;
static char c='\0';
while(1)
{
switch (estado)
{
case 0:if (c==',') {c=le_char();return TK_virgula;}
       if (c=='+') {c=le_char();return TK_Mais;}
       if (c=='-') {c=le_char();return TK_Menos;}
       if (c=='*') {c=le_char();return TK_Mult;}
       if (c=='{') {c=le_char();return TK_Abre_Chaves;}
       if (c=='}') {c=le_char();return TK_Fecha_Chaves;}
       if (c==';') {c=le_char();return TK_pv;}
       if (c=='[') {c=le_char();return TK_Abre_Colch;}
       if (c==']') {c=le_char();return TK_Fecha_Colch;}
       if (c=='(') {c=le_char();return TK_Abre_Par;}
       if (c==')') {c=le_char();return TK_Fecha_Par;}
       if (c=='=') 
	      {
		  c=le_char();
		  if (c=='=')
		     {
             c=le_char();
		     return TK_Igual;	
			 }
		  return TK_Atrib;
		  }
       if (c=='<') 
	      {
		  c=le_char();
		  if (c=='=')
		     {
             c=le_char();
		     return TK_Menor_Igual;
			 }
		  return TK_Menor;
		  }
       if (c=='>') 
	      {
		  c=le_char();
		  if (c=='=')
		     {
             c=le_char();
		     return TK_Maior_Igual;
			 }
		  return TK_Maior;
		  }
       if (c=='!') 
	      {
		  c=le_char();
		  if (c=='=')
		     {
             c=le_char();
		     return TK_Diferente;
			 }
		  }
       if (c>='a' && c<='z' || c=='_')
          {
          lex[0]=c;
          c=le_char();
		  pos=1;
		  estado=1;
		  break;	
		  }
       if (c>='0' && c<='9')
          {
          lex[0]=c;
          c=le_char();
		  pos=1;
		  estado=2;
		  break;	
		  }
	   if (c==-1) return TK_Fim_Arquivo;
	   if (c=='\n'||c=='\r'||c=='\t'||c=='\0'||c==' '){c=le_char();break;}
case 1:if (c>='a' && c<='z' || c=='_' || c>='0' && c<='9')
          {
          lex[pos++]=c;
          c=le_char();
		  break;	
		  }
	   else 
	      {
		  estado=0;
		  lex[pos]='\0';
		  return pal_res(lex);
		  }
case 2:if (c>='0' && c<='9')
          {
          lex[pos++]=c;
          c=le_char();
		  break;	
		  }
	   else 
	      {
		  estado=0;
		  lex[pos]='\0';
		  return TK_Const_Int;
		  }
}
}
}

/********************/
/*                  */
/*  FIM DO LÉXICO   */
/*                  */
/********************/

#define MAX_COD 1000

void mostra_t()
{
printf("%s lex=%s na lin %d, col %d\n",tokens[token],lex,linlex,collex);
}

/****************/
/*              */
/*  EXPRESSÔES  */
/*              */
/****************/

int T(char T_c[MAX_COD]);
int E(char E_c[MAX_COD]);
int R(char R_h[MAX_COD],char R_s[MAX_COD]);

int E(char E_c[MAX_COD])
{
char T_c[MAX_COD],R_h[MAX_COD],R_s[MAX_COD];
if (T(T_c))
   {
   strcpy(R_h,T_c);
   if (R(R_h,R_s))
      {
      strcpy(E_c,R_s);
      return 1;
	  }
   }
return 0;
}

int R(char R_h[MAX_COD],char R_s[MAX_COD])
{
char T_c[MAX_COD],R1_h[MAX_COD],R1_s[MAX_COD];
if (token==TK_Mais)
   {   
   token=le_token();
   if (T(T_c))
      {
      sprintf(R1_h,"%s%s\t+\n",R_h,T_c);
      if (R(R1_h,R1_s))
         {
         strcpy(R_s,R1_s);
         return 1;
	     }
      }
   return 0;
   }
if (token==TK_Menos)
   {   
   token=le_token();
   if (T(T_c))
      {
      sprintf(R1_h,"%s%s\t-\n",R_h,T_c);
      if (R(R1_h,R1_s))
         {
         strcpy(R_s,R1_s);
         return 1;
	     }
      }
   return 0;
   }
strcpy(R_s,R_h);
return 1;
}

int T(char T_c[MAX_COD])
{
if (token==TK_Const_Int)
   {
   sprintf(T_c,"\tpush %s\n",lex);
   token=le_token();
   return 1;
   }
if (token==TK_id)
   {
   sprintf(T_c,"\tvalor-r %s\n",lex);
   token=le_token();
   return 1;
   }
if (token==TK_Abre_Par)
   {
   char E_c[MAX_COD];
   token=le_token();
   if (E(E_c))
      if (token==TK_Fecha_Par)
         {
         token=le_token();
         strcpy(T_c,E_c);
         return 1;
		 }
   }

return 0;
}

/**************/
/*            */
/*  COMANDOS  */
/*            */
/**************/

int Atrib(char Com_c[MAX_COD])
{
if (token==TK_id)
   {
   char id[10];
   strcpy(id,lex);
   token=le_token();
	if (token==TK_Atrib)
	   {
        token=le_token();
        char E_c[MAX_COD];
	   	if (E(E_c))
	   	   {
	   	   if (token==TK_pv)
	           {
               token=le_token();
               sprintf(Com_c,"\tvalor-l %s\n%s\t:=\n\tpop\n",id,E_c);
		       return 1;
		       }
		    else
		       {
		       	printf("Faltou ponto-e-vírgula após atribuição\n");
		       	return 0;
			   }
		   }
	   }
   }
return 0;
}
int main()
{
FILE *arqout;
char Atrib_c[MAX_COD];
if ((arqin=fopen("c:\\teste\\prog.cpp","rt"))==NULL){printf("Erro na abertura do arquivo");exit(0);}
if ((arqout=fopen("c:\\teste\\saida.kvmp","wt"))==NULL){printf("Erro na abertura do arquivo de saida");exit(0);}
token=le_token();
while (token!=TK_Fim_Arquivo)
   {
   if (Atrib(Atrib_c)==0) 
      printf("Erro no comando!!!\n");
   else 
      {
	  fprintf(arqout,"%s",Atrib_c);
	  printf("%s",Atrib_c);
      }
   getch();
   }
fclose(arqin);
fclose(arqout);
system("pause");
}

