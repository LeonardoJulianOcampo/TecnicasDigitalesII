#include "tpo.h"
#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <pigpio.h>
#include <stdint.h>
#include <pthread.h>



void lacarrera(void){

int led1=128;
int led2=128;
int aux =0  ;
int leds[8] ;
int i=0     ;
int ch;
int row, col;
int pigpioInitialized = 0;


gpioInitialise(); //inicializacion de la libreria pigpio

if(gpioInitialise()>=0)
    pigpioInitialized = 1;
else 
    pigpioInitialized = 0;

nodelay(stdscr,TRUE);                          //para que no espere a que se presione F2
clear();


// Crear un nuevo hilo para leer el teclado
pthread_t thread_id;
pthread_create(&thread_id, NULL, read_keyboard, NULL);

for (i = 0; i < 8; i++) {
leds[i] = 0;
}

interfaz(leds);
 

while(!s && pigpioInitialized){
	
	led1 = 128;
	led2 = 128;

	
    while (led1 <= 128 && led1 >= 8 ) {
        aux = led1 | led2;
        itob(aux, leds);
        interfaz(leds);
        gpioDelay(time_factor);
        led1 = led1 >> 1;
    }

    if(s==1)
	break;

    while (led1 >= 1 && led1 <8) {
	led2 = led2 >> 1;
        aux = led1 | led2;
        itob(aux, leds);
        interfaz(leds);
        gpioDelay(time_factor / 2);
	led1 = led1 >> 1;
	led2 = led2 >> 2;
        aux = led1 | led2;
	itob(aux,leds);
	interfaz(leds);
	gpioDelay(time_factor / 2);	
    }

 }

for(i=0;i<8;i++) // Una vez que se rompe el ciclo se apagan los leds 
leds[i]=0;

// Detener el hilo de lectura del teclado
keep_reading = false;
pthread_join(thread_id, NULL);


interfaz(leds);
gpioTerminate();
refresh();
nodelay(stdscr,FALSE);
keep_reading = true;
last_key = ERR;
s = 0;
pthread_cancel(thread_id);

}

