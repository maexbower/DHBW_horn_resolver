/* Find and add all integers and floats... */

%option noyywrap

%{
  #include "hornschema_datatypes.h"
  #include "hornschema.tab.h"
  int linecount;
%}

VARIABLELEX    [n-z]{INTLEX}*
FUNKTIONLEX    [a-m]{INTLEX}*
PRAEDIKATLEX   [A-Z]{INTLEX}*
INTLEX         [0-9]


%%

"true"        {
  return TRUE;
}
"false"       {
  return FALSE;
}
{VARIABLELEX}    {
  yylval.var = addLineCountToVariable(strdup(yytext), linecount);
  /*fprintf(TEXTOUT, "Variable gefunden: %s\n", yylval.var);*/
  return VARIABLE;
}
{FUNKTIONLEX}    {
  yylval.funk = strdup(yytext);
  /*fprintf(TEXTOUT, "Funktion gefunden: %s\n", yylval.funk);*/
 return FUNKTION;
}
{PRAEDIKATLEX}    {
  yylval.pra = strdup(yytext);
  /*fprintf(TEXTOUT, "Praedikat gefunden: %s\n", yylval.pra);*/
 return PRAEDIKAT;
}
"&"     {
 return AND;
}
"->"    {
 return ARROW;
}
"("     {
 return KLAMMERAUF;
}
")"     {
 return KLAMMERZU;
}
","    {
 return KOMMA;
}

"\n"    {
  linecount++;
 return NEWLINE;
}
\040 {

}
%%
