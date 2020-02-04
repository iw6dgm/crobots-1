

/*****************************************************************************/
/*                                                                           */
/*  CROBOTS                                                                  */
/*                                                                           */
/*  (C) Copyright Tom Poindexter, 1985, all rights reserved.                 */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

/* main.c - top level controller */
/* compile in compact memory model*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* INIT causes externals in crobots.h to have storage, & init intrinsic table */
#define INIT 1
#include "crobots.h"

#ifdef UNIX
#include <signal.h>
extern int catch_int();
#endif


int UPDATE_CYCLES=5;         /* number of cycles before screen update */


#ifdef LATTICE
int _stack = 6000;  /* Lattice C: give more stack than default of 2048 */
#endif
#ifdef DOS /* Turbo C */
#include <dos.h>
#include <process.h>
extern unsigned _stklen = 8000U;
#endif
/* files declared in compiler.h */
FILE *f_in;
FILE *f_out;

char *version   = "CROBOTS - version 1.1, PatchLevel3.4\n";
char *copyright = "Copyright 1985-2007 by Tom Poindexter, All rights reserved.\n";
int garbage=0;

char *nuxx="main";
char *bpoint="";


main(argc,argv)
int argc;
char *argv[];
{
  long limit = CYCLE_LIMIT;
  int matches = 0;
  int comp_only = 0;
  int debug_only = 0;
  int i;
  int num_robots = 0;
  char *files[MAXROBOTS];
  char *prog;
  char *strrchr();   /* this is rindex in some compilers */
  long atol();
  long time();
  void srand();

  /* init robots */
  for (i = 0; i < MAXROBOTS; i++) {
    init_robot(i);
    robots[i].name[0] = '\0';
  }


#ifdef UNIX
  prog = argv[0];
#else
  prog = "crobots";
#endif
  ndebug=0;
  ritardo=DEFAULT;

  /* parse the command line */
  for (i = 1; --argc; i++) {

    if (argv[i][0] == '-') {

      switch (argv[i][1]) {

	/* limit number of cycles in a match */
	case 'l':
	case 'L':
	  limit = atol((argv[i])+2);
	  break;

	/* run multiple matches */
	case 'm':
	case 'M':
	  matches = atoi((argv[i])+2);
	  break;

	/* compile only flag */
	case 'c':
	case 'C':
	  comp_only = 1;
	  break;

	/* debug one robot */
	case 'd':
	case 'D':
	  debug_only = 1;
	  break;

	/* full debug */
	case 's':
	case 'S':
	  ndebug=1;
          ritardo=LENTO;

	  if (strlen(argv[i])>3) bpoint=argv[i]+3;
	  else bpoint="";
	  break;

	/*Noheader - Quiet mode*/
//#ifdef __MSDOS__
	case 'g':
	case 'G':
	  garbage = 1;
	  break;
//#endif

	default:
	  break;
      }

    } else { 	/* a file name, check for existence */

    if (num_robots < MAXROBOTS) {
	if ((f_in = fopen(argv[i],"r")) != (FILE *) NULL) {
	  fclose(f_in);
	  files[num_robots] = argv[i];
	  num_robots++;
	} else {
	  fprintf(stderr,"%s: robot source file `%s' not found\n",prog, argv[i]);
	  printf("\n");
	}
      } else {
	fprintf(stderr,"%s: extra robot source `%s' ignored\n",prog,argv[i]);
      }
    }

  }

  /* print version, copyright notice */
  if (!garbage)
  {
    fprintf(stderr,"%s",version);
    fprintf(stderr,"%s",copyright);
    fprintf(stderr,"\n");
  }

  /* make sure there is at least one robot at this point */
  if (num_robots == 0) {
    fprintf(stderr,"%s: no robot source files\n",prog);
    exit(1);
  }

  /* seed the random number generator */
  srand((unsigned) time(NULL));

  /* now, figure out what to do */

  /* compile only */
  if (comp_only) comp(files,num_robots);
  else
    /* debug the first robot listed */
    if (debug_only) tracef(files[0]); /* trace only first source */
  else {
	if (num_robots < 2) {	/* if only one robot, make it fight itself */
	  fprintf(stderr,"%s: only one robot?, cloning a second from %s.\n", prog,files[0]);
	  num_robots++;
	  files[1] = files[0];
	}


      /* run a series of matches */
    if (matches != 0) match(matches,limit,files,num_robots);

      /* play with full display */
    else play(files,num_robots);

  /* all done */
  }
  exit(0);

}


