/*
  LANGUAGES.H
  july 11 2009
  Javier Novoa C.
  
  MasterMind game
  localization library
	
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

#ifdef LOCALE_TRANSLATION
#include <libintl.h>
#define __(String) String
#endif

//Program strings
char * programTitle = __("MasterMind");
char * versionNumber = __("1.1");
char * author = __("Javier Novoa C.");
char * authorNick = __("JStitch");
char * authorEmail = __("jstitch@gmail.com");

char * lastUpdateDate = __("July 11");
char * lastUpdateYear = __("2009");

char * aboutCopyleft = __("Copyleft 1998");
char * aboutCity = __("Mexico, D.F.");
char * aboutPlace = __("Escuela Superior de Computo, ESCOM-IPN");
char * aboutEmail = __("e-mail:");

char * errorMessage = __("ERROR !!!!");

char * menuInst = __("Pick an option:");
char * menuOptInst = __("How to play");
char * menuOptPlay = __("Play");
char * menuOptOptions = __("Options");
char * menuOptAbout = __("About...");
char * menuOptQuit= __("Quit");

char * playInst = __("Can you use logic to guess the secret combination in less than 10 turns?");
char * playInst2 = __("Press 'Q' at any moment to quit");
char * playColor = __("Color ");
char * playPosition = __("Position ");

char * optionsInst = __("Options. Press the number of the option you want to modify, to quit press 'Q'");
char * optionsOpt1 = __(" ALLOW COLOR REPETITIONS EN SECRET COMBINATION (DIFFICULT MODE)");

char * inst1 = __("To start playing, pick option 2 from main menu");
char * inst2 = __("For game options, pick option 3 from main menu");
char * inst3 = __("For game informtation, pick option 4 from main menu");
char * inst4 = __("To quit the game, pick option 5 from main menu");
char * inst5 = __("Press a number between 1 and 6 to pick a color in to the ");
char * inst6 = __("red");
char * inst7 = __("positions:");
char * instRed = __("Red");
char * instGreen = __("Green");
char * instBrown = __("Brown");
char * instBlue = __("Blue");
char * instMagenta = __("Magenta");
char * instCyan = __("Cyan");
char * inst8 = __("When you have each color established, press INTRO.");
char * inst9 = __("You can press BACKSPACE to undo a color in the current turn.");
char * inst10 = __("A code will appear in the ");
char * inst11 = __("blue");
char * inst12 = __("positions:");
char * inst13 = __("  White");
char * inst14 = __(" says that you hit some color");
char * inst15 = __("  Yellow");
char * inst16 = __(" says that you hit also its position");
char * inst17 = __("Empty");
char * inst18 = __(" says you have nothing");
char * inst19 = __("The order of these colors has no relation with the order of your input");
char * inst20 = __("You have 10 tries, the program will evaluate your performance at the end");
char * inst21 = __("Try to use the least of them.   GOOD LUCK!");

char * aboutAuthor = __("Written by");
char * aboutDate = __("december 9 1998");
char * aboutLastUpdate = __("last update");
char * about1 = __("This program comes with ABSOLUTELY NO WARRANTY. This program is Free Software,");
char * about2 = __("and you may redistribute it only under the terms of the General Public License");
char * about3 = __("as published by the Free Software Foundation, either version 2 or any later");
char * about4 = __("version (always preserving the means by which they made this a free software).");
char * about5 = __("You must have received a file named LICENSE within this program distribution.");
char * about6 = __("If not, please contact the author of this program. For more information, please");
char * about7 = __("read the file named LICENSE or visit the FSF web site at ");
char * about8 = __("http://www.gnu.org/licenses/gpl.html");

char * win1 = __(" C O N G R A T U L A T I O N S !!!! ");
char * win2 = __(" Y O U   W O N ");
char * win3 = __(" WOW!!! in 1 try!! ");
char * win4 = __(" You made it in ");
char * win5 = __(" tries ");

char * result1 = __("Pure luck (or did you cheated?)");
char * result2 = __("You had a lot of luck, but you didn't used logic");
char * result3 = __("You had some luck, try to use logic instead");
char * result4 = __("You had luck, use logic instead");
char * result5 = __("You make an excellent use of logic, CONGRATULATIONS!");
char * result6 = __("You make good use of logic, CONGRATULATIONS!");
char * result7 = __("You make good use of logic");
char * result8 = __("You make use of logic, but you can improve it");
char * result9 = __("You make a bad use of logic, practice a little more");
char * result10 = __("You have an awful use of logic, practice a lot more");

char * loose1 = __("YOU LOST =_-(");
char * loose2 = __("Correct answer was:");
char * loose3 = __("Practice a lot more");

char * final = __(" G O O D B Y E!!! ");
