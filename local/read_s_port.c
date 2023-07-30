/*********************************************************************************************
 * funcion que se ejecuta en un hilo paralelo al principal y lee constantemente una trama de *
 * datos de 8 caracteres. El primero indica el estado de lectura de teclado mientras que el  *
 * resto de los caracteres son los digitos que componen a time_factor                        *
 *********************************************************************************************/

#include "tpo.h"

pthread_mutex_t t_factor_mutex = PTHREAD_MUTEX_INITIALIZER;


void *read_s_port(void *arg){
	
	uint8_t buffer[8]={"0"};
	uint8_t tecla = 0;

	while(keep_reading){
		
		read_port(fd,buffer,sizeof(buffer));	
		pthread_mutex_lock(&t_factor_mutex);
		time_factor = (uint32_t)atoi(buffer);
		pthread_mutex_unlock(&t_factor_mutex);
				
	}

return NULL

}