/* comp - only compile the files with full info */

void comp(f,n)

char *f[];
int n;
{
  int i;
  char outfile[256];
  struct func *nextf;

  f_out = stdout;
  r_debug = 1;  /* turns on full compile info */

  for (i = 0; i < n; i++) {
    fprintf(f_out,"Compiling robot source: %s\n\n",f[i]);
    f_in = fopen(f[i],"r");

    /* compile the robot */
    r_flag = 0;
    cur_robot = &robots[i];
    init_comp();	/* initialize the compiler */
    yyparse();		/* start compiling */
    reset_comp();	/* reset compiler and complete robot */
    fclose(f_in);

    /* check r_flag for compile errors */
    if (r_flag) {
      fprintf(stdout,"\n%s could not compile\n\n",f[i]);
    } else {
      fprintf(stdout,"\n%s compiled without errors\n\n",f[i]);
	  strcpy(outfile,f[i]);
	  strcat(outfile,"o");
	  f_out=fopen(outfile,"wb");
	  fwrite(&(robots[i].code),sizeof(long),1,f_out); /*questo è un valore di offset*/
	  fwrite(&(robots[i].ext_count),sizeof(int),1,f_out);
	  fwrite(robots[i].funcs,ILEN,MAXSYM,f_out);
	  fwrite(robots[i].code, sizeof(struct instr),CODESPACE,f_out);
	  nextf=robots[i].code_list;
	  while (nextf != (struct func *) 0) {
		fwrite(nextf,sizeof(struct func),1,f_out);
        nextf = nextf->nextfunc;
	  }
	  fclose(f_out);
	  fprintf(stdout,"\nSaved object robot: %s\n\n",outfile);
    }
    if (i < n-1) {
      fprintf(stdout,"\n\n\nPress <enter> to continue.\n");
      getchar();
    }
  }
}




/* play - watch the robots compete */

void play(f,n)

