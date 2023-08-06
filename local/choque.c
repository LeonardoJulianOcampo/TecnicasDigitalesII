#include "tpo.h"
#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <pigpio.h>


void choque(WINDOW *win){
	
	int leds[8];
	int matrizA[8];
	int matrizB[8];
	int resultado;
	int ida=128;
	int vuelta=1;
	int i,j;
	int ch;
	int pigpioInitialized=0;

    gpioInitialise();

    if(gpioInitialise()>=0)
            pigpioInitialized = 1;
    else 
            pigpioInitialized = 0;

    nodelay(stdscr,TRUE);                          //para que no espere a que se presione F2

    // Crear un nuevo hilo para leer el teclado
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, read_keyboard, NULL);



    while(!s && pigpioInitialized){    
        
        
        ida    = 128;
        vuelta =   1;
	resultado = 0;
	


        for(i=0;i<=7;i++){
		resultado = ida + vuelta;
		itob(resultado,leds);
		interfaz(leds);
		ida    =    ida >> 1;
            	vuelta = vuelta << 1;
            	gpioDelay(time_factor);
        }

	print_efecto(win,1,control_flag);
	wrefresh(win);
    }

	for(i=0;i<=7;i++){
		leds[i] = 0;
	}
	


    // Detener el hilo de lectura del teclado
    keep_reading = false;
    pthread_join(thread_id, NULL);

        
    interfaz(leds);
    gpioTerminate();
    wrefresh(win);
    nodelay(stdscr,FALSE);
    keep_reading = true;
    last_key = ERR;
    s = 0;
    pthread_cancel(thread_id);

}
