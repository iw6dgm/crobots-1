CFLAGS = -O4 -march=native -mtune=native
CFLAGS += -Dlinux -DUNIX
LIBS = -lm -lcurses
# Linux gcc flags: optimize(O) separate text and data(i)
# Sembra che linkare -ltermcap sia inutile

# makefile for crobots

OBJS =  ap.o main.o debug.o grammar.o lexanal.o compiler.o cpu.o intrins.o display.o screen.o motion.o

#  nota - dopo lunghi infruttuosi tentativi per ricompilare lexanal.l
#  mi sono arreso e ho usato quello fornito nella distro gia' trasformato in *.c
#  Ovviamente qualche cosa doveva andare storto.... in lexanal.c la gestione dei file di i/o
#  non andava bene. Cosi' ho passato lexanal.l sotto lex e con un rapido C&P le cose si sono
#  sistemate.
#  Il Makefile e' il risultato di numerosi tentativi e non ne garantisco la tenuta.
#  La patch ap.c modificata e' gia' inclusa e sembra funzionare correttamente.
#  Ho dovuto modificare un fprintf in printf nel main.c che non compilava.
#  Inoltre in Crobots.h vanno modificati alcuni short int in long, e in cpu.c bisogna
#  cambiare un int offset; in long offset;.


crobots: 	$(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o crobots $(LIBS)

grammar.o: 	crobots.h compiler.h grammar.y
#		yacc -d grammar.y
#		egrep -v '# line|^#$$' y.tab.c >grammar.c
#		rm y.tab.c
#		mv y.tab.h tokens.h
		$(CC) $(CFLAGS) -c grammar.c

lexanal.o: 	crobots.h compiler.h lexanal.l grammar.y
#		lex lexanal.l
#		egrep -v '# ifdef|# endif' lex.yy.c >lexanal.c
#		rm lex.yy.c
		$(CC) $(CFLAGS) -c lexanal.c

cpu.o: 		crobots.h grammar.y cpu.c
		$(CC) $(CFLAGS) -c cpu.c
	
compiler.o: 	crobots.h compiler.h tokens.h compiler.c
		$(CC) $(CFLAGS) -c compiler.c

debug.o:	debug.c crobots.h tokens.h
		$(CC) $(CFLAGS) -c debug.c		

%.o:		%.c crobots.h
		$(CC) $(CFLAGS) -c $<
	
clean:
		rm -f $(OBJS) crobots
