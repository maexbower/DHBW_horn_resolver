#ifndef DATATYPES_H
#define DATATYPES_H

#define TEXTOUT stdout
#define MAXTIEFE 100
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct termElem {
    char* name;
    struct termList *argument;
} termElem, *ptrTermElem;
typedef struct termList {
  struct termElem *elem;
  struct termList *next;
} termList, *ptrTermList;
typedef struct atomElem {
    char* praedikat;
    struct termList *argument;
} atomElem, *ptrAtomElem;
typedef struct atomList {
  struct atomElem *elem;
  struct atomList *next;
} atomList, *ptrAtomList;
typedef struct formelElem {
    struct kopfElem *kopf;
    struct bodyElem *body;
} formelElem, *ptrFormelElem;
typedef struct formelList {
    struct formelElem *elem;
    struct formelList *next;
} formelList, *ptrFormelList;
typedef struct bodyElem {
  struct atomList *atomlist;
} bodyElem, *ptrBody;
typedef struct kopfElem {
  struct atomElem *atom;
} kopfElem, *ptrKopf;
typedef struct unifikator {
  struct termElem *elem;
  struct termElem *wirdzu;
} unifikatorElem, *ptrUnifikator;

termElem* createTermElem(char* pname, termList *termlist);
atomElem* createAtomElem(char* pname, termList *termlist);
formelElem* createFormelElem(kopfElem *kopf, bodyElem *body);
termList* createTermListe(termElem *elem);
atomList* createAtomListe();
formelList* createFormelListe();
kopfElem* createKopfElem(atomElem *kopf);
bodyElem* createBodyElem(atomList *body);
unifikatorElem* createUnifikator(termElem *elem, termElem *wirdzu);
bodyElem* addToBodyElem(bodyElem *list, atomElem *elem);
formelList* addToFormelListe(formelList *list, formelElem *elem);
atomList* addToAtomListe(atomList *list, atomElem *elem);
termList* addToTermListe(termList *list, termElem *elem);
void printTermElem(termElem *term);
void printAtomElem(atomElem *atom);
void printFormelElem(formelElem *formel);
void printKopfElem(kopfElem *kopf);
void printBodyElem(bodyElem *body);
void printTermListe(termList *liste);
void printAtomListe(atomList *liste);
void printFormelListe(formelList *liste);
void printTermElemShort(termElem *term);
void printAtomElemShort(atomElem *atom);
void printFormelElemShort(formelElem *formel);
void printKopfElemShort(kopfElem *kopf);
void printBodyElemShort(bodyElem *body);
void printTermListeShort(termList *liste);
void printAtomListeShort(atomList *liste);
void printFormelListeShort(formelList *liste);
void printUnifikator(unifikatorElem *elem);
int istGleicheAtomListe(atomList *liste, atomList *vergleich);
int istGleicheTermListe(termList *liste, termList *vergleich);
int istGleichesFormelElem(formelElem *elem, formelElem *vergleich);
int istGleichesAtomElem(atomElem *elem, atomElem *vergleich);
int istGleichesTermElem(termElem *elem, termElem *vergleich);
int replaceVariableInFormelList(formelList *list, termElem *alt, termElem *neu);
int replaceVariableInFormelElem(formelElem *elem, termElem *alt, termElem *neu);
int replaceVariableInKopf(kopfElem *kopf, termElem *alt, termElem *neu);
int replaceVariableInBody(bodyElem *body, termElem *alt, termElem *neu);
int replaceVariableInAtomList(atomList *list, termElem *alt, termElem *neu);
int replaceVariableInAtomElem(atomElem *elem, termElem *alt, termElem *neu);
int replaceVariableInTermListe(termList *list, termElem *alt, termElem *neu);
bodyElem* removeFromBodyElem(bodyElem *list, atomElem *elem);
atomList* removeFromAtomList(atomList *list, atomElem *elem);
formelList* removeFromFormelListe(formelList *list, formelElem *elem);
termList* removeFromTermListe(termList *list, termElem *elem);
atomElem** findAtomElemInFormel(formelElem* list, atomElem* elem);
atomElem* copyAtomElem(atomElem* elem);
atomList* copyAtomList(atomList* list);
termList* copyTermList(termList* list);
termElem* copyTermElem(termElem* elem);
bodyElem* copyBodyElem(bodyElem* elem);
kopfElem* copyKopfElem(kopfElem* elem);
formelElem* copyFormelElem(formelElem* elem);
formelList* copyFormelList(formelList* list);
char* addLineCountToVariable(char* name, int linecount);
#endif