char *f[];
int n;
{
  int num_robots = 0;
  int robotsleft;
  int display;
  int movement;
  int i, j, k;
  long c = 0L;
  char *s;
  char *strrchr();  /* this is rindex in some implementations */

  f_out = stdout;
  r_debug = 0;  /* turns off full compile info */

  for (i = 0; i < n; i++) {

    /* compile the robot */
    r_flag = 0;
    cur_robot = &robots[num_robots];
	loadrobot(f[i]);

    /* check r_flag for compile errors */
    if (r_flag) {
      fprintf(stdout,"\n %s could not compile\n",f[i]);
      free_robot(num_robots);
    } else {
      fprintf(stdout,"\n %s compiled without errors\n",f[i]);
      /* get last part of file name */
#ifdef UNIX
      s = strrchr(f[i],'/');
#else
      if (*f[i]+1 == ':')   	/* drive specified? */
	  f[i] = f[i] + 2;        /* yes, skip it */
      s = strrchr(f[i],'\\');
#endif
      if (s == (char *) NULL)
	  s = f[i];

      strncpy(robots[num_robots].name,s,MAXROBOTNAMELEN);

	  s=robots[num_robots].name;	/*questo serve per mettere in output sempre .r*/
	  if(tolower(s[strlen(s)-1])!='r') s[strlen(s)-1]=0;

      robot_go(&robots[num_robots]);
      num_robots++;
    }
    fprintf(stdout,"\n\nPress <enter> to continue.\n");
    getchar();
  }

  if (num_robots < 2) {
    fprintf(stdout,"\n\nCannot play without at least 2 good robots.\n\n");
    exit(1);
  }

#ifdef UNIX
  /* catch interrupt */
  /*if (signal(SIGINT,SIG_IGN) != SIG_IGN)
    signal(SIGINT,catch_int);*/
#endif

  rand_pos(num_robots);

  init_disp();
  update_disp();
  movement = MOTION_CYCLES;
  display = UPDATE_CYCLES;
  robotsleft = num_robots;

  /* multi-tasker; give each robot one cycle per loop */
  while (robotsleft > 1) {
    robotsleft = 0;
    for (i = 0; i < num_robots; i++) {
      if (robots[i].status == ACTIVE) {
	robotsleft++;
	cur_robot = &robots[i];
	cycle();
      }
    }

    /* is it time to update motion? */
    if (--movement <= 0) {
      movement = MOTION_CYCLES;
      move_robots(1);
      move_miss(1);
    }
    /* is it time to update display */
    if (--display <= 0) {


      display = UPDATE_CYCLES;
      c += UPDATE_CYCLES;
      show_cycle(c);
      update_disp();
    }
  }

  /* allow any flying missiles to explode */
  while (1) {
    k = 0;
    for (i = 0; i < num_robots; i++) {
      for (j = 0; j < MIS_ROBOT; j++) {
	if (missiles[i][j].stat == FLYING) {
	  k = 1;
	}
      }
    }
    if (k) {
      move_robots(1);
      move_miss(1);
      update_disp();
    }
    else
      break;
  }

  end_disp();

  k = 0;
  for (i = 0; i < MAXROBOTS; i++) {
    if (robots[i].status == ACTIVE) {
      fprintf(stdout,"\r\nAnd the winner is: ");
      fprintf(stdout,"(%d) %s\r\n",i+1,robots[i].name);
      k = 1;
      break;
    }
  }

  if (k == 0) {
    fprintf(stdout,"\r\nIt's a draw\r\n");
  }

  exit(0);

}




/* match - run a series of matches */

void match(m,l,f,n)

