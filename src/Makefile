# makefile for crobots

OBJS =  ap.o main.o debug.o grammar.o lexanal.o compiler.o cpu.o intrins.o display.o screen.o motion.o

# Linux gcc flags: optimize(O) separate text and data(i)

CFLAGS = -O4 -march=native -mtune=native -Dwin64
LIBS = -lm -lcurses

#  Sembra che linkare -ltermcap sia inutile

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
		gcc -s $(CFLAGS) $(OBJS) -o crobots $(LIBS)

ap.o: 	ap.c
		gcc $(CFLAGS) -c ap.c

main.o: 	crobots.h main.c
		gcc $(CFLAGS) -c main.c

grammar.o: 	crobots.h compiler.h grammar.y
#		yacc -d grammar.y
#		egrep -v '# line|^#$$' y.tab.c >grammar.c
#		rm y.tab.c
#		mv y.tab.h tokens.h
		gcc $(CFLAGS) -c grammar.c

lexanal.o: 	crobots.h compiler.h lexanal.l grammar.y
#		lex lexanal.l
#		egrep -v '# ifdef|# endif' lex.yy.c >lexanal.c
#		rm lex.yy.c
		gcc $(CFLAGS) -c lexanal.c

compiler.o: 	crobots.h compiler.h tokens.h compiler.c
		gcc $(CFLAGS) -c compiler.c
	
cpu.o: 		crobots.h grammar.y cpu.c
		gcc $(CFLAGS) -c cpu.c
	
intrins.o:	crobots.h intrins.c
		gcc $(CFLAGS) -c intrins.c
	
display.o:	crobots.h display.c
		gcc $(CFLAGS) -c display.c
	
screen.o:	crobots.h screen.c
		gcc $(CFLAGS) -c screen.c

screenx.o:	crobots.h screenx.c
		gcc $(CFLAGS) -c screenx.c
	
motion.o:	crobots.h motion.c
		gcc $(CFLAGS) -c motion.c
	
