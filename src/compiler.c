/*****************************************************************************/
/*                                                                           */
/*  CROBOTS                                                                  */
/*                                                                           */
/*  (C) Copyright Tom Poindexter, 1985, all rights reserved.                 */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

/* compiler.c - compiler routines in support of grammar.c */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "crobots.h"
/* EXT causes externals to be declared without extern keyword in compiler.h */
/* that is, to give them actual storage (some compilers require this method) */
#define EXT 1
#include "compiler.h"
#include "tokens.h"

#include <stdint.h>


/*load and compile the robot*/
void loadrobot(char *robotname)
{
	char teststring[256];
	struct func *nextf,*prevf;
	int64_t myoffset;
	int zzz;
	struct instr* contrinstr;
	int64_t *n;

	if(strrchr(robotname,'.')) strcpy(teststring,strrchr(robotname,'.'));
	teststring[1]=tolower(teststring[1]);

	if(!strcmp(teststring,".r")) {
		fprintf(f_out,"Compiling robot source: %s\n\n",robotname);
		f_in = fopen(robotname,"r");
		init_comp();	/* initialize the compiler */
		yyparse();		/* start compiling */
		reset_comp();	/* reset compiler and complete robot */
		fclose(f_in);
	} else {
		if(ndebug) {
			fprintf(f_out,"\n** Error ** can't use symbolic debugger with Object file\n");
			r_flag = 1;
			return;
		}
		f_in = fopen(robotname,"rb");

		fread(&myoffset,sizeof(int64_t),1,f_in); /*questo è un valore di offset*/
		fread(&(cur_robot->ext_count),sizeof(int32_t),1,f_in);
		cur_robot->external = (int64_t *) malloc(cur_robot->ext_count * sizeof(int64_t));

		cur_robot->funcs = (char*) malloc(MAXSYM * ILEN);  /* should not be freed, part of robot */
		fread(cur_robot->funcs,ILEN,MAXSYM,f_in);

		cur_robot->code = (struct instr *) malloc(CODESPACE * sizeof(struct instr));
		fread(cur_robot->code, sizeof(struct instr),CODESPACE,f_in);
		myoffset-=(int64_t)cur_robot->code;


		/*rilocazione*/
		contrinstr=cur_robot->code;
		for (zzz=0;zzz<CODESPACE;zzz++) {
			if ( (contrinstr+zzz)->ins_type == BRANCH ) {
				n=(int64_t*)&((contrinstr+zzz)->u.br);
				(*n)-=myoffset; //memory relocation
			}
		}


		nextf=(struct func *)malloc(sizeof(struct func));
		cur_robot->code_list=nextf;
		while (nextf) {
			if(fread(nextf,sizeof(struct func),1,f_in)){
				prevf=nextf;

				n=(int64_t*)&(nextf->first);
				(*n)-=myoffset;	//memory relocation

				nextf=(struct func *)prevf->nextfunc;
				if(nextf) {
					nextf=(struct func *)malloc(sizeof(struct func));
					prevf->nextfunc=(int64_t)nextf;
				}
			}
		}


		fclose(f_in);

		cur_robot->stackbase = (int64_t*) malloc(DATASPACE * sizeof(int64_t));
		cur_robot->stackend = cur_robot->stackbase + DATASPACE;

		cur_robot->status = ACTIVE;


	}
}



/* yyerror - simple error message on parser failure */

void yyerror(char *s)
{
  int i;
  r_flag = 1;
  fprintf(f_out,"\n");
  for (i = 1; i < column; i++)
    fprintf(f_out," ");
  fprintf(f_out,"^\n");
  fprintf(f_out,"** Error ** %s",s);
}



//void *malloc();


/* init_comp - initializes the compiler for one file */
/* assumes robot structure allocated and pointed to by cur->robot */

