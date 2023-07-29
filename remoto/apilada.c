#include "tpo-remoto.h"
#include <stdio.h>
#include <stdbool.h>
#include <ncurses.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#define tiempo 100000
#define elements 7

 // Variable global para indicar si el hilo de lectura del teclado debe seguir ejecutándose
bool keep_reading = true;
// Variable global para almacenar la última tecla presionada
int last_key = ERR;
int time_factor=10000;
int s = 0;
int fd;

char time_factor_converted[elements];



void apilada(WINDOW *win){

    nodelay(stdscr,TRUE);                          //para que no espere a que se presione F2


    // Crear un nuevo hilo para leer el teclado
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, read_keyboard, NULL);

    fd = open_port("/dev/ttyUSB0",9600);
        
	while(!s){	
		sprintf(time_factor_converted,"%d",time_factor);                       // convierto time_factor que es un entero a una cadena de caracteres
		write_port(fd,time_factor_converted,sizeof(time_factor_converted));    //escribo en el puerto serie time_factor
		print_efecto(win,0);                                                   // imprimo en pantalla el efecto actual y la velocidad
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
    close(fd);
}
