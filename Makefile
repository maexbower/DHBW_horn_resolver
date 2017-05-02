LEX  = flex
YACC = bison
CC   = gcc
LD   = gcc
TMPFILES = *.out *.o *.exe hornschemalex.c hornschemalex.o hornschema.tab.c hornschema.tab.h hornschema.tab.o lex.yy.c hornschema_datatypes.o hornschema_code.o
RED	 = '\033[0;31m'
GREEN = '\033[0;32m'
NC   = '\033[0m'
EXECBASE = hornschema
WINEXEC = ${EXECBASE}.exe

ifeq ($(OS),Windows_NT)
	#Windows stuff
	EXEC = ${WINEXEC}
else
	#Linux stuff
	EXEC = ${EXECBASE}
endif

all: $(EXEC)

hornschemalex.c: hornschema.l hornschema.tab.h hornschema_datatypes.h hornschema_datatypes.o
	$(LEX) -t hornschema.l > hornschemalex.c

hornschema.tab.h: hornschema.y hornschema_datatypes.h hornschema_code.h hornschema_code.o hornschema_datatypes.o
	$(YACC) -d hornschema.y

hornschema.tab.c: hornschema.y hornschema_datatypes.h hornschema_code.h
	$(YACC) -d hornschema.y

hornschemalex.o: hornschemalex.c
	$(CC) -c -o hornschemalex.o hornschemalex.c

hornschema.tab.o: hornschema.tab.c
	$(CC) -c -o hornschema.tab.o hornschema.tab.c

hornschema_code.o:  hornschema_code.c hornschema_code.h hornschema_datatypes.h
	$(CC) -c -o hornschema_code.o hornschema_code.c

hornschema_datatypes.o: hornschema_datatypes.c hornschema_datatypes.h
	$(CC) -c -o hornschema_datatypes.o hornschema_datatypes.c

$(EXEC): hornschema_code.o hornschema_datatypes.o hornschemalex.o hornschema.tab.o
	$(LD) hornschema_code.o hornschema_datatypes.o hornschemalex.o hornschema.tab.o -o $(EXEC)

forceall:
	$(CC) -c -o hornschema_code.o hornschema_code.c
	$(CC) -c -o hornschema_datatypes.o hornschema_datatypes.c
	$(YACC) -d hornschema.y
	$(LEX) -t hornschema.l > hornschemalex.c
	$(CC) -c -o hornschemalex.o hornschemalex.c
	$(CC) -c -o hornschema.tab.o hornschema.tab.c
	$(LD) hornschema_code.o hornschema_datatypes.o hornschemalex.o hornschema.tab.o -o $(EXEC)

run:
	make test-s
	make test-u
	
test-s: $(EXEC)
	{ \
	for f in $$(ls ./satisfiable); do ( 					\
		printf "Run Testfile $$f"									;\
		./$(EXEC) ./satisfiable/$$f >>/dev/null	;\
		if [ $$? -eq 0 ]; then											\
			printf "${GREEN}...Erfolgreich${NC}\n"								;\
		else																			\
			printf "${RED}...Fehlgeschlagen${NC}\n"						;\
		fi																				\
		); done																		;\
	}

test-u: $(EXEC)
	{ \
	for f in $$(ls ./unsatisfiable); do ( 					\
		printf "Run Testfile $$f"									;\
		./$(EXEC) ./unsatisfiable/$$f >>/dev/null	;\
		if [ $$? -eq 1 ]; then											\
			printf "${GREEN}...Erfolgreich${NC}\n"								;\
		else																			\
			printf "${RED}...Fehlgeschlagen${NC}\n"						;\
		fi																				\
		); done																		;\
	}
clean:
	rm -f $(TMPFILES) ${EXECBASE} ${WINEXEC}
