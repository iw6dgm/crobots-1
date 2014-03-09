/***************************************************************************
                          ap.c  -  description
                             -------------------
    begin                : Sun Oct 15 2000
    copyright            : (C) 2000 by 
    email                : 
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
/*
	Scritto da Antonio Pennino
*/

#include <stdio.h>
#include "crobots.h"
#ifdef __MSDOS__
#include <conio.h>
#else
#include <stdlib.h>
#include <string.h>
#include <termio.h>
#endif


#define LATENCY 700000
char buffer[2];
extern int UPDATE_CYCLES;
extern long ritardo;


void ap_main()
{
#ifdef UNIX
  int n;
  unsigned long int loop;

  struct termio t_old, t_new;

  ioctl(0,TCGETA,&t_old);     /* leggo la config. attuale del terminale      */
  ioctl(0,TCGETA,&t_new);     /* leggo la config. attuale del terminale      */

  t_new.c_lflag &= ~ICANON;   /* modifico, in modo da togliere ICANON        */
  t_new.c_lflag &= ~ECHO;     /* modifico, in modo da togliere ECHO          */
  t_new.c_cc[VMIN] = 0;       /* modifico, in modo da NON aspettare l' input */
  t_new.c_cc[VTIME] = 0;      /* modifico, in modo da NON aspettare l' input */
  ioctl(0,TCSETA,&t_new);     /* salvo la modifica                           */

   read(0,buffer,1);
	if (*buffer=='.') {
		ritardo=LENTO;
		while (!read(0,buffer,1));
	}
#else
  long n;
	if (kbhit()) *buffer = (getch());
	if (*buffer=='.') {
		ritardo=LENTO;
		while (!kbhit());
	  }
#endif
	if (*buffer == ' ')                        ritardo =VELOCE;
	if (*buffer == '*')                        ritardo =DEFAULT;
	if (*buffer == '/')                        ritardo =LENTO;
	if (*buffer == '9')                        ritardo =1;
	if (*buffer == '8')                        ritardo =2;
	if (*buffer == '7')                        ritardo =3;
	if (*buffer == '6')                        ritardo =4;
	if (*buffer == '5')                        ritardo =5;
	if (*buffer == '4')                        ritardo =6;
	if (*buffer == '3')                        ritardo =7;
	if (*buffer == '2')                        ritardo =8;
	if (*buffer == '1')                        ritardo =9;
	if (*buffer == 'q' || *buffer == 'Q')
		for (n=0;n<MAXROBOTS;n++) robots[n].status=DEAD;
	if(ndebug) UPDATE_CYCLES=1;
	else UPDATE_CYCLES=46-ritardo*5;
	for (n=1;n<(ritardo*LATENCY);++n);
#ifdef UNIX
	ioctl(0,TCSETA,&t_old);     /* rimetto a posto il terminale                */
#endif
}
