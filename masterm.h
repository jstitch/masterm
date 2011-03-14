/*
  MASTERM.H
  january 23 2009
  Javier Novoa C.
  
  MasterMind game
  game's routines
	
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

#include "languages.h"
#include <libintl.h>
#include <locale.h>

#ifdef CURSORS_INTERFACE
#include "cursors.h"
#endif

//Program's options
int norepit = 1;//Allow repetition in secret combination (0) or do not (1)

/*Functions' prototypes*/
//main loop
void mastermind(void);

//several game functions
void init(void);
void finalize(void);
void shuffle(int []);
void play(int [],int *,int *,int *);
void whathappens(int [], int, int);

/*Initializations*/
void init() {
#ifdef CURSORS_INTERFACE
    init_screen();
#endif
#ifdef LOCALE_TRANSLATION
    setlocale(LC_MESSAGES, "");
    bindtextdomain("masterm", LOCALEDIR);
    textdomain("masterm");
#endif
}

/*Termination*/
void finalize() {
#ifdef CURSORS_INTERFACE
    end_screen();
#endif
}

/*GENERATES 4 RANDOM NUMBERS FROM A POOL OF 6 POSSIBILITIES, EACH NUMBER GOES
 * IN ONE LOCATION IN THE TO-GUESS ARRAY*/
void shuffle(int array[4]) {
    int nrep(int, int[]); //used to prohibit repetition
    int cont;                          /*BLUE    1*//*GREEN 2*/
    srand(time(NULL));                 /*CYAN    3*//*RED   4*/
    for(cont = 0; cont <= 3; cont++) { /*MAGENTA 5*//*BROWN 6*/
	if(norepit == 0)//allows repetition of numbers
	    array[cont] = rand() % 6 + 1;
	else {//default option: less difficulty level
	    do {//numbers in combination cannot repeat themselves
		array[cont] = rand() % 6 + 1;
	    } while (nrep(cont - 1, array) == 0);
	}
    }
/*TESTING CODE:
	array[0]=;
	array[1]=;
	array[2]=;
	array[3]=;*/
}

/*VERIFIES THE LAST ELEMENT IN THE ARRAY DOESN'T REPEATS WITH THE PREVIOUS
 * ONES*/
int nrep(int ind, int arr[]) {
    int cont;
    int col = arr[ind + 1];
    
    if (ind < 0)/*if index is for the first element, it cannot repeat itself
		 * with anything*/
	return 1;
    for (cont = 0; cont <= ind; cont++)
	if (arr[cont] == col)
	    return 0;
    return 1;
}

/*WAITS FOR INPUT NUMBERS AND DECIDES IF THEY BELONG TO THE SECRET COMBINATION
 * ARRAY AND IN WHICH ORDER THEY WERE ENTERED.
 *
 * This function is too tied to the interface, TODO: CHANGE!!*/