void init_comp()
{
  long i;

  /* these tables freed after the entire file is compiled */
  ifs = (struct fix_if *) malloc(sizeof (struct fix_if) * NESTLEVEL);
  if_nest = 0;
  whiles = (struct fix_while *) malloc(sizeof (struct fix_while) * NESTLEVEL);
  while_nest = 0;

  /* compiler flags */
  column = 0;
  num_parm = 0;
  num_instr = 0;
  in_func = 0;
  r_flag = 0;  /* global error flag */
  undeclared = 0;
  postfix = 0;

  strncpy(last_ident,"",ILEN);
  strncpy(func_ident,"",ILEN);

  ext_tab = (char *)malloc(MAXSYM * ILEN);   /* freed after file */
  var_tab = (char *)malloc(MAXSYM * ILEN);   /* freed after function */

  func_tab = (char *)malloc(MAXSYM * ILEN);  /* should not be freed, part of robot */

  var_stack = (char *)malloc(MAXSYM * ILEN);  /* freed after file */
  var_off = 0;

  func_stack = (char *)malloc(MAXSYM * ILEN);  /* freed after file */
  func_off = 0;

  op_stack = (int *) malloc(MAXSYM * sizeof (int)); /* freed after file */
  op_off = 0;

  /* allocate code space in robot, code should not be freed */
  cur_robot->code_list = (struct func *) 0;
  cur_robot->code = (struct instr *) malloc(CODESPACE * sizeof(struct instr));
  instruct = (struct instr *) cur_robot->code;

  /* initialize all tables */
  for (i = 0; i < MAXSYM; i++) {
    *(ext_tab + (i * ILEN)) = '\0';
    *(var_tab + (i * ILEN)) = '\0';
    *(func_tab+ (i * ILEN)) = '\0';
    *(var_stack + (i * ILEN)) = '\0';
    *(func_stack + (i * ILEN)) = '\0';
    *(op_stack + i) = 0;
  }

}



/* reset_comp - resets the compiler for another file */
/* completes the robot structure */

int reset_comp()
{
  long i, j;
  int found = 0;
  int mainfunc = 0;
  struct func *chain;
  int good = 1;
  int32_t ext_size;

  /* check for too many intructions */
  if (num_instr == CODESPACE) {
    fprintf(f_out,"\n** Error ** instruction space exceeded\n");
    r_flag = 1;
    if (r_debug)
      fprintf(f_out,"\n\n**reset_comp**\n\n");
    good = 0;
  }

  /* check func_tab to code_list for missing functions (accept intrinsics) */
  /* this ensures no functions are referenced that are not coded or intrinsic */
  for (i = 0; *(func_tab + (i * ILEN)) != '\0'; i++) {
    found = 0;
    for (chain = cur_robot->code_list; chain != (struct func *) 0;
	 chain = (struct func *)chain->nextfunc) {
      if (strcmp((func_tab + (i *ILEN)),chain->func_name) == 0) {
	found = 1;
	break;
      }
    }

    /* if not found as a coded function, check the intrinsic table */
    for (j = 0; *intrinsics[j].n != '\0'; j++) {
      if (strcmp((func_tab + (i * ILEN)),intrinsics[j].n) == 0) {
	found = 1;
	break;
      }
    }

    /* make sure that a main was declared */
    if (strcmp("main",(func_tab + (i * ILEN))) == 0)
      mainfunc = 1;

    if (!found) {
      fprintf(f_out,
   "\n** Error ** '%s (%ld)' function referenced, but not defined or intrinsic\n",
	(func_tab + (i * ILEN)),i);
      good =0;
      r_flag = 1;
      if (r_debug)
	fprintf(f_out,"\n\n**reset_comp**\n\n");
    }
  }

  if (!mainfunc) {
    fprintf(f_out,"\n** Error ** 'main' not defined\n");
    good = 0;
    r_flag = 1;
    if (r_debug)
      fprintf(f_out,"\n\n**reset_comp**\n\n");
  }

  if (undeclared > 0)
    fprintf(f_out,"\n** Warning ** %d undeclared variables\n",undeclared);

  if (postfix > 0)
    fprintf(f_out,"\n** Warning ** %d postfix operators\n",postfix);

  fprintf(f_out,"\nCode utilization: %d%%   (%d / %d) \n",
	  (int) (((long) num_instr) * 100L / CODESPACE) ,num_instr,CODESPACE);
  fflush(f_out);

  /* clean up compiler tables and flags */
  num_parm = 0;
  num_instr = 0;
  in_func = 0;
  undeclared = 0;
  postfix = 0;
  ext_size = poolsize(ext_tab);
  free(ifs);
  free(whiles);
  free(var_tab);
  free(var_stack);
  free(func_stack);
  free(op_stack);

  /* if compile was ok, then allocate external pool, stack, and robot flags */
  if (good) {
    cur_robot->ext_count = ext_size;
    cur_robot->external = (int64_t*) malloc(cur_robot->ext_count * sizeof(int64_t));
    cur_robot->stackbase = (int64_t*) malloc(DATASPACE * sizeof(int64_t));
    cur_robot->stackend = cur_robot->stackbase + DATASPACE;
    cur_robot->vnames = ext_tab;
    cur_robot->funcs = func_tab;
    cur_robot->status = ACTIVE;
    instruct->ins_type = NOP;
  }
/*elimino se uso l'ifdef di sopra*/
  if(!ndebug) free(ext_tab);

  return (good);
}


