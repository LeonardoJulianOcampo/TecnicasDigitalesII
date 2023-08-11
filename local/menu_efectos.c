#include "tpo.h"

#define OPTIONS 9

void menu_efectos(WINDOW *win){
	int op,row,col,wcol,wrow;
	int exit = 0;
	char title[] = "MENU DE EFECTOS";
	//char title_remoto[] = "MODO REMOTO ACTIVADO";
	char options[OPTIONS][30] = {"La carrera",
				     "Choque",
				     "Auto fantástico",
				     "Apilada",
				     "Sirena",
				     "Move",
             "SOS",
             "Ráfaga",
				     "Salir"};
	int  fd = open_port("/dev/ttyAMA0",115200);			
	char buffer[7];  	
	int key;
  int tecl;

	getmaxyx(stdscr,row,col);
	clear();
	getmaxyx(win, wrow, wcol);
  


	while(!exit && control_flag){
		wclear(win);
		box(win,0,0);
		mvwprintw(win,2,(wcol - strlen(title))/2,title);
		mvwprintw(win,18,2,"ENTER: Seleccionar Opcion. UP/DOWN: cambiar opcion");

		for (int i = 0; i < OPTIONS; i++) {
            		if (i == counter(-1,0,OPTIONS)) {
                		wattron(win,A_STANDOUT); // Resaltar opción seleccionada
		                mvwprintw(win,(wrow - 9) / 2 + i + 1, (wcol - strlen(options[i])) / 2, "%s", options[i]);
                		wattroff(win,A_STANDOUT);
            		} else {
                		mvwprintw(win,(wrow-9) / 2 + i + 1, (wcol - strlen(options[i])) / 2, "%s", options[i]);
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
                lacarrera(win);
                break;
              case 1: 
                wclear(win);
                wrefresh(win);
                choque(win);
                break;
              case 2: 
                wclear(win);
                wrefresh(win);
                autofan(win);
                break;
              case 3: 
                wclear(win);	
                wrefresh(win);
                apilada(win);
                break;
              case 4:
                wclear(win);
                wrefresh(win);
                sirena(win);
                break;
              case 5: 
                wclear(win);
                wrefresh(win);
                mov(win);
                break;
              case 6:
                wclear(win);
                wrefresh(win);
                sos(win);
                break;
              case 7:
                wclear(win);
                wrefresh(win);
                rafaga(win);
                break;
              case 8: exit = 1; 
                      break;

              default: break;
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


close(fd);
}
