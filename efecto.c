/*esta funcion recibe la opcion desde el menu siendo un entero entre 1 y 8*/
#include <ncurses.h>
#include <stdlib.h>

void efecto(int op){

initscr();
raw();
noecho();
keypad(stdscr,TRUE);

while(op != 0)
  switch(op){
		case 1: 
			printw("\nEfecto: La corrida. Presione F2 para salir.");
			refresh  ();
			lacorrida();
			op=0;       // pongo op=0 para salir del while
			break;
		case 2: 
			printw("\nEfecto: Auto Fantastico. Presione F2 para salir");
			refresh();
			autofan();
			op=0;
			break;
		default: 
			op=0;
			break;	
  }
endwin();
}
