/*
  CURSORS.H
  january 23 2009
  Javier Novoa C.
  
  MasterMind game
  cursors graphic interface
	
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

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

#ifdef LOCALE_TRANSLATION
#include <libintl.h>
#define _(String) gettext (String)
#endif

#include "curstextlib.h"

extern int norepit;

void inst(void);
extern void mastermind(void);
void opcs(void);
void about(void);
void error(void);

//Screen functions
void init_screen(void);
void end_screen(void);
void menu(void);
void mscreen(void);
void screen(void);

//Utility screen functions
void title(void);
void quit(void);

//Game result message functions
void winner(int);
void looser(int []);

/*SCREEN INITIALIZATION*/
void init_screen() {
#ifdef CONIO

#elif defined CURSES
    initscr();
    cbreak();
    noecho();
    if (has_colors()) {
	start_color();
	init_pair(BLACK, BLACK, BLACK);
	init_pair(RED, RED,     BLACK);
	init_pair(GREEN, GREEN,   BLACK);
	init_pair(YELLOW, YELLOW,  BLACK);
	init_pair(BLUE, BLUE,    BLACK);
	init_pair(CYAN, CYAN,    BLACK);
	init_pair(MAGENTA, MAGENTA, BLACK);
	init_pair(WHITE, WHITE,   BLACK);
	init_pair(BL_WHITE, WHITE, BLUE);
	init_pair(BL_YELLOW, YELLOW, BLUE);
	init_pair(DG_LIGHTMAGENTA, LIGHTMAGENTA, DARKGRAY);
	init_pair(LB_LIGHTGREEN, LIGHTGREEN, LIGHTBLUE);
	if (can_change_color()) {
/*	    init_color(WHITE, 1000, 1000, 1000);
	    init_color(YELLOW, 1000, 1000, 0);*/
/*	    init_color(BROWN, 529, 0, 0);
	    init_color(LIGHTGRAY, 920, 920, 920);
	    init_color(DARKGRAY, 462, 462, 462);
	    init_color(LIGHTBLUE, 470, 470, 1000);
	    init_color(LIGHTGREEN, 615, 1000, 615);
	    init_color(LIGHTCYAN, 100, 941, 1000);
	    init_color(LIGHTRED, 1000, 0, 0);
	    init_color(LIGHTMAGENTA, 0, 235, 941);*/
	}
    }
#endif
}

/*SCREEN FINALIZATION*/
void end_screen() {
#ifdef CONIO

#elif defined CURSES
    endwin();
#endif
}

/*MAIN MENU LOOP*/
void menu(void) {
    void (*f[5])(void) = {inst,
			  mastermind,
			  opcs,
			  about,
			  error};//main menu options functions
    char opc;
    
    mscreen();
    opc = getKeyPrompt("", 1, sizeY());
    
    while (1) {
	if(opc=='1' || opc=='2' ||
	   opc=='3' || opc=='4')//options 1 - 4
	    (*f[opc-48-1])();
	else if(opc=='5')//option 5: quit
	    break;
	else {//something else: error
	    (*f[4])();
	    mscreen();
	}
	mscreen();
	opc = getKeyPrompt("", 1, sizeY());
    }
    quit();//good-bye
}

/*MAIN MENU SCREEN*/
void mscreen(void) {
    title();
    
    char * txt1 = (char *)malloc(3 + strlen(_(menuOptInst)) + 1);
    txt1[0] = '\0';
    txt1 = strcat(txt1, "1 ");
    char * txt2 = (char *)malloc(3 + strlen(_(menuOptPlay)) + 1);
    txt2[0] = '\0';
    txt2 = strcat(txt2, "2 ");
    char * txt3 = (char *)malloc(3 + strlen(_(menuOptOptions)) + 1);
    txt3[0] = '\0';
    txt3 = strcat(txt3, "3 ");
    char * txt4 = (char *)malloc(3 + strlen(_(menuOptAbout)) + 1);
    txt4[0] = '\0';
    txt4 = strcat(txt4, "4 ");
    char * txt5 = (char *)malloc(3 + strlen(_(menuOptQuit)) + 1);
    txt5[0] = '\0';
    txt5 = strcat(txt5, "5 ");
    
    printText(_(menuInst), 1, 5, WHITE, BLACK);
    printText(strcat(txt1, _(menuOptInst)), 2, 8, WHITE, BLACK);
    printText(strcat(txt2, _(menuOptPlay)), 2, 11, WHITE, BLACK);
    printText(strcat(txt3, _(menuOptOptions)), 2, 14, WHITE, BLACK);
    printText(strcat(txt4, _(menuOptAbout)), 2, 17, WHITE, BLACK);
    printText(strcat(txt5, _(menuOptQuit)), 2, 20, WHITE, BLACK);
    
    free(txt1);
    free(txt2);
    free(txt3);
    free(txt4);
    free(txt5);
}

