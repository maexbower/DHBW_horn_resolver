#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TEXTOUT stdout


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

termElem* createTermElem(char* pname, termList *termlist);
atomElem* createAtomElem(char* pname, termList *termlist);
formelElem* createFormelElem(kopfElem *kopf, bodyElem *body);
termList* createTermListe(termElem *elem);
atomList* createAtomListe();
formelList* createFormelListe();
kopfElem* createKopfElem(atomElem *kopf);
bodyElem* createBodyElem(atomList *body);
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
