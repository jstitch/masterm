MasterMind 1.1.1b
=================

*by Javier Novoa C.*


**MasterMind** is a game I've been developing since my school
days. Occasionally (sometimes separated literally by periods of years)
I maintain and upgrade it's capabilities. Since 1.1 I'm intending to
not let it rot by time.

The most recent changes (which led to v1.1) finally made me program the port
to GNU/Linux using the curses library. Originally the program was done for
MS-DOS with the conio library, and developed, compiled and debugged through
Borland C++ 3.1 IDE. Now I've used MAKE, GCC and GDB as main developing tools
(and no IDE!), which means a great evolution (for me at least). By the way,
I've used these tools on Linux 2.6.22, on an OpenSuSe 10.3 distribution.

Please mind that **MasterMind** was originally written from a spanish
language perspective, so the interface of the program was originally
written in that language. One of the TODOs in my list is to write a
good localization support for it, so that this won't be a problem any
more. The purpose of version 1.1.1 is to implement that localization
support. But even though this fact, I consider the interface to be
pretty simple, so it shouldn't be a problem learning to use it by
simple experimentation, at least until an english interface is
actually implemented.

**MasterMind** is free/opensource software under the GNU General
Public License v2, so please read the *LICENSE* file that is included
with this distribution for information on
modification/distribution/general questions about licensing.

For information on compiling, installing and running, there is an
*INSTALL* file.

For information on how to use the program, please read the online help
provided within the program itself (as I said, in spanish for the current
release).

For hackers, there's additional information on the *TODO* file. You
may also be interested in the *BUGS* file.

There is also a *HISTORY* file with the historic data for the program.


CONTENTS
--------

This distribution of Masterind includes the following files:

- README this readme file
- LICENSE licensing information
- INSTALL information on compiling and running the program
- HISTORY historical information on the program
- TODO things pending to-do and hackers general help file
- BUGS bugs reported and found to be still living in the code
- Makefile the makefile to build the project with MAKE
- masterm.c the main source file in C
- masterm.h the main header file
- cursors.h the cursors interface 'main' file
- curstextlib.h the cursors interface header file
- languages.h adds a basic translation system and an english
  translation


FEEDBACK
--------

The current maintainer of **MasterMind** is Javier Novoa C., you can
contact him at his email at jstitch@gmail.com or via msn IM at
naranjamecanica00@hotmail.com (also via GoogleTalk IM through the same
Gmail account)



Mexico city
23/january/2009
