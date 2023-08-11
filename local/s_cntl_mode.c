/* Funcion que determina si el control es remoto o no. En caso afirmativo setea la bandera control en 1, que es una variable global que luego es empleada 
 * en las funciones de efectos para determinar si se realiza la lectura del teclado de forma local o si se tiene que leer el puerto serie
 
 */


#include "tpo.h"
#define OPTIONS 2

void s_cntl_mode(WINDOW * win){

	int op,row,col,wcol,wrow;
	int exit = 0;
	char title[] = "Selección de modo local/remoto";
	char options[OPTIONS][30] = {"Modo Local ",
				     "Modo Remoto"};
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
		    case KEY_UP  : counter(0,0,OPTIONS); break;
		    case KEY_DOWN: counter(1,0,OPTIONS); break;
		    case 10:
          switch(counter(-1,0,OPTIONS)){ 
            case 0: 
              wclear(win);
              wrefresh(win);
              control_flag = true; //bandera global de control de modo (1 para modo local)
              exit = 1;
              break;
            case 1: 
              wclear(win);
              wrefresh(win);
              control_flag = false;  //bandera global de control de modo (0 para modo remoto)
              exit = 1;
              break;
            default:
              wclear(win);
              wrefresh(win);
              break;
          }
          wrefresh(win);
          break;
		    case KEY_F(2): exit = 1; break;
		    default: break;
		}
	 

	}
endwin();



}
