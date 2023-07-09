#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <pigpio.h>
#define tiempo    100000


int ciclos = 7;
int leds[8];
int aux[8];
int mascara_on=1;
int mascara_off=0;
int resultante[8]={0};

int valor = 128;
int ch=0;

void apilada(void){
    int i,k;

    itob(valor,leds);                    // convierto valor a binario y lo almaceno en un arreglo
    
    gpioInitialise();

    initscr();                           //inicializo subrutinas de ncurses
    raw();
    noecho();
    keypad(stdscr,TRUE);
    timeout(1);                          //para que no espere a que se presione F2
    

    while(ch != KEY_F(2)){      
        
        ch = getch();

        if(ciclos == 0){
            leds[ciclos]=1;
            gpioDelay(tiempo);
            for (k = 0; k <= 7; k++){
                aux[k]=0;
            }
        interfaz(leds,8);
        gpioDelay(tiempo);
        leds[ciclos]=0;
        interfaz(leds,8);
        gpioDelay(tiempo);
        ciclos = 7;   
        }

        valor = 128;
        itob(valor,leds);
        gpioDelay(tiempo);
        
            for(k=0;k<=7;k++)
                leds[k]=leds[k] || aux[k];
            interfaz(leds,8);
            gpioDelay(tiempo);
            
            for(i=0;i<=ciclos;i++){
                valor = valor >> 1;              // a valor lo desplazo en una unidad hacia la derecha
                itob(valor,leds);
                
                for(k=0;k<=7;k++)
                    leds[k]=leds[k] || aux[k];  // OR bit a bit entre los elementos de leds y aux
                
                interfaz(leds,8);
                gpioDelay(tiempo);
            }
            
            leds[ciclos]=0;
            interfaz(leds,8);
            gpioDelay(tiempo);
            
            leds[ciclos]=1;
            interfaz(leds,8);
            gpioDelay(tiempo);
            ciclos --;                          // decremento en una unidad la variable ciclos
            
            for(int k=0;k<=7;k++){              // ciclo para cargar el ultimo valor de valor en buffer 
                aux[k]=leds[k] || aux[k];
            }
  

    }
        
    
    for(i=0;i<8;i++)                        // Una vez que se rompe el ciclo se apagan los leds 
      leds[i]=0;
  	
      
    printf("\nF2 presionado.Sale.\n "); 
    interfaz(leds,8);
    gpioTerminate();
    refresh      ();
    endwin       ();

}



