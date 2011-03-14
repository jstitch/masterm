/*
  UTILS.H
  july 17 2009
  Javier Novoa C.
  
  Utility functions
  
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

#ifndef UTILS_H

#define UTILS_H 1

#include <stdlib.h>
#include <string.h>

char * untrim(char *);

/*Untrims a given string: inserts a space between every character of the string*/
char * untrim (char * str) {
    unsigned int i;
    
    char * nstr = (char *) malloc ((strlen(str) * 2) + 2);
    nstr[0] = '\0';
    
    for (i = 0; i < (strlen(str)); i++) {
	nstr[i * 2] = ' ';
	nstr[(i * 2) + 1] = str[i];
    }
    
    nstr[strlen(str) * 2] = ' ';
    nstr[(strlen(str) * 2) + 1] = '\0';
    
    return nstr;
}

#endif
