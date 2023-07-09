/*funcion que realiza el efecto de auto fantastico recibe como parametro la velocidad inicial del adc*/ 
#include <ncurses.h>
#include <stdlib.h>
#include <pigpio.h>
#define tiempo    100000

void autofan(void){

int numero=128;
int leds[8]   ;
int i=0       ;
int ch;
int row, col;


gpioInitialise(); //inicializacion de la libreria pigpio


initscr();
raw();
noecho();
keypad(stdscr,TRUE);
timeout(1);       //para que no espere a que se presione F2

while(ch != KEY_F(2)){
  ch = getch();
    itob(numero,leds);
       interfaz(leds,8);
  
  if(numero!=1){
    numero=numero>>1;
   gpioDelay(tiempo);}

  else
    while(numero!=128){

       itob(numero,leds);
       interfaz(leds,8);
      numero = numero<<1;
       gpioDelay(tiempo);
    }
    
 }

     for(i=0;i<8;i++)
      leds[i]=0;
  	printf("\nF2 presionado.Sale.\n "); 
    interfaz(leds,8);
    gpioTerminate();
    refresh      ();
    endwin       ();
}

