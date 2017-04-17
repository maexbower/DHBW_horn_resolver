LEX  = flex
YACC = bison
CC   = gcc -Wall
LD   = gcc
TMPFILES = *.out hornschemalex.c hornschemalex.o hornschema.tab.c hornschema.tab.h hornschema.tab.o lex.yy.c
all: hornschema
clean:
	rm $(TMPFILES)

hornschemalex.c: hornschema.l hornschema.tab.h
	$(LEX) -t hornschema.l > hornschemalex.c

hornschema.tab.h: hornschema.y hornschema_code.h
	$(YACC) -d hornschema.y

hornschema.tab.c: hornschema.y hornschema_code.h
	$(YACC) -d hornschema.y

hornschemalex.o: hornschemalex.c
	$(CC) -c -o hornschemalex.o hornschemalex.c

hornschema.tab.o: hornschema.tab.c
	$(CC) -c -o hornschema.tab.o hornschema.tab.c

hornschema.o:  hornschema_code.c
	$(CC) -c -o hornschema.o hornschema_code.c

hornschema: hornschemalex.o hornschema.tab.o hornschema.o
	$(LD) hornschema.o hornschemalex.o hornschema.tab.o -o hornschema

forceall:
	$(YACC) -d hornschema.y
	$(LEX) -t hornschema.l > hornschemalex.c
	$(YACC) -d hornschema.y
	$(CC) -c -o hornschema.o hornschema_code.c
	$(CC) -c -o hornschema.tab.o hornschema.tab.c
	$(CC) -c -o hornschemalex.o hornschemalex.c
	$(LD)  hornschemalex.o hornschema.tab.o  hornschema.o -o hornschema
