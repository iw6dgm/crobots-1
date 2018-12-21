/***************************************************************************
			  debug.C  -  description
			     -------------------
    begin                : Fri Oct 13 2000
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


/*****************************************************************************/
/*                                                                           */
/*  CROBOTS                                                                  */
/*                                                                           */
/*  (C) Copyright Tom Poindexter, 1985, all rights reserved.                 */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

/* debug.c - */
/*           */

#define ILEN      8		/* length of identifiers, also in lexanal.l */
/* structure passed on int86 call */
#define STAT_WID 20   /* width of characters for status boxes */

#include "crobots.h"
#include "tokens.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef UNIX
	#include <curses.h>
	#define clreol clrtoeol
		/* e qua come si fa? */
	/*#ifdef debug*/
	#define LINES 21
	/*#endif*/
#else
	#include <dos.h>
	#include <conio.h>
	#define COLS  80
	#define LINES 25
	#define printw printf
#endif


static int col_1;    /* column for damage & speed */
static int col_2;    /* column for scan & heading */
static int col_3;    /* column for cpu cycle count*/
static int molt;

extern long ritardo;
extern char *bpoint;
extern char buffer[2];
static char *old[10000];
extern char *nuxx;

static int livello;
static int intra;

void debug_par(int n)
{
  col_1 = COLS - STAT_WID + 5;
  col_2 = COLS - STAT_WID + 14;
  col_3 = COLS - STAT_WID + 11;

	move(5*n+3,COLS-STAT_WID);
	printw("  X=       Y=    ");
	move(5*n+3,col_1);
	printw("%3d",robots[n].x / CLICK);
	move(5*n+3,col_2);
	printw("%3d",robots[n].y / CLICK);

	if (!n)
		{
			cur_robot=&robots[0];
			move(LINES,0);
			miss_dat(0);
			dvar(cur_robot->vnames,cur_robot->external,cur_robot->ext_count);
			dlocal(nuxx,cur_robot->local);
		}
}

/* varnamefind - return the name of a variable in a pool by offset*/

char* varnamefind(int s,char *pool)
{
	return (&(pool[s * ILEN]));
}

struct func* funcfind(char* name)
{
	struct func* temp;
	temp=robots[0].code_list;
	while(temp) {
		if(!strcmp(name,temp->func_name)) {
			return temp;
		}
		else temp=(struct func*)temp->nextfunc;
	}
	return robots[0].code_list;
}

void dlocal(char *name, long* pool1)
{
	register int i,y;
#ifdef linux
    int x;
#endif // linux
	struct func* temp;
	static char oldname[80];


	temp=funcfind(name);
	if (strcmp(oldname,name)) {
#ifdef linux
		getyx(stdscr,y,x);
#else
		y=wherey();
#endif
		for(i=y;i<49;i++){ move(i,0); clreol(); }
		move(y-1,1);
		strcpy(oldname,name);
	} else {
		printw("\nFunction: %8s Local symbol table\n",name);

		i=0;
		while(*(&temp->vnames+i*ILEN*sizeof(int64_t))!='\0') {
#ifdef linux
			getyx(stdscr,y,x);
			if(x>70) printw("\n");
#else
			if(wherex()>70) printw("\n");
#endif
			for (y = 0; (*intrinsics[y].n != '\0') && (strcmp(intrinsics[y].n,varnamefind(i,(char *)temp->vnames))); y++);
			if(*intrinsics[y].n=='\0') {
				printw("%8s:",varnamefind(i, (char *)temp->vnames));
				printw(" %8ld ",*(pool1 + i++));
			} else i++;
		}
	}
}


void dvar(char *pool,long *pool1,int size)
{
  int j;
  register int i;
  register char *n;
  for (i = 0; i < size; i++) {
    old[0]="main";
    switch(cur_robot->ip->ins_type) {
      case FCALL:
	++livello;
	n=nuxx= cur_robot->funcs + (cur_robot->ip->u.var1 * ILEN);
	for (j = 0; *intrinsics[j].n != '\0'; j++)
	if (!strcmp(intrinsics[j].n,n) ) {nuxx=old[--livello];intra=1;}
	old[livello]=nuxx;
	break;
      case RETSUB:
	if (intra){
	     if (--livello<0) livello=0;
	     nuxx=old[livello];
	} else intra=0;
	break;
      default:
	break;
    }

    if (!(i % 4)) printw("\n");
    printw("%8s:",varnamefind(i,pool));
    if (!strcmp(nuxx,varnamefind(i,pool)))    printw("   <---   "); /*,*(pool1 + i));*/
    else printw(" %8ld ",*(pool1 + i));
  }
}