void play(int guess[],int *pos, int *f, int *win) {
#ifdef COLORBLIND
	char colorblind_text[4];
#endif
    void aim(int [], int [], int *, int *);
    char intro;
    int turn[4] = {0};
    int x = 0, cont = 0;//both does the same thing, gotta simplify!
    int s1 = 0, s2 = 0;//'state machine' for debugging...
    
    while (cont <= 3)/*4 cycles iteration, one for each number in the
		      *  secret combination*/ {
#ifdef CURSORS_INTERFACE
	intro = getKeyPrompt("", (x * 6) + 1, (*pos * 2) + 4);
#endif
	if ('1' <= intro && intro <= '6') {//valid guess input
	    s1 = s2 = 0;
	    turn[x] = intro - 48;//48:ASCII code of '0'
#ifdef CURSORS_INTERFACE
#ifdef COLORBLIND
		snprintf(colorblind_text, 4, "#%d#", turn[x]);
	    printText(colorblind_text, (x * 6) + 1, (*pos * 2) + 4, turn[x], BLACK);
#else
	    printText("###", (x * 6) + 1, (*pos * 2) + 4, turn[x], BLACK);
#endif
#endif
	} else if (intro == 'q' || intro == 'Q') {//exit
	    s1 = s2 = 0;
	    *f = 99;
	    break;
	} else if (intro == 'X' && s1 == 0) {/*backgate: trick for winning
					      * always, and of course, ehem,
					      * for DEBUGGING purposes*/
	    s1 = 1;
	} else if (intro == 'T' && s1 == 1 && s2 == 0) {
	    s2 = 1;
	} else if (intro == 'O' && s1 == 1 && s2 == 1) {
	    s1 = s2 = 0;
	    char txt[5];
	    int cont2;
	    for (cont2 = 0; cont2 <= 3; cont2++)
		txt[cont2] = guess[cont2] + 48;
	    txt[4] = '\0';
#ifdef CURSORS_INTERFACE
	    printText(txt, 70, sizeY(), WHITE, BLACK);
#endif
	} else if (intro == '\n' && turn[cont] != 0) {/*user press RETURN,
							* means he has
							* finished entering an
							* input*/
	    s1 = s2 = 0;//resets debugging state machine
	    x++;//to the next input in the turn
	    cont++;
	} else if (intro == 127) {//undoes previous input
	    s1 = s2 = 0;
	    //clears current turn
	    turn[x] = 0;
#ifdef CURSORS_INTERFACE
	    printText("   ", getX(), getY(), BLACK, BLACK);
#endif
	    //undoes turn
	    if (cont == 0)/*if it happens to be the first input in present
			   * turns, it doesn't undoes anything*/
		continue;
	    cont--;
	    x--;
	} else
	    s1 = s2 = 0;//resets state machine
    }
    aim(guess, turn, pos, win);
    *pos = *pos + 1;//changes for the next turn
}

#define WIN -1
#define LOSE 0
#define TIE 1

/*GIVES A CODE, DEPENDING ON THE LAST TURN INPUT*/
void aim(int guess[], int turno[], int *pos, int *skill) {
    int cont1, cont2, x = 0, index;
    int luck[4] = {LOSE}, array[4] = {0}, flag[4] = {0};
    
    for (cont1 = 0; cont1 <= 3; cont1++)
	if (guess[cont1] == turno[cont1])/*player got correct number and
					  * position*/
	    if(flag[cont1] != 1) {
		flag[cont1] = 1;
		luck[cont1] = WIN;
	    } else
		for (cont2 = 0; cont2 <= 3; cont2++) {
		    if (guess[cont1] == turno[cont2] &&
			        flag[cont2] != 1) {
			flag[cont2] = 1;
			luck[cont2] = WIN;
			break;
		    }
		} else //just got right numbers, not their positions
	    for (cont2 = 0; cont2 <= 3; cont2++)
		if(guess[cont1] == turno[cont2] &&
		   flag[cont2] != 1) {
		    flag[cont2] = 1;
		    luck[cont2] = TIE;
		    break;
		}

    /*Randiomizes indices, so resulting codes won't have relation with the
     * order in which numbers were entered*/
    for (cont1 = 0; cont1 <= 3; cont1++) {
	index = rand() % 4 + 1;
	while (array[0] == index || array[1] == index ||
	       array[2] == index || array[3] == index)
	    index = rand() % 4 + 1;
	array[cont1] = index;
#ifdef CURSORS_INTERFACE
	printText((luck[index - 1] == LOSE ?
		   "   " : "###"),
		  (x * 6) + 30,
		  (*pos * 2) + 4,
		  (luck[index - 1] == WIN ?
		   YELLOW : (luck[index - 1] == TIE ?
			     WHITE : BLACK)),
		  BLACK);
#endif
	x++;
    }
    
    if (luck[0] == WIN &&
	luck[1] == WIN &&
	luck[2] == WIN &&
	luck[3] == WIN)
	
	*skill = 1;//Winner
    else
	*skill = 0;//Not yet
}

/*DECIDES IF PLAYER WON THE GAME OR NOT*/
void whathappens(int master[], int turn, int win) {
#ifdef CURSORS_INTERFACE
    getKey();//waits before erasing - TOO TIED TO INTERFACE!!
#endif
    if(win == 1)
	winner(turn);
    else
	looser(master);
#ifdef CURSORS_INTERFACE
    getKeyPrompt("", 1, sizeY());//waits...
#endif
}
