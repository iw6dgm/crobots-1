

/*****************************************************************************/
/*                                                                           */
/*  CROBOTS                                                                  */
/*                                                                           */
/*  (C) Copyright Tom Poindexter, 1985, all rights reserved.                 */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

/* screen.c - low level screen display routines */
/*            change or modify this module for different systems */

#include "crobots.h"
#include "math.h"
#include <curses.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
/*#include "/home/gyugyi/turmite/bitmaps/icon_bitmap"*/

/* #define SUN_SOUND /* sound */
#define GRID 100
#define GRIDSIZE 5
#define EXP_SIZE (40*GRID*GRIDSIZE/MAX_X)
/* #define DRAW_CURSES /**/
#define COLOR

#define BITMAPDEPTH 1
#define MAXCOLORS 8

Display *display;
int screen;

#ifdef SUN_SOUND
FILE *sp;
#endif

/* x windows defines */
Window win;
unsigned int width,height;
int x=0, y=0;
unsigned int border_width=4;
unsigned int display_width, display_height;
char *window_name = "CROBOTS.X";
char *icon_name = "basicwin";
Pixmap icon_pixmap;
XSizeHints size_hints;
XEvent report;
GC gc;
XFontStruct *font_info;
char *display_name = NULL;
int window_size = 0;
int k,kk;
int depth;
Visual *visual;
char *name[] = 
{"Gray20","Gray40","Gray60","Gray80","Gray30","Gray50","Gray70","Gray90"};
char *color_name[] = 
{"blue","green","red","cyan","magenta","yellow","orange","purple"};
XColor exact_def;
Colormap cmap;
int ncolors = MAXCOLORS;
int colors[MAXCOLORS];
int color_robots[MAXCOLORS];
int robot_virgin[MAXROBOTS] = {1,1,1,1};
int missile_virgin[MAXROBOTS][MIS_ROBOT] =
{{1,1},{1,1},{1,1},{1,1}};
int missiles_last_x[MAXROBOTS][MIS_ROBOT];
int missiles_last_y[MAXROBOTS][MIS_ROBOT];
int robots_old_x[MAXROBOTS];
int robots_old_y[MAXROBOTS];
/* init_disp - initialize display */


init_disp()
{
    int i;

   if ((display=XOpenDisplay(display_name))==NULL)
    {
    (void) fprintf( stderr, "cannot connect to X server %s\n",
    XDisplayName(display_name));
    exit(-1);
    }

    screen = DefaultScreen(display);
    display_width = DisplayWidth(display, screen);
    display_height = DisplayHeight(display, screen);
    
    width =  GRIDSIZE * (GRID + 1); 
    height = GRIDSIZE * (GRID + 1) + 100 ;
    
  win = XCreateSimpleWindow(display, RootWindow(display,screen),
        x,y,width,height,border_width,BlackPixel(display,screen),
        WhitePixel(display, screen));
  icon_pixmap = XCreateBitmapFromData(display,win,icon_bitmap_bits,
        icon_bitmap_width, icon_bitmap_height);

  size_hints.flags = PPosition | PSize | PMinSize;
  size_hints.x = x;
  size_hints.y = y;
  size_hints.width = width;
  size_hints.height = height;
  size_hints.min_width = 16;
  size_hints.min_height = 16;

  XSetStandardProperties(display, win, window_name, icon_name,
    icon_pixmap, NULL, NULL, &size_hints);
/*  XSetStandardProperties(display, win, window_name, icon_name,
    icon_pixmap, argv, argc, &size_hints);
*/
/*  XSelectInput(display, win, ExposureMask | KeyPressMask | 
    ButtonPressMask | StructureNotifyMask);
*/
  load_font(&font_info);
  get_GC(win, &gc, font_info);
  XSetFunction(display, gc, GXxor);
  XMapWindow(display, win);
  XFlush(display);

  /* color stuff */
  depth = DisplayPlanes(display, screen);
  visual = DefaultVisual(display, screen);
  cmap = DefaultColormap(display, screen);
  if (depth == 1)
    {
    for (i=0; i<4; i++)
      {
      color_robots[i] = WhitePixel(display,screen);
      };
    }
  else
    {
    for (i=0; i<MAXCOLORS; i++)
      {
#ifdef COLOR
      if (!XParseColor (display, cmap, color_name[i], &exact_def))
        {
        fprintf(stderr, "color name %s not in database\n",name[i]);
        exit(0);
        }
#else
      if (!XParseColor (display, cmap, name[i], &exact_def))
        {
        fprintf(stderr, "color name %s not in database\n",name[i]);
        exit(0);
        }
#endif
      if (!XAllocColor(display, cmap, &exact_def))
        {
        fprintf(stderr,"all colorcells allocated and read/write\n");
        exit(0);
        }
        colors[i] = exact_def.pixel;
       }
    for (i=0; i<4; i++)
      {
      color_robots[i]  = colors[(i%(MAXCOLORS-1)) + 1];
      };
    }
#ifdef SUN_SOUND
    if ((sp = fopen("/dev/audio","w")) == NULL) {
	printf("Can't open sound\n");
    };
#endif
    draw_field();
    printf("Press <enter> to begin.\n");
    getchar();
}


