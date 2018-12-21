#ifndef lint
static char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif
#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define yyclearin (yychar=(-1))
#define yyerrok (yyerrflag=0)
#define YYRECOVERING (yyerrflag!=0)
#define YYPREFIX "yy"
#line 1 "grammar.y"



/*****************************************************************************/
/*                                                                           */
/*  CROBOTS                                                                  */
/*                                                                           */
/*  (C) Copyright Tom Poindexter, 1985, all rights reserved.                 */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include <stdio.h>
#include <string.h>
#include "crobots.h"
#include "compiler.h"

#line 29 "y.tab.c"
#define IDENTIFIER 257
#define CONSTANT 258
#define INC_OP 259
#define DEC_OP 260
#define LEFT_OP 261
#define RIGHT_OP 262
#define LE_OP 263
#define GE_OP 264
#define EQ_OP 265
#define NE_OP 266
#define AND_OP 267
#define OR_OP 268
#define MUL_ASSIGN 269
#define DIV_ASSIGN 270
#define MOD_ASSIGN 271
#define ADD_ASSIGN 272
#define SUB_ASSIGN 273
#define LEFT_ASSIGN 274
#define RIGHT_ASSIGN 275
#define AND_ASSIGN 276
#define XOR_ASSIGN 277
#define OR_ASSIGN 278
#define EXTERN 279
#define AUTO 280
#define REGISTER 281
#define INT 282
#define LONG 283
#define IF 284
#define ELSE 285
#define WHILE 286
#define FOR 287
#define RETURN 288
#define BREAK 289
#define U_NEGATIVE 290
#define U_NOT 291
#define U_ONES 292
#define YYERRCODE 256
short yylhs[] = {                                        -1,
    1,    1,    1,    4,    4,    4,    4,    4,    5,    6,
    6,    8,    8,    8,    8,    9,    9,    9,   10,   10,
   12,   12,   12,   12,   13,   13,   13,   14,   14,   14,
   15,   15,   15,   15,   15,   16,   16,   16,   17,   17,
   18,   18,   19,   19,   20,   20,   21,   21,   22,    7,
    7,   23,   24,   24,   24,   24,   24,   24,   24,   24,
   24,   24,   24,    3,   25,   25,   26,   26,   26,   26,
   27,   27,   30,   30,   28,   28,   28,   29,   29,   31,
   33,   33,   33,   34,   36,   36,   37,   35,   35,   38,
   39,   39,   40,   40,   11,   11,   41,   42,   42,   42,
   42,   42,   32,   32,   32,   43,   43,   44,   44,   44,
   44,   44,   45,   45,   45,   45,   51,   51,   50,   50,
   46,   46,   47,   47,   52,   53,   54,   55,   48,   57,
   56,   49,   49,   49,    0,    0,   58,   58,   59,   59,
   60,   60,    2,
};
short yylen[] = {                                         2,
    1,    1,    3,    1,    3,    2,    2,    2,    2,    1,
    3,    1,    2,    2,    2,    1,    1,    1,    1,    4,
    1,    3,    3,    3,    1,    3,    3,    1,    3,    3,
    1,    3,    3,    3,    3,    1,    3,    3,    1,    3,
    1,    3,    1,    3,    1,    3,    1,    3,    1,    1,
    2,    2,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    2,    3,    1,    2,    1,    2,
    1,    3,    1,    3,    1,    1,    1,    1,    1,    1,
    1,    2,    3,    2,    1,    2,    1,    1,    3,    1,
    1,    3,    2,    1,    1,    2,    1,    3,    2,    3,
    3,    4,    1,    3,    4,    1,    3,    1,    1,    1,
    1,    1,    2,    3,    3,    4,    1,    2,    1,    2,
    1,    2,    1,    1,    2,    4,    4,    1,    2,    1,
    4,    2,    2,    3,    1,    2,    1,    1,    2,    3,
    1,    2,    1,
};
short yydefred[] = {                                      0,
  143,   75,   76,   77,   78,   79,    0,   81,  138,    0,
    0,    0,    0,    0,    0,  135,  137,  136,   65,    0,
   71,    0,   68,   70,    0,  117,    0,  141,    0,  139,
   84,   82,   87,    0,   88,    0,   66,    0,  140,    2,
    0,    0,    0,  130,    0,    0,   16,   17,   18,    0,
  121,  113,    4,    1,    0,    0,    0,   64,    0,    0,
   21,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   50,    0,  119,  108,  109,  110,  111,  112,    0,
    0,  123,  124,    0,    0,    0,    0,  118,  142,   83,
    0,   72,    0,  103,   74,    0,   13,   14,    0,  133,
    0,  132,    0,    0,   85,    0,  122,    7,    8,    9,
    6,    0,   10,   54,   55,   56,   57,   58,   59,   60,
   61,   62,   63,   53,   52,   19,   15,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   51,  114,  120,  115,    0,
    0,  129,    0,   89,  106,    0,    0,  134,    3,    0,
    0,   86,   96,    0,    5,    0,   22,   23,   24,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  116,  128,    0,    0,    0,  104,
  127,   20,   99,   94,    0,    0,    0,   91,    0,    0,
   11,  126,  131,  105,  107,   93,  100,    0,   98,  101,
    0,   92,  102,
};
short yydgoto[] = {                                       7,
   53,   54,   55,   56,   57,  112,   58,  126,   60,   61,
  194,   62,   63,   64,   65,   66,   67,   68,   69,   70,
   71,   72,   73,  125,   26,   27,   20,   11,   12,   21,
   13,   95,   14,   15,   34,  195,   35,  196,  197,  198,
  163,  164,  156,   74,   75,   76,   77,   78,   79,   80,
   29,   82,   83,   84,  187,   85,   86,   16,   17,   30,
};
short yysindex[] = {                                    182,
    0,    0,    0,    0,    0,    0,  182,    0,    0,  -57,
  -87,  -87, -119,  -31,  -40,    0,    0,    0,    0,   16,
    0,  508,    0,    0,  -33,    0,  -57,    0, -119,    0,
    0,    0,    0,   14,    0, -244,    0,  522,    0,    0,
  535,  535,  -13,    0,  725,   -6,    0,    0,    0,   40,
    0,    0,    0,    0,    8,   71,  188,    0,  528,  648,
    0,   79,    6, -222,  -32,  -98,   21,   25,  -36, -183,
 -168,    0,  648,    0,    0,    0,    0,    0,    0,  -16,
  -22,    0,    0,   32,   32,   68,   70,    0,    0,    0,
 -244,    0,  522,    0,    0,  648,    0,    0,  648,    0,
   58,    0,   96,   98,    0,   -4,    0,    0,    0,    0,
    0,   37,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  648,  648,  648,
  648,  648,  648,  648,  648,  648,  648,  648,  648,  648,
  648,  648,  648,  648,  648,    0,    0,    0,    0,   17,
 -144,    0,  648,    0,    0,  -10,  113,    0,    0,  648,
    4,    0,    0,  117,    0,  648,    0,    0,    0,   79,
   79,    6,    6, -222, -222, -222, -222,  -32,  -32,  -98,
   21,   25,  -36, -183,    0,    0,   32,  124,   85,    0,
    0,    0,    0,    0,   12,  128,  129,    0,  134,   42,
    0,    0,    0,    0,    0,    0,    0, -111,    0,    0,
  136,    0,    0,
};
short yyrindex[] = {                                      0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  -51,  -45,    0,   53,    0,    0,    0,    0,    0,    0,
    0,   27,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   91,    0,    0,  160,    0,
    0,  335,  372,  432,  489,  626,  115,  700,   61,  -38,
   54,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   27,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  139,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   23,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   55,    0,    0,    0,    0,    0,  343,
  355,  392,  412,  440,  449,  460,  469,  501,  624,  628,
  702,  719,  140,   20,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   83,    0,  141,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,
};
short yygindex[] = {                                      0,
    0,  813,  -30,    0,    0,    0,  -19,  878,    0,  211,
  168,   56,   80,  212,  187,   48,   81,  102,   90,  107,
    0,    0,    0,    0,   41,   35,    0,    0,  -17,  227,
   -5,  -83,    0,    0,    0,  243,  205,  104,    0,   94,
  147,    0,    0,  290,    3,    0,    0,    0,    0,  229,
  288,    0,    0,    0,    0,    0,    0,  308,    0,  295,
};
#define YYTABLESIZE 1067
short yytable[] = {                                      48,
   32,   19,   47,   25,   22,   47,   50,   67,   31,  155,
   48,   47,    1,   69,  101,   28,   48,   50,   94,  103,
   47,   87,   47,   50,   28,   51,   99,  137,   47,  138,
   87,   89,  105,  189,   10,  161,   51,  113,  133,  134,
    9,   10,   51,  161,  193,   23,   24,    9,  131,   48,
  132,  161,  102,  146,   90,  125,   50,   91,  141,   36,
   48,   47,  125,   48,   48,  103,  107,  125,  157,   88,
   73,   50,   48,   94,   37,   51,   47,  165,   48,   50,
  166,  125,  210,  144,   47,   73,   47,  143,  162,   25,
   51,   52,   49,   80,   49,   97,   80,   49,   97,  145,
   25,   45,  149,   49,   45,  205,   25,  153,  147,   49,
  110,   80,   49,   80,  190,  130,  158,   48,  142,   45,
  128,   88,  188,   95,   50,  129,   95,   12,   12,   47,
   38,   12,   12,   12,   12,   12,  159,   12,  160,   25,
  186,  185,   49,  105,   48,  125,  201,  125,  125,   12,
   12,   12,   12,  191,   25,   41,  200,   49,   41,    2,
    3,    4,    5,    6,  203,   49,  139,  140,  207,   94,
    5,    6,  208,   41,  209,   80,  213,  162,   49,   95,
   46,   90,  105,   46,   12,   45,  170,  171,  180,  206,
  105,    2,    3,    4,    5,    6,   19,   19,   46,    1,
   19,   19,   19,   19,   19,   67,   19,   93,   41,  204,
   49,   69,  172,  173,   12,   12,    1,  104,   19,   19,
   48,   19,  181,    1,   40,   41,   42,   50,  111,   47,
  135,  136,   47,  183,    1,   40,   41,   42,   41,   41,
    1,   40,   41,   42,  182,    2,    3,    4,    5,    6,
   43,  184,   44,   19,   45,   46,    2,    3,    4,    5,
    6,   43,   92,   44,   46,   45,   46,   43,    1,   44,
  127,   45,   46,    1,   40,   41,   42,    5,    6,  125,
  125,  125,  125,   19,   19,    5,    6,   48,    1,   40,
   41,   42,  106,    5,    6,  154,    1,   40,   41,   42,
   43,  212,   44,  211,   45,   46,  125,  199,  125,  150,
  125,  125,   81,   49,   18,   43,   39,   44,    0,   45,
   46,    5,    6,    5,    6,  178,  179,   45,   45,  108,
  109,   80,   80,   80,   80,   80,    0,    0,  167,  168,
  169,    1,   40,   41,   42,    0,  174,  175,  176,  177,
    0,   12,   12,   12,   12,   12,   12,   12,   12,   12,
   12,   12,   12,   12,   12,   12,   12,   12,   12,  148,
  192,    0,   25,  151,  152,   25,    0,   25,   25,   25,
   26,   41,   41,   26,    0,   26,   26,   26,    0,    0,
    0,    0,   27,   25,   25,   27,   25,   27,   27,   27,
    0,   26,   26,    0,   26,    0,   46,   46,    0,   28,
    0,    0,   28,   27,   27,   28,   27,    0,    0,    0,
   19,   19,   19,   19,   19,   19,   19,   19,   25,   29,
   28,   28,   29,   28,    0,   29,   26,    0,    1,  148,
    0,    0,    0,    0,    1,   40,   41,   42,   27,   30,
   29,   29,   30,   29,    0,   30,    0,    0,   25,   25,
    2,    3,    4,    5,    6,   28,   26,   26,    0,   31,
   30,   30,   31,   30,    0,   31,  202,   34,   27,   27,
   34,    0,    0,   34,    0,   29,   35,    0,    0,   35,
   31,   31,   35,   31,    0,   28,   28,   32,   34,   34,
   32,   34,    0,   32,    0,   30,   33,   35,   35,   33,
   35,    0,   33,    0,    0,   29,   29,    0,   32,   32,
    0,   32,    0,    0,    0,   31,   36,   33,   33,   36,
   33,    0,   36,   34,    0,   30,   30,    0,   37,    0,
    0,   37,   35,    0,   37,    0,    0,   36,    0,    0,
    0,    0,    0,   32,   48,   31,   31,    0,    0,   37,
    0,   50,   33,   34,   34,    0,   47,   48,   38,    0,
    0,    0,   35,   35,   96,    0,    0,    0,    0,   47,
    0,    0,   36,   32,   32,    0,    0,    0,  124,    0,
    0,    0,   33,   33,   37,   25,   25,   25,   25,   25,
   25,   25,   25,   26,   26,   26,   26,   26,   26,   26,
   26,    0,   36,   36,    0,   27,   27,   27,   27,   27,
   27,   27,   27,    0,   37,   37,    0,    0,    0,    0,
   25,    0,   28,   28,   28,   28,   28,   28,   28,   28,
    0,    0,    0,    0,   93,    0,    0,   49,    0,    0,
    0,    0,   29,   29,   29,   29,   29,   29,   29,   29,
   49,   38,    0,   39,   38,   40,   39,   38,   40,   39,
    0,   40,   30,   30,   30,   30,   30,   30,   30,   30,
   48,    0,   38,    0,   39,    0,   40,   50,    0,    0,
    0,    0,   47,    0,   31,   31,   31,   31,   31,   31,
    0,    0,   34,   34,   34,   34,   34,   34,    0,    0,
    0,   35,   35,   35,   35,   35,   35,   38,    0,   39,
    0,   40,   32,   32,   32,   32,   32,   32,    0,    0,
    0,   33,   33,   33,   33,   33,   33,    0,    0,    0,
   43,    0,   42,   43,    0,   42,    0,   38,   38,   39,
   39,   40,   40,   36,   36,   36,   36,   48,   43,   44,
   42,    0,   44,    0,   50,   37,   37,   37,   37,   47,
    0,    0,    0,   49,    0,    0,    0,   44,    1,   40,
   41,   42,    0,  100,    0,    0,    2,    3,    4,    5,
    6,    1,   40,   41,   42,   42,  114,  115,  116,  117,
  118,  119,  120,  121,  122,  123,    0,    0,    0,    0,
    0,    0,    8,    0,    0,    0,    0,    0,    0,    8,
    0,    0,    8,   43,   43,   42,   42,   33,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    8,
    0,    0,   44,   44,    0,    0,    0,    0,    8,    0,
   49,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   38,   38,
   38,   38,   39,   39,   40,   40,    0,    0,    0,    0,
    0,    0,   59,   33,    1,   40,   41,   42,    0,    0,
    0,    0,    0,    0,    0,   59,    0,    0,   97,   98,
    0,    0,   59,    0,    0,    0,    0,   59,    0,    0,
    0,    0,    0,    0,   59,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   59,    0,    0,    0,    0,    0,    0,   59,   59,    0,
    0,   59,   59,    0,    0,    0,   43,   43,   42,   42,
   59,    0,    0,   59,    0,    0,   59,    0,    0,    0,
    0,    1,   40,   41,   42,   44,   44,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    8,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   59,    0,    0,
   59,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   59,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   59,    0,   59,
};
short yycheck[] = {                                      33,
   41,   59,   41,  123,   10,   44,   40,   59,   40,   93,
   33,   45,  257,   59,   45,   13,   33,   40,   38,   50,
   59,   27,   45,   40,   22,   59,   40,   60,   45,   62,
   36,   29,   50,   44,    0,   40,   59,   57,  261,  262,
    0,    7,   59,   40,   41,   11,   12,    7,   43,   33,
   45,   40,   59,   73,   41,   33,   40,   44,   38,   44,
   41,   45,   40,   44,   33,   96,   59,   45,   99,   29,
   44,   40,   33,   93,   59,   59,   45,   41,   59,   40,
   44,   59,   41,  267,   45,   59,  125,  124,  106,  123,
   59,  125,  126,   41,   41,   41,   44,   44,   44,  268,
  123,   41,  125,  126,   44,  189,  123,   40,  125,  126,
   40,   59,   59,   61,  125,   37,   59,   33,   94,   59,
   42,   81,  153,   41,   40,   47,   44,   37,   38,   45,
   61,   41,   42,   43,   44,   45,   41,   47,   41,  123,
  285,  125,  126,  161,  125,  123,  166,  125,  126,   59,
   60,   61,   62,   41,  123,   41,   40,  126,   44,  279,
  280,  281,  282,  283,   41,  126,  265,  266,   41,  189,
  282,  283,   44,   59,   41,  123,   41,  195,  125,   41,
   41,   41,  200,   44,   94,  125,  131,  132,  141,  195,
  208,  279,  280,  281,  282,  283,   37,   38,   59,  257,
   41,   42,   43,   44,   45,  257,   47,  123,   94,  125,
  126,  257,  133,  134,  124,  125,  257,   50,   59,   60,
   33,   62,  142,  257,  258,  259,  260,   40,   41,  268,
  263,  264,   45,  144,  257,  258,  259,  260,  124,  125,
  257,  258,  259,  260,  143,  279,  280,  281,  282,  283,
  284,  145,  286,   94,  288,  289,  279,  280,  281,  282,
  283,  284,   36,  286,  125,  288,  289,  284,  257,  286,
   60,  288,  289,  257,  258,  259,  260,  282,  283,  257,
  258,  259,  260,  124,  125,  282,  283,  268,  257,  258,
  259,  260,   50,  282,  283,   91,  257,  258,  259,  260,
  284,  208,  286,  200,  288,  289,  284,  161,  286,   81,
  288,  289,   25,  126,    7,  284,   22,  286,   -1,  288,
  289,  282,  283,  282,  283,  139,  140,  267,  268,  259,
  260,  279,  280,  281,  282,  283,   -1,   -1,  128,  129,
  130,  257,  258,  259,  260,   -1,  135,  136,  137,  138,
   -1,  261,  262,  263,  264,  265,  266,  267,  268,  269,
  270,  271,  272,  273,  274,  275,  276,  277,  278,   80,
  160,   -1,   38,   84,   85,   41,   -1,   43,   44,   45,
   38,  267,  268,   41,   -1,   43,   44,   45,   -1,   -1,
   -1,   -1,   38,   59,   60,   41,   62,   43,   44,   45,
   -1,   59,   60,   -1,   62,   -1,  267,  268,   -1,   38,
   -1,   -1,   41,   59,   60,   44,   62,   -1,   -1,   -1,
  261,  262,  263,  264,  265,  266,  267,  268,   94,   38,
   59,   60,   41,   62,   -1,   44,   94,   -1,  257,  150,
   -1,   -1,   -1,   -1,  257,  258,  259,  260,   94,   38,
   59,   60,   41,   62,   -1,   44,   -1,   -1,  124,  125,
  279,  280,  281,  282,  283,   94,  124,  125,   -1,   38,
   59,   60,   41,   62,   -1,   44,  187,   38,  124,  125,
   41,   -1,   -1,   44,   -1,   94,   38,   -1,   -1,   41,
   59,   60,   44,   62,   -1,  124,  125,   38,   59,   60,
   41,   62,   -1,   44,   -1,   94,   38,   59,   60,   41,
   62,   -1,   44,   -1,   -1,  124,  125,   -1,   59,   60,
   -1,   62,   -1,   -1,   -1,   94,   38,   59,   60,   41,
   62,   -1,   44,   94,   -1,  124,  125,   -1,   38,   -1,
   -1,   41,   94,   -1,   44,   -1,   -1,   59,   -1,   -1,
   -1,   -1,   -1,   94,   33,  124,  125,   -1,   -1,   59,
   -1,   40,   94,  124,  125,   -1,   45,   33,   61,   -1,
   -1,   -1,  124,  125,   40,   -1,   -1,   -1,   -1,   45,
   -1,   -1,   94,  124,  125,   -1,   -1,   -1,   61,   -1,
   -1,   -1,  124,  125,   94,  261,  262,  263,  264,  265,
  266,  267,  268,  261,  262,  263,  264,  265,  266,  267,
  268,   -1,  124,  125,   -1,  261,  262,  263,  264,  265,
  266,  267,  268,   -1,  124,  125,   -1,   -1,   -1,   -1,
  123,   -1,  261,  262,  263,  264,  265,  266,  267,  268,
   -1,   -1,   -1,   -1,  123,   -1,   -1,  126,   -1,   -1,
   -1,   -1,  261,  262,  263,  264,  265,  266,  267,  268,
  126,   38,   -1,   38,   41,   38,   41,   44,   41,   44,
   -1,   44,  261,  262,  263,  264,  265,  266,  267,  268,
   33,   -1,   59,   -1,   59,   -1,   59,   40,   -1,   -1,
   -1,   -1,   45,   -1,  263,  264,  265,  266,  267,  268,
   -1,   -1,  263,  264,  265,  266,  267,  268,   -1,   -1,
   -1,  263,  264,  265,  266,  267,  268,   94,   -1,   94,
   -1,   94,  263,  264,  265,  266,  267,  268,   -1,   -1,
   -1,  263,  264,  265,  266,  267,  268,   -1,   -1,   -1,
   41,   -1,   41,   44,   -1,   44,   -1,  124,  125,  124,
  125,  124,  125,  265,  266,  267,  268,   33,   59,   41,
   59,   -1,   44,   -1,   40,  265,  266,  267,  268,   45,
   -1,   -1,   -1,  126,   -1,   -1,   -1,   59,  257,  258,
  259,  260,   -1,   59,   -1,   -1,  279,  280,  281,  282,
  283,  257,  258,  259,  260,   94,  269,  270,  271,  272,
  273,  274,  275,  276,  277,  278,   -1,   -1,   -1,   -1,
   -1,   -1,    0,   -1,   -1,   -1,   -1,   -1,   -1,    7,
   -1,   -1,   10,  124,  125,  124,  125,   15,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   27,
   -1,   -1,  124,  125,   -1,   -1,   -1,   -1,   36,   -1,
  126,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  265,  266,
  267,  268,  267,  268,  267,  268,   -1,   -1,   -1,   -1,
   -1,   -1,   25,   91,  257,  258,  259,  260,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   38,   -1,   -1,   41,   42,
   -1,   -1,   45,   -1,   -1,   -1,   -1,   50,   -1,   -1,
   -1,   -1,   -1,   -1,   57,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   73,   -1,   -1,   -1,   -1,   -1,   -1,   80,   81,   -1,
   -1,   84,   85,   -1,   -1,   -1,  267,  268,  267,  268,
   93,   -1,   -1,   96,   -1,   -1,   99,   -1,   -1,   -1,
   -1,  257,  258,  259,  260,  267,  268,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  195,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  150,   -1,   -1,
  153,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  166,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  187,   -1,  189,
};
#define YYFINAL 7
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 292
#if YYDEBUG
char *yyname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"'!'",0,0,0,"'%'","'&'",0,"'('","')'","'*'","'+'","','","'-'",0,"'/'",0,0,0,0,0,
0,0,0,0,0,0,"';'","'<'","'='","'>'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,"'^'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"'{'","'|'","'}'","'~'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"IDENTIFIER","CONSTANT","INC_OP",
"DEC_OP","LEFT_OP","RIGHT_OP","LE_OP","GE_OP","EQ_OP","NE_OP","AND_OP","OR_OP",
"MUL_ASSIGN","DIV_ASSIGN","MOD_ASSIGN","ADD_ASSIGN","SUB_ASSIGN","LEFT_ASSIGN",
"RIGHT_ASSIGN","AND_ASSIGN","XOR_ASSIGN","OR_ASSIGN","EXTERN","AUTO","REGISTER",
"INT","LONG","IF","ELSE","WHILE","FOR","RETURN","BREAK","U_NEGATIVE","U_NOT",
"U_ONES",
};
char *yyrule[] = {
"$accept : file",
"primary_expr : identifier",
"primary_expr : CONSTANT",
"primary_expr : '(' expr ')'",
"postfix_expr : primary_expr",
"postfix_expr : fcall_start argument_expr_list ')'",
"postfix_expr : fcall_start ')'",
"postfix_expr : postfix_expr INC_OP",
"postfix_expr : postfix_expr DEC_OP",
"fcall_start : postfix_expr '('",
"argument_expr_list : assignment_expr",
"argument_expr_list : argument_expr_list ',' assignment_expr",
"unary_expr : postfix_expr",
"unary_expr : INC_OP unary_expr",
"unary_expr : DEC_OP unary_expr",
"unary_expr : unary_operator cast_expr",
"unary_operator : '-'",
"unary_operator : '!'",
"unary_operator : '~'",
"cast_expr : unary_expr",
"cast_expr : '(' type_name ')' cast_expr",
"multiplicative_expr : cast_expr",
"multiplicative_expr : multiplicative_expr '*' cast_expr",
"multiplicative_expr : multiplicative_expr '/' cast_expr",
"multiplicative_expr : multiplicative_expr '%' cast_expr",
"additive_expr : multiplicative_expr",
"additive_expr : additive_expr '+' multiplicative_expr",
"additive_expr : additive_expr '-' multiplicative_expr",
"shift_expr : additive_expr",
"shift_expr : shift_expr LEFT_OP additive_expr",
"shift_expr : shift_expr RIGHT_OP additive_expr",
"relational_expr : shift_expr",
"relational_expr : relational_expr '<' shift_expr",
"relational_expr : relational_expr '>' shift_expr",
"relational_expr : relational_expr LE_OP shift_expr",
"relational_expr : relational_expr GE_OP shift_expr",
"equality_expr : relational_expr",
"equality_expr : equality_expr EQ_OP relational_expr",
"equality_expr : equality_expr NE_OP relational_expr",
"and_expr : equality_expr",
"and_expr : and_expr '&' equality_expr",
"exclusive_or_expr : and_expr",
"exclusive_or_expr : exclusive_or_expr '^' and_expr",
"inclusive_or_expr : exclusive_or_expr",
"inclusive_or_expr : inclusive_or_expr '|' exclusive_or_expr",
"logical_and_expr : inclusive_or_expr",
"logical_and_expr : logical_and_expr AND_OP inclusive_or_expr",
"logical_or_expr : logical_and_expr",
"logical_or_expr : logical_or_expr OR_OP logical_and_expr",
"conditional_expr : logical_or_expr",
"assignment_expr : conditional_expr",
"assignment_expr : assignment_lval assignment_expr",
"assignment_lval : unary_expr assignment_operator",
"assignment_operator : '='",
"assignment_operator : MUL_ASSIGN",
"assignment_operator : DIV_ASSIGN",
"assignment_operator : MOD_ASSIGN",
"assignment_operator : ADD_ASSIGN",
"assignment_operator : SUB_ASSIGN",
"assignment_operator : LEFT_ASSIGN",
"assignment_operator : RIGHT_ASSIGN",
"assignment_operator : AND_ASSIGN",
"assignment_operator : XOR_ASSIGN",
"assignment_operator : OR_ASSIGN",
"expr : assignment_expr",
"declaration : declaration_specifiers ';'",
"declaration : declaration_specifiers init_declarator_list ';'",
"declaration_specifiers : storage_class_specifier",
"declaration_specifiers : storage_class_specifier declaration_specifiers",
"declaration_specifiers : type_specifier",
"declaration_specifiers : type_specifier declaration_specifiers",
"init_declarator_list : init_declarator",
"init_declarator_list : init_declarator_list ',' init_declarator",
"init_declarator : declarator",
"init_declarator : declarator '=' initializer",
"storage_class_specifier : EXTERN",
"storage_class_specifier : AUTO",
"storage_class_specifier : REGISTER",
"type_specifier : INT",
"type_specifier : LONG",
"declarator : declarator2",
"declarator2 : identifier",
"declarator2 : func_start ')'",
"declarator2 : func_start parameter_declaration_list ')'",
"func_start : declarator2 '('",
"type_specifier_list : type_specifier",
"type_specifier_list : type_specifier_list type_specifier",
"parameter_identifier : identifier",
"parameter_declaration_list : parameter_identifier",
"parameter_declaration_list : parameter_declaration_list ',' parameter_identifier",
"parameter_type_list : parameter_list",
"parameter_list : parameter_declaration",
"parameter_list : parameter_list ',' parameter_declaration",
"parameter_declaration : type_specifier_list declarator",
"parameter_declaration : type_name",
"type_name : type_specifier_list",
"type_name : type_specifier_list abstract_declarator",
"abstract_declarator : abstract_declarator2",
"abstract_declarator2 : '(' abstract_declarator ')'",
"abstract_declarator2 : '(' ')'",
"abstract_declarator2 : '(' parameter_type_list ')'",
"abstract_declarator2 : abstract_declarator2 '(' ')'",
"abstract_declarator2 : abstract_declarator2 '(' parameter_type_list ')'",
"initializer : assignment_expr",
"initializer : '{' initializer_list '}'",
"initializer : '{' initializer_list ',' '}'",
"initializer_list : initializer",
"initializer_list : initializer_list ',' initializer",
"statement : compound_statement",
"statement : expression_statement",
"statement : selection_statement",
"statement : iteration_statement",
"statement : jump_statement",
"compound_statement : '{' '}'",
"compound_statement : '{' statement_list '}'",
"compound_statement : '{' declaration_list '}'",
"compound_statement : '{' declaration_list statement_list '}'",
"declaration_list : declaration",
"declaration_list : declaration_list declaration",
"statement_list : statement",
"statement_list : statement_list statement",
"expression_statement : ';'",
"expression_statement : expr ';'",
"selection_statement : selection1_statement",
"selection_statement : selection2_statement",
"selection1_statement : if_clause statement",
"selection2_statement : if_clause statement else_clause statement",
"if_clause : IF '(' expr ')'",
"else_clause : ELSE",
"iteration_statement : while_clause statement",
"while_token : WHILE",
"while_clause : while_token '(' expr ')'",
"jump_statement : BREAK ';'",
"jump_statement : RETURN ';'",
"jump_statement : RETURN expr ';'",
"file : external_definition",
"file : file external_definition",
"external_definition : function_definition",
"external_definition : declaration",
"function_definition : declarator function_body",
"function_definition : declaration_specifiers declarator function_body",
"function_body : compound_statement",
"function_body : declaration_list compound_statement",
"identifier : IDENTIFIER",
};
#endif
#ifndef YYSTYPE
typedef int YYSTYPE;
#endif
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 500
#define YYMAXDEPTH 500
#endif
#endif
int yydebug;
int yynerrs;
int yyerrflag;
int yychar;
short *yyssp;
YYSTYPE *yyvsp;
YYSTYPE yyval;
YYSTYPE yylval;
short yyss[YYSTACKSIZE];
YYSTYPE yyvs[YYSTACKSIZE];
#define yystacksize YYSTACKSIZE
#define YYABORT goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab
int
yyparse()
{
    register int yym, yyn, yystate;
#if YYDEBUG
    register char *yys;
    extern char *getenv();

    if (yys = getenv("YYDEBUG"))
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = (-1);

    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

yyloop:
    if (yyn = yydefred[yystate]) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yyssp >= yyss + yystacksize - 1)
        {
            goto yyoverflow;
        }
        *++yyssp = yystate = yytable[yyn];
        *++yyvsp = yylval;
        yychar = (-1);
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;
#ifdef lint
    goto yynewerror;
