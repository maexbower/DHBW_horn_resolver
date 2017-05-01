#include "hornschema_datatypes.h"

termElem* createTermElem(char* pname, termList *termlist)
{
  termElem *term = malloc(sizeof(termElem));
  term->name = strdup(pname);
  term->argument = termlist;
  //printTermElem(term);
  return term;
}
void printTermElem(termElem *term)
{
  fprintf(TEXTOUT, "-------------- \nPrint Term Element \n-------------- \n");
  fprintf(TEXTOUT, "\tAdresse: %p\n", term);
  fprintf(TEXTOUT, "\tname: %s\n", term->name);
  fprintf(TEXTOUT, "\targument: %p\n", term->argument);
  fprintf(TEXTOUT, "-------ENDTermElem------- \n");
}
atomElem* createAtomElem(char* pname, termList *termlist)
{
  atomElem *atom = malloc(sizeof(atomElem));
  atom->praedikat = strdup(pname);
  atom->argument = termlist;
  //printAtomElem(atom);
  return atom;
}
void printAtomElem(atomElem *atom)
{
  fprintf(TEXTOUT, "-------------- \nPrint Atom Element \n-------------- \n");
  fprintf(TEXTOUT, "\tAdresse: %p\n", atom);
  fprintf(TEXTOUT, "\tname: %s\n", atom->praedikat);
  fprintf(TEXTOUT, "\targument: %p\n", atom->argument);
  fprintf(TEXTOUT, "-------ENDAtomElem------- \n");
}

formelElem* createFormelElem(kopfElem *kopf, bodyElem *body)
{
  formelElem *formel = malloc(sizeof(formelElem));
  formel->kopf = kopf;
  formel->body = body;
  //printFormelElem(formel);
  return formel;
}
void printFormelElem(formelElem *formel)
{
  fprintf(TEXTOUT, "-------------- \nPrint Formel Element \n-------------- \n");
  fprintf(TEXTOUT, "\tAdresse: %p\n", formel);
  fprintf(TEXTOUT, "\tKopf: %p\n", formel->kopf);
  if(formel->kopf)
  {
    printKopfElem(formel->kopf);
  }
  fprintf(TEXTOUT, "\tBody: %p\n", formel->body);
  if(formel->body)
  {
    printBodyElem(formel->body);
  }
  fprintf(TEXTOUT, "-------ENDFormelElem------- \n");
}
kopfElem* createKopfElem(atomElem *kopfelem)
{
  kopfElem *kopf = malloc(sizeof(kopfElem));
  kopf->atom = kopfelem;
  //printKopfElem(kopf);
  return kopf;
}
void printKopfElem(kopfElem *kopf)
{
  fprintf(TEXTOUT, "-------------- \nPrint Kopf Element \n-------------- \n");
  fprintf(TEXTOUT, "\tAdresse: %p\n", kopf);
  fprintf(TEXTOUT, "\tKopf: %p\n", kopf->atom);
  if(kopf->atom)
  {
    printAtomElem(kopf->atom);
  }
  fprintf(TEXTOUT, "-------ENDKopfElem------- \n");
}
bodyElem* createBodyElem(atomList *bodyelem)
{
  bodyElem *body = malloc(sizeof(bodyElem));
  body->atomlist = bodyelem;
  //printBodyElem(body);
  return body;
}
void printBodyElem(bodyElem *body)
{
  fprintf(TEXTOUT, "-------------- \nPrint Body Element \n-------------- \n");
  fprintf(TEXTOUT, "\tAdresse: %p\n", body);
  fprintf(TEXTOUT, "\tAtomliste: %p\n", body->atomlist);
  if(body->atomlist)
  {
    printAtomListe(body->atomlist);
  }
  fprintf(TEXTOUT, "-------ENDBodyElem------- \n");
}

