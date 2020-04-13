

/*****************************************************************************/
/*                                                                           */
/*  CROBOTS                                                                  */
/*                                                                           */
/*  (C) Copyright Tom Poindexter, 1985, all rights reserved.                 */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

/* common defines */


/*#define UNIX    1*/
/*#define __MSDOS__ 1*/
/*#define bcc32 1*/
#define w64 1

#include <stdint.h>


/* note-the INIT flag (or lack of it) causes extern for all but one module */

#define ILEN      8		/* length of identifiers, also in lexanal.l */
#define MAXSYM    128    /* maximum number of symbol table entries per pool */
#define MAXROBOTS 4		/* maximum number of robots */
#define MAXROBOTNAMELEN	14
#define CODESPACE 2000		/* maximum number of machine instructions */
#define DATASPACE 2000		/* maximum number of data stack entries */
#define MOTION_CYCLES 15 	/* number of cycles before motion update */
#define CYCLE_LIMIT 500000L	/* limit of background cycles */
#define ROBOT_SPEED 7		/* multiplicative speed factor */
#define TURN_SPEED 50		/* maximum speed for direction change */
#define ACCEL  10		/* acceleration factor per motion cycle */

#define ACTIVE    1		/* robot active & running */
#define DEAD      0		/* dead robot */

struct robot {			/* robot context */
  int status;			/* status of robot, active or dead */
  char name[MAXROBOTNAMELEN];	/* name of robot */
  int x;			/* current x location * 100 */
  int y;			/* current y location * 100 */
  int org_x;			/* orgin x location * 100 */
  int org_y;			/* orgin y location * 100 */
  int range;			/* distance traveled on this heading * 100 */
  int last_x;			/* last plotted physical x */
  int last_y;			/* last plotted physical y */
  int speed;			/* current speed, 0 - 100 */
  int last_speed;		/* last speed, 0 - 100 */
  int accel;			/* linear acceleration / de-acceleration lag */
  int d_speed;			/* desired speed */
  int heading;			/* current heading, 0 - 359 */
  int last_heading;		/* last heading, 0 - 359 */
  int d_heading;		/* desired heading, 0 - 359 */
  int damage;			/* damage sustained, percent */
  int last_damage;		/* last damage */
  int scan;			/* current scan direction */
  int last_scan;		/* last scan direction */
  int reload;			/* number of cycles between reloading */
  int32_t ext_count;		/* size of external pool needed */
  int64_t *external;		/* external variable pool */
  char *vnames;     		/*store external variables*/
  int64_t *local;			/* current local variables on stack */
  int64_t *stackbase;		/* base of local & expression stack */
  int64_t *stackend;		/* end of stack */
  int64_t *stackptr;		/* current stack pointer, grows up */
  int64_t *retptr;			/* return frame pointers, grow down */
  char *funcs;			/* table of function names by offset */
  struct func *code_list;	/* list of function headers */
  struct instr *code;		/* machine instructions, actually instr */
  struct instr *ip;		/* instruction pointer */
};


//struct func {			/* function header */
//	struct func *nextfunc;	/* next function header in chain */
//	char func_name[ILEN];		/* function name */
//	char *vnames;     		/*store local variables*/
//	struct instr *first;		/* first instruction pointer */
//	int var_count;		/* number of pool variables needed */
//	int par_count;		/* number of parameters expected */
//};

struct func {			/* function header */
	int64_t nextfunc;	/* next function header in chain */
	char func_name[ILEN];		/* function name */
	int64_t vnames;     		/*store local variables*/
	int64_t first;		/* first instruction pointer */
	int32_t var_count;		/* number of pool variables needed */
	int32_t par_count;		/* number of parameters expected */
};

//struct instr {			/* robot machine instruction */
//  char ins_type;		/* instruction type */
//  union {
//	int64_t k;			/* constant value */
//	int64_t var1;		/* variable offset, function offset, operator */
//    struct intstr *br;			/* false branch */
//    struct {
#ifdef UNIX
//	int64_t var2;		/* assignment variable offset */
//	int64_t a_op;		/* assignment operator */
#elif w64
//	int64_t var2;		/* assignment variable offset */
//	int64_t a_op;		/* assignment operator */
#else
//    int var2;           /* assignment variable offset */
//    int a_op;           /* assignment operator */
#endif
//    } a;
//  } u;
//};

struct instr {			/* robot machine instruction */
	int64_t ins_type;		/* instruction type */
	union {
		int64_t k;			/* constant value */
		int64_t var1;		/* variable offset, function offset, operator */
		int64_t br;			/* false branch */
		struct {
			int64_t var2;		/* assignment variable offset */
			int64_t a_op;		/* assignment operator */
		} a;
	} u;
};


/* ap.c constants*/
#define  VELOCE  ( 0 )
#define  DEFAULT ( 7 )
#define  LENTO   ( 9 )
#ifndef INIT
extern
#endif
long ritardo;



/* missile constants */
#define MIS_SPEED 500		/* how far in one motion cycle (in clicks) */
#define MIS_RANGE 700 		/* maximum missile range (see MAX_X, MAX_Y */
#define MIS_ROBOT 2		/* number of active missiles per robot */
#define AVAIL  0		/* missile available for use */
#define FLYING 1		/* missile in air */
#define EXPLODING 2		/* missile exploding on ground */
#define RELOAD 15		/* motion cycles before reload */
#define EXP_COUNT 5 		/* motion cycles for exploding missile */

