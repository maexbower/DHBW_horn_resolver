#include "hornschema_datatypes.h"
#include "hornschema_code.h"


formelList* getQueryFormeln(formelList *list)
{
    formelList *newList = createFormelListe();
    formelList *tmp = list;
    while(tmp)
    {
      if(tmp->elem)
      {
        if(tmp->elem->kopf->atom == 0)
        {
          newList = addToFormelListe(newList, tmp->elem);
        }
      }

      tmp = tmp->next;
    }
    return newList;
}
formelList* getNoQueryFormeln(formelList *list)
{
    formelList *newList = createFormelListe();
    formelList *tmp = list;
    while(tmp)
    {
      if(tmp->elem)
      {
        if(tmp->elem->kopf->atom != 0)
        {
          newList = addToFormelListe(newList, tmp->elem);
        }
      }

      tmp = tmp->next;
    }
    return newList;
}
atomList* getTrueAtoms(formelList *list)
{
  atomList *newList = createAtomListe();
  formelList *tmp = list;
  while(tmp)
  {
    if(tmp->elem)
    {
      if(tmp->elem->body)
      {
        if(tmp->elem->body->atomlist == 0)
        {
          newList = addToAtomListe(newList, tmp->elem->kopf->atom);
        }
      }
    }
    tmp = tmp->next;
  }
  return newList;
}