/* end_disp - cleanup and end display */

end_disp()
{
    printf("Press <enter> to end.\n");
    getchar();
  XUnloadFont(display, font_info->fid);
  XFreeGC(display, gc);
  XCloseDisplay(display);
#ifdef SUN_SOUND
  if (sp) {fclose(sp);}
#endif
}


/* draw_field - draws the playing field and status boxes */

draw_field()
{
    int i;

    XSetForeground(display, gc, BlackPixel(display,screen));
    XFillRectangle(display, win, gc,
		   0, 0, GRIDSIZE*(GRID+1) +1, GRIDSIZE*(GRID+1)+1);

}

/* plot_robot - plot the robot position */
erase_robot(n)
int n;
{
  if (robot_virgin[n] == 0) {
    XSetForeground(display, gc, color_robots[n]);
    XFillRectangle(display, win, gc,
		   (int)(GRIDSIZE*GRID*robots_old_x[n]/(1.0*CLICK*MAX_X))
		   - GRIDSIZE/2,
		   GRIDSIZE*GRID - 1 -
		   (int)(GRIDSIZE*GRID*robots_old_y[n]/(1.0*CLICK*MAX_Y))
		   - GRIDSIZE/2,
		   GRIDSIZE+1,GRIDSIZE+1);
    XDrawLine(display, win, gc,
	      (int)(GRIDSIZE*GRID*robots_old_x[n]/(1.0*CLICK*MAX_X)),
	      GRIDSIZE*GRID - 1 - 
	      (int)(GRIDSIZE*GRID*robots_old_y[n]/(1.0*CLICK*MAX_Y)),
	      (int)(GRIDSIZE*GRID*robots_old_x[n]/(1.0*CLICK*MAX_X)
		    + 2*GRIDSIZE * cos(robots[n].last_scan*3.14159/180.0)),
	      GRIDSIZE*GRID - 1 - 
	      (int)(GRIDSIZE*GRID*robots_old_y[n]/(1.0*CLICK*MAX_Y)
		    + 2*GRIDSIZE * sin(robots[n].last_scan*3.14159/180.0))
	      );
    if (robots[n].status == DEAD) {
	/* draw burned-out hull */
	XDrawRectangle(display, win, gc,
		   (int)(GRIDSIZE*GRID*robots_old_x[n]/(1.0*CLICK*MAX_X))
		   - GRIDSIZE/2,
		   GRIDSIZE*GRID - 1 -
		   (int)(GRIDSIZE*GRID*robots_old_y[n]/(1.0*CLICK*MAX_Y))
		   - GRIDSIZE/2,
		   GRIDSIZE+1,GRIDSIZE+1);
	robot_virgin[n] = 1; /* shouldn't be drawn anymore */
    }
  } 
}


plot_robot(n)

int n;
{
  int i, k;

  if (robot_virgin[n]  == 0) {
      erase_robot(n);
  } else {
      robot_virgin[n]=0;
  }

  XSetForeground(display, gc, color_robots[n]);
  XFillRectangle(display, win, gc,
		 (int)(GRIDSIZE*GRID*robots[n].x/(1.0*CLICK*MAX_X))
		 -GRIDSIZE/2,
		 GRIDSIZE*GRID - 1 - 
		 (int)(GRIDSIZE*GRID*robots[n].y/(1.0*CLICK*MAX_Y))
		 -GRIDSIZE/2,
		 GRIDSIZE+1,GRIDSIZE+1);
  XDrawLine(display, win, gc,
	    (int)(GRIDSIZE*GRID*robots[n].x/(1.0*CLICK*MAX_X)),
	    GRIDSIZE*GRID - 1 - 
	    (int)(GRIDSIZE*GRID*robots[n].y/(1.0*CLICK*MAX_Y)),
	    (int)(GRIDSIZE*GRID*robots[n].x/(1.0*CLICK*MAX_X)
		  + 2*GRIDSIZE * cos(robots[n].scan*3.14159/180.0)),
	    GRIDSIZE*GRID - 1 - (int)(GRIDSIZE*GRID*robots[n].y/(1.0*CLICK*MAX_Y)
			       + 2*GRIDSIZE * sin(robots[n].scan*3.14159/180.0))
	    );
  XFlush(display);
  robots_old_x[n] = robots[n].x;
  robots_old_y[n] = robots[n].y;
  robots[n].last_scan = robots[n].scan;
}


/* plot_miss - plot the missile position */

plot_miss(r,n)

