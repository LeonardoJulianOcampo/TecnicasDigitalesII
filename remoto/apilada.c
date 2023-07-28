#include "tpo-remoto.h"
#include <stdio.h>
#include <stdbool.h>
#include <ncurses.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#define tiempo 100000


 // Variable global para indicar si el hilo de lectura del teclado debe seguir ejecutándose
bool keep_reading = true;
// Variable global para almacenar la última tecla presionada
int last_key = ERR;
uint32_t time_factor=10000;
int s = 0;



void apilada(WINDOW *win){

    nodelay(stdscr,TRUE);                          //para que no espere a que se presione F2


    // Crear un nuevo hilo para leer el teclado
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, read_keyboard, NULL);


        while(!s){
		print_efecto(win,0);
		wrefresh(win);
	    
    
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
