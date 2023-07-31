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

bool control_flag = true;

// Variable global para almacenar la última tecla presionada
int last_key = ERR;
uint32_t time_factor=10000;
int s = 0;




void delaynprint(uint32_t delay_time, WINDOW *win){
	int i =0;

	while(i<=delay_time){
		wrefresh(win);
		if (s==1) break;          //en caso de que se haya detectado la tecla F2 se rompe el bucle
		print_efecto(win,3);
		gpioDelay(100);          //espera 100 us por ciclo
		i ++;

	}

}



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

    nodelay(stdscr,TRUE);                          //para que getch no espere enter luego de leer el teclado


    // Crear un nuevo hilo para leer el teclado (solo para el caso de modo local)

    pthread_t thread_id;

    if (control_flag == true){
    	pthread_create(&thread_id, NULL, read_keyboard, NULL);      // 
    }else{
	pthread_t thread_id;
	pthread_create(&thread_id,NULL, read_s_port,NULL);
    } 

    for (i = 0; i < 8; i++) {
        leds[i] = 0;
        aux[i] = 0;
        }

        interfaz(leds);
    
        while(!s && pigpioInitialized){

	print_efecto(win,3);
	wrefresh(win);

        if(ciclos == 0){
            leds[ciclos]=1;
            delaynprint(time_factor,win);
            for (k = 0; k <= 7; k++){
                aux[k]=0;
            }
        interfaz(leds);
	delaynprint(time_factor,win);
        leds[ciclos]=0;
        interfaz(leds);
        delaynprint(time_factor,win);
        ciclos = 7;   
        }
	
	print_efecto(win,3);
	if(s==1)
		break;

        valor = 128;
        itob(valor,leds);
        delaynprint(time_factor,win);
      	wrefresh(win); 
            for(k=0;k<=7;k++)
                leds[k]=leds[k] || aux[k];
            interfaz(leds);
            delaynprint(time_factor,win);
       	    wrefresh(win);           
            for(i=0;i<=ciclos;i++){
                valor = valor >> 1;              // a valor lo desplazo en una unidad hacia la derecha
                itob(valor,leds);
                   
	    for(k=0;k<=7;k++)
                leds[k]=leds[k] || aux[k];  // OR bit a bit entre los elementos de leds y aux
                
                interfaz(leds);
		print_efecto(win,3);
		wrefresh(win);
                delaynprint(time_factor,win);
            }
            wrefresh(win);
            leds[ciclos]=0;
            interfaz(leds);
            delaynprint(time_factor,win);
      	    wrefresh(win);
            leds[ciclos]=1;
            interfaz(leds);
            delaynprint(time_factor,win);
	    wrefresh(win);
            ciclos --;                          // decremento en una unidad la variable ciclos
            
	    if (s==1)
		    break;

            for(int k=0;k<=7;k++){              // ciclo para cargar el ultimo valor de valor en buffer 
                aux[k]=leds[k] || aux[k];
            }
  

    }
        
    
    for(i=0;i<8;i++)                        // Una vez que se rompe el ciclo se apagan los leds 
      leds[i]=0;

    // Detener el hilo de lectura del teclado. Ocurre tanto para el modo local como para el modo remoto
    keep_reading = false;
    pthread_join(thread_id, NULL);
    pthread_cancel(thread_id);
        
    interfaz(leds);
    gpioTerminate();
    refresh();
    wrefresh(win);
    nodelay(stdscr,FALSE);
    keep_reading = true;
    last_key = ERR;
    s = 0;

}
