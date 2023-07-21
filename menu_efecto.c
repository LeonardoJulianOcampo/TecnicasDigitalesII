#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#define OPTIONS 5

void menu_efectos(void){
	int op,row,col;
	int exit = 0;
	char title[] = "MENU DE EFECTOS";
	char options[OPTIONS][30] = {"La corrida",
				     "Choque",
				     "Auto fantástico",
				     "Apilada",
				     "Salir"};

	clear();

	while(!exit){
		clear();
		mvprintw(row/2,(col - strlen(title))/2,title);
 
		for (int i = 0; i < OPTIONS; i++) {
            		if (i == counter(-1)) {
                		attron(A_STANDOUT); // Resaltar opción seleccionada
                		mvprintw(row / 2 + i + 1, (col - strlen(options[i])) / 2, "-> %s", options[i]);
                		attroff(A_STANDOUT);
            		} else {
                mvprintw(row / 2 + i + 1, (col - strlen(options[i])) / 2, "   %s", options[i]);
            		}
        	}

		refresh();
		op = getch();


		switch (op) {
		    case KEY_UP:
			counter(0);
			break;
		    case KEY_DOWN:
			counter(1);
			break;
		    case 10: // Enter key
			
			switch(counter(-1)){
			
				case 0: lacorrida();
					break;
				case 1: choque();
					break;
				case 2: autofan();
					break;
				case 3: apilada();
					break;
				case 4: exit = 1;
					break;


			}

			mvprintw(2, 2, "Opción seleccionada: %s", options[counter(-1)]);
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

}
