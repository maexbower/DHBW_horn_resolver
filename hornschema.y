%{
  #include "hornschema_code.h"
  extern int yyerror(char*);
  extern int yylex(void);
  extern FILE *yyin;
  formelList *formlist;

%}




%union {
    char* pra;
    char* funk;
    char* var;
    termElem *term;
    atomElem *atom;
    formelElem *formel;
    termList *termliste;
    atomList *atomliste;
    formelList *formelliste;
    kopfElem *kopf;
    bodyElem *body;
}

%start stmtseq


%token TRUE
%token FALSE
%token VARIABLE
%token FUNKTION
%token PRAEDIKAT
%token AND
%token ARROW
%token KLAMMERAUF
%token KLAMMERZU
%token KOMMA
%token NEWLINE


%%
stmtseq: formel NEWLINE stmtseq {formlist = addToFormelListe(formlist, $<formel>1);}
    | formel {formlist = addToFormelListe(formlist, $<formel>1);}
    | formel NEWLINE {formlist = addToFormelListe(formlist, $<formel>1);}
    | NEWLINE stmtseq {}
term: VARIABLE {$<term>$ = createTermElem($<var>1, 0);}
    | FUNKTION {$<term>$ = createTermElem($<funk>1, 0);}
    | FUNKTION KLAMMERAUF params KLAMMERZU  {$<term>$ = createTermElem($<funk>1, $<termliste>3);}
params: term  {$<termliste>$ = createTermListe($<term>1);}
    | params KOMMA term  {$<termliste>$ = addToTermListe($<termliste>1, $<term>3);}
atom: PRAEDIKAT KLAMMERAUF params KLAMMERZU {$<atom>$ = createAtomElem($<pra>1, $<termliste>3);}
formel: body ARROW head {$<formel>$ = createFormelElem($<kopf>3, $<body>1);}
    | TRUE ARROW head {$<formel>$ = createFormelElem($<kopf>3,createBodyElem(0));}
    | body ARROW FALSE  {$<formel>$ = createFormelElem(createKopfElem(0),$<body>1);}
body: atom  {$<body>$ = createBodyElem(addToAtomListe(createAtomListe(),$<atom>1));}
    | body AND atom {$<body>$ = addToBodyElem($<body>1, $<atom>3);}
head: atom  {$<kopf>$ = createKopfElem($<atom>1);}


%%

int yyerror(char* err)
{
   printf("Error: %s\n", err);
   return 0;
}
int main (int argc, char* argv[])
{
  formlist = createFormelListe();
	if(argc == 2)
	{
		yyin = fopen(argv[1], "r");
	}
	if(!yyin){
		yyin = stdin;
	}
  yyparse();
  fprintf(TEXTOUT, "Parse Abgeschlossen\n");
  printFormelListeShort(formlist);
  formelList *queryFormeln;
  formelList *noQueryFormeln;
  atomList *trueAtoms;
  queryFormeln = getQueryFormeln(formlist);
  fprintf(TEXTOUT, "Query Formeln:\n");
  printFormelListeShort(queryFormeln);

  noQueryFormeln = getNoQueryFormeln(formlist);
  fprintf(TEXTOUT, "No Query Formeln:\n");
  printFormelListeShort(noQueryFormeln);
  trueAtoms = getTrueAtoms(noQueryFormeln);
  fprintf(TEXTOUT, "True Atoms:\n");
  printAtomListeShort(trueAtoms);
  if(SETsatisfiable(queryFormeln, noQueryFormeln))
  {
    fprintf(TEXTOUT, "Satisfiable\n");
  }else{
    fprintf(TEXTOUT, "Not Satisfiable\n");

  }
  return 0;
}
