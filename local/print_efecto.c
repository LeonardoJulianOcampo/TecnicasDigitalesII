#include "tpo.h"

void print_efecto(WINDOW *win,int op,bool local_mode){
	int wrow,wcol;	
  char title_remoto[]="MODO REMOTO ACTIVADO";	
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

  if (local_mode){
    box(win,0,0);
    mvwprintw(win,(wrow/2)-2,(wcol - strlen(efecto[op]))/2  ,efecto[op]);
    mvwprintw(win,(wrow/2)  ,(wcol-16)/2,"                            ");
    mvwprintw(win,(wrow/2)  ,(wcol-16)/2,"Velocidad: %.1f %%",output_value);
    mvwprintw(win,18,2,"F2: Salir. UP/DOWN: Cambiar vel.");
    wrefresh(win);
  }
  else{
    wclear(win);
    box(win,0,0);
    mvwprintw(win,2,(wcol-strlen(title_remoto))/2,title_remoto);
    mvwprintw(win,(wrow/2)-2,(wcol - strlen(efecto[op]))/2  ,efecto[op]);
    mvwprintw(win,(wrow/2) ,(wcol-16)/2,"                            ");
    mvwprintw(win,(wrow/2) ,(wcol-16)/2,"Velocidad: %.1f %%",output_value);
    mvwprintw(win,18,2,"F2: Salir.");
    wrefresh(win);
  }
    
}

bool delaynprint(uint32_t delay_time, WINDOW *win,int efecto){

  int i = 0;

  while(i<=delay_time/1000){
    if(s==1) return true;
    print_efecto(win,efecto,control_flag);
    wrefresh(win);
    gpioDelay(1000);
    i++;
  }
  return false;
}


