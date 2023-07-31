#include "tpo.h"

#define OPTIONS 7

void menu_efectos(WINDOW *win){
	int op,row,col,wcol,wrow;
	int exit = 0;
	char title[] = "MENU DE EFECTOS";
	char title_remoto[] = "MODO REMOTO ACTIVADO";
	char options[OPTIONS][30] = {"La carrera",
				     "Choque",
				     "Auto fantástico",
				     "Apilada",
				     "Sirena",
				     "Move",
				     "Salir"};
	int         fd    = open_port("/dev/ttyAMA0",115200);			
	uint8_t buffer[1] = {"0"};  	
	int key;

	getmaxyx(stdscr,row,col);
	clear();
	getmaxyx(win, wrow, wcol);

	while(!exit && control_flag == true){
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


	while(!exit && control_flag == false){                         // este bucle es el que se ejecuta cuando el control remoto se encuentra habilitado
	
		bool cont = true;

		clear();                                               // solo despliega una ventana informativa. No permite el control por teclado 
		box(win,0,0);
		mvwprintw(win,2,(wcol - strlen(title_remoto))/2,title_remoto);
		mvwprintw(win,18,2,"F2 para volver.");
		op = getch();

		/********************************************************************************************************************************************************************************************************************
		 * El siguiente bucle se implementa para que se lea constantemente el puerto serie hasta que se envie desde el programa remoto una combinación de caracteres que coincida con la de alguno de los efectos de luces. *
		 * cuando eso suceda se disparará alguna de las funciones de efectos luminosos. Caso contrario, el programa queda esperando a no ser que se vuelva al menu anterior con la tecla F2.                                *
		 ********************************************************************************************************************************************************************************************************************/
		

		while(cont){
		
			read_port(fd,buffer,sizeof(key));	//para la clave solo se emplea un caracter de información
			key = atoi(buffer);                     //convierto el caracter a int
			
			switch (key){
				
				case 1: lacarrera(win); break;
				case 2: choque   (win); break;
				case 3: autofan  (win); break;
				case 4: apilada  (win); break;
				case 5: sirena   (win); break;
				case 6: mov      (win); break;
				case 7: cont =   false; break;    // si se presiona F2 se corta el bucle 
				default: break;

			}
		}

	}


endwin();
}
