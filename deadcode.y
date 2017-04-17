stmtseq: /* Empty */
    | NEWLINE stmtseq   {printf("stmtseq->NEWLINE stmtseq\n");}
    | formel NEWLINE stmtseq   {printf("stmtseq->formel NEWLINE stmtseq\n");}
term: VARIABLE {printf("term-> VARIABLE(%s)\n", $<var>1);}
    | FUNKTION {printf("term-> FUNKTION(%s)\n", $<funk>1);}
    | FUNKTION KLAMMERAUF params KLAMMERZU  {printf("term->FUNKTION(%s) KLAMMERAUF params KLAMMERZU\n", $<funk>1);}
params: term  {printf("params->term\n");}
    | term KOMMA params  {printf("params->term KOMMA params\n");}
atom: PRAEDIKAT KLAMMERAUF params KLAMMERZU {printf("atom->PRAEDIKAT(%s) KLAMMERAUF params KLAMMERZU\n", $<pra>1);}
formel: body ARROW head {printf("formel->body ARROW head\n");}
    | TRUE ARROW head {printf("formel->TRUE ARROW head\n");}
    | body ARROW FALSE  {printf("formel->body ARROW FALSE\n");}
body: atom  {printf("body->atom\n");}
    | atom AND body {printf("body->atom AND body\n");}
head: atom  {printf("head->atom\n");}
