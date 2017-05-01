#include "hornschema_datatypes.h"
#include "hornschema_code.h"

/* Funktion: getQueryFormeln
 * Parameter: formelList *list
 * Returns: formelList* liste aller querry Formeln
 * Beschreibung: geht durch die gegebenen Formeln und gibt alle mit leerem Kopf Element (query Formeln) zurück.
 */
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
/* Funktion: getDefiniteFormeln
 * Parameter: formelList *list
 * Returns: formelList* Liste aller definiten Formeln
 * Beschreibung: geht durch die gegebene Liste an Formeln und gibt die definiten Formeln zurück
 */
formelList* getDefiniteFormeln(formelList *list)
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
/* Funktion: SLDsatisfiable
 * Parameter: formelElem *query, formelList *definite, int tiefe
 * Returns: 0 wenn nicht Erfüllbar, 1 wenn Erfüllbar
 * Beschreibung: Geht bis zu einer bestimmten Tiefe durch die Formeln und versucht diese zu Unifizieren.
 *               Wird durch unifizierung die Formel true->false erzeugt ist die Resolution unerfüllbar
 *               Wird die maximale Tiefe überschritten ist das Problem nicht entscheidbar
 *               Sind keine Unifizierbaren Formeln in dem Set mehr vorhanden gilt das Set als Erfüllbar
 */
int SLDsatisfiable(formelElem *query, formelList *definite, int tiefe)
{
  fprintf(TEXTOUT, "\n");
  fprintf(TEXTOUT, "---------------------\n");
  fprintf(TEXTOUT, "SLD Satisfiable\n");
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
    fprintf(TEXTOUT, "0 Abbruch keine definiten Formeln\n");
    return 0;
  }
  fprintf(TEXTOUT, "Definite Formeln\n");
  printFormelListeShort(definite);
  fprintf(TEXTOUT, "\n");
  fprintf(TEXTOUT, "Query Formeln\n");
  printFormelElemShort(query);
  fprintf(TEXTOUT, "\n");
  //else let query = {l1 , l2 , ... , ln}
  atomElem *l1 = query->body->atomlist->elem;
  //fprintf(TEXTOUT, "l1: %p\n", l1);
  //let C be the Elements of D whose head is unifiable with l1
  formelList *unifiableFormeln = getUnifiableFormels(l1, definite);
  if(0 == unifiableFormeln->elem)
  {
    fprintf(TEXTOUT, "Keine syntaktische Gleichheit...Suche Unifikator:\n");
    formelList *tmpDefinite = definite;
    do{
      //Wenn das Atom nicht komplett gleich ist prüfe auf Unifizierbarkeit
      unifikatorElem *unifikator = unify(l1, tmpDefinite->elem->kopf->atom);
      if(unifikator)
      {

        fprintf(TEXTOUT, "Unifikator gefunden: ");
        printUnifikator(unifikator);
        fprintf(TEXTOUT, "\n");
        formelList *unifiedDefinite = copyFormelList(definite);
        fprintf(TEXTOUT, "Es wurden %d Variablen ersetzt in den Definiten Formeln ersetzt.\n", replaceVariableInFormelList(unifiedDefinite, unifikator->elem, unifikator->wirdzu));
        printFormelListeShort(unifiedDefinite);
        formelElem *unifiedQuery = copyFormelElem(query);
        fprintf(TEXTOUT, "Es wurden %d Variablen ersetzt in Query ersetzt.\n", replaceVariableInFormelElem(unifiedQuery, unifikator->elem, unifikator->wirdzu));
        printFormelElemShort(unifiedQuery);
        int sldreturn = SLDsatisfiable(unifiedQuery, unifiedDefinite, tiefe);
        if(sldreturn == 0)
        {
          return 0;
        }else if(sldreturn == 2)
        {
          return 2;
        }
      }else{
        fprintf(TEXTOUT, "kein Unifikator für ");
        printAtomElemShort(l1);
        fprintf(TEXTOUT, " und ");
        printAtomElemShort(tmpDefinite->elem->kopf->atom);
        fprintf(TEXTOUT, " gefunden\n");
      }
      tmpDefinite = tmpDefinite->next;
    } while(tmpDefinite);


  }else{
    fprintf(TEXTOUT, "syntaktische Gleichheit...Unifizierbare Formeln:\n");
    printFormelListeShort(unifiableFormeln);
  }



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
      //   if SLDsatisfiable(query_new, D) then return satisfiable
        if(SLDsatisfiable(newQuery, definite, tiefe) == 0)
        {
          fprintf(TEXTOUT, "0 Abbruch eine war unsatisfiable\n");
          return 0;
        }
        //return unsatisfiable

      tmpUnifiableFormels = tmpUnifiableFormels->next;
    }
    fprintf(TEXTOUT, "1 Abbruch keine war unsatisfiable\n");
    fprintf(TEXTOUT, "\n");
    fprintf(TEXTOUT, "---------------------\n");
    return 1;
}
/* Funktion: SETsatisfiable
 * Parameter: formelList *query, formelList *definite
 * Returns: 0 wenn nicht Erfüllbar, 1 wenn Erfüllbar
 * Beschreibung: wendet alle Query Formeln nacheinander auf die Definiten Formeln an. Sobald eine Query eine "Erfüllbarkeit" verursacht, wird abgebrochen.
 *               Sind alle Query Formeln "nicht Erfüllbar" wird dies zurüchgegeben.
 */
