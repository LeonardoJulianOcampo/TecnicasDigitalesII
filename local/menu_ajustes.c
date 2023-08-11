#include "tpo.h"

#define OPTIONS 3



void menu_ajustes(WINDOW *win){
	int op,row,col,wcol,wrow;
	int exit = 0;
	char title[] = "MENU DE AJUSTES";
	char options[OPTIONS][31] = {"   Sel. de modo local/remoto  ",
                  				     "    Condiciones iniciales     ",
                               "            Salir             "};

	getmaxyx(stdscr,row,col);
  clear();
	getmaxyx(win, wrow, wcol);


	while(!exit){
		wclear(win);
		box(win,0,0);
		mvwprintw(win,2,(wcol - strlen(title))/2,title);
		mvwprintw(win,18,2,"ENTER: Seleccionar Opcion. UP/DOWN: cambiar opcion");
    

		for (int i = 0; i < OPTIONS; i++) {
            		if (i == counter(-1,0,OPTIONS)) {
                		wattron(win,A_STANDOUT); // para resaltar opción seleccionada
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
        case KEY_F(2):
          exit = 1;
          break; 

		    case 10: // Enter key
			
			switch(counter(-1,0,OPTIONS)){
			
				case 0: 
					wclear(win);
					wrefresh(win);
					s_cntl_mode(win);
					break;
				case 1: 
					wclear(win);
					wrefresh(win);
					s_intl_cond(win);
					break;

        case 2:
          exit = 1;
				default:
					wclear(win);
					wrefresh(win);
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

