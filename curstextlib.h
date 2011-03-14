/*
  CURSTEXTLIB.H
  january 23 2009
  Javier Novoa C.
  
  MasterMind game
  utility routines for cursors graphics interface
  
  Copyleft 1998, 2009, Javier Novoa C., Mexico, jstitch@gmail.com
  
  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License v2 or any later version.
  
  This program is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
  more details.
  
  You should have received a copy of the GNU General Public License along with
  this program; if not, please contact the current project maintainer.
*/

//#define CONIO
#define CURSES

#include <stdlib.h>
#include <string.h>

#ifdef CURSES
 #include <ncurses.h>
#endif
#ifdef CONIO
 #include <dos.h>
 #include <conio.h>
#endif

//Colors
#ifdef CONIO
 #define BLACK 0
 #define BLUE 4
 #define GREEN 2
 #define CYAN 6
 #define RED 1
 #define MAGENTA 5
 #define BROWN 3
 #define LIGHTGRAY 7
 #define DARKGRAY 8
 #define LIGHTBLUE 9
 #define LIGHTGREEN 10
 #define LIGHTCYAN 11
 #define LIGHTRED 12
 #define LIGHTMAGENTA 13
 #define YELLOW 14
 #define WHITE 15
#elif defined CURSES
 #define BLACK COLOR_BLACK
 #define BLUE COLOR_BLUE
 #define GREEN COLOR_GREEN
 #define CYAN COLOR_CYAN
 #define RED COLOR_RED
 #define MAGENTA COLOR_MAGENTA
 #define YELLOW COLOR_YELLOW
 #define WHITE COLOR_WHITE
 //TODO: accomplish 16 colors for ncurses!
 #define BROWN YELLOW
 #define LIGHTGRAY WHITE
 #define DARKGRAY BLACK
 #define LIGHTBLUE BLUE
 #define LIGHTGREEN GREEN
 #define LIGHTCYAN CYAN
 #define LIGHTRED RED
 #define LIGHTMAGENTA MAGENTA
#endif

//color combinations (background_foreground)
#define BL_WHITE 16
#define BL_YELLOW 17
#define DG_LIGHTMAGENTA 18
#define LB_LIGHTGREEN 19

//styles for text to print in screen
#define TITLE_TEXT 1
#define MESSAGE_TEXT 2
#define SUBTITLE_TEXT 3
#define STATUS_TEXT 4

void printText(char *, int, int, int, int);
void printStyleText(char *, int);
void clearScreen();
int getKey();
int getKeyPrompt(char *, int, int);
int sizeX();
int sizeY();
int centerX();
int centerY();
void gotoCoordinates(int, int);
int getX();
int getY();
int getTextColor();
int getTextBackground();
void setTextColor(int);
void setTextBackground(int);
void print(char *, int, int);
void doBeep();

/*Prints a text with specified coordinates and colors*/
void printText(char * text, int x, int y, int txtcol, int txtback) {
#ifdef CONIO
    int lastTxtCol = getTextColor();
    int lastTxtBack = getTextBackground();
    setTextColor(txtcol);
    setTextBackground(txtback);
#elif defined CURSES
    //TODO : polish this horrible special cases
    if (txtback == BLACK)
	attron(COLOR_PAIR(txtcol));
    else if (txtback == BLUE) {
	if (txtcol == WHITE)
	    attron(COLOR_PAIR(BL_WHITE));
	else if (txtcol == YELLOW)
	    attron(COLOR_PAIR(BL_YELLOW));
    } else if (txtback == DARKGRAY) {
	if (txtcol == LIGHTMAGENTA)
	    attron(COLOR_PAIR(DG_LIGHTMAGENTA));
    } else if (txtback == LIGHTGREEN) {
	if (txtcol == LIGHTBLUE)
	    attron(COLOR_PAIR(LB_LIGHTGREEN));
    }
#endif
    print(text, x, y);
#ifdef CONIO
    setTextColor(lastTxtCol);
    setTextBackground(lastTxtBack);
#elif defined CURSES
    attroff(COLOR_PAIR(BLACK));
    refresh();
#endif	
}

/*Prints a text, with a defined style, according to given properties*/
void printStyleText(char * text, int properties) {
    switch(properties) {
	case TITLE_TEXT:
	    printText(text, centerX(text),
		      1, LIGHTBLUE, LIGHTGREEN);
	    break;
	case MESSAGE_TEXT:
	    printText(text,
		      centerX(text), centerY(text),
		      LIGHTGREEN, BLACK);
	    break;
	case SUBTITLE_TEXT:
	    printText(text, 1, 3, WHITE, BLACK);
	    break;
	case STATUS_TEXT:
	    printText(text, 1, sizeY(), WHITE, BLACK);
	    break;
	default:
	    break;
    }
}

/*Clears screen*/
void clearScreen() {
#ifdef CONIO
    clrscr();
#elif defined CURSES
    clear();
#endif
}

/*Gets a key pressed on keyboard*/
int getKey() {
#ifdef CONIO
    return getch();
#elif defined CURSES
    return getch();
#endif
}

/*Gets a key pressed on keyboard, with a given prompt*/
int getKeyPrompt(char *prompt, int x, int y) {
    print(prompt, x, y);
    return getKey();
}

/*Horizontal size of screen (X or width)*/
int sizeX() {
    int x, y;
#ifdef CONIO
    //TODO
#elif defined CURSES
    getmaxyx(stdscr, y, x);
#endif
    return x;
}

/*Vertical size of screen (Y or height)*/
int sizeY() {
    int x, y;
#ifdef CONIO
    //TODO
#elif defined CURSES
    getmaxyx(stdscr, y, x);
#endif
    return y - 1;
}

/*X coordinate to center a given text in screen*/
int centerX(char *txt) {
    return (sizeX() - strlen(txt)) / 2;
}

/*Y coordinate to center in screen*/
int centerY() {
    return (sizeY()) / 2;
}

/*Moves cursor to given coordinetes in screen*/
void gotoCoordinates(int x, int y) {
#ifdef CONIO
    gotoxy(x, y);
#elif defined CURSES
    move(y, x);
#endif
}

/*Get current X coordinate*/
int getX() {
    int x, y;
#ifdef CONIO
    //TODO
#elif defined CURSES
    getyx(stdscr, y, x);
#endif
    return x;
}

/*Get current Y coordinate*/
int getY() {
    int x, y;
#ifdef CONIO
    //TODO
#elif defined CURSES
    getyx(stdscr, y, x);
#endif
    return y;
}

#ifdef CONIO
/*Get current text (foreground) color*/
int getTextColor () {
    return WHITE;//TODO
}
#endif

#ifdef CONIO
/*Get current background color*/
int getTextBackground () {
    return BLACK;//TODO
}
#endif

#ifdef CONIO
/*Sets text (foreground) color*/
void setTextColor (int txtcolor) {
    textcolor(txtcolor);
}
#endif

#ifdef CONIO
/*Sets background color*/
void setTextBackground (int txtbackgrnd) {
    textbackground(txtbackgrnd);
}
#endif

/*Prints a string in the given coordinates*/
void print (char * text, int x, int y) {
#ifdef CONIO
    gotoCoordinates(x, y);
    cprintf(text);
#elif defined CURSES
    mvprintw(y, x, text);
#endif
}

/*Sounds a beep*/
void doBeep() {
#ifdef CONIO
    cprintf("\a");
#elif defined CURSES
    beep();
#endif
}