/* new_func - reset the compiler for a new function within the same file */

int new_func()
{
  long i;


  /* make sure name is not an intrinsic */
  for (i = 0; *(intrinsics[i].n) != '\0'; i++) {
    if (strcmp(intrinsics[i].n,func_ident) == 0) {
     fprintf(f_out,"\n** Error ** '%s' function definition same as intrinsic\n",
	      func_ident);
      r_flag = 1;
      if (r_debug)
	fprintf(f_out,"\n\n**new_func**\n\n");
      return (0);
    }
  }

  /* func name ok, insert a new function header */
  newo = (struct func *) malloc(sizeof (struct func)); /* never freed */
  newo->nextfunc =(int64_t) cur_robot->code_list;		/* link in */
  cur_robot->code_list = newo;			/*  "    " */
  strcpy(newo->func_name,func_ident);		/* copy name */
  newo->first = (int64_t)instruct;			/* current instruct is start */
  newo->var_count = 0; 				/* filled-in later */
  newo->par_count = num_parm;			/* number of parms */
  in_func = 1;
  if (findvar(func_ident,func_tab) == -1)	/* add name to function table */
    allocvar(func_ident,func_tab);
  return (1);

}


/* end_func - cleanup the end of a function */

void end_func()
{
  long i;

  /* fill in the space required by local variables into function header */
  cur_robot->code_list->var_count = poolsize(var_tab);
  newo->vnames=(int64_t)malloc((cur_robot->code_list->var_count+1)* ILEN);
  for (i=0; i<=(cur_robot->code_list->var_count)*ILEN;i++) *(char *)(newo->vnames+i)=*(var_tab+i);
  num_parm = 0;
  in_func = 0;
  func_off = 0;
  op_off = 0;
  var_off = 0;

  if(!ndebug) free((void *)newo->vnames);


  if (r_debug) {
    fprintf(f_out,"\n\nFunction: %s\n\n  Local symbol table:\n",newo->func_name);
    dumpoff(var_tab);
    fprintf(f_out,"\n\n\nExternal symbol table:\n");
    dumpoff(ext_tab);
    fprintf(f_out,"\n\nFunction symbol table:\n");
    dumpoff(func_tab);
    fprintf(f_out,"\n\n Generated code:\n");
    decompile((struct instr*)cur_robot->code_list->first);
  }

  /* initialize local variable table again */
  for (i = 0; i < NESTLEVEL; i++) {
    *(var_tab + (i * ILEN)) = '\0';
  }

}


/* allocvar - allocates a variable in a pool, returns offset */

long allocvar(char s[],char *pool)
{
  long i;

  for (i = 0; i < MAXSYM; i++) {
    if (*(pool + (i * ILEN)) == '\0') {		/* pool is treated as two- */
      strcpy(pool + (i * ILEN),s);		/* dim array, by adding ints */
      return (i);				/* to pointers; see K&R */
    }
  }
  r_flag = 1;
  if (r_debug)
    fprintf(f_out,"\n\n**alloc_var**\n\n");
  fprintf(f_out,"\n\n** Error ** symbol pool exceeded\n");
  return (-1L);
}