int SLDsatisfiable(formelElem *query, formelList *definite, int tiefe)
{
  fprintf(TEXTOUT, "\n");
  fprintf(TEXTOUT, "---------------------\n");
  //Returns 0 when unsatisfiable and >0 when satisfiable
  //if query == [] then return unsatisfiable
  tiefe++;
  if(tiefe > MAXTIEFE)
  {
    fprintf(TEXTOUT, "1 Abbruch MAXTIEFE\n");
    return 2;
  }
  if(isQueryEmpty(query))
  {
    fprintf(TEXTOUT, "0 Abbruch Query = 0\n");
    return 0;
  }
  if(!definite)
  {
    fprintf(TEXTOUT, "0 Abbruch keine definiten\n");
    return 0;
  }
  //else let query = {l1 , l2 , ... , ln}
  atomElem *l1 = query->body->atomlist->elem;
  //fprintf(TEXTOUT, "l1: %p\n", l1);
  //let C be the Elements of D whose head is unifiable with l1
  formelList *unifiableFormeln = getUnifiableFormels(l1, definite);

  fprintf(TEXTOUT, "Definite Formeln\n");
  printFormelListeShort(definite);
  fprintf(TEXTOUT, "\n");
  fprintf(TEXTOUT, "Query Formeln\n");
  printFormelElemShort(query);
  fprintf(TEXTOUT, "\n");
  fprintf(TEXTOUT, "Unifizierbare Formeln\n");
  printFormelListeShort(unifiableFormeln);

  //for all c e C do
  formelList *tmpUnifiableFormels;
  tmpUnifiableFormels = unifiableFormeln;
  if(tmpUnifiableFormels->elem == 0)
  {
    fprintf(TEXTOUT, "1 Abbruch keine Unifizierbaren Formeln mehr = 0\n");

    return 1;

  }
    while(tmpUnifiableFormels) {
      //   let b be the body of c

      //   let query_new = {l2, ..., ln} u b
      atomList *newBodyAtomList = copyAtomList(query->body->atomlist->next);
      if(newBodyAtomList == 0)
      {
        //Wenn die Query keine weiteren Literale hat wird hier eine leere AtomListe erzeugt.
        newBodyAtomList = createAtomListe(0);
      }
      //fprintf(TEXTOUT, "newBody: %p\n", newBody);
      //hole die Liste der Atome aus der unifizierbaren Formel.
      atomList *tmpAtomList;
      if(tmpUnifiableFormels->elem)
      {
        if(tmpUnifiableFormels->elem->body)
        {
          tmpAtomList = tmpUnifiableFormels->elem->body->atomlist;
        }else{
          tmpAtomList = 0;
        }
      }else{
        tmpAtomList = 0;
      }
      //fprintf(TEXTOUT, "tmpAtomList: %p\n", tmpAtomList);
      //Sofern in der unifizierbaren Formel eine Atomliste gefunden wurde (!= "true =>")
      while(tmpAtomList)
      {
        //Füge alle Atome der Atomliste dem Body der neuen Query hinzu.
        newBodyAtomList = addToAtomListe(newBodyAtomList, copyAtomElem(tmpAtomList->elem));
        tmpAtomList = tmpAtomList->next;
      }
      formelElem *newQuery = 0;
      //Wenn der neue Body nun mindestens ein Element hat, dann erstelle ein neues Query Objekt.
      if(newBodyAtomList->elem != 0)
      {
        newQuery = createFormelElem(createKopfElem(0), createBodyElem(newBodyAtomList));
      }
      //fprintf(TEXTOUT, "newQuery: %p\n", newQuery);

      //   if SLDsatisfiable(query_new, D) then return satisfiable
        if(SLDsatisfiable(newQuery, definite, tiefe) == 0)
        {
          fprintf(TEXTOUT, "0 Abbruch eine war unsatisfiable\n");
          return 0;
        }
        //return unsatisfiable


      //fprintf(TEXTOUT, "tmpUnifiableFormels->next: %p\n", tmpUnifiableFormels->next);
      tmpUnifiableFormels = tmpUnifiableFormels->next;
    }
    fprintf(TEXTOUT, "1 Abbruch keine war unsatisfiable\n");
    fprintf(TEXTOUT, "\n");
    fprintf(TEXTOUT, "---------------------\n");
    return 1;
}
int SETsatisfiable(formelList *query, formelList *definite)
{
  if(query->elem == 0)
  {
      //no query clause == satisfiable
      return 1;
  }
  formelList *tmp = query;

  do {
    if(SLDsatisfiable(tmp->elem, definite, 0))
    {
      return 1;
    }
    if(tmp->next)
    {
      tmp = tmp->next;
    }
  } while(tmp->next);
  return 0;
}
int isUnifiable(atomElem *elem, atomElem *vergleich)
{
  //Returns 0 when not unifiable and > 0 when unifiable
  //Ohne Funktionen einfacher Vergleich ob gleich.
  //fprintf(TEXTOUT, "\nisunifiable:");
  //printAtomElemShort(elem);
  //fprintf(TEXTOUT, " - ");
  //printAtomElemShort(vergleich);
  //fprintf(TEXTOUT, " \n");


  return istGleichesAtomElem(elem, vergleich);
}
unifikatorElem* unify(atomElem *elem, atomElem *vergleich)
{
  //Input: Atome s, t
  //Output: au(s, t), wenn s und t unifizierbar sind; nicht unifizierbar“, sonst
  //1: σ := ()
  if(elem && vergleich)
  {
    // while σ(s) 6= σ(t) do
    //  sei i die erste Position, an der sich σ(s) und σ(t) unterscheiden
    // sei i die erste Position, an der sich σ(s) un if σ(s)|i oder σ(t)|i ist Prädikat then
    // return nicht unifizierbar“
    if(strcmp(elem->praedikat, vergleich->praedikat) == 0)
    {
        if(elem->argument && vergleich ->argument)
        {


            termList *tmpElemArg = elem->argument;
            termList *tmpVergArg = vergleich->argument;
            do{
              if(istGleichesTermElem(tmpElemArg->elem, tmpVergArg->elem) == 0)
              {
                  if(istVariable(tmpElemArg->elem) || istVariable(tmpVergArg->elem))
                  {
                    //sei x die Variable, y der andere Term
                    //if x ist echter Subterm von y then
                    //return nicht unifizierbar
                    //else
                    //σ := σ · ([x/y])
                      if(istVariable(tmpElemArg->elem))
                      {
                        //Ist das erste die Variable?
                        if(istEchterSubterm(tmpElemArg->elem, tmpVergArg->elem))
                        {
                          return 0;
                        }else{
                          unifikatorElem *unifikator = createUnifikator(copyTermElem(tmpVergArg->elem), copyTermElem(tmpElemArg->elem));
                          return unifikator;
                        }
                      }else{
                        //Die zweite ist die Variable.
                        if(istEchterSubterm(tmpVergArg->elem, tmpElemArg->elem))
                        {
                          return 0;
                        }else{
                          unifikatorElem *unifikator = createUnifikator(copyTermElem(tmpElemArg->elem), copyTermElem(tmpVergArg->elem));
                          return unifikator;
                        }
                      }
                  }else{
                    //else if weder σ(s)|i noch σ(t)|i ist Variable then
                    //return nicht unifizierbar
                    return 0;
                  }
              }
              tmpElemArg = tmpElemArg->next;
              tmpVergArg = tmpVergArg->next;
            }while(tmpElemArg && tmpVergArg);
        }else{
          return 0;
        }
    }else{
      return 0;
    }


  }
    return 0;
}
int isQueryEmpty(formelElem *query)
{
  if(query)
  {
    if(query->body == 0)
    {
      fprintf(TEXTOUT, "0 Abbruch Body = 0\n");

      return 1;
    }else{
      if(query->body->atomlist == 0)
      {
        fprintf(TEXTOUT, "0 Abbruch Body->atomlist = 0\n");
        printBodyElem(query->body);
        return 1;
      }else{
        return 0;
      }
    }
  }else{
    return 1;
  }

}
formelList* getUnifiableFormels(atomElem *l1, formelList *definite)
{
  formelList *unifiableFormeln = createFormelListe();
  if(l1 && definite)
  {
    do {
      if(isUnifiable(l1, definite->elem->kopf->atom))
      {
        unifiableFormeln = addToFormelListe(unifiableFormeln, copyFormelElem(definite->elem));
      }
      definite = definite->next;
    } while(definite);
  }
  return unifiableFormeln;
}
int istVariable(termElem *elem)
{
  if(elem)
  {
    if(('n' <= elem->name[0]) && ('z' >= elem->name[0]))
    {
      return 1;
    }else{
      return 0;
    }
  }else{
    return 0;
  }
}
int istEchterSubterm(termElem *elem, termElem *vergleich)
{
  if(strcmp(elem->name, vergleich->name))
  {
    return 1;
  }
  if(vergleich->argument)
  {
    termList *tmpVergleich = vergleich->argument;
    do{
      if(istEchterSubterm(elem, tmpVergleich->elem))
      {
        return 1;
      }
      tmpVergleich = tmpVergleich->next;
    }while(tmpVergleich);
  }
  return 0;
}
