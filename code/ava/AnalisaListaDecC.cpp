#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

// Lista de tokens reconhecidos e seus códigos numéricos

#define TKId 1
#define TKVoid 2
#define TKInt 3
#define TKFloat 4
#define TKVirgula 5
#define TKDoisPontos 6
#define TKAbrePar 7
#define TKFechaPar 8
#define TKAtrib 9
#define TKPontoeVirg 10
#define TKAbreChaves 11
#define TKFechaChaves 12
#define TKSoma 13
#define TKDuploMais 14
#define TKProd 15
#define TKAbreColch 16
#define TKFechaColch 17
#define TKString 18
#define TKCteInt 19
#define TK_Fim_Arquivo 20


typedef struct Tnodo {char tipo; // 'I'-int 'F'-float 'A'-array
                      int tamanho;
                      struct Tnodo *tipo_ar;} Tnodo;

// Tabela de Símbolos - Cada entrada tem o identificador e o tipo

struct TS_Ent{
	char id[20];
	Tnodo *tipo;
} Tab_Simb[30];

int proxposTS=0;

// poe_TS - coloca identificador e tipo na tabela de símbolos e retorna 1
// se o identificador já existe na tabela de símbolos retorna 0

int poe_TS(char id[], Tnodo *tipo)
{
   int i=0;
   while (i<proxposTS)
      {
      if (strcmp(id,Tab_Simb[i++].id)==0) return 0;	
	  }
   strcpy(Tab_Simb[proxposTS].id,id);
   Tab_Simb[proxposTS++].tipo=tipo;
   return 1;
}

/***********************************************************************************/
/*                                                                                 */
/*  INÍCIO DO LÉXICO - Não entre a não ser que tenha interesse pessoal em léxicos  */
/*                                                                                 */
/***********************************************************************************/

int linlex=0,collex=1;

// lista de strings correspondentes a cada token para colocar em mensagens de depuração. Deve
// estar na mesma ordem da lista de defines

char tokens[][20]={"","TK_id",
					  "TK_void",
					  "TK_int",
					  "TK_float",
					  "TK_virgula",
					  "TK_dois_pontos",
					  "TK_Abre_Par",
					  "TK_Fecha_Par",
					  "TK_Atrib",
					  "TK_Ponto_e_virg",
					  "TK_Abre_Chaves",
					  "TK_Fecha_Chaves",
					  "TK_Soma",
					  "TK_Duplo_Mais",
					  "TK_Prod",
					  "TK_Abre_Colch",
					  "TK_Fecha_Colch",
					  "TK_String",
					  "TK_Fim_Arquivo"
					  };

FILE *arqin;
int token;
char lex[200];

struct pal_res{char palavra[20]; int tk;};
struct pal_res lista_pal[]={{"void",TKVoid},
                  {"int",TKInt},
                  {"float",TKFloat},
                  {"fimtabela",TKId}};

int palavra_reservada(char lex[])
{
int postab=0;
while (strcmp("fimtabela",lista_pal[postab].palavra)!=0)
   {
   if (strcmp(lex,lista_pal[postab].palavra)==0)
      return lista_pal[postab].tk;
   postab++;
   }
return TKId;
}

char le_char()
{
unsigned char c;

if (fread(&c,1,1,arqin)==0) return -1;
if (c=='\n') {linlex++;collex=1;}
else collex++;
return c;
};

