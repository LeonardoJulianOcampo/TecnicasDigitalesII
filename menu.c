/*no recibe ningun valor. Imprime las opciones disponibles. Cuando se selecciona un valor correcto
 se devuelve ese valor como entero para ser tomado por la funcion 'efecto'*/

#include "tpo.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#define OPTIONS 3

void menu(void) {
    int op, row, col;
    int i;
    int exit = 0;
    char mesg[] = "   MENU PRINCIPAL   ";
    char options[OPTIONS][30] = {
        "Selección de Efectos",
        "Ajustes       ",
	"Salir        ",
    };

    initscr();
    getmaxyx(stdscr, row, col);
    raw();
    keypad(stdscr, TRUE);
    noecho();
    nodelay(stdscr, FALSE); // Importante para que getch() espere a que se presione una tecla
    curs_set(0);

    while (!exit) {
        clear();
        mvprintw(row / 2, (col - strlen(mesg)) / 2, mesg);
	refresh();

		
        for (i = 0; i < OPTIONS; i++) {
            if (i == counter(-1,0,OPTIONS)) {
                attron(A_STANDOUT); // Resaltar opción seleccionada
                mvprintw(row / 2 + i + 1, (col - strlen(options[i])) / 2, "-> %s", options[i]);
                attroff(A_STANDOUT);
            } else {
                mvprintw(row / 2 + i + 1, (col - strlen(options[i])) / 2, "   %s", options[i]);
            }
        }

	op=getch();

        switch (op) {
            case KEY_UP:
                counter(0,0,OPTIONS);
                break;
            case KEY_DOWN:
                counter(1,0,OPTIONS);
                break;
            case 10: // Enter key
                if (counter(-1,0,OPTIONS) == OPTIONS - 1)
                    	exit = 1;
                else if (counter(-1,0,OPTIONS)==0){
			menu_efectos();
			i = counter(-1,1,OPTIONS);
		}
		else
			menu_ajustes(); 
                refresh();
                break;
            default:
                break;
        }
    }

    endwin();

}


