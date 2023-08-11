#include "tpo.h"
#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <pigpio.h>
#include <stdint.h>
#include <pthread.h>



void lacarrera(WINDOW *win){

int led1=128;
int led2=128;
int aux =0  ;
int leds[8] ;
int i=0     ;
int ch;
int row, col;
int pigpioInitialized = 0;
int current_time_factor = 10000;
int salir = 0;

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
 

while(!salir && pigpioInitialized){
	
	led1 = 128;
	led2 = 128;

  pthread_mutex_lock(&t_factor_mutex);
  current_time_factor = time_factor;
  salir = s;
  pthread_mutex_unlock(&t_factor_mutex);

	
    while (led1 <= 128 && led1 >= 8 ) {
        aux = led1 | led2;
        itob(aux, leds);
        interfaz(leds);
        if(delaynprint(current_time_factor,win,EFECTO_LACARRERA)){salir=1;break;}
        led1 = led1 >> 1;
    }

    print_efecto(win,EFECTO_LACARRERA,control_flag);
    wrefresh(win);

    if(s==1)
    	break;

    while (led1 >= 1 && led1 <8) {
        led2 = led2 >> 1;
        aux = led1 | led2;
        itob(aux, leds);
        interfaz(leds);
        if(delaynprint(current_time_factor/2,win,EFECTO_LACARRERA)){salir=1;break;}
	      led1 = led1 >> 1;
	      led2 = led2 >> 2;
        aux = led1 | led2;
      	itob(aux,leds);
      	interfaz(leds);
      	if(delaynprint(current_time_factor/2,win,EFECTO_LACARRERA)){salir=1;break;}	
    }

 }

for(i=0;i<8;i++) // Una vez que se rompe el ciclo se apagan los leds 
leds[i]=0;

// Detener el hilo de lectura del teclado
keep_reading = false;
pthread_join(thread_id, NULL);


interfaz(leds);
gpioTerminate();
wrefresh(win);
nodelay(stdscr,FALSE);
keep_reading = true;
last_key = ERR;
salir = 0;
s = 0;
pthread_cancel(thread_id);

}