int le_token()
{
static int pos=0;
int estado=0;
static char c='\0';
while(1)
{
switch (estado)
{
case 0:if (c>='a' && c<='z' || c>='A' && c<='Z' || c=='_')
		  {
          lex[0]=c;
          pos=1;
          c=le_char();
		  estado=1;
		  break;	
		  }
       if (c==',') {c=le_char();return TKVirgula;}
       if (c==';') {c=le_char();return TKPontoeVirg;}
       if (c=='{') {c=le_char();return TKAbreChaves;}
       if (c=='}') {c=le_char();return TKFechaChaves;}
       if (c=='(') {c=le_char();return TKAbrePar;}
       if (c==')') {c=le_char();return TKFechaPar;}
       if (c==':') {c=le_char();return TKDoisPontos;}
       if (c=='[') {c=le_char();return TKAbreColch;}
       if (c==']') {c=le_char();return TKFechaColch;}
       if (c=='"')
          {
          lex[0]=c;
          c=le_char();
		  pos=1;
		  estado=3;
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
	   if (c=='\n'||c=='\r'||c=='\t'||c=='\0'||c==' ')
	      {
		  c=le_char();
		  break;
		  }
case 1:if (c>='a' && c<='z' || c>='A' && c<='Z' || c=='_' || c>='0' && c<='9') 
          {
		  lex[pos++]=c;
          c=le_char();
		  break;
		  }
        lex[pos]='\0';
        return palavra_reservada(lex);
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
		  return TKCteInt;
		  }
case 3:if (c>='a' && c<='z' || c=='_' || c>='0' && c<='9')
          {
          lex[pos++]=c;
          c=le_char();
		  break;	
		  }
	   else 
	      {
		  estado=0;
		  lex[pos]='\0';
		  return TKString;
		  }
}
}
}

/********************/
/*                  */
/*  FIM DO LÉXICO   */
/*                  */
/********************/

#define MAX_COD 10000

int DIM(Tnodo **LTipo)
{
if (token!=TKAbreColch) return 1;
printf("Achei abre colchete\n");
token=le_token();
if (token!=TKCteInt){printf("Erro na dimensão. Esperava constante inteira.\n");return 0;}
Tnodo *naux=(Tnodo *)malloc(sizeof(Tnodo));
naux->tipo='A';
naux->tamanho=atoi(lex);
token=le_token();
if (token!=TKFechaColch){printf("Erro na dimensão. Esperava fecha colchetes.\n");return 0;}
token=le_token();
if (!DIM(LTipo)) return 0;
naux->tipo_ar=*LTipo;
*LTipo=naux;
return 1;
}   

int L(Tnodo *LTipo) // reconhece lista de identificadores
{
Tnodo *L1Tipo;
if (token==TKId)
   {
   char id[100];
   strcpy(id,lex);
   if (LTipo->tipo=='I')
      printf("Var %s é do tipo base inteir\n",lex);
   else 	
      printf("Var %s é do tipo base %c\n",lex,LTipo->tipo);
   token=le_token();
   Tnodo *LDim=LTipo;
   if (!DIM(&LDim))
      {
	  printf("Erron no reconhecimento das dimensões de %s\n",id);
	  return 0;
	  }   
   if (poe_TS(id,LTipo)==0)
      {
      printf("Variavel %s já declarada\n",lex);
      return 0;
	  }
   if (token==TKVirgula)
      {
      token=le_token();
      L1Tipo=LTipo;
      return L(L1Tipo);
	  }
   else return 1;
   }
return 0;
}

int T(Tnodo **TTipo)
{
if (token==TKInt || token==TKFloat)
   {
   *TTipo=(Tnodo *)malloc(sizeof(Tnodo));
   if (token==TKInt) (*TTipo)->tipo='I';
   else if (token==TKFloat) (*TTipo)->tipo='F';
   printf("Reconheci tipo %s\n",tokens[token]);
   token=le_token();
   return 1;	
   }
return 0;
}

int D( )  // reconhece declaração
{
	Tnodo *LTipo,*TTipo;
	if (!T(&TTipo)) return 0;  // reconhece tipo base da declaração
	LTipo=TTipo;
	if (!L(LTipo)) return 0;
	if (token!=TKPontoeVirg)
	   {
	   	printf("Esperava ponto e virgula - achei token %d\n",token);
	   	return 0;
	   }
	token=le_token();
	return 1;
}

int L()
{
if (token!=TKInt && token!=TKFloat) return 1; // reconhece lista vazia
if (D())
   return L();
return 0;
}

int main()
{
char c;
if ((arqin=fopen("c:\\teste\\teste.c","rt"))==NULL)
   {printf("Erro na abertura do arquivo");exit(0);}
token=le_token();
if (L()) printf("Reconheceu tudo\n");
else printf("Erro no reconhecimento\n");   
fclose(arqin);
system("pause");
}