/* findvar - returns offset of variable in a pool */

long findvar(char s[], char *pool)
{
  long i;

  for (i = 0; i < MAXSYM; i++) {
    if (strcmp(pool + (i * ILEN),s) == 0)
      return (i);
  }

  return (-1L);
}


/* stackid - stacks an identifier, note pointer to stack offset */

int stackid(char id[], char *stack, int *ptr)
{
  if (*ptr < MAXSYM - 1) {
    (*ptr)++;				/* the ptr itself is incremented */
    strcpy(stack + (*ptr * ILEN),id);
    return (1);
  } else {
    r_flag = 1;
    if (r_debug)
      fprintf(f_out,"\n\n**stackid**\n\n");
    return (-1);
  }
}


/* popid - unstacks an identifier, note pointer to stack offset */

int popid(char id[], char *stack, int *ptr)
{
  if (*ptr > 0) {
    strcpy(id,stack + (*ptr * ILEN));
    (*ptr)--;
    return (1);
  } else {
    r_flag = 1;
    if (r_debug)
      fprintf(f_out,"\n\n**popid**\n\n");
    return (-1);
  }
}




/* poolsize - returns the size of a pool */

int32_t poolsize(char *pool)
{
  int32_t i;

  /* count the number of items */
  for (i = 0; i < MAXSYM; i++) {
    if (*(pool + (i * ILEN)) == '\0')
      return (i);
  }

  r_flag = 1;
  if (r_debug)
    fprintf(f_out,"\n\n**poolsize**\n\n");
  return (-1);
}


/* dumpoff - print a table of names and offsets in a symbol pool */

void dumpoff(char *pool)
{
  long i;
  int count = 0;

  for (i = 0; i < MAXSYM; i++) {
    if (*(pool + (i * ILEN)) == '\0')
      return;
    fprintf(f_out,"%4ld : %-8s  ",i,pool + (i * ILEN));
    if (++count == 4) {
      fprintf(f_out,"\n");
      count = 0;
    }
  }
}
/* all code emit functions check for code space availability, and increments */
/* the current instruction pointer within the code space */

/* efetch - emit a fetch instruction */

int efetch(long offset)
{
  if (++num_instr == CODESPACE) {
    r_flag = 1;
    if (r_debug)
      fprintf(f_out,"\n\n**efetch**\n\n");
    return (0);
  }
  instruct->ins_type = FETCH;
  instruct->u.var1 = offset;
  last_ins = instruct++;
  return (1);
}


/* estore - emit a store instruction */

int estore(long offset, long operatore)
{
  if (++num_instr == CODESPACE) {
    r_flag = 1;
    if (r_debug)
      fprintf(f_out,"\n\n**estore*\n\n");
    return (0);
  }
  instruct->ins_type = STORE;
  instruct->u.a.var2 = offset;
  instruct->u.a.a_op = operatore;
  last_ins = instruct++;
  return (1);
}


/* econst - emit a constant instruction */

int econst(long c)
{
  if (++num_instr == CODESPACE) {
    r_flag = 1;
fprintf(f_out,"\n\n**econst*\n\n");
    return (0);
  }
  instruct->ins_type = CST;
  instruct->u.k = c;
  last_ins = instruct++;
  return (1);
}


/* ebinop - emit a binop instruction */

int ebinop(long c)
{
  if (++num_instr == CODESPACE) {
    r_flag = 1;
    if (r_debug)
      fprintf(f_out,"\n\n**ebinop**\n\n");
    return (0);
  }
  instruct->ins_type = BINOP;
  instruct->u.var1 = c;
  last_ins = instruct++;
  return (1);
}


/* efcall - emit a fcall instruction */

int efcall (long c)
{
  if (++num_instr == CODESPACE) {
    r_flag = 1;
    if (r_debug)
      fprintf(f_out,"\n\n**efcall**\n\n");
    return (0);
  }
  instruct->ins_type = FCALL;
  instruct->u.var1 = c;
  last_ins = instruct++;
  return (1);
}


/* eretsub - emit a retsub instruction */

