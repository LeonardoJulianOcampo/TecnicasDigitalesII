#include <stdio.h>
#include <pigpio.h>
#include <ncurses.h>
#include <stdlib.h>
#include "tpo.h"

// Variable global para indicar si el hilo de lectura del teclado debe seguir ejecutándose
bool keep_reading = true;
// Variable global para almacenar la última tecla presionada
int last_key = ERR;
uint32_t time_factor = 10000;
int s = 0;





int main(){
int op;

op=1;

	if(contrasenia()==1){	
			while(op){
				menu();
				break;
			}
}
return 0;
}
