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
void salir(void);

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
    if(has_colors()) {
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
    
    while(1) {
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
    salir();//good-bye
}

/*MAIN MENU SCREEN*/
void mscreen(void) {
    title();
    printText("Elige una opcion:", 1, 5, WHITE, BLACK);
    printText("1 Instrucciones", 2, 8, WHITE, BLACK);
    printText("2 Jugar", 2, 11, WHITE, BLACK);
    printText("3 Opciones", 2, 14, WHITE, BLACK);
    printText("4 Acerca de...", 2, 17, WHITE, BLACK);
    printText("5 Salir", 2, 20, WHITE, BLACK);
}

/*GAME'S MAIN SCREEN*/
void screen(void) {
    int cont;
    
    title();
    printStyleText("Puedes usar la logica para adivinar la combinacion en menos de 10 turnos?",
		   SUBTITLE_TEXT);
    printStyleText("Para salir en cualquier momento teclea 'Q'",
		   STATUS_TEXT);
    
    for(cont = 5; cont <= 23; cont += 2) {
	printText("___   ___   ___   ___",
		  1, cont,
		  LIGHTRED, BLACK);//user input spaces
	printText("___   ___   ___   ___",
		  30, cont,
		  LIGHTBLUE, BLACK);//game answers spaces
    }
    
    /*(Help system) keys corresponding to each color*/
    printText("Color ", 65, 6, WHITE, BLACK);
    printText("###", 71, 6, WHITE, BLACK);
    printText("Posicion ", 62, 8, WHITE, BLACK);
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
	printStyleText("Opciones. Teclea el numero de la opcion que quieres modificar, 'Q' para salir",
		       SUBTITLE_TEXT);
	
	printText("1 ", 1, 7, WHITE, BLACK);
	if (norepit == 1)
	    printText("_", 3, 7, WHITE, BLACK);
	else
	    printText("X", 3, 7, WHITE, BLACK);
	printText(" PERMITIR REPETIR COLORES EN LA COMBINACION SECRETA",
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
    printStyleText(" M a s t e r M i n d ", TITLE_TEXT);
}

/*ERROR SCREEN*/
void error(void) {
    title();
    printStyleText("ERROR !!!!", MESSAGE_TEXT);
    doBeep();
    doBeep();
    getKey();
}

/*QUIT SCREEN*/
void salir(void) {
    title();
    char *bye = " A D I O S!!! ";
    printText(bye, centerX(bye), centerY(bye), YELLOW, BLUE);
    printText("Javier Novoa C.", 1, sizeY(), WHITE, BLUE);
    getKey();//gracias por usar mi programa
}

/*ABOUT SCREEN*/
void about(void) {
    title();
    printText("MasterMind 1.1", 1, 3, YELLOW, BLACK);
    printText("Hecho por JStitch (Javier Novoa)",
	      1, 5, YELLOW, BLACK);//Este soy yo
    printText("9 de diciembre de 1998 (Ultima actualizacion, 23 de enero de 2009)",
	      1, 7, YELLOW, BLACK);
    printText("Escuela Superior de Computo, ESCOM-IPN",
	      1, 9, YELLOW, BLACK);
    printText("Copyleft 1998, 2009, Javier Novoa C., Mexico, D.F.",
	      1, 11, YELLOW, BLACK);
    printText("e-mail: jstitch@gmail.com", 1, 13, YELLOW, BLACK);
    printText("Este programa no incluye NINGUNA GARANTIA. Este programa es Software Libre,",
	      1, 15, YELLOW, BLACK);
    printText("puedes redistribuirlo solo bajo los terminos de la Licencia Publica General de",
	      1, 16, YELLOW, BLACK);
    printText("GNU, version 2 o posterior (siempre y cuando se conserven los principios que",
	      1, 17, YELLOW, BLACK);
    printText("hacen de este programa un software libre). Debiste haber recibido el archivo",
	      1, 18, YELLOW, BLACK);
    printText("LICENSE junto con los archivos de este programa. Si no es asi, comunicate con",
	      1, 19, YELLOW, BLACK);
    printText("el autor del programa. Para mas informacion, lee el archivo LICENSE o visita el",
	      1, 20, YELLOW, BLACK);
    printText("sitio en internet de la FSF http://www.gnu.org/licenses/gpl.html",
	      1, 21, YELLOW, BLACK);
    getKeyPrompt("", 1, sizeY());
}

/*ONLINE INSTRUCTIONS SCREEN*/
void inst(void) {
    title();
    printText("Para jugar elige la opcion 2 del menu",
	      1, 3, WHITE, BLACK);
    printText("Para las opciones del juego elige la opcion 3 del menu",
	      1, 4, WHITE, BLACK);
    printText("Para informacion del juego elige la opcion 4 del menu",
	      1, 5, WHITE, BLACK);
    printText("Para salir del juego elige la opcion 5 del menu",
	      1, 6, WHITE, BLACK);
    
    char *txt1 = "Teclea un numero del 1 al 6 para elegir un color en las posiciones ";
    printText(txt1, 1, 8, WHITE, BLACK);
    printText("rojas", strlen(txt1) + 1, 8, LIGHTRED, BLACK);
    printText(":", strlen(txt1) + 6, 8, WHITE, BLACK);
    
    printText("  1 ", 1, 9, WHITE, BLACK);
    printText("Rojo", 5, 9, RED, BLACK);
    printText("  2 ", 1, 10, WHITE, BLACK);
    printText("Verde", 5, 10, GREEN, BLACK);
    printText("  3 ", 1, 11, WHITE, BLACK);
    printText("Cafe", 5, 11, BROWN, BLACK);
    printText("  4 ", 1, 12, WHITE, BLACK);
    printText("Azul", 5, 12, BLUE, BLACK);
    printText("  5 ", 1, 13, WHITE, BLACK);
    printText("Magenta", 5, 13, MAGENTA, BLACK);
    printText("  6 ", 1, 14, WHITE, BLACK);
    printText("Cyan", 5, 14, CYAN, BLACK);
    
    printText("Cuando tengas cada color establecido teclea INTRO.",
	      1, 15, WHITE, BLACK);
    printText("Puedes teclear BACKSPACE para deshacer un color de la misma jugada.",
	      1, 16, WHITE, BLACK);
    char *txt2 = "Aparecera un codigo en las posiciones ";
    printText(txt2, 1, 18, WHITE, BLACK);
    printText("azules", strlen(txt2) + 1, 18, LIGHTBLUE, BLACK);
    printText(":", strlen(txt2) + 7, 18, WHITE, BLACK);
    
    printText("  Blanco", 3, 19, WHITE, BLACK);
    printText(" dice que le atinaste a algun color",
	      11, 19, WHITE, BLACK);
    printText("  Amarillo", 1, 20, YELLOW, BLACK);
    printText(" dice que le atinaste tambien a su posicion",
	      11, 20, WHITE, BLACK);
    printText("Vacio dice que no tienes nada", 6, 21, WHITE, BLACK);
    printText("Estos colores no se relacionan con el orden de tu entrada",
	      1, 22, WHITE, BLACK);
    printText("Tienes 10 intentos, el programa te calificara de acuerdo a lo bien que jugaste",
	      1, 23, WHITE, BLACK);
    printText("Trata de usar los menos posibles.   SUERTE!",
	      1, 24, WHITE, BLACK);
    getKey();
}

/*WINNER SCREEN*/
void winner(int numero) {
    title();
    printText(" F E L I C I D A D E S !!!! ",
	      20, 5, LIGHTMAGENTA, DARKGRAY);
    printText(" G A N A S T E ", 20, 10, LIGHTMAGENTA, DARKGRAY);
    if(numero == 1)
	printText(" WOW!!! en 1 intento!! ",
		  20, 15, LIGHTMAGENTA, DARKGRAY);
    else {
	printText(" Lo hiciste en ", 20, 15, LIGHTMAGENTA, DARKGRAY);
	char txt[13];
	sprintf(txt, "%d", numero);
	printText(txt, 35, 15, LIGHTMAGENTA, DARKGRAY);
	printText(" intentos ",
		  35 + strlen(txt), 15, LIGHTMAGENTA, DARKGRAY);
    }
    switch(numero) {
	case 1:
	    printText("Pura suerte (o hiciste trampa?)",
		      20, 16, LIGHTMAGENTA, DARKGRAY);
	    break;
	case 2:
	    printText("Has tenido mucha suerte, pero no usas la logica",
		      20, 16, LIGHTMAGENTA, DARKGRAY);
	    break;
	case 3:
	    printText("Has tenido algo de suerte, trata de usar la logica",
		      20, 16, LIGHTMAGENTA, DARKGRAY);
	    break;
	case 4:
	    printText("Has tenido suerte, usa la logica",
		      20, 16, LIGHTMAGENTA, DARKGRAY);
	    break;
	case 5:
	    printText("Haces un excelente uso de la logica, FELICIDADES!",
		      20, 16, LIGHTMAGENTA, DARKGRAY);
	    break;
	case 6:
	    printText("Haces un muy buen uso de la logica, FELICIDADES!",
		      20, 16, LIGHTMAGENTA, DARKGRAY);
	    break;
	case 7:
	    printText("Haces un buen uso de la logica",
		      20, 16, LIGHTMAGENTA, DARKGRAY);
	    break;
	case 8:
	    printText("Haces un uso regular de la logica, trata de mejorar",
		      20, 16, LIGHTMAGENTA, DARKGRAY);
	    break;
	case 9:
	    printText("Haces un mal uso de la logica, practica un poco mas",
		      20, 16, LIGHTMAGENTA, DARKGRAY);
	    break;
	case 10:
	    printText("Tienes un pesimo uso de la logica, practica mas",
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
    printText("PERDISTE =_-(", 19, 5, LIGHTGRAY, BLACK);
    doBeep();
    printText("La respuesta era:", 19, 7, LIGHTGRAY, BLACK);
    
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
    
    printText("Practica mucho mas", 19, 15, WHITE, BLACK);
}
