#ifndef HORNSCHEMA_CODE_H
#define HORNSCHEMA_CODE_H

/* header file contents go here */


formelList* getQueryFormeln(formelList *list);
formelList* getDefiniteFormeln(formelList *list);
int SLDsatisfiable(formelElem *query, formelList *definite, int tiefe);
int SETsatisfiable(formelList *query, formelList *definite);
int isUnifiable(atomElem *elem, atomElem *vergleich);
int isTermUnifiable(termElem *elem, termElem *vergleich);
unifikatorElem* unify(atomElem *elem, atomElem *vergleich);
int isQueryEmpty(formelElem *query);
formelList* getUnifiableFormels(atomElem *l1, formelList *definite);
int istVariable(termElem *elem);
int istEchterSubterm(termElem *elem, termElem *vergleich);
#endif