struct missile {			/* active missiles */
  int stat;			/* missile status */
  int beg_x;			/* beginning x * 100 */
  int beg_y;			/* beginning y * 100 */
  int cur_x;			/* current x * 100 */
  int cur_y;			/* current y * 100 */
  int last_xx;			/* last plotted x */
  int last_yy;			/* last plotted y */
  int head;			/* heading, 0 - 359 */
  int count;			/* cycle count for exploding missiles */
  int rang;			/* range of missile */
  int curr_dist;		/* current distance from orgin * 100 */
};

#ifndef INIT
extern
#endif
struct missile missiles[MAXROBOTS][MIS_ROBOT];

#ifndef INIT
extern
#endif
struct robot *cur_robot,	/* current robot */
	     robots[MAXROBOTS];	/* all robots */

#ifndef INIT
extern
#endif
int r_debug,			/* debug switch */
    ndebug,
    r_flag;			/* global flag for push/pop errors */

/* instruction types */
#define NOP    0		/* end of code marker */
#define FETCH  1		/* push(varpool(offset)) */
#define STORE  2		/* push(pop op pop) --> varpool(offset) */
#define CST  3		/* push(constant) */
#define BINOP  4		/* pop -->y, pop -->x, push(x op y) */
#define FCALL  5		/* pop --> parmn..parm1, save ip, call */
#define RETSUB 6		/* push(returnval), restore ip */
#define BRANCH 7		/* if (pop == 0) branch --> ip*/
#define CHOP   8		/* pop --> bit bucket */
#define FRAME  9		/* frame stack pointer for call */

/* external variable flag (or'ed in or and'ed out) , also in grammar.y */
#define EXTERNAL 0x8000

/* size of battlefield, see MIS_RANGE also. note - x and y coordinates */
/* of robots and missiles are measured in CLICKS * MAX_? */
#define CLICK 10		/* 10 clicks per meter */
#define MAX_X 1000		/* 1000 meters x axis */
#define MAX_Y 1000		/* 1000 meters y axis */

/* damage factors, percent */
#define DIRECT_HIT 10
#define NEAR_HIT   5
#define FAR_HIT    3
#define COLLISION  2
/* distance of damage factors */
#define DIRECT_RANGE 5
#define NEAR_RANGE   20
#define FAR_RANGE    40

/* declare the intrinsic functions, all must push a long value on the stack */
void c_scan();    /* scan(degree,res);  >0 = robot distance, 0 = nothing */
void c_cannon();  /* cannon(degree,dist); fire cannon */
void c_drive();   /* drive(degree,speed); speed 0-100 in % */
void c_damage();  /* damage(); = current damage in % */
void c_speed();   /* speed(); = current speed */
void c_loc_x();   /* loc_x(); = current x location */
void c_loc_y();   /* loc_y(); = current y location */
void c_rand();    /* rand(limit); = 0 -- limit (2**15)-1 */
void c_sin();     /* sin(degree); = sin * 100000 */
void c_cos();     /* cos(degree); = cos * 100000 */
void c_tan();     /* tan(degree); = tan * 100000 */
void c_atan();    /* atan(ratio); = degree */
void c_sqrt();    /* sqrt(x); = square root */

/* declare instrinsic function table */
#ifndef INIT
extern
#endif
struct intrin {
  char *n;
  void (*f)();
} intrinsics[20]

#ifdef INIT
 = {
  {"*dummy*",	(void (*)()) 0},
  {"scan",	c_scan},
  {"cannon",	c_cannon},
  {"drive",	c_drive},
  {"damage",	c_damage},
  {"speed",	c_speed},
  {"loc_x",	c_loc_x},
  {"loc_y",	c_loc_y},
  {"rand",	c_rand},
  {"sin",	c_sin},
  {"cos",	c_cos},
  {"tan",	c_tan},
  {"atan",	c_atan},
  {"sqrt",	c_sqrt},
  {"",		(void (*)()) 0}
}
#endif
;

/*definitions*/
void ap_main();
int32_t poolsize(char *);
long findvar(char [], char *);
long allocvar(char [], char *);
void dumpoff(char *);
void decompile(struct instr*);
void decinstr(struct instr*);
void printop(int64_t);
void loadrobot(char *);
void init_robot(int);
void init_comp();
int reset_comp();
int yyparse();
void binaryop(int);
void robot_go(struct robot*);
void dumpvar(int64_t *,int);
void warn();
void miss_dat(int);
void dvar(char *, int64_t *,int);
void dlocal(char *, int64_t *);
void showinstr(struct instr *,int);
void newprint(int);
void plot_robot(int);
void robot_stat(int);
void debug_par(int);
void plot_miss(int,int);
void plot_exp(int,int);
void count_miss(int,int);
void draw_field();
void rand_pos(int);
void free_robot(int);
void tracef(char *);
void match(int,long,char *[],int);
void play(char *[],int);
void comp(char *[],int);
void init_disp();
void update_disp();
void cycle();
void move_robots(int);
void move_miss(int);
void show_cycle(long);
void end_disp();
void gotoxy(int, int);
int wherex();
int wherey();
void clrscr();
void clreol();
#ifndef UNIX
void move(int, int);
#endif







/* end of crobots.h header */
