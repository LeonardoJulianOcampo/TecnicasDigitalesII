#include "tpo.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#define OPTIONS 7

void menu_efectos(WINDOW *win){
	int op,row,col,wcol,wrow;
	int exit = 0;
	char title[] = "MENU DE EFECTOS";
	char options[OPTIONS][30] = {"La carrera",
				     "Choque",
				     "Auto fantástico",
				     "Apilada",
				     "Sirena",
				     "Move",
				     "Salir"};
	getmaxyx(stdscr,row,col);
	clear();
	getmaxyx(win, wrow, wcol);

	while(!exit){
		clear();
		box(win,0,0);
		mvwprintw(win,2,(wcol - strlen(title))/2,title);
		mvwprintw(win,18,2,"ENTER: Seleccionar Opcion. UP/DOWN: cambiar opcion");


		for (int i = 0; i < OPTIONS; i++) {
            		if (i == counter(-1,0,OPTIONS)) {
                		wattron(win,A_STANDOUT); // Resaltar opción seleccionada
		                mvwprintw(win,(wrow-5) / 2 + i + 1, (wcol - strlen(options[i])) / 2, "%s", options[i]);
                		wattroff(win,A_STANDOUT);
            		} else {
                		mvwprintw(win,(wrow-5) / 2 + i + 1, (wcol - strlen(options[i])) / 2, "%s", options[i]);
			}
        	}

		wrefresh(win);
		op = getch();


		switch (op) {
		    case KEY_UP:
			counter(0,0,OPTIONS);
			break;
		    case KEY_DOWN:
			counter(1,0,OPTIONS);
			break;
		    case 10: // Enter key
			
			switch(counter(-1,0,OPTIONS)){
			
				case 0: 
					clear();
					wrefresh(win);
					lacarrera(win);
					break;
				case 1: 
					clear();
					wrefresh(win);
					choque(win);
					break;
				case 2: 
					clear();
					wrefresh(win);
					autofan(win);
					break;
				case 3: 
					clear();	
					wrefresh(win);
					apilada(win);
					break;
				case 4:
					clear();
					wrefresh(win);
					sirena(win);
					break;
				case 5: 
					clear();
					wrefresh(win);
					mov(win);
					break;
				case 6: exit = 1;
					break;


			}

			wrefresh(win);
			refresh();
			//getch(); // Esperar a que el usuario presione una tecla para continuar
			break;
		    case 27: // Escape key
			exit = 1;
			break;
		    default:
			break;
		}
	 

	}
endwin();
}
