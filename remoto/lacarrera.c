#include "tpo-remoto.h"

void lacarrera(WINDOW *win){

int fd;
int i=0;

nodelay(stdscr,TRUE);                          //para que no espere a que se presione F2
wclear(win);


pthread_t thread_id;
pthread_create(&thread_id,NULL, read_keyboard,NULL);


fd = open_port("/dev/ttyUSB0",115200);
memset(key_acceso,'9',sizeof(key_acceso));
key_acceso[5]='0';
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
	
	
	snprintf(time_factor_converted,sizeof(time_factor_converted),"%06d",time_factor);               // convierto time_factor que es un entero a una cadena de caracteres y la concateno con el caracter key
	write_port(fd,time_factor_converted,sizeof(time_factor_converted));    //escribo en el puerto serie time_factor + caracter de teclado
	napms(3);			

	print_efecto(win,0);                                                   // imprimo en pantalla el efecto actual y la velocidad

	//mvwprintw(win,5,2,"%s\n",time_factor_converted);

	wrefresh(win);

	}	

	
	memset(key_acceso,'9',sizeof(key_acceso));
	key_acceso[6]='\0';
	
	i=0;
	while(i<5){
    	write_port(fd,key_acceso,sizeof(key_acceso)); //envio 999999 para el programa local que al leer esto debe salir del efecto actual
	napms(1);
	i++;
	}


	keep_reading = false;
	pthread_join(thread_id,NULL);

	nodelay(stdscr,FALSE);
	keep_reading = true;
	last_key = ERR;
	s = 0;

	pthread_cancel(thread_id);
}