void miss_dat(int n)
{
	int rel;
	printw("miss_stat  %7d",missiles[cur_robot-&robots[n]][0].stat);
	printw(" miss_head  %7d\t",missiles[cur_robot-&robots[n]][0].head);
	showinstr(cur_robot->ip,n);
	printw("miss_beg_x %7ld",missiles[cur_robot-&robots[n]][0].beg_x / CLICK);
	printw(" miss_beg_y %7ld\t",missiles[cur_robot-&robots[n]][0].beg_y / CLICK);
	printw("tos %ld: * %ld",(long)cur_robot->stackptr,*cur_robot->stackptr);
	clreol();
	printw("\nmiss_cur_x %7ld",missiles[cur_robot-&robots[n]][0].cur_x / CLICK);
	printw(" miss_cur_y %7ld",missiles[cur_robot-&robots[n]][0].cur_y / CLICK);
	printw("\nmiss_dist  %7ld",missiles[cur_robot-&robots[n]][0].curr_dist / CLICK);
	printw(" miss_range %7ld",missiles[cur_robot-&robots[n]][0].rang / CLICK);
	if (strlen(bpoint)>0) printw("\tbreakpoint  : %s",bpoint);
	if (((rel=(robots[n].reload))<15)&&(rel>0)){
		if ((++molt)>15) molt=1;
		if ((rel*=15)>0) rel-=molt;
	} else rel=0;
	printw("\nrel. time  %7ld\n",rel);
}

void showinstr(struct instr *code,int n)
{

  printw("%8ld : ",(long) code);	/* this could be flakey */
  switch (code->ins_type) {
    case FETCH:
      if (code->u.var1 & EXTERNAL)
	printw("fetch   %s ext",varnamefind((int)code->u.var1 & ~EXTERNAL,robots[n].vnames));
      else
	printw("fetch   %s local",varnamefind((int)code->u.var1, (char *)funcfind(nuxx)->vnames));

      break;
    case STORE:
      if (code->u.a.var2 & EXTERNAL)
	printw("store   %s ext, ",
		varnamefind(code->u.a.var2 & ~EXTERNAL,robots[n].vnames));
      else
	printw("store   %s local, ",varnamefind((int)code->u.a.var2, (char *)funcfind(nuxx)->vnames));
      newprint((int)code->u.a.a_op);
      break;
    case CONST:
      printw("const   %I64d",code->u.k);
      break;
    case BINOP:
      printw("binop ");
      newprint(code->u.var1);
      break;
    case FCALL:
      printw("fcall   %s",cur_robot->funcs + (cur_robot->ip->u.var1 * ILEN));
      if (strcmp(bpoint,cur_robot->funcs + (cur_robot->ip->u.var1 * ILEN))==0) *buffer='.';
      break;
    case RETSUB:
      printw("retsub");
      break;
    case BRANCH:
      printw("branch  %ld",(long) code->u.br); /* more flakiness */
      break;
    case CHOP:
      printw("chop");
      break;
    case FRAME:
      printw("frame");
      break;
    default:
      printw("ILLEGAL %d",code->ins_type);
      return;
  }
  clreol();
  printw ("\n");
}


/* newprint - print a binary operation code */

void newprint(int op)
{

  switch (op) {

    case  '=':
      printw("=");
      break;

    case  '|':
      printw("|");
      break;

    case  '^':
      printw("^");
      break;

    case  '&':
      printw("&");
      break;

    case  '<':
      printw("<");
      break;

    case  '>':
      printw(">");
      break;

    case  '+':
      printw("+");
      break;

    case  '-':
      printw("-");
      break;

    case  '*':
      printw("*");
      break;

    case  '/':
      printw("/");
      break;

    case  '%':
      printw("%%");
      break;

    case  LEFT_OP:
      printw("<<");
      break;

    case  RIGHT_OP:
      printw(">>");
      break;

    case  LE_OP:
      printw("<=");
      break;

    case  GE_OP:
      printw(">=");
      break;

    case  EQ_OP:
      printw("==");
      break;

    case  NE_OP:
      printw("!=");
      break;

    case  AND_OP:
      printw("&&");
      break;

    case  OR_OP:
      printw("||");
      break;

    case  MUL_ASSIGN:
      printw("*=");
      break;

    case  DIV_ASSIGN:
      printw("/=");
      break;

    case  MOD_ASSIGN:
      printw("%%=");
      break;

    case  ADD_ASSIGN:
      printw("+=");
      break;

    case  SUB_ASSIGN:
      printw("-=");
      break;

    case  LEFT_ASSIGN:
      printw("<<=");
      break;

    case  RIGHT_ASSIGN:
      printw(">>=");
      break;

    case  AND_ASSIGN:
      printw("&=");
      break;

    case  XOR_ASSIGN:
      printw("^=");
      break;

    case  OR_ASSIGN:
      printw("|=");
      break;

    case  U_NEGATIVE:
      printw("(-)");
      break;

    case  U_NOT:
      printw("(!)");
      break;

    case  U_ONES:
      printw("(~)");
      break;

    default:
      printw("ILLEGAL %d",op);
      break;

  }
}

void warn()
{
char c;
    move (LINES+1,col_1);
    printw("Robot Reset!!");
    move (LINES+2,col_1);
    printw("Press A");
#ifndef UNIX
	while(!kbhit());
#endif
    do c=getch(); while ((c!='A')&&(c!='a'));
    move (LINES+1,col_1);
    clreol();
    move (LINES+2,col_1);
    clreol();
}