int r;
int n;
{
  int i, k;

  if (missile_virgin[r][n] == 0) {
      XSetForeground(display, gc, color_robots[r]);
      XFillRectangle(display, win, gc,
		     (int)(GRIDSIZE*GRID*missiles_last_x[r][n]/(1.0*CLICK*MAX_X)) - GRIDSIZE/4,
		     GRIDSIZE*GRID - 1 - 
		     (int)(GRIDSIZE*GRID*missiles_last_y[r][n]/(1.0*CLICK*MAX_Y)) - GRIDSIZE/4,
		     GRIDSIZE/2+1, GRIDSIZE/2+1);
  } else {
      missile_virgin[r][n] = 0;
  }

  XSetForeground(display, gc, color_robots[r]);
  XFillRectangle(display, win, gc,
		 (int)(GRIDSIZE*GRID*missiles[r][n].cur_x/(1.0*CLICK*MAX_X))-GRIDSIZE/4,
		 GRIDSIZE*GRID - 1 - 
		 (int)(GRIDSIZE*GRID*missiles[r][n].cur_y/(1.0*CLICK*MAX_Y))-GRIDSIZE/4,
		 GRIDSIZE/2 + 1, GRIDSIZE/2+1);
  XFlush(display);
  missiles_last_x[r][n] = missiles[r][n].cur_x;
  missiles_last_y[r][n] = missiles[r][n].cur_y;
}



/* plot_exp - plot the missile exploding */

plot_exp(r,n)

int r;
int n;
{
  if (missiles[r][n].count == EXP_COUNT) {
    /* erase last missile postion */
    XSetForeground(display, gc, color_robots[r]);
    XFillRectangle(display, win, gc,
		   (int)(GRIDSIZE*GRID*missiles_last_x[r][n]/(1.0*CLICK*MAX_X))-GRIDSIZE/4,
		   GRIDSIZE*GRID - 1 - 
		   (int)(GRIDSIZE*GRID*missiles_last_y[r][n]/(1.0*CLICK*MAX_Y))-GRIDSIZE/4,
		   GRIDSIZE/2+1, GRIDSIZE/2+1);
    XSetForeground(display, gc, color_robots[r]);
    XFillArc(display, win, gc,
		   (int)(GRIDSIZE*GRID*
			 (missiles[r][n].cur_x/(1.0*CLICK*MAX_X)))-EXP_SIZE/2,
		   GRIDSIZE*GRID - 1 - 
		   (int)(GRIDSIZE*GRID*
			 (missiles[r][n].cur_y/(1.0*CLICK*MAX_Y)))-EXP_SIZE/2,
		   EXP_SIZE, EXP_SIZE, 0, 360*64);
    XFlush(display);
    /* reset xor flag */
      missile_virgin[r][n] = 1;
#ifdef SUN_SOUND
    if (sp) {fprintf(sp,"AzAzAzAzAzAzAzAzAzAzAzAzAzAzAzAzAzAz");fflush(sp);}
#endif    
  }
  else if (missiles[r][n].count == 1) {
      XSetForeground(display, gc, color_robots[r]);
      XFillArc(display, win, gc,
		     (int)(GRIDSIZE*GRID*
			   (missiles[r][n].cur_x/(1.0*CLICK*MAX_X)))-EXP_SIZE/2,
		     GRIDSIZE*GRID - 1 - 
		     (int)(GRIDSIZE*GRID*
			   (missiles[r][n].cur_y/(1.0*CLICK*MAX_Y)))-EXP_SIZE/2,
		 EXP_SIZE, EXP_SIZE, 0, 360*64);
      XFlush(display);
  }
}


/* robot_stat - update status info */

robot_stat(n)

int n;
{
    char buf[128];
    static int olddamage[4]={-1,-1,-1,-1};

    if (robots[n].damage != olddamage[n]) {
	XSetFunction(display, gc, GXcopy);
	XFlush(display);
	XSetForeground(display, gc, BlackPixel(display, screen));
	XFillRectangle(display,win,gc,10,GRIDSIZE*(GRID+1)+20*(n+1)-15,
		       GRIDSIZE*(GRID+1)-20,18);
	XSetFunction(display, gc, GXxor);
	XFlush(display);
	XSetForeground(display, gc, color_robots[n]);
	sprintf(buf,"%d: %s %d",n,robots[n].name,robots[n].damage);
	XDrawString(display,win,gc, 20, GRIDSIZE*(GRID+1)+20*(n+1),
		    buf, strlen(buf));
	olddamage[n]=robots[n].damage;

	if (robots[n].status == DEAD) {
	    erase_robot(n);
	}
	XFlush(display);
    }
}


show_cycle(l)

long l;
{
}

get_GC(win,gc,font_info)
Window win;
GC *gc;
XFontStruct *font_info;
{
  unsigned long valuemask = 0;
  XGCValues values;

  *gc = XCreateGC(display, win, valuemask, &values);
  XSetFont(display, *gc, font_info->fid);
  XSetForeground(display, *gc, BlackPixel(display,screen));
}

load_font(font_info)
XFontStruct **font_info;
{
  char *fontname = "9x15";
  if ((*font_info  = XLoadQueryFont(display,fontname))==NULL)
    {
    (void) fprintf( stderr, "Basic: Cannot open 9x15 font\n");
    exit(-1);
    }
}
