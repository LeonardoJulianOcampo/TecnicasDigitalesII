/*no recibe ningun valor. Imprime las opciones disponibles. Cuando se selecciona un valor correcto
 se devuelve ese valor como entero para ser tomado por la funcion 'efecto'
 */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#define OPTIONS 4

int counter(int select){
	static int count = 0;
	if (select == 1 && count < OPTIONS)
		count ++;
	else if (select == 1 && count >= OPTIONS)
		count = 0;
	else if (select == 0 && count > 0)
		count = count--;
	else if (select == 0 && count == 0)
		count = OPTIONS - 1;
	else 
		count = count;


	return count;
}



int menu(void){
	
	int op,row,col;
	int exit = 0;
	char mesg[]="MENU PRINCIPAL";
	char mesg_efecto[]="Primer item";

	initscr();                                 // inicializa el modo curses
	getmaxyx(stdscr,row,col);                    // obtiene el máximo valor de filas y columnas de la ventana actual
	raw();                                     
	keypad(stdscr,TRUE);
	noecho();
	nodelay(stdscr,TRUE);
	
	while(!exit){
		
		mvprintw(row    ,(col-strlen(mesg))/2,"-> %s",mesg);
		mvprintw(row + 2,(col-strlen(mesg_efecto))/2 + 2,"%s",mesg_efecto);
		refresh();
		op = getch();

		switch(op){
			
			case KEY_UP: 
				clear();
				mvprintw(counter(1)*2,(col-strlen(mesg))/2,"->");
				refresh();
				break;
			case KEY_DOWN:
				clear();
				mvprintw(counter(0)*2,(col-strlen(mesg))/2,"->");
				refresh();
				break;
			case KEY_F(2):
				clear();
				refresh();
				exit = 1;
				break;
				
		}
		
	}	
	endwin();
	
	return 0;

}