int eretsub()
{
  if (++num_instr == CODESPACE) {
    r_flag = 1;
    if (r_debug)
      fprintf(f_out,"\n\n**eretsub**\n\n");
    return (0);
  }
  instruct->ins_type = RETSUB;
  last_ins = instruct++;
  return (1);
}


/* ebranch - emit a  branch instruction */

int ebranch()
{
  if (++num_instr == CODESPACE) {
    r_flag = 1;
    if (r_debug)
      fprintf(f_out,"\n\n**ebranch**\n\n");
    return (0);
  }
  instruct->ins_type = BRANCH;
  instruct->u.br = 0;	/* must be fixed later */
  last_ins = instruct++;
  return (1);
}


/* echop - emit a chop instruction */

int echop()
{
  if (++num_instr == CODESPACE) {
    r_flag = 1;
    if (r_debug)
      fprintf(f_out,"\n\n**echop**\n\n");
    return (0);
  }
  instruct->ins_type = CHOP;
  last_ins = instruct++;
  return (1);
}


/* eframe - emit a stack frame instruction */

int eframe()
{
  if (++num_instr == CODESPACE) {
    r_flag = 1;
    if (r_debug)
      fprintf(f_out,"\n\n**eframe**\n\n");
    return (0);
  }
  instruct->ins_type = FRAME;
  last_ins = instruct++;
  return (1);
}


/* new_if - start a nest for an if statement */

int new_if()
{
  if (if_nest == NESTLEVEL) {
    fprintf(f_out,"\n** Error ** 'if' nest level exceeded\n");
    r_flag = 1;
    if (r_debug)
      fprintf(f_out,"\n\n**new_if**\n\n");
    return (0);
  }

  if_nest++;
  if (!ebranch())
    return (0);

  /* save the not-true branch instruction address to be fixed later */
  /* this branch jumps to the else part, if any */
  (ifs + if_nest)->fix_false = last_ins;

  return (1);
}


/* else_part - the else part of an if-then-else */

int else_part()
{
  /* setup a unconditional branch around the else part */
  if (!econst(0L))
    return(0);
  if (!ebranch())
    return (0);

  /* save the else branch instruction address */
  /* this branch jumps around the else part, if any */
  (ifs + if_nest)->fix_true = last_ins;

  /* fix the not-true branch */
  /* the branch instrunction address was saved in new_if() */
  (ifs + if_nest)->fix_false->u.br = (int64_t)instruct;

  return (1);
}


/* close_if - close out an if nest */

void close_if()
{
  /* fix the not-else branch saved in else_part() */
  (ifs + if_nest)->fix_true->u.br = (int64_t)instruct;

  if_nest--;
}


/* new_while - start a nest for a new while statement */

int new_while()
{
  if (while_nest == NESTLEVEL) {
    fprintf(f_out,"\n** Error ** 'while' nest level exceeded\n");
    r_flag = 1;
    if (r_debug)
      fprintf(f_out,"\n\n**new_while**\n\n");
    return (0);
  }
  while_nest++;

  /* save the target intruction for while-loop expression evaluation */
  (whiles + while_nest)->loop = instruct;

  return (1);
}


/* while_expr - while expression loop fix */

int while_expr()
{
  if (!ebranch())
    return (0);

  /* save the branch out of while-loop address to fix later */
  /* this branch jumps around the while-body */
  (whiles + while_nest)->fix_br = last_ins;

  return (1);
}


/* close_while - close out the while nest */

int close_while()
{
  /* emit an unconditional branch */
  if (!econst(0L))
    return (0);
  if (!ebranch())
    return (0);

  /* fix the jump back to expression evaluation */
  /* this was saved in new_while() */
  last_ins->u.br = (int64_t)(whiles + while_nest)->loop;

  /* fix the not while branch */
  /* this was saved in while_expr() */
  (whiles + while_nest)->fix_br->u.br =(int64_t) instruct;

  while_nest--;
  return (1);
}


/* decompile - print machine code */

void decompile(struct instr *code)
{

  while (code->ins_type != NOP) {
    decinstr(code);
    code++;
  }
}



/* decinstr - print one instruct; watch out for pointer to long conversion! */

