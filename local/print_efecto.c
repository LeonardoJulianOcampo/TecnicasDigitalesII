#include "tpo.h"
#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <pigpio.h>
#include <stdint.h>
#include <pthread.h>
#include <string.h>




void print_efecto(WINDOW *win,int op,bool local_mode){
	int wrow,wcol;	
  char title_remoto[]="MODO REMOTO ACTIVADO";	
	char   efecto[8][30] = {"La carrera",
				"Choque",
				"Auto fantástico",
				"Apilada",
				"Sirena",
				"Move",
				" ",
				" ",
				     };

	const float min_input = 10000.0;
  const float max_input = 400000.0;
  const float min_output = 0.1;
  const float max_output = 10.0;
	float input_value = (float)time_factor;
  float output_value = (input_value - min_input) * (max_output - min_output) / (max_input - min_input) + min_output;


  if (local_mode){
    box(win,0,0);
    mvwprintw(win,2 ,2,efecto[op]);
    mvwprintw(win,4 ,2,"Velocidad: %.2f",output_value);
    mvwprintw(win,18,2,"F2: Salir. UP/DOWN: Cambiar vel.");
    wrefresh(win);
  }
  else{
		box(win,0,0);
		mvwprintw(win,2,(wcol - strlen(title_remoto))/2,title_remoto);
		mvwprintw(win,18,2,"F2 para volver.");
    wrefresh(win);
  }
    
}