termList* createTermListe(termElem *elem)
{
  termList *termListe = malloc(sizeof(termList));
  termListe->elem = elem;
  termListe->next = 0;
  //printTermListe(termListe);
  return termListe;
}
void printTermListe(termList *liste)
{
  fprintf(TEXTOUT, "-------------- \nPrint Term Liste \n-------------- \n");
  fprintf(TEXTOUT, "\tAdresse: %p\n", liste);
  termList *tmpTerm = liste;
  do{
    fprintf(TEXTOUT, "\tTermElem: %p\n", tmpTerm->elem);
    if(tmpTerm->elem)
    {
        printTermElem(tmpTerm->elem);
    }
  }while((tmpTerm = liste->next));

  fprintf(TEXTOUT, "-------ENDTermListe------- \n");
}
atomList* createAtomListe()
{
  atomList *atomListe = malloc(sizeof(atomListe));
  atomListe->elem = 0;
  atomListe->next = 0;
  //printAtomListe(atomListe);
  return atomListe;
}
void printAtomListe(atomList *liste)
{
  fprintf(TEXTOUT, "-------------- \nPrint Atom Liste \n-------------- \n");
  fprintf(TEXTOUT, "\tAdresse: %p\n", liste);
  atomList *tmpAtom = liste;
  do{
    fprintf(TEXTOUT, "\tTermElem: %p\n", tmpAtom->elem);
      if(tmpAtom->elem)
      {
        printAtomElem(tmpAtom->elem);
      }
  }while((tmpAtom = liste->next));

  fprintf(TEXTOUT, "-------ENDAtomListe------- \n");
}
formelList* createFormelListe()
{
  formelList *formelListe = malloc(sizeof(formelList));
  formelListe->elem = 0;
  formelListe->next = 0;
  //printFormelListe(formelListe);
  return formelListe;
}
void printFormelListe(formelList *liste)
{
  fprintf(TEXTOUT, "-------------- \nPrint Formel Liste \n-------------- \n");
  fprintf(TEXTOUT, "\tAdresse: %p\n", liste);
  fprintf(TEXTOUT, "\tTermElem: %p\n", liste->elem);
  formelList *tmpList = liste;
  do{
      if(tmpList->elem)
      {
        printFormelElem(tmpList->elem);
      }
      tmpList = tmpList->next;
  }while(tmpList);
  fprintf(TEXTOUT, "-------ENDFormelListe------- \n");
}
bodyElem* addToBodyElem(bodyElem *list, atomElem *elem)
{
  //ToDo hier stimmt noch was nicht.
  if(list->atomlist)
  {
    list->atomlist = addToAtomListe(list->atomlist, elem);
  }else{
    fprintf(TEXTOUT, "\n keien Atomliste in Body Element vorhanden\n" );
  }
  return list;
}
formelList* addToFormelListe(formelList *list, formelElem *elem)
{
  //formelList *newList = createFormelListe();
  //newList->next = list;
  //newList->elem = elem;
  //return newList;
    if(list->elem || list->next)
    {
      formelList *newList = createFormelListe();
      formelList *tmp = list;
      //gehe durch die Liste und füge das Element am Ende ein.
      //Wenn es bereits existiert füge es nicht nochmal ein.
      do
      {
        if(istGleichesFormelElem(tmp->elem, elem))
        {
          return list;
        }
        if(tmp->next)
        {
          tmp = tmp->next;
        }
      }while(tmp->next);
      tmp->next = newList;
      tmp->next->elem = elem;
    }else{
      list->elem = elem;
    }
    return list;
}
atomList* addToAtomListe(atomList *list, atomElem *elem)
{
  if(list->elem)
  {
    atomList *newList = createAtomListe();
    atomList *tmp = list;
    //gehe durch die Liste und füge das Element am Ende ein.
    //Wenn es bereits existiert füge es nicht nochmal ein.
    do
    {
      if(istGleichesAtomElem(tmp->elem, elem))
      {
        return list;
      }
      if(tmp->next)
      {
        tmp = tmp->next;
      }
    }while(tmp->next);
    tmp->next = newList;
    tmp->next->elem = elem;
  }else{
    list->elem = elem;
  }
  return list;
}
termList* addToTermListe(termList *list, termElem *elem)
{
  //termList *newList = createTermListe(elem);
  //termList *tmp = list;
  //gehe durch die Liste und füge das Element am Ende ein.
  //Wenn es bereits existiert füge es nicht nochmal ein.
  //while(tmp->next)
  //{
    //if(istGleichesTermElem(tmp->elem, elem))
  //  {
  //    fprintf(TEXTOUT, "gleicher Term in Liste");
  //    return list;
  //  }
  //  tmp = tmp->next;
  //}
  //tmp->next = newList;
  //tmp->next->elem = elem;
  //return list;
  if(list->elem)
  {
    termList *newList = createTermListe(elem);
    termList *tmp = list;
    //gehe durch die Liste und füge das Element am Ende ein.
    //Wenn es bereits existiert füge es nicht nochmal ein.
    do
    {
      if(istGleichesTermElem(tmp->elem, elem))
      {
        return list;
      }
      if(tmp->next)
      {
        tmp = tmp->next;
      }
    }while(tmp->next);
    tmp->next = newList;
    tmp->next->elem = elem;
  }else{
    list->elem = elem;
  }
  return list;
}
void printTermElemShort(termElem *term)
{
  //fprintf(TEXTOUT, "printTermElemShort\n" );
  fprintf(TEXTOUT, "%s", term->name);
  if(term->argument)
  {
    fprintf(TEXTOUT, "(");
    printTermListeShort(term->argument);
    fprintf(TEXTOUT, ")");
  }

}
void printAtomElemShort(atomElem *atom)
{
  //fprintf(TEXTOUT, "**printAtomElemShort**");
  fprintf(TEXTOUT, "%s", atom->praedikat);
  if(atom->argument)
  {
    fprintf(TEXTOUT, "(");
    printTermListeShort(atom->argument);
    fprintf(TEXTOUT, ")");
  }

}
void printFormelElemShort(formelElem *formel)
{
  //fprintf(TEXTOUT, "printFormelElemShort\n" );
    printBodyElemShort(formel->body);
    fprintf(TEXTOUT, "->" );
    printKopfElemShort(formel->kopf);
    fprintf(TEXTOUT, "\n" );
}
void printKopfElemShort(kopfElem *kopf)
{
  //fprintf(TEXTOUT, "printKopfElemShort\n" );
    if(kopf->atom)
    {
      printAtomElemShort(kopf->atom);
    }else{
      fprintf(TEXTOUT, "false" );
    }

}
void printBodyElemShort(bodyElem *body)
{
  //fprintf(TEXTOUT, "printBodyElemShort\n" );
  if(body->atomlist)
  {
    printAtomListeShort(body->atomlist);
  }else{
    fprintf(TEXTOUT, "true" );
  }
}
void printTermListeShort(termList *liste)
{
  ////fprintf(TEXTOUT, "printTermListeShort\n" );
  printTermElemShort(liste->elem);
  if(liste->next)
  {
    fprintf(TEXTOUT, ",");
    printTermListeShort(liste->next);
  }
}
void printAtomListeShort(atomList *liste)
{
  //fprintf(TEXTOUT, "**printAtomListeShort**");
  //fprintf(TEXTOUT, "\n Elem: %p \n Next: %p \n", liste->elem, liste->next);
  if(liste->elem)
  {
    printAtomElemShort(liste->elem);
  }
  if(liste->next)
  {
    fprintf(TEXTOUT, " & ");
    printAtomListeShort(liste->next);
  }
}
void printFormelListeShort(formelList *liste)
{
    //fprintf(TEXTOUT, "printFormelListeShort\n" );
    if(liste->elem)
    {
      printFormelElemShort(liste->elem);
    }
    if(liste->next)
    {
      printFormelListeShort(liste->next);
    }
}
int istGleicheAtomListe(atomList *liste, atomList *vergleich)
{
  if(liste && vergleich)
  {
    //wenn beide nicht der Nullpointer sind:
    if(istGleichesAtomElem(liste->elem, vergleich->elem))
    {
      if(istGleicheAtomListe(liste->next, vergleich->next))
      {
        return 1;
      }else{
        return 0;
      }
    }else{
      return 0;
    }
  }else{
    if(liste || vergleich)
    {
      //Wenn nur eine der Nullpointer ist gebe False zurück ansonsten true
      return 0;
    }
  }
  return 1;
}
int istGleicheTermListe(termList *liste, termList *vergleich)
{
  if(liste && vergleich)
  {
    //wenn beide nicht der Nullpointer sind:
    if(istGleichesTermElem(liste->elem, vergleich->elem))
    {
      if(istGleicheTermListe(liste->next, vergleich->next))
      {
        return 1;
      }else{
        return 0;
      }
    }else{
      return 0;
    }
  }else{
    if(liste || vergleich)
    {
      //Wenn nur eine der Nullpointer ist gebe False zurück ansonsten true
      return 0;
    }
  }
  return 1;
}
int istGleichesFormelElem(formelElem *elem, formelElem *vergleich)
{
  int returnval = 0;
  if(elem && vergleich)
  {
    if(elem->kopf && vergleich->kopf)
    {
      if(istGleichesAtomElem(elem->kopf->atom, vergleich->kopf->atom))
      {
        returnval = 1;
      }else{
        returnval = 0;
      }
    }else{
      if(elem->kopf || vergleich->kopf)
      {
        return 0;
      }else{
        returnval = 1;
      }
    }
    if(returnval)
    {
      //Prüfe Body nur wenn Kopf gleich ist
      if(elem->body && vergleich->body)
      {
        if(istGleicheAtomListe(elem->body->atomlist, vergleich->body->atomlist))
        {
          returnval = 1;
        }else{
          returnval = 0;
        }
      }else{
        if(elem->body || vergleich->body)
        {
          return 0;
        }else{
          returnval = 1;
        }
      }
    }
    return returnval;
  }else{
    if(elem || vergleich)
    {
      return 0;
    }else{
      return 1;
    }
  }
  return returnval;
}
int istGleichesAtomElem(atomElem *elem, atomElem *vergleich)
{
  if(elem && vergleich)
  {
    //wenn beide nicht der Nullpointer sind:
    if(strcmp(elem->praedikat, vergleich->praedikat) == 0)
    {
      if(istGleicheTermListe(elem->argument, vergleich->argument))
      {
        return 1;
      }else{
        return 0;
      }
    }else{
      return 0;
    }
  }else{
    if(elem || vergleich)
    {
      //Wenn nur eine der Nullpointer ist gebe False zurück ansonsten true
      return 0;
    }
  }
  return 1;
}
int istGleichesTermElem(termElem *elem, termElem *vergleich)
{
  if(elem && vergleich)
  {

    //wenn beide nicht der Nullpointer sind:
    if(strcmp(elem->name, vergleich->name) == 0)
    {
      if(istGleicheTermListe(elem->argument, vergleich->argument))
      {
        return 1;
      }else{
        return 0;
      }
    }else{
      return 0;
    }
  }else{
    if(elem || vergleich)
    {
      //Wenn nur eine der Nullpointer ist gebe False zurück ansonsten true
      return 0;
    }
  }
  return 1;
}
int replaceVariableInFormelList(formelList *list, termElem *alt, termElem *neu)
{
    int returnval = 0;
    if(list)
    {
      if(list->elem)
      {
        returnval += replaceVariableInFormelElem(list->elem, alt, neu);
      }
      returnval += replaceVariableInFormelList(list->next, alt, neu);
    }
    return returnval;
}
int replaceVariableInFormelElem(formelElem *elem, termElem *alt, termElem *neu)
{
  int returnval = 0;
  if(elem)
  {
    returnval += replaceVariableInKopf(elem->kopf, alt, neu);
    returnval += replaceVariableInBody(elem->body, alt, neu);
  }
  return returnval;
}
int replaceVariableInKopf(kopfElem *kopf, termElem *alt, termElem *neu)
{
  if(kopf->atom)
  {
    return replaceVariableInAtomElem(kopf->atom, alt, neu);
  }
  return 0;
}
int replaceVariableInBody(bodyElem *body, termElem *alt, termElem *neu)
{
  if(body->atomlist)
  {
    return replaceVariableInAtomList(body->atomlist, alt, neu);
  }
  return 0;
}
int replaceVariableInAtomList(atomList *list, termElem *alt, termElem *neu)
{
  int returnval = 0;
  if(list)
  {
    returnval += replaceVariableInAtomElem(list->elem, alt, neu);
    returnval += replaceVariableInAtomList(list->next, alt, neu);
  }
  return returnval;
}
int replaceVariableInAtomElem(atomElem *elem, termElem *alt, termElem *neu)
{

  if(elem->argument)
  {
    return replaceVariableInTermListe(elem->argument, alt, neu);
  }
  return 0;
}
int replaceVariableInTermListe(termList *list, termElem *alt, termElem *neu)
{
  int returnval = 0;
  if(list)
  {
    if(istGleichesTermElem(list->elem, alt))
    {
      list->elem = neu;
      returnval++;
    }
    returnval += replaceVariableInTermListe(list->next, alt, neu);
  }
  return returnval;
}
bodyElem* removeFromBodyElem(bodyElem *list, atomElem *elem)
{
  if(list->atomlist)
  {
    list->atomlist = removeFromAtomList(list->atomlist, elem);
  }
  return list;
}
atomList* removeFromAtomList(atomList *list, atomElem *elem)
{
  atomList* tmp = list;
  //Wenn es das erste Element ist muss es besonders behandelt werden.
  if(istGleichesAtomElem(tmp->elem, elem))
  {
    if(tmp->next)
    {
        list = tmp->next;
    }else{
      list->elem = 0;
      list->next = 0;
    }
    //Element kann nur ein mal drin sein.
    return list;
  }
  do {
    if(tmp->next)
    {
      if(istGleichesAtomElem(tmp->next->elem, elem))
      {
        //lösche nächstes Element aus der Liste
        tmp->next = tmp->next->next;
      }
    }
    tmp = tmp->next;
  } while(tmp);
  return list;
}
formelList* removeFromFormelListe(formelList *list, formelElem *elem)
{
  formelList *tmp = list;
  //Erster Fall: Formel ist erstes Element:
  if(istGleichesFormelElem(tmp->elem, elem))
  {
    if(tmp->next)
    {
      list = list->next;
    }else{
      list->elem = 0;
      list->next = 0;
    }
  }
  //zweiter Fall: Formel ist irgendwo in der Liste
  do {
      if(tmp->next)
      {
        if(istGleichesFormelElem(tmp->next->elem, elem))
        {
          //lösche nächstes Element aus der Liste
          tmp->next = tmp->next->next;
        }
      }
      tmp = tmp->next;
    } while(tmp);
    return list;
}
atomElem** findAtomElemInFormel(formelElem* list, atomElem* elem)
{
  if(list->kopf)
  {
    if(istGleichesAtomElem(list->kopf->atom, elem))
    {
      return &(list->kopf->atom);
    }
  }
  if(list->body)
  {
    atomList *tmp = list->body->atomlist;
    do {
      if(istGleichesAtomElem(tmp->elem, elem))
      {
          return &(tmp->elem);
      }
      tmp = tmp->next;
    } while(tmp);
  }
  return 0;
}
atomElem* copyAtomElem(atomElem* elem)
{
  if(elem){
    //fprintf(TEXTOUT, "copy Atom: %p - termlist:%p\n",elem, elem->argument );

    atomElem *newElem = createAtomElem(elem->praedikat, copyTermList(elem->argument));
    return newElem;
  }
  return 0;
}
atomList* copyAtomList(atomList* list)
{
  if(list)
  {
    //fprintf(TEXTOUT, "copy AtomList: %p - elem:%p - next:%p\n",list, list->elem, list->next );

    atomList *newList = createAtomListe();
    if(list->elem)
    {
      newList->elem = copyAtomElem(list->elem);
    }
    if(list->next)
    {
      newList->next = copyAtomList(list->next);
    }
    return newList;
  }
  return 0;
}
termList* copyTermList(termList* list)
{
  if(list)
  {
    //fprintf(TEXTOUT, "copy TermList: %p - elem:%p - next:%p\n",list, list->elem, list->next );

    termList *newList = createTermListe(0);
    if(list->elem)
    {
      newList->elem = copyTermElem(list->elem);
    }
    if(list->next)
    {
      newList->next = copyTermList(list->next);
    }
    return newList;
  }
  return 0;
}
formelList* copyFormelList(formelList* list)
{
  if(list)
  {
    //fprintf(TEXTOUT, "copy TermList: %p - elem:%p - next:%p\n",list, list->elem, list->next );
    formelList *newList = createFormelListe(0);
    if(list->elem)
    {
      newList->elem = copyFormelElem(list->elem);
    }
    if(list->next)
    {
      newList->next = copyFormelList(list->next);
    }
    return newList;
  }
  return 0;
}
termElem* copyTermElem(termElem* elem)
{
  if(elem)
  {
    //fprintf(TEXTOUT, "copy Term: %p - termlist:%p\n",elem, elem->argument );

    termElem *newElem = createTermElem(elem->name, copyTermList(elem->argument));
    return newElem;
  }
  return 0;
}
bodyElem* copyBodyElem(bodyElem* elem)
{
  if(elem)
  {

    //fprintf(TEXTOUT, "copy Body: %p - atomlist:%p\n",elem, elem->atomlist );

    bodyElem *newElem;
    if(elem->atomlist)
    {
      newElem = createBodyElem(copyAtomList(elem->atomlist));
    }else{
      newElem = createBodyElem(0);
    }
    return newElem;
  }
  return 0;
}
kopfElem* copyKopfElem(kopfElem* elem)
{
  if(elem)
  {
    //fprintf(TEXTOUT, "copy Kopf: %p - atom:%p\n",elem, elem->atom );

    kopfElem *newElem;
    if(elem->atom)
    {
      newElem = createKopfElem(copyAtomElem(elem->atom));
    }else{
      newElem = createKopfElem(0);
    }
    return newElem;
  }
  return 0;
}
formelElem* copyFormelElem(formelElem* elem)
{
  if(elem)
  {
    //fprintf(TEXTOUT, "copy Formel: %p - kopf:%p - body: %p\n",elem, elem->kopf, elem->body );
    formelElem *newElem = createFormelElem(copyKopfElem(elem->kopf), copyBodyElem(elem->body));
    return newElem;
  }
  return 0;
}
unifikatorElem* createUnifikator(termElem *elem, termElem *wirdzu)
{
  if(elem && wirdzu)
  {
    unifikatorElem *tmpelem = malloc(sizeof(unifikatorElem));
    tmpelem->elem = elem;
    tmpelem->wirdzu = wirdzu;
    return tmpelem;
  }
  return 0;
}
void printUnifikator(unifikatorElem *elem)
{
  if(elem)
  {
    fprintf(TEXTOUT, "Unifikator: ");
    if(elem->elem)
    {
      printTermElemShort(elem->elem);
    }else{
      fprintf(TEXTOUT, "(nil)");
    }
    fprintf(TEXTOUT, " -> ");
    if(elem->wirdzu)
    {
      printTermElemShort(elem->wirdzu);
    }else{
      fprintf(TEXTOUT, "(nil)");
    }
    fprintf(TEXTOUT,"\n");
  }
}
char* addLineCountToVariable(char* name, int linecount)
{
  int stellenDerZahl = 1;
  int zehnerpotenz = 10;
  while((linecount-zehnerpotenz) > 0)
  {
    stellenDerZahl++;
    zehnerpotenz*=10;
  }
  char *text = malloc((sizeof(name)/sizeof(name[0]))+1+stellenDerZahl+1);
  //fprintf(TEXTOUT, "Größe des alten Strings: %d\n", (int)(sizeof(name)/sizeof(name[0])));
  sprintf(text, "%s_%d", name, linecount);
  //fprintf(TEXTOUT, "Größe des neuen Strings: %d\n", (int)(sizeof(text)/sizeof(text[0])));
  return text;
}
