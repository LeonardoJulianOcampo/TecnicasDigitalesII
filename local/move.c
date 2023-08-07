#include <ncurses.h>
#include <stdlib.h>
#include <pigpio.h>
#include "tpo.h"

void mov(WINDOW *win){

int numero=170;
int leds[8]   ;
int i=0       ;
int ch;
int row, col;
int pigpioInitialized = 0;


gpioInitialise(); //inicializacion de la libreria pigpio

if(gpioInitialise()>=0)
    pigpioInitialized = 1;
else 
    pigpioInitialized = 0;

nodelay(stdscr,TRUE);                          //para que no espere a que se presione F2


// Crear un nuevo hilo para leer el teclado
pthread_t thread_id;

if(control_flag)
  pthread_create(&thread_id, NULL, read_keyboard, NULL);
else
  pthread_create(&thread_id, NULL, port_thread, NULL);


for (i = 0; i < 8; i++) {
leds[i] = 0;
}

interfaz(leds);
 

while(!s && pigpioInitialized){
	
	itob(numero,leds);
	interfaz(leds);
 	if(delaynprint(time_factor,win,EFECTO_MOV)){s=1;break;}
	numero = ~numero;
  numero = numero & 255;

 }

for(i=0;i<8;i++) // Una vez que se rompe el ciclo se apagan los leds 
leds[i]=0;

// Detener el hilo de lectura del teclado
keep_reading = false;
pthread_join(thread_id, NULL);


interfaz(leds);
gpioTerminate();
refresh();
wrefresh(win);
nodelay(stdscr,FALSE);
keep_reading = true;
last_key = ERR;
s = 0;
pthread_cancel(thread_id);

}
