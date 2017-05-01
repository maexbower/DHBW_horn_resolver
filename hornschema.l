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
  return VARIABLE;
}
{FUNKTIONLEX}    {
  yylval.funk = strdup(yytext);
 return FUNKTION;
}
{PRAEDIKATLEX}    {
  yylval.pra = strdup(yytext);
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