void decinstr(struct instr *code)
{

  fprintf(f_out,"%8ld : ",(long) code);	/* this could be flakey */
  switch (code->ins_type) {
    case FETCH:
      if (code->u.var1 & EXTERNAL)
	fprintf(f_out,"fetch   %I64d external\n",code->u.var1 & ~EXTERNAL);
      else
	fprintf(f_out,"fetch   %I64d local\n",code->u.var1);
      break;
    case STORE:
      if (code->u.a.var2 & EXTERNAL)
	fprintf(f_out,"store   %I64d external, ",
		code->u.a.var2 & ~EXTERNAL);
      else
	fprintf(f_out,"store   %I64d local, ",code->u.a.var2);
      printop(code->u.a.a_op);
      fprintf(f_out,"\n");
      break;
    case CST:
      fprintf(f_out,"const   %I64d\n",code->u.k);
      break;
    case BINOP:
      fprintf(f_out,"binop   ");
      printop(code->u.var1);
      fprintf(f_out,"\n");
      break;
    case FCALL:
      fprintf(f_out,"fcall   %I64d\n",code->u.var1);
      break;
    case RETSUB:
      fprintf(f_out,"retsub\n");

      break;
    case BRANCH:
      fprintf(f_out,"branch  %ld\n",(long) code->u.br); /* more flakiness */
      break;
    case CHOP:
      fprintf(f_out,"chop\n");
      break;
    case FRAME:
      fprintf(f_out,"frame\n");
      break;
    default:
      fprintf(f_out,"ILLEGAL %d\n",code->ins_type);
      return;
  }
}


/* printop - print a binary operation code */

void printop(int64_t op)
{

  switch (op) {

    case  '=':
      fprintf(f_out,"=");
      break;

    case  '|':
      fprintf(f_out,"|");
      break;

    case  '^':
      fprintf(f_out,"^");
      break;

    case  '&':
      fprintf(f_out,"&");
      break;

    case  '<':
      fprintf(f_out,"<");
      break;

    case  '>':
      fprintf(f_out,">");
      break;

    case  '+':
      fprintf(f_out,"+");
      break;

    case  '-':
      fprintf(f_out,"-");
      break;

    case  '*':
      fprintf(f_out,"*");
      break;

    case  '/':
      fprintf(f_out,"/");
      break;

    case  '%':
      fprintf(f_out,"%%");
      break;

    case  LEFT_OP:
      fprintf(f_out,"<<");
      break;

    case  RIGHT_OP:
      fprintf(f_out,">>");
      break;

    case  LE_OP:
      fprintf(f_out,"<=");
      break;

    case  GE_OP:
      fprintf(f_out,">=");
      break;

    case  EQ_OP:
      fprintf(f_out,"==");
      break;

    case  NE_OP:
      fprintf(f_out,"!=");
      break;

    case  AND_OP:
      fprintf(f_out,"&&");
      break;

    case  OR_OP:
      fprintf(f_out,"||");
      break;

    case  MUL_ASSIGN:
      fprintf(f_out,"*=");
      break;

    case  DIV_ASSIGN:
      fprintf(f_out,"/=");
      break;

    case  MOD_ASSIGN:
      fprintf(f_out,"%%=");
      break;

    case  ADD_ASSIGN:
      fprintf(f_out,"+=");
      break;

    case  SUB_ASSIGN:
      fprintf(f_out,"-=");
      break;

    case  LEFT_ASSIGN:
      fprintf(f_out,"<<=");
      break;

    case  RIGHT_ASSIGN:
      fprintf(f_out,">>=");
      break;

    case  AND_ASSIGN:
      fprintf(f_out,"&=");
      break;

    case  XOR_ASSIGN:
      fprintf(f_out,"^=");
      break;

    case  OR_ASSIGN:
      fprintf(f_out,"|=");
      break;

    case  U_NEGATIVE:
      fprintf(f_out,"(-)");
      break;

    case  U_NOT:
      fprintf(f_out,"(!)");
      break;

    case  U_ONES:
      fprintf(f_out,"(~)");
      break;

    default:
      fprintf(f_out,"ILLEGAL %I64d",op);
      break;

  }
}