int SETsatisfiable(formelList *query, formelList *definite)
{
  if(query->elem == 0)
  {
      //no query clause == satisfiable
      return 1;
  }
  formelList *tmp = query;

  do {
    int sldreturn = SLDsatisfiable(tmp->elem, definite, 0);
    if(sldreturn == 1)
    {
      return 1;
    }else if(sldreturn == 2)
    {
      return 2;
    }
    if(tmp->next)
    {
      tmp = tmp->next;
    }
  } while(tmp->next);
  return 0;
}
/* Funktion: isUnifiable
 * Parameter: atomElem *elem, atomElem *vergleich
 * Returns: 0 wenn Falsch, 1 wenn Wahr
 * Beschreibung: prüft beide Atom Elemente auf syntaktische Gleichheit.
 */
int isUnifiable(atomElem *elem, atomElem *vergleich)
{
  //Returns 0 when not unifiable and > 0 when unifiable
  //Ohne Funktionen einfacher Vergleich ob gleich.

  if(istGleichesAtomElem(elem, vergleich))
  {
    return 1;
  }else{

    return 0;
  }
}
/* Funktion: unify
 * Parameter: atomElem *elem, atomElem *vergleich
 * Returns: unifikatorElem* Enthält die zwei Term Elemente, die sich Unifizieren.
 * Beschreibung: Geht durch die beiden Atomelemente durch und prüft ob der erste Stelle an der sich beide unterscheiden zur Unifizierung eignen.
 *               Dabei muss das Prädikat gleich sein und die Variable nicht als Subterm in der Ersetzung vorkommen.
 */
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
    if(strcmp(elem->praedikat, vergleich->praedikat) == 0)
    {
        fprintf(TEXTOUT, "Prädikat gleich\n" );
        if(elem->argument && vergleich ->argument)
        {
            termList *tmpVergArg = vergleich->argument;
            termList *tmpElemArg = elem->argument;
            do{

                if(istGleichesTermElem(tmpElemArg->elem, tmpVergArg->elem) == 0)
                {
                  fprintf(TEXTOUT, "Term Elem gleich\n" );
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
                            printTermElemShort(tmpElemArg->elem);
                            fprintf(TEXTOUT, " ist ein echter Subterm von " );
                            printTermElemShort(tmpVergArg->elem);
                            fprintf(TEXTOUT, " \n" );
                            return 0;
                          }else{

                            unifikatorElem *unifikator = createUnifikator(copyTermElem(tmpElemArg->elem), copyTermElem(tmpVergArg->elem));
                            return unifikator;
                          }
                        }else{
                          //Die zweite ist die Variable.
                          if(istEchterSubterm(tmpVergArg->elem, tmpElemArg->elem))
                          {
                            printTermElemShort(tmpVergArg->elem);
                            fprintf(TEXTOUT, " ist ein echter Subterm von " );
                            printTermElemShort(tmpElemArg->elem);
                            fprintf(TEXTOUT, " \n" );
                            return 0;
                          }else{
                            unifikatorElem *unifikator = createUnifikator(copyTermElem(tmpVergArg->elem), copyTermElem(tmpElemArg->elem));
                            return unifikator;
                          }
                        }


                    }else{
                      //else if weder σ(s)|i noch σ(t)|i ist Variable then
                      //ToDo look Deeper!!!
                      if(tmpVergArg->elem->argument && tmpElemArg->elem->argument)
                      {
                        unifikatorElem *unifikator = unify(createAtomElem("_temp", tmpElemArg->elem->argument),createAtomElem("_temp", tmpVergArg->elem->argument));
                        return unifikator;
                      }

                      //return nicht unifizierbar
                      return 0;
                    }
                }
              tmpVergArg = tmpVergArg->next;
              tmpElemArg = tmpElemArg->next;
            }while(tmpElemArg && tmpVergArg);
        }else{
          return 0;
        }
    }else{
      // sei i die erste Position, an der sich σ(s) un if σ(s)|i oder σ(t)|i ist Prädikat then
      // return nicht unifizierbar“
      return 0;
    }


  }
    return 0;
}
/* Funktion: isQueryEmpty
 * Parameter: formelElem *query
 * Returns: 0 wenn Falsch, 1 wenn Wahr
 * Beschreibung: Prüft auf die verschiedenen Möglichkeiten wie eine Query leer sein kann.
 */
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
/* Funktion: getUnifiableFormels
 * Parameter: atomElem *l1, formelList *definite
 * Returns: formelList* mit allen (sysntaktisch) unifizierbaren Formeln.
 * Beschreibung: geht alle defininiten Formeln durch und prüft ob der Kopf dieser mit dem gegeben Atom Element unifizierbar ist.
 */
formelList* getUnifiableFormels(atomElem *l1, formelList *definite)
{

  formelList *unifiableFormeln = createFormelListe();
  formelList *tmpDefinite = definite;
  if(l1 && tmpDefinite)
  {
    do {
      if(isUnifiable(l1, tmpDefinite->elem->kopf->atom))
      {
        unifiableFormeln = addToFormelListe(unifiableFormeln, copyFormelElem(tmpDefinite->elem));
      }
      tmpDefinite = tmpDefinite->next;
    } while(tmpDefinite);
  }
  return unifiableFormeln;
}
/* Funktion: istVariable
 * Parameter: termElem *elem
 * Returns: 0 wenn Falsch, 1 wenn Wahr
 * Beschreibung: Prüft ob der Name des Terms der Definition einer Variable entspricht.
 */
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
/* Funktion: istEchterSubterm
 * Parameter: termElem *elem, termElem *vergleich
 * Returns: 0 wenn Falsch, 1 wenn Wahr.
 * Beschreibung: Durchsucht das gegebene Vergleichselement rekursiv, ob es darin vorkommt.
 */
int istEchterSubterm(termElem *elem, termElem *vergleich)
{

  if(!strcmp(elem->name, vergleich->name))
  {
    fprintf(TEXTOUT, "Name gleich\n");
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