int m;
long l;
char *f[];
int n;
{
  int num_robots = 0;
  int robotsleft;
  int m_count;
  int movement;
  int i, j, k;
  int wins[MAXROBOTS];
  int ties[MAXROBOTS];
  long c;
  char *s;
  char *strrchr();  /* this is rindex in some implementations */

#ifdef UNIX
  f_out = fopen("/dev/null","w");
#elif defined (__MSDOS__)
  f_out = stdin; /* e' una porcheria... ma funziona*/
#else
  f_out = fopen("nul:","w");
#endif
  r_debug = 0; ndebug=0;  /* turns off full compile info */

  for (i = 0; i < n; i++) {
    wins[i] = 0;
    ties[i] = 0;

    /* compile the robot */
    r_flag = 0;
    cur_robot = &robots[num_robots];

	loadrobot(f[i]);

    /* check r_flag for compile errors */
    if (r_flag) {
      fprintf(stderr,"\n %s could not compile\n",f[i]);
      free_robot(num_robots);
    } else {
      if (!garbage) fprintf(stderr,"\n %s compiled without errors\n",f[i]);
      /* get last part of file name */
#ifdef UNIX
      s = strrchr(f[i],'/');
#else
      if (*f[i]+1 == ':')   	/* drive specified? */
	f[i] = f[i] + 2;        /* yes, skip it */
      s = strrchr(f[i],'\\');
#endif
      if (s == (char *) NULL)
	  s = f[i];
      strncpy(robots[num_robots].name,s,MAXROBOTNAMELEN);

	  s=robots[num_robots].name;	/*questo serve per mettere in output sempre .r*/
	  if(tolower(s[strlen(s)-1])!='r') s[strlen(s)-1]=0;

      num_robots++;
    }
  }

  fclose(f_out);

  if (num_robots < 2) {
    fprintf(stderr,"\n\nCannot play without at least 2 robots.\n\n");
    exit(1);
  }

  if (!garbage) fprintf(stderr,"\nMatch play starting.\n\n");
  for (m_count = 1; m_count <= m; m_count++) {

    printf("\nMatch %6d: ",m_count);
    for (i = 0; i < num_robots; i++) {
      init_robot(i);
      robot_go(&robots[i]);
      robots[i].status = ACTIVE;
    }
    rand_pos(num_robots);
    movement = MOTION_CYCLES;
    robotsleft = num_robots;
    c = 0L;
    while (robotsleft > 1 && c < l) {
      robotsleft = 0;
      for (i = 0; i < num_robots; i++) {
	if (robots[i].status == ACTIVE) {
	  robotsleft++;
	  cur_robot = &robots[i];
	  cycle();
	}
      }
      if (--movement == 0) {
	c += MOTION_CYCLES;
	movement = MOTION_CYCLES;
	move_robots(0);
	move_miss(0);
#ifdef DOS
	kbhit();  /* check keyboard so ctrl-break can work */
#endif
	for (i = 0; i < num_robots; i++) {
	  for (j = 0; j < MIS_ROBOT; j++) {
	    if (missiles[i][j].stat == EXPLODING) {
	      count_miss(i,j);
	    }
	  }
	}
      }
    }

    /* allow any flying missiles to explode */
    while (1) {
      k = 0;
      for (i = 0; i < num_robots; i++) {
	for (j = 0; j < MIS_ROBOT; j++) {
	  if (missiles[i][j].stat == FLYING) {
	    k = 1;
	  }
	}
      }
      if (k) {
	move_robots(0);
	move_miss(0);
      }
      else
	break;
    }

    printf(" cycles = %ld:\n  Survivors:\n",c);

    k = 0;
    for (i = 0; i < num_robots; i++) {
      if (robots[i].status == ACTIVE) {
	printf("   (%d)%*s: damage=%% %d  ",i+1,MAXROBOTNAMELEN,robots[i].name,
		robots[i].damage);
	if (i == 1)
	  printf("\n");
	else
	  printf("\t");
	k++;
      }
    }

    if (k == 0) {
      printf("mutual destruction\n");
    } else {
      printf("\n");
    }

    printf("  Cumulative score:\n");
    for (i = 0; i < n; i++) {
      if (robots[i].status == ACTIVE) {
	if (k == 1)
	  wins[i]++;
	else
	  ties[i]++;
      }
      printf("   (%d)%*s: wins=%d ties=%d  ",i+1,MAXROBOTNAMELEN,robots[i].name,
	      wins[i],ties[i]);
      if (i == 1)
	printf("\n");
      else
	printf("\t");
    }
    printf("\n");
  }

  fprintf(stderr,"\n Match play finished.\n\n");
  exit(0);

}



/* trace - compile and run the robot in debug mode */

void tracef(f)

char *f;
{
  int c = 1;

  r_debug = 1; /* turns on debugging in cpu */
  ndebug=0;
  f_out= stdout;

  /* compile the robot */
  r_flag = 0;
  cur_robot = &robots[0];
  loadrobot(f);


  /* check r_flag for compile errors */
  if (r_flag) {
    fprintf(stderr," %s could not compile\n",f);
    exit(1);
  }
  else
    robot_go(&robots[0]);

  /* randomly place robot */
  robots[0].x = rand() % MAX_X * 100;

  robots[0].y = rand() % MAX_Y * 100;

  /* setup a dummy robot at the center */
  robots[1].x = MAX_X / 2 * 100;
  robots[1].y = MAX_Y / 2 * 100;
  robots[1].status = ACTIVE;

  cur_robot = &robots[0];

  printf("\n\nReady to debug, use `d' to dump robot info, `q' to quit.\n\n");

  while (c) {
    cycle();

    /* r_flag set by hitting 'q' in cycle()'s debug mode */
    if (r_flag)
      c = 0;
    move_robots(0);
    move_miss(0);
  }

}




/* init a robot */
void init_robot(i)

