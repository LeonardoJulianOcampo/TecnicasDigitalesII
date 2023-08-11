#include "tpo-remoto.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#define OPTIONS 9


void exit_menu(void){
	int fd = open_port("/dev/ttyUSB0",115200);
	
	char cadena_salida[]={"888888"};

	for(int i=0;i<5;i++){
		write_port(fd,cadena_salida,sizeof(cadena_salida));
		napms(1);
	}
	close(fd);
}



void menu_efectos(WINDOW *win){
	int op,row,col,wcol,wrow;
	int fd;
	static int i=0;
	int exit = 0;
	char c[] = "A";
	char salida[] = "999998";
	char title[] = "MENU DE EFECTOS";
	char options[OPTIONS][30] = {"La carrera",
				     "Choque",
				     "Auto fantástico",
				     "Apilada",
				     "Sirena",
				     "Move",
				     "SOS",
				     "Ráfaga",
				     "Salir"};
	getmaxyx(stdscr,row,col);
	clear();
	getmaxyx(win, wrow, wcol);
	nodelay(stdscr,TRUE);

	wclear(win);
	box(win,0,0);
	mvwprintw(win,2,(wcol - strlen(title))/2,title);
	mvwprintw(win,18,2,"ENTER: Seleccionar Opcion. UP/DOWN: cambiar opcion");
	wrefresh(win);

	while(!exit){
		
		box(win,0,0);
		mvwprintw(win,2,(wcol - strlen(title))/2,title);
		mvwprintw(win,18,2,"ENTER: Seleccionar Opcion. UP/DOWN: cambiar opcion");
		wrefresh(win);

		for (int i = 0; i < OPTIONS; i++) {
            		if (i == counter(-1,0,OPTIONS)) {
                		wattron(win,A_STANDOUT); // Resaltar opción seleccionada
		                mvwprintw(win,(wrow-9) / 2 + i + 1, (wcol - strlen(options[i])) / 2, "%s", options[i]);
                		wattroff(win,A_STANDOUT);
            		} else {
                		mvwprintw(win,(wrow-9) / 2 + i + 1, (wcol - strlen(options[i])) / 2, "%s", options[i]);
			}
        	}

		wrefresh(win);
		op = getch();
    		

		//el siguiente if debería emitir un caracter cada 200ms (0.2 segundos) a fines de no bloquear a la función read en 
		//menu_efectos_remoto en el programa local
		if(i == 15000){
			fd = open_port("/dev/ttyUSB0",115200);
			write_port(fd,c,sizeof(c));
			i=0;
			napms(150);
			close(fd);
		}	

		i++;

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
					wclear(win);
					lacarrera(win);
					wclear(win);
					break;
				case 1: 
					wclear(win);
					wrefresh(win);
					choque(win);
					wclear(win);
					break;
				case 2: 
					wclear(win);
					wrefresh(win);
					autofan(win);
					wclear(win);
					break;
				case 3: 
					wclear(win);
					wrefresh(win);
					apilada(win);
					wclear(win);
					break;
				case 4:
					wclear(win);
					wrefresh(win);
					sirena(win);
					wclear(win);
					break;
				case 5: 
					wclear(win);
					wrefresh(win);
					mov(win);
					wclear(win);
					break;
				case 6:
					wclear(win);
					wrefresh(win);
					cont_binario(win);
					wclear(win);
					break;

				case 7:
					wclear(win);
					wrefresh(win);
					flashh(win);
					wclear(win);
					break;
				case 8:	
					exit_menu();
					close(fd);
					exit = 1;
					break;
				default: break;


			}
			nodelay(stdscr,TRUE);
			wrefresh(win);
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
nodelay(stdscr,FALSE);
}