/*GAME'S MAIN SCREEN*/
void screen(void) {
    int cont;
    
    title();
    printStyleText(_(playInst),
		   SUBTITLE_TEXT);
    printStyleText(_(playInst2),
		   STATUS_TEXT);
    
    for (cont = 5; cont <= 23; cont += 2) {
	printText("___   ___   ___   ___",
		  1, cont,
		  LIGHTRED, BLACK);//user input spaces
	printText("___   ___   ___   ___",
		  30, cont,
		  LIGHTBLUE, BLACK);//game answers spaces
    }
    
    /*(Help system) keys corresponding to each color*/
    printText(_(playColor), 65, 6, WHITE, BLACK);
    printText("###", 71, 6, WHITE, BLACK);
    printText(_(playPosition), 62, 8, WHITE, BLACK);
    printText("###", 71, 8, YELLOW, BLACK);
    
    printText("1 ", 69, 12, WHITE, BLACK);
    printText("###", 71, 12, RED, BLACK);
    
    printText("2 ", 69, 14, WHITE, BLACK);
    printText("###", 71, 14, GREEN, BLACK);
    
    printText("3 ", 69, 16, WHITE, BLACK);
    printText("###", 71, 16, BROWN, BLACK);
    
    printText("4 ", 69, 18, WHITE, BLACK);
    printText("###", 71, 18, BLUE, BLACK);
    
    printText("5 ", 69, 20, WHITE, BLACK);
    printText("###", 71, 20, MAGENTA, BLACK);
    
    printText("6 ", 69, 22, WHITE, BLACK);
    printText("###", 71, 22, CYAN, BLACK);
}

/*GAME OPTIONS LOOP & SCREEN*/
void opcs(void) {
    char intro;
    while(1) {
	title();
	printStyleText(_(optionsInst),
		       SUBTITLE_TEXT);
	
	printText("1 ", 1, 7, WHITE, BLACK);
	if (norepit == 1)
	    printText("_", 3, 7, WHITE, BLACK);
	else
	    printText("X", 3, 7, WHITE, BLACK);
	printText(_(optionsOpt1),
		  4, 7, WHITE, BLACK);
	
	intro = getKeyPrompt("", 1, sizeY());
	
	if (intro == '1') {
	    if (norepit == 1)
		norepit = 0;
	    else
		norepit = 1;
	} else if (intro == 'Q' || intro == 'q')
	    break;
    }
}

/*Title*/
void title(void) {
    clearScreen();
    printStyleText(untrim(_(programTitle)), TITLE_TEXT);
}

/*ERROR SCREEN*/
void error(void) {
    title();
    printStyleText(_(errorMessage), MESSAGE_TEXT);
    doBeep();
    doBeep();
    getKey();
}

/*QUIT SCREEN*/
void quit(void) {
    title();
    char *bye = _(final);
    printText(bye, centerX(bye), centerY(bye), YELLOW, BLUE);
    printText(_(author), 1, sizeY(), WHITE, BLUE);
    getKey();//gracias por usar mi programa
}

