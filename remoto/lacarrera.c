#include "tpo-remoto.h"
#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>



void lacarrera(WINDOW *win){

nodelay(stdscr,TRUE);                          //para que no espere a que se presione F2
wclear(win);


pthread_t thread_id;
pthread_create(&thread_id,NULL, read_keyboard,NULL);


while(!s){
	
    	print_efecto(win,0);
    	wrefresh(win);

	}	
	
	keep_reading = false;
	pthread_join(thread_id,NULL);

	nodelay(stdscr,FALSE);
	keep_reading = true;
	last_key = ERR;
	s = 0;

	pthread_cancel(thread_id);
}



