/*funcion que realiza el efecto de auto fantastico recibe como parametro la velocidad inicial del adc*/ 
#include <ncurses.h>
#include <stdlib.h>

#include "tpo-remoto.h"



void autofan(WINDOW *win){




nodelay(stdscr,TRUE);                          //para que no espere a que se presione F2


// Crear un nuevo hilo para leer el teclado
pthread_t thread_id;
pthread_create(&thread_id, NULL, read_keyboard, NULL);


 

while(!s){
  
	print_efecto(win,2);  
    	wrefresh(win);

    }
    

// Detener el hilo de lectura del teclado
keep_reading = false;
pthread_join(thread_id, NULL);


refresh();
wrefresh(win);
nodelay(stdscr,FALSE);
keep_reading = true;
last_key = ERR;
s = 0;
pthread_cancel(thread_id);

}

