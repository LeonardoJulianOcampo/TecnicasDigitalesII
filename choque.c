#include "tpo.h"
#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <pigpio.h>
#define tiempo    100000

/*
int leds[7];
int matrizA[7];
int matrizB[7];

int ida=128;
int vuelta=2;
int i,j,k;
int ch;
*/

void choque(void){
	
	int leds[8];
	int matrizA[8];
	int matrizB[8];
	int resultado;
	int ida=128;
	int vuelta=1;
	int i,j;
	int ch;


    gpioInitialise();
    nodelay(stdscr,TRUE);


    while(ch != KEY_F(2)){    
        
        ch=getch();
        
        ida    = 128;
        vuelta =   1;
	resultado = 0;
        	
        for(i=0;i<=7;i++){
		resultado = ida + vuelta;
		itob(resultado,leds);
		interfaz(leds);
		ida    =    ida >> 1;
            	vuelta = vuelta << 1;
            	gpioDelay(tiempo);
        }
    }

	for(i=0;i<=7;i++){
		leds[i] = 0;
	}
	interfaz(leds);
	gpioTerminate();
	refresh();
	nodelay(stdscr,FALSE);
}
