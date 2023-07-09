#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <pigpio.h>
#define tiempo    100000

int leds[7];
int matrizA[7];
int matrizB[7];

int ida=128;
int vuelta=2;
int i,j,k;
int ch;


void choque(void){

    gpioInitialise();

    initscr();                           //inicializo subrutinas de ncurses
    raw();
    noecho();
    keypad(stdscr,TRUE);
    timeout(1);                          //para que no espere a que se presione F2



    while(ch != KEY_F(2)){    
        
        ch=getch();
        
        ida    = 128;
        vuelta =   1;
        
        itob(ida,matrizA);
        itob(ida,matrizB);   



        for(i=0;i<=6;i++){
            ida    =    ida >> 1;
            vuelta = vuelta << 1;
            
            itob(ida,matrizA);
            itob(ida,matrizB);
            
            for(j=0;j<=6;j++)
                leds[j]=matrizA[j] || matrizB[j];
            
            interfaz(leds,7);
            gpioDelay(tiempo);
        }
    }

}