int i;
{
  register int j;

  robots[i].status = DEAD;
  robots[i].x = 0;
  robots[i].y = 0;
  robots[i].org_x = 0;
  robots[i].org_y = 0;
  robots[i].range = 0;
  robots[i].last_x = -1;
  robots[i].last_y = -1;
  robots[i].speed = 0;
  robots[i].last_speed = -1;
  robots[i].accel = 0;
  robots[i].d_speed = 0;
  robots[i].heading = 0;
  robots[i].last_heading = -1;
  robots[i].d_heading = 0;
  robots[i].damage = 0;
  robots[i].last_damage = -1;
  robots[i].scan = 0;
  robots[i].last_scan = -1;
  robots[i].reload = 0;
  for (j = 0; j < MIS_ROBOT; j++) {
    missiles[i][j].stat = AVAIL;
    missiles[i][j].last_xx = -1;
    missiles[i][j].last_yy = -1;
  }
}



/* free_robot - frees any allocated storage in a robot */

void free_robot(i)

int i;
{
  struct func *temp;

  if (robots[i].funcs != (char *) 0)
    free(robots[i].funcs);

  if (robots[i].code != (struct instr *) 0)
    free(robots[i].code);

  if (robots[i].external != (long *) 0)
    free(robots[i].external);

  if (robots[i].stackbase != (long *) 0)
    free(robots[i].stackbase);

  while (robots[i].code_list != (struct func *) 0) {
    temp = robots[i].code_list;
    robots[i].code_list = temp->nextfunc;
    free(temp);
  }

}

/* rand_pos - randomize the starting robot postions */
/*           dependent on MAXROBOTS <= 4 */
/*            put robots in separate quadrant */

void rand_pos(n)

int n;
{
  int i, k, s, r;
  int quad[4];

  for (i = 0; i < 4; i++) {
    quad[i] = 0;
  }
  s = rand() % n;
  /* get a new quadrant */
  for (i = 0; i < n; i++) {
      if (i == 3) {
          k = 0;
          while (quad[k] != 0) k++;
      } else do {
          k = rand() % 4;
      } while (quad[k] != 0);
      quad[k] = 1;
      r = (i + s) % n;
    robots[r].org_x = robots[r].x =
       (rand() % (MAX_X * CLICK / 2)) + ((MAX_X * CLICK / 2) * (k%2));
    robots[r].org_y = robots[r].y =
       (rand() % (MAX_Y * CLICK / 2)) + ((MAX_Y * CLICK / 2) * (k<2));
  }
}





#ifdef UNIX
/* catch_int - catch the interrupt signal and die, cleaning screen */

catch_int()
{
  int i;
/*
  for (i = 0; i < MAXROBOTS; i++) {
    cur_robot = &robots[i];
      printf("\nrobot: %d",i);
      printf("\tstatus......%d",cur_robot->status);
      printf("\nx...........%5d",cur_robot->x);
      printf("\ty...........%5d",cur_robot->y);
      printf("\norg_x.......%5d",cur_robot->org_x);
      printf("\torg_y.......%5d",cur_robot->org_y);
      printf("\nrange.......%5d",cur_robot->range);
      printf("\tspeed.......%5d",cur_robot->speed);
      printf("\nd_speed.....%5d",cur_robot->d_speed);
      printf("\theading.....%5d",cur_robot->heading);
      printf("\nd_heading...%5d",cur_robot->d_heading);
      printf("\tdamage......%5d",cur_robot->damage);
      printf("\nmiss[0]stat.%5d",missiles[cur_robot-&robots[0]][0].stat);
      printf("\tmiss[1]stat.%5d",missiles[cur_robot-&robots[0]][1].stat);
      printf("\nmiss[0]head.%5d",missiles[cur_robot-&robots[0]][0].head);
      printf("\tmiss[1]head.%5d",missiles[cur_robot-&robots[0]][1].head);
      printf("\nmiss[0]x....%5d",missiles[cur_robot-&robots[0]][0].cur_x);
      printf("\tmiss[1]y....%5d",missiles[cur_robot-&robots[0]][1].cur_y);
      printf("\nmiss[0]dist.%5d",missiles[cur_robot-&robots[0]][0].curr_dist);
      printf("\tmiss[1]dist.%5d",missiles[cur_robot-&robots[0]][1].curr_dist);
      printf("\n\n");
  }
*/
  if (!r_debug)
    end_disp();
  exit(0);
}
#endif


/* end of main.c */
