all : masterm.c masterm.h cursors.h curstextlib.h
	gcc masterm.c -W -Wall -lncurses -o masterm -DLOCALEDIR=\"\"
	chmod +x masterm

colorblind : masterm.c masterm.h cursors.h curstextlib.h
	gcc masterm.c -W -Wall -lncurses -o masterm -DLOCALEDIR=\"\" -DCOLORBLIND
	chmod +x masterm

debug : masterm.c masterm.h cursors.h curstextlib.h
	gcc masterm.c -W -Wall -lncurses -o masterm -g
	chmod +x masterm

clean :
	chmod -x *
	rm masterm
	rm *~