/*ABOUT SCREEN*/
void about(void) {
    title();
    
    char *txt1 = (char *) malloc (strlen(_(programTitle)) + 1 + 2 + strlen(_(versionNumber)) + 1);
    txt1 [0] = '\0';
    strcat(txt1, _(programTitle));
    strcat(txt1, " ");
    strcat(txt1, _(versionNumber));
    printText(txt1, 1, 3, YELLOW, BLACK);
    
    char *txt2 = (char *) malloc (strlen(_(aboutAuthor)) + 1 + 2 + strlen(_(authorNick)) + 1 + 3 + strlen(_(author)) + 1 + 2);
    txt2 [0] = '\0';
    strcat(txt2, _(aboutAuthor));
    strcat(txt2, " ");
    strcat(txt2, _(authorNick));
    strcat(txt2, " (");
    strcat(txt2, _(author));
    strcat(txt2, ")");
    
    printText(txt2,
	      1, 5, YELLOW, BLACK);//Este soy yo
    
    char *txt3 = (char *) malloc (strlen(_(aboutDate)) + 1 + 3 + strlen(_(aboutLastUpdate)) + 1 + 2 + strlen(_(lastUpdateDate)) + 1 + 3 + strlen(_(lastUpdateYear)) + 1 + 2);
    txt3[0] = '\0';
    strcat(txt3, _(aboutDate));
    strcat(txt3, " (");
    strcat(txt3, _(aboutLastUpdate));
    strcat(txt3, " ");
    strcat(txt3, _(lastUpdateDate));
    strcat(txt3, ", ");
    strcat(txt3, _(lastUpdateYear));
    strcat(txt3, ")");
    printText(txt3,
	      1, 7, YELLOW, BLACK);
    
    printText(_(aboutPlace),
	      1, 9, YELLOW, BLACK);
    
    char *txt4 = (char *) malloc (strlen(_(aboutCopyleft)) + 1 + 2 + strlen(_(lastUpdateYear)) + 1 + 3 + strlen(_(author)) + 1 + 3 + strlen(_(aboutCity)) + 1);
    txt4[0] = '\0';
    strcat(txt4, _(aboutCopyleft));
    strcat(txt4, "-");
    strcat(txt4, _(lastUpdateYear));
    strcat(txt4, ", ");
    strcat(txt4, _(author));
    strcat(txt4, ", ");
    strcat(txt4, _(aboutCity));
    printText(txt4,
	      1, 11, YELLOW, BLACK);
    
    char *txt5 = (char *) malloc (strlen(_(aboutEmail)) + 1 + 2 + strlen(_(authorEmail)));
    txt5[0] = '\0';
    strcat(txt5, _(aboutEmail));
    strcat(txt5, " ");
    strcat(txt5, _(authorEmail));
    printText(txt5, 1, 13, YELLOW, BLACK);
    
    printText(_(about1),
	      1, 15, YELLOW, BLACK);
    printText(_(about2),
	      1, 16, YELLOW, BLACK);
    printText(_(about3),
	      1, 17, YELLOW, BLACK);
    printText(_(about4),
	      1, 18, YELLOW, BLACK);
    printText(_(about5),
	      1, 19, YELLOW, BLACK);
    printText(_(about6),
	      1, 20, YELLOW, BLACK);
    printText(_(about7),
	      1, 21, YELLOW, BLACK);
    printText(_(about8),
	      1, 22, YELLOW, BLACK);
    
    free(txt1);
    free(txt2);
    free(txt3);
    free(txt4);
    free(txt5);
    
    getKeyPrompt("", 1, sizeY());
}

/*ONLINE INSTRUCTIONS SCREEN*/
void inst(void) {
    title();
    printText(_(inst1),
	      1, 3, WHITE, BLACK);
    printText(_(inst2),
	      1, 4, WHITE, BLACK);
    printText(_(inst3),
	      1, 5, WHITE, BLACK);
    printText(_(inst4),
	      1, 6, WHITE, BLACK);
    
    char *txt1 = _(inst5);
    char *txt2 = _(inst6);
    char *txt3 = _(inst7);
    printText(txt1, 1, 8, WHITE, BLACK);
    printText(txt2, strlen(txt1) + 1, 8, LIGHTRED, BLACK);
    printText(txt3, strlen(txt1) + strlen(txt2) + 2, 8, WHITE, BLACK);
    
    printText("  1 ", 1, 9, WHITE, BLACK);
    printText(_(instRed), 5, 9, RED, BLACK);
    printText("  2 ", 1, 10, WHITE, BLACK);
    printText(_(instGreen), 5, 10, GREEN, BLACK);
    printText("  3 ", 1, 11, WHITE, BLACK);
    printText(_(instBrown), 5, 11, BROWN, BLACK);
    printText("  4 ", 1, 12, WHITE, BLACK);
    printText(_(instBlue), 5, 12, BLUE, BLACK);
    printText("  5 ", 1, 13, WHITE, BLACK);
    printText(_(instMagenta), 5, 13, MAGENTA, BLACK);
    printText("  6 ", 1, 14, WHITE, BLACK);
    printText(_(instCyan), 5, 14, CYAN, BLACK);
    
    printText(_(inst8),
	      1, 15, WHITE, BLACK);
    printText(_(inst9),
	      1, 16, WHITE, BLACK);
    char *txt4 = _(inst10);
    char *txt5 = _(inst11);
    char *txt6 = _(inst12);
    printText(txt4, 1, 18, WHITE, BLACK);
    printText(txt5, strlen(txt4) + 1, 18, LIGHTBLUE, BLACK);
    printText(txt6, strlen(txt4) + strlen(txt5) + 2, 18, WHITE, BLACK);
    
    char *txt7 = _(inst13);
    char *txt8 = _(inst15);
    char *txt9 = _(inst17);
    printText(txt7, 3, 19, WHITE, BLACK);
    printText(_(inst14),
	      strlen(txt7) + 3, 19, WHITE, BLACK);
    
    printText(txt8, 1, 20, YELLOW, BLACK);
    printText(_(inst16),
	      strlen(txt8) + 1, 20, WHITE, BLACK);
    
    printText(txt9, 6, 21, WHITE, BLACK);
    printText(_(inst18), strlen(txt9) + 6, 21, WHITE, BLACK);
    printText(_(inst19),
	      1, 22, WHITE, BLACK);
    printText(_(inst20),
	      1, 23, WHITE, BLACK);
    printText(_(inst21),
	      1, 24, WHITE, BLACK);
    getKey();
}

