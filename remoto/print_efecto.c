#include "tpo-remoto.h"
#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <string.h>




void print_efecto(WINDOW *win,int op){
	int wrow,wcol;	
	
	char   efecto[8][30] = {"La carrera",
				"Choque",
				"Auto fantástico",
				"Apilada",
				"Sirena",
				"Move",
				"SOS",
				"Ráfaga",
				     };

	const float pendiente = -1.0/3900;
	const float offset = 102.56;
	float input_value;
	float output_value;

	input_value = time_factor;
	output_value = (pendiente * input_value) + offset;
	getmaxyx(win,wrow,wcol);

	box(win,0,0);
	mvwprintw(win,(wrow/2)-2,(wcol-strlen(efecto[op]))/2,efecto[op]);
	mvwprintw(win,(wrow/2)  ,(wcol-16)/2,"                  ");
	mvwprintw(win,(wrow/2)  ,(wcol-16)/2,"Velocidad: %.1f %%",output_value);
	mvwprintw(win,18,2,"F2: Salir. UP/DOWN: Cambiar vel.");
	wrefresh(win);
	
}
