/*funcion que realiza el efecto de auto fantastico recibe como parametro la velocidad inicial del adc*/ 
#include <ncurses.h>
#include <stdlib.h>

#include "tpo-remoto.h"



void autofan(WINDOW *win){

int fd;
int i=0;
nodelay(stdscr,TRUE);                          //para que no espere a que se presione F2

// Crear un nuevo hilo para leer el teclado
pthread_t thread_id;
pthread_create(&thread_id, NULL, read_keyboard, NULL);


fd = open_port("/dev/ttyUSB0",9600);

memset(key_acceso,'9',sizeof(key_acceso));
key_acceso[5]='2';
key_acceso[6]='\0';
i=0;

while(i<5){
write_port(fd,key_acceso,sizeof(key_acceso)); //envio 999999 para el programa local que al leer esto debe salir del efecto actual.
i++;
}

napms(100);
		

while(!s){

	pthread_mutex_lock(&key_mutex);
	current_key = key;
	current_time_factor = time_factor;
	pthread_mutex_unlock(&key_mutex);
	
	
	snprintf(time_factor_converted,sizeof(time_factor_converted),"%06d",time_factor);               // convierto time_factor que es un entero a una cadena de caracteres
	write_port(fd,time_factor_converted,sizeof(time_factor_converted));    //escribo en el puerto serie time_factor
	napms(3);			

	print_efecto(win,EFECTO_AUTOFAN);                                                   // imprimo en pantalla el efecto actual y la velocidad 
    }
   
memset(key_acceso,'9',sizeof(key_acceso));
key_acceso[6]='\0';

i=0;
while(i<5){
	write_port(fd,key_acceso,sizeof(key_acceso)); //envio 999999 para el programa local que al leer esto debe salir del efecto actual
	napms(1);
	i++;
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

