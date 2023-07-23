/*funcion que realiza el efecto de auto fantastico recibe como parametro la velocidad inicial del adc*/ 
#include <ncurses.h>
#include <stdlib.h>
#include <pigpio.h>
#include "tpo.h"

void autofan(void){

int numero=128;
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
clear();


// Crear un nuevo hilo para leer el teclado
pthread_t thread_id;
pthread_create(&thread_id, NULL, read_keyboard, NULL);

for (i = 0; i < 8; i++) {
leds[i] = 0;
}

interfaz(leds);
 

while(!s && pigpioInitialized){
	itob(numero,leds);
	interfaz(leds);
  
  if(numero!=1){
    	numero=numero>>1;
	gpioDelay(time_factor);}
  else
    while(numero!=128){
       	itob(numero,leds);
       	interfaz(leds);
	numero = numero<<1;
       	gpioDelay(time_factor);
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

