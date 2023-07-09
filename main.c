#include <stdio.h>
#include <pigpio.h>
#include <ncurses.h>
#include <stdlib.h>
#include "tpo.h"

int main(){
int op;

op=1;

	if(contrasenia()==1){	
			while(op){
				menu();
				op=0;	
			}
}
return 0;
}
