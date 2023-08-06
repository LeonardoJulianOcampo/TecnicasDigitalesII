/*********************************************************************************************
 * funcion que se ejecuta en un hilo paralelo al principal y lee constantemente una trama de *
 * datos de 8 caracteres. El primero indica el estado de lectura de teclado mientras que el  *
 * resto de los caracteres son los digitos que componen a time_factor                        *
 *********************************************************************************************/

#include "tpo.h"

pthread_mutex_t t_factor_mutex = PTHREAD_MUTEX_INITIALIZER;

int readd_port(void){
  int fd;
  char buffer[7];
  int value;  
  fd = open_port("/dev/ttyAMA0",115200); 
  tcflush(fd, TCIFLUSH);
  read(fd,buffer,sizeof(buffer));
  buffer[6]=0;
  value = atoi(buffer);
  close(fd);
  return value;
  

}

void *port_thread(void *arg){
	int tecla = ERR;
  int value;

	while(keep_reading){
	  tecla = getch();	
    time_factor = readd_port();
    if(time_factor == 999999 || tecla == KEY_F(2)) s=1;
    //if(tecla == KEY_F(2)) s=1;
	}

return NULL;

}
