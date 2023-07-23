#include "tpo.h"
#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <pigpio.h>
#include <stdint.h>
#include <pthread.h>
#define tiempo 100000


 // Variable global para indicar si el hilo de lectura del teclado debe seguir ejecutándose
bool keep_reading = true;
// Variable global para almacenar la última tecla presionada
int last_key = ERR;
uint32_t time_factor=10000;
int s = 0;


void apilada(WINDOW *win){
    int i,k;
    int ciclos = 7;
    int leds[8];
    int aux[8];
    int mascara_on = 1;
    int mascara_off = 0;
    int resultante[8]={0};
    int valor = 128;
    int ch=0;
//    int exit = 0;
    int pigpioInitialized = 0;


    itob(valor,leds);                    // convierto valor a binario y lo almaceno en un arreglo
    
    if(gpioInitialise()>=0)
            pigpioInitialized = 1;
    else 
            pigpioInitialized = 0;

    nodelay(stdscr,TRUE);                          //para que no espere a que se presione F2


    // Crear un nuevo hilo para leer el teclado
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, read_keyboard, NULL);

    for (i = 0; i < 8; i++) {
        leds[i] = 0;
        aux[i] = 0;
        }

        interfaz(leds);
    
        while(!s && pigpioInitialized){

	

        if(ciclos == 0){
            leds[ciclos]=1;
            gpioDelay(time_factor);
            for (k = 0; k <= 7; k++){
                aux[k]=0;
            }
        interfaz(leds);
        gpioDelay(time_factor);
        leds[ciclos]=0;
        interfaz(leds);
        gpioDelay(time_factor);
        ciclos = 7;   
        }
	
	print_efecto(win,3);

        valor = 128;
        itob(valor,leds);
        gpioDelay(time_factor);
      	wrefresh(win); 
            for(k=0;k<=7;k++)
                leds[k]=leds[k] || aux[k];
            interfaz(leds);
            gpioDelay(time_factor);
       	    wrefresh(win);           
            for(i=0;i<=ciclos;i++){
                valor = valor >> 1;              // a valor lo desplazo en una unidad hacia la derecha
                itob(valor,leds);
                   
	    for(k=0;k<=7;k++)
                leds[k]=leds[k] || aux[k];  // OR bit a bit entre los elementos de leds y aux
                
                interfaz(leds);
                gpioDelay(time_factor);
      		wrefresh(win);
            }
            wrefresh(win);
            leds[ciclos]=0;
            interfaz(leds);
            gpioDelay(time_factor);
      	    wrefresh(win);
            leds[ciclos]=1;
            interfaz(leds);
            gpioDelay(time_factor);
            ciclos --;                          // decremento en una unidad la variable ciclos
            
            for(int k=0;k<=7;k++){              // ciclo para cargar el ultimo valor de valor en buffer 
                aux[k]=leds[k] || aux[k];
            }
  

    }
        
    
    for(i=0;i<8;i++)                        // Una vez que se rompe el ciclo se apagan los leds 
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
