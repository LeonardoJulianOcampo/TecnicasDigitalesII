#include "tpo-remoto.h"
/* #include <stdio.h>
#include <stdbool.h>
#include <ncurses.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h> */


#define tiempo 100000
#define elements 7

 // Variable global para indicar si el hilo de lectura del teclado debe seguir ejecutándose
bool keep_reading = true;
// Variable global para almacenar la última tecla presionada
int last_key = ERR;
int time_factor=10000;
int current_time_factor=10000;
int s = 0;
int fd;

uint8_t key;
uint8_t key_acceso='1';
char time_factor_converted[elements];
char current_key;

void apilada(WINDOW *win){

    nodelay(stdscr,TRUE);                          //para que no espere a que se presione F2

    // Crear un nuevo hilo para leer el teclado
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, read_keyboard, NULL);


    fd = open_port("/dev/ttyUSB0",9600);
    
    write_port(fd,&key_acceso,sizeof(key_acceso));                                                                   //clave de acceso para poder acceder a la funcion correspondiente en el modo local.
    napms(10);     

	while(!s){

		pthread_mutex_lock(&key_mutex);
		current_key = key;
		current_time_factor = time_factor;
		pthread_mutex_unlock(&key_mutex);
		
		
		snprintf(time_factor_converted,sizeof(time_factor_converted),"%d",time_factor);               // convierto time_factor que es un entero a una cadena de caracteres y la concateno con el caracter key
		write_port(fd,time_factor_converted,sizeof(time_factor_converted));    //escribo en el puerto serie time_factor + caracter de teclado
		napms(3);			

		print_efecto(win,3);                                                   // imprimo en pantalla el efecto actual y la velocidad

		//mvwprintw(win,5,2,"%s\n",time_factor_converted);

		wrefresh(win);
	}
    // Detener el hilo de lectura del teclado
    memset(time_factor_converted,0,sizeof(time_factor_converted));
    write_port(fd,time_factor_converted,sizeof(time_factor_converted));

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
