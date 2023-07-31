/*no recibe ningun valor. Imprime las opciones disponibles. Cuando se selecciona un valor correcto
 se devuelve ese valor como entero para ser tomado por la funcion 'efecto'*/

#include "tpo.h"

#define OPTIONS 3

#define WCLINES 20
#define WCCOLS  60

#define WCX     4
#define WCY     4

bool control_flag = true;

void menu(void) {
    int op, row, col,wcol,wrow;
    int i;
    int exit = 0;
    char mesg[] = "   MENU PRINCIPAL   ";
    char options[OPTIONS][30] = {
        "Selección de Efectos",
        "Ajustes             ",
	"Salir               ",
    };
    initscr();
    raw();
    keypad(stdscr,TRUE);
    noecho();
    nodelay(stdscr, FALSE); // Importante para que getch() espere a que se presione una tecla
    curs_set(0);

    getmaxyx(stdscr,row,col);

    WINDOW * win_corner = subwin(stdscr, WCLINES, WCCOLS, 10, 10);
    
    control_flag = true;

    getmaxyx(win_corner, wrow, wcol);

    while (!exit) {
        clear();
	box(win_corner,0,0);
        mvwprintw(win_corner,2,(wcol-strlen(mesg))/2, mesg);
	mvwprintw(win_corner,18,2,"ENTER: Seleccionar Opcion. UP/DOWN: cambiar opcion");
	wrefresh(win_corner);

    mvwprintw(win_corner,17,2,"control_flag: %d",control_flag);
		
        for (i = 0; i < OPTIONS; i++) {
            if (i == counter(-1,0,OPTIONS)) {
                wattron(win_corner,A_STANDOUT); // Resaltar opción seleccionada
                mvwprintw(win_corner,(wrow-5) / 2 + i + 1, (wcol - strlen(options[i])) / 2, "%s", options[i]);
		wattroff(win_corner,A_STANDOUT);
            } else {
                mvwprintw(win_corner,(wrow-5) / 2 + i + 1, (wcol - strlen(options[i])) / 2, "%s", options[i]);
	    	
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
			menu_efectos(win_corner);
			i = counter(-1,1,OPTIONS);
		}
		else
			menu_ajustes(win_corner); 
                	refresh();
                break;
            default:
                break;
        }
    }
    endwin();
}