#endif
yynewerror:
    yyerror("syntax error");
#ifdef lint
    goto yyerrlab;
#endif
yyerrlab:
    ++yynerrs;
yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yyss + yystacksize - 1)
                {
                    goto yyoverflow;
                }
                *++yyssp = yystate = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = (-1);
        goto yyloop;
    }
yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    yyval = yyvsp[1-yym];
    switch (yyn)
    {
case 1:
#line 77 "grammar.y"
{ /* printf("IDENTIFIER\n"); */
		if ((work = findvar(last_ident,var_tab)) == -1)
		  if ((work = findvar(last_ident,ext_tab)) == -1) {
		    if (findvar(last_ident,func_tab) == -1) {
		      /* printf("\n***undeclared %s***\n",last_ident); */
		      undeclared++;
		    }
		    work = allocvar(last_ident,var_tab);
		  }
		  else
		    work |= EXTERNAL;
		if (!efetch(work))
		  return(1);
		}
break;
case 2:
#line 92 "grammar.y"
{ /*printf("CONSTANT\n"); */
		 if (!econst(kk))
		   return(1);
		}
break;
case 5:
#line 102 "grammar.y"
{ /* printf("FCALL\n"); */
		popid(func_ident,func_stack,&func_off); /* note ptr to off */
		if ((work = findvar(func_ident,func_tab)) == -1) {
		  /* printf("\n***declared %s***\n",func_ident); */
		  undeclared--; /*function name mistakenly undeclared*/
		  work = allocvar(func_ident,func_tab);
		}
		if(!efcall(work))
		  return(1);
		}
break;
case 6:
#line 113 "grammar.y"
{ /* printf("FCALL\n"); */
		popid(func_ident,func_stack,&func_off); /* note ptr to off */
		if ((work = findvar(func_ident,func_tab)) == -1) {
		  /* printf("\n***declared %s***\n",func_ident); */
		  undeclared--; /*function name mistakenly undeclared*/
		  work = allocvar(func_ident,func_tab);
		}
		if (!efcall(work))
		  return(1);
		}
break;
case 7:
#line 124 "grammar.y"
{ /* printf("POSTFIX-INC\n"); */
		/* this is wrong!  same as infix increment */
		postfix++;
		if (!econst(1L))
		  return(1);
		if ((work = findvar(last_ident,var_tab)) == -1)
		  if ((work = findvar(last_ident,ext_tab)) == -1) {
		    work = allocvar(last_ident,var_tab);
		  }
		  else
		    work |= EXTERNAL;
		if(!estore(work,ADD_ASSIGN))
		  return(1);
		}
break;
case 8:
#line 139 "grammar.y"
{ /* printf("POSTFIX-DEC\n"); */
		/* this is wrong!  same as infix decrement */
		postfix++;
		if (!econst(1L))
		  return(1);
		if ((work = findvar(last_ident,var_tab)) == -1)
		  if ((work = findvar(last_ident,ext_tab)) == -1) {
		    work = allocvar(last_ident,var_tab);
		  }
		  else
		    work |= EXTERNAL;
		if (!estore(work,SUB_ASSIGN))
		  return(1);
		}
break;
case 9:
#line 157 "grammar.y"
{ /* printf("FCALL-START\n"); */
		stackid(last_ident,func_stack,&func_off); /* note ptr to off */
		if (!eframe())
		  return(1);
		}
break;
case 13:
#line 172 "grammar.y"
{ /* printf("INFIX-INC\n"); */
		if (!econst(1L))
		  return(1);
		if ((work = findvar(last_ident,var_tab)) == -1)
		  if ((work = findvar(last_ident,ext_tab)) == -1) {
		    work = allocvar(last_ident,var_tab);
		  }
		  else
		    work |= EXTERNAL;
		if (!estore(work,ADD_ASSIGN))
		  return(1);
		}
break;
case 14:
#line 185 "grammar.y"
{ /* printf("INFIX-DEC\n"); */
		if (!econst(1L))
		  return(1);
		if ((work = findvar(last_ident,var_tab)) == -1)
		  if ((work = findvar(last_ident,ext_tab)) == -1) {
		    work = allocvar(last_ident,var_tab);

		  }
		  else
		    work |= EXTERNAL;
		if (!estore(work,SUB_ASSIGN))
		  return(1);
		}
break;
case 15:
#line 198 "grammar.y"
{ /* printf("UNARY-OP\n"); */
		/* note special tokens defined only to pass to interpreter */
		un_op = *(op_stack + op_off);
		op_off--;
		if (un_op == '-') {
		  if (!econst(0L))
		    return(1);
		  if (!ebinop(U_NEGATIVE))
		    return(1);
		} else if (un_op == '!') {
		  if (!econst(0L))
		    return(1);
		  if (!ebinop(U_NOT))
		    return(1);
		} else if (un_op == '~') {
		  if (!econst(0L))
		    return(1);
		  if (!ebinop(U_ONES))
		    return(1);
		}
		}
break;
case 16:
#line 223 "grammar.y"
{ /* printf("UNARY-OP\n"); */
		op_off++;
		*(op_stack + op_off) = '-';
		}
break;
case 17:
#line 228 "grammar.y"
{ 
		op_off++;
		*(op_stack + op_off) = '!';
		}
break;
case 18:
#line 233 "grammar.y"
{ 
		op_off++;
		*(op_stack + op_off) = '~';
		}
break;
case 22:
#line 247 "grammar.y"
{ /* printf("MULTIPLY\n"); */
		if (!ebinop('*'))
		  return(1);
		}
break;
case 23:
#line 252 "grammar.y"
{ /*printf("DIVIDE\n"); */
		if (!ebinop('/'))
		  return(1);
		}
break;
case 24:
#line 257 "grammar.y"
{ /* printf("MOD\n"); */
		if (!ebinop('%'))
		  return(1);
		}
break;
case 26:
#line 266 "grammar.y"
{ /* printf("ADD\n"); */
		if (!ebinop('+'))
		  return(1);

		}
break;
case 27:
#line 272 "grammar.y"
{ /* printf("SUBTRACT\n"); */
		if (!ebinop('-'))
		  return(1);
		}
break;
case 29:
#line 281 "grammar.y"
{ /* printf("SHIFT-LEFT\n"); */
		if (!ebinop(LEFT_OP))
		  return(1);
		}
break;
case 30:
#line 286 "grammar.y"
{ /* printf("SHIFT-RIGHT\n"); */
		if (!ebinop(RIGHT_OP))
		  return(1);
		}
break;
case 32:
#line 295 "grammar.y"
{ /* printf("LESS-THAN\n"); */
		if (!ebinop('<'))
		  return(1);
		}
break;
case 33:
#line 300 "grammar.y"
{ /* printf("GREATER-THAN\n"); */
		if (!ebinop('>'))
		  return(1);
		}
break;
case 34:
#line 305 "grammar.y"
{ /*printf("LESS-EQUAL\n"); */
		if (!ebinop(LE_OP))
		  return(1);
		}
break;
case 35:
#line 310 "grammar.y"
{ /* printf("GREATER-EQUAL\n"); */
		if (!ebinop(GE_OP))
		  return(1);
		}
break;
case 37:
#line 319 "grammar.y"
{ /* printf("EQUAL\n"); */
		if (!ebinop(EQ_OP))
		  return(1);
		}
break;
case 38:
#line 324 "grammar.y"
{ /* printf("NOT-EQUAL\n"); */
		if (!ebinop(NE_OP))
		  return(1);
		}
break;
case 40:
#line 333 "grammar.y"
{ /* printf("AND\n"); */
		if (!ebinop('&'))
		  return(1);
		}
break;
case 42:
#line 342 "grammar.y"
{ /* printf("EXCLUSIVE-OR\n"); */
		if (!ebinop('^'))
		  return(1);
		}
break;
case 44:
#line 351 "grammar.y"
{ /* printf("INCLUSIVE-OR\n"); */
		if (!ebinop('|'))
		  return(1);
		}
break;
case 46:
#line 360 "grammar.y"
{ /* printf("LOGICAL-AND\n"); */
		if (!ebinop(AND_OP))
		  return(1);
		}
break;
case 48:
#line 369 "grammar.y"
{ /* printf("LOGICAL-OR\n"); */
		if (!ebinop(OR_OP))
		  return(1);
		}
break;
case 51:
#line 382 "grammar.y"
{ /* printf("ASSIGNMENT\n"); */
		/* func_ident used as temp storage */
		popid(func_ident,var_stack,&var_off); /* note ptr to off */
		if ((work = findvar(func_ident,var_tab)) == -1)
		  if ((work = findvar(func_ident,ext_tab)) == -1) {
		    work = allocvar(func_ident,var_tab);
		  }
		  else
		    work |= EXTERNAL;
		if (!estore(work,*(op_stack + op_off)))
		  return(1);
		op_off--;
		}
break;
case 52:
#line 399 "grammar.y"
{ /* printf("ASSIGNMENT-LVAL\n"); */
		stackid(last_ident,var_stack,&var_off); /* note ptr to off */
		op_off++;
		*(op_stack + op_off) = work;
		}
break;
case 53:
#line 408 "grammar.y"
{ work =  '=';}
break;
case 54:
#line 410 "grammar.y"
{ work = MUL_ASSIGN;}
break;
case 55:
#line 412 "grammar.y"
{ work = DIV_ASSIGN;}
break;
case 56:
#line 414 "grammar.y"
{ work = MOD_ASSIGN;}
break;
case 57:
#line 416 "grammar.y"
{ work = ADD_ASSIGN;}
break;
case 58:
#line 418 "grammar.y"
{ work = SUB_ASSIGN;}
break;
case 59:
#line 420 "grammar.y"
{ work = LEFT_ASSIGN;}
break;
case 60:
#line 422 "grammar.y"
{ work = RIGHT_ASSIGN;}
break;
case 61:
#line 424 "grammar.y"
{ work = AND_ASSIGN;}
break;
case 62:
#line 426 "grammar.y"
{ work = XOR_ASSIGN;}
break;
case 63:
#line 428 "grammar.y"
{ work = OR_ASSIGN;}
break;
case 74:
#line 455 "grammar.y"
{ /* printf("INITIALIZER\n"); */
		fprintf(f_out,"\n**Warning** unsupported initializer\n");
		/* get rid of constant placed on stack */
		if (!echop())
		  return(1);
		}
break;
case 81:
#line 480 "grammar.y"
{ /* printf("VARIABLE-DECLARE\n"); */
		if (in_func) {
		  if (findvar(last_ident,var_tab) == -1)
		    allocvar(last_ident,var_tab);
		}
		else {
		  if (findvar(last_ident,ext_tab) == -1)
		    allocvar(last_ident,ext_tab);
		}
		}
break;
case 82:
#line 491 "grammar.y"
{ /* printf("FUNCTION-DECLARE\n"); */
		if (new_func() == -1)
		  return (1); /* exit the parser */
		}
break;
case 83:
#line 496 "grammar.y"
{ /* printf("FUNCTION-DECLARE\n"); */
		if (new_func() == -1)
		  return (1); /* exit the parser */
		}
break;
case 84:
#line 504 "grammar.y"
{ /* printf("FUNCTION-DEF-START\n"); */
		strcpy(func_ident,last_ident);

		}
break;
case 87:
#line 516 "grammar.y"
{ /* printf("PARAMETER-DECLARE\n"); */
		allocvar(last_ident,var_tab);
		num_parm++;
		}
break;
case 122:
#line 597 "grammar.y"
{ /* printf("CHOP\n"); */
		if (!echop())
		  return(1);
		}
break;
case 125:
#line 610 "grammar.y"
{ /* printf("IF-THEN\n"); */
		else_part();
		close_if();
		}
break;
case 126:
#line 618 "grammar.y"
{ /* printf("IF-THEN-ELSE\n"); */
		close_if();
		}
break;
case 127:
#line 625 "grammar.y"
{ /* printf("IF-CLAUSE\n"); */
		if (!new_if())
		  return (1); /* exit parser */
		}
break;
case 128:
#line 633 "grammar.y"
{ /* printf("ELSE-CLAUSE\n"); */
		else_part();
		}
break;
case 129:
#line 640 "grammar.y"
{ /* printf("WHILE\n"); */
		close_while();
		}
break;
case 130:
#line 647 "grammar.y"
{ /* printf("WHILE-TOKEN\n"); */
		if (!new_while())
		  return (1);  /* exit the parser */
		}
break;
case 131:
#line 655 "grammar.y"
{ /* printf("WHILE-CLAUSE\n"); */
		while_expr();
		}
break;
case 132:
#line 662 "grammar.y"
{ /* printf("BREAK\n"); */
		/* breaks can be handled by building a instruct chain */
		/* as part of the while_nest structures and patching them */
		/* on while_close.  maybe later */
		fprintf(f_out,"\n**Warning** unsupported break\n");
		}
break;
case 133:
#line 669 "grammar.y"
{ /* printf("RETURN-NOEXPR\n"); */
		/* all functions must return a value */
		if (!econst(1L))
		  return(1);
		if (!eretsub())
		  return(1);
		}
break;
case 134:
#line 677 "grammar.y"
{ /* printf("RETURN\n"); */
		if (!eretsub())
		  return(1);
		}
break;
case 137:
#line 690 "grammar.y"
{ /* printf("FUNCTION-DEFINITION\n"); */
		/* all functions must return a value */
		if (!econst(1L))
		  return(1);
		if (!eretsub())
		  return(1);
		end_func();
		}
break;
case 138:
#line 699 "grammar.y"
{ /* printf("EXTERNAL-DECLARE\n"); */
		}
break;
#line 1246 "y.tab.c"
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yyssp, yystate);
#endif
    if (yyssp >= yyss + yystacksize - 1)
    {
        goto yyoverflow;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;
    goto yyloop;
yyoverflow:
    yyerror("yacc stack overflow");
yyabort:
    return (1);
yyaccept:
    return (0);
}
