/*
  MASTERM.C v1.1
  january 23 2009
  Javier Novoa C.
  
  MasterMind game
  main routine
  
  december 9 1998 - v1.0 - original first version - Javier Novoa C.
  
  somewhere beyond 1998 and 2006 - v1.0.1 - enhancements in 'instructions' and
  'about' sections from main menu - Javier Novoa C.
  
  january 6 2006 (dia de Reyes) - v1.0.2 - added final evaluation for players
  - Javier Novoa C.
  
  january 23 2009 - v1.1 - port to Linux - Javier Novoa C.
  
  TODO
  
  *separate engine from interface (here in this file and in masterm.h there
  still are clear calls to the current cursors interface)
  
  *test & correct MSDOS' conio library compatibility
  
  *implement localization support for the interface
  
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

#define CURSORS_INTERFACE 1

#include <time.h>
#include "masterm.h"

int main() {
    init();
#ifdef CURSORS_INTERFACE
    menu();
#endif
    finalize();
    return 0;
}

/*MASTERMIND GAME*/
void mastermind(void) {
    int turn;//current turn
    int position = 0;//position in screen - TOO TIED TO INTERFACE!!
    int win = 0;//has player won? 1=yes, 0=no
    int guess[4] = {0};//secret combination for the player to guess
    
#ifdef CURSORS_INTERFACE
    screen();
#endif
    shuffle(guess);
    for(turn = 1; turn <= 10; turn++) {
	play(guess, &position, &turn, &win);
	if(win == 1)/*you won, or you were lucky*/
	    break;
    }
    if(turn != 100)//if turn == 100, they bored, so they left
	whathappens(guess, turn, win);
}
