/*********************************************************************************************
 * funcion que se ejecuta en un hilo paralelo al principal y lee constantemente una trama de *
 * datos de 8 caracteres. El primero indica el estado de lectura de teclado mientras que el  *
 * resto de los caracteres son los digitos que componen a time_factor                        *
 *********************************************************************************************/

#include "tpo.h"

void *port_thread(void *arg){
	int tecla = ERR;
  int value;

	while(keep_reading){
    tecla = getch();	
    time_factor = read_port();
    if(time_factor == 999999 || tecla == KEY_F(2)) s=1;
	}

return NULL;

}
