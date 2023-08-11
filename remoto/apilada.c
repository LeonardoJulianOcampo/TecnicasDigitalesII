#include "tpo-remoto.h"


#define tiempo 100000
#define elements 6

 // Variable global para indicar si el hilo de lectura del teclado debe seguir ejecutándose
bool keep_reading = true;
// Variable global para almacenar la última tecla presionada
int last_key = ERR;
int time_factor=10000;
int current_time_factor=10000;
int s = 0;
int fd;
int i=0;
uint8_t key;
char key_acceso[elements+1];
char time_factor_converted[elements+1];
char current_key;

void apilada(WINDOW *win){

    nodelay(stdscr,TRUE);                          //para que no espere a que se presione F2

    // Crear un nuevo hilo para leer el teclado
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, read_keyboard, NULL);


    fd = open_port("/dev/ttyUSB0",9600);

    	memset(key_acceso,'9',sizeof(key_acceso));
    	key_acceso[5]='3';
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

		print_efecto(win,EFECTO_APILADA);                                                   // imprimo en pantalla el efecto actual y la velocidad

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

    // Detener el hilo de lectura del teclado
    keep_reading = false;
    pthread_join(thread_id, NULL);

    refresh();
    wrefresh(win);
    nodelay(stdscr,FALSE);
    last_key = ERR;
    s = 0;
    pthread_cancel(thread_id);
    keep_reading = true;
    close(fd);
    
}