/*WINNER SCREEN*/
void winner(int numero) {
    title();
    printText(_(win1),
	      20, 5, LIGHTMAGENTA, DARKGRAY);
    printText(_(win2), 20, 10, LIGHTMAGENTA, DARKGRAY);
    if(numero == 1)
	printText(_(win3),
		  20, 15, LIGHTMAGENTA, DARKGRAY);
    else {
	char * txt1 = _(win4);
	printText(txt1, 20, 15, LIGHTMAGENTA, DARKGRAY);
	char txt[13];
	sprintf(txt, "%d", numero);
	printText(txt, 20 + strlen(txt1), 15, LIGHTMAGENTA, DARKGRAY);
	printText(_(win5),
		  20 + strlen(txt1) + strlen(txt), 15, LIGHTMAGENTA, DARKGRAY);
    }
    switch(numero) {
	case 1:
	    printText(_(result1),
		      20, 16, LIGHTMAGENTA, DARKGRAY);
	    break;
	case 2:
	    printText(_(result2),
		      20, 16, LIGHTMAGENTA, DARKGRAY);
	    break;
	case 3:
	    printText(_(result3),
		      20, 16, LIGHTMAGENTA, DARKGRAY);
	    break;
	case 4:
	    printText(_(result4),
		      20, 16, LIGHTMAGENTA, DARKGRAY);
	    break;
	case 5:
	    printText(_(result5),
		      20, 16, LIGHTMAGENTA, DARKGRAY);
	    break;
	case 6:
	    printText(_(result6),
		      20, 16, LIGHTMAGENTA, DARKGRAY);
	    break;
	case 7:
	    printText(_(result7),
		      20, 16, LIGHTMAGENTA, DARKGRAY);
	    break;
	case 8:
	    printText(_(result8),
		      20, 16, LIGHTMAGENTA, DARKGRAY);
	    break;
	case 9:
	    printText(_(result9),
		      20, 16, LIGHTMAGENTA, DARKGRAY);
	    break;
	case 10:
	    printText(_(result10),
		      20, 16, LIGHTMAGENTA, DARKGRAY);
	    break;
    }
#ifdef CONIO
    sound(500);
    delay(500);
    nosound();
#endif
}

/*LOOSER SCREEN*/
void looser(int solucion[]) {
#ifdef COLORBLIND
    char colorblind_text[4][4];
#endif
    int cont;
    
    title();
    printText(_(loose1), 19, 5, LIGHTGRAY, BLACK);
    doBeep();
    printText(_(loose2), 19, 7, LIGHTGRAY, BLACK);
    
#ifdef COLORBLIND
    for(cont = 0; cont <= 3; cont++)
        snprintf(colorblind_text[cont], 4, "#%d#", solucion[cont]);
    for(cont = 0; cont <= 3; cont++)
    printText(colorblind_text[cont],
      6 * cont + 20, 10, solucion[cont], BLACK);
#else
    for(cont = 0; cont <= 3; cont++)
    printText("###   ",
          6 * cont + 20, 10, solucion[cont], BLACK);
#endif
    
    printText(_(loose3), 19, 15, WHITE, BLACK);
}
