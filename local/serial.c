#include "tpo.h"
#define BAUDRATE B115200
#define MODEMDEVICE "/dev/ttyAMA0"

int open_port(const char * device, uint32_t baud_rate){
  
  int result;
	int fd = open(device, O_RDWR | O_NOCTTY);
	if(fd == -1){
		perror(device);
		return -1;
	}

	
	struct termios oldtty,newtty;
	
	result = tcgetattr(fd,&oldtty);
  
	if(result){
		perror("tcgetattr falló");
		close(fd);
		return -1;
	}
	
  bzero(&newtty,sizeof(newtty));


  // Establece la velocidad de BAUDRATE
  cfsetispeed(&newtty,BAUDRATE);
  
  //Establezco el modo no canonico (raw)
  newtty.c_lflag &= (ICANON | ECHO | ECHOE | ISIG);

  //Activa el receptor y el modo local
  newtty.c_cflag |= (CLOCAL | CREAD);

  // puerto configurado para 8N1
	newtty.c_cflag &= ~PARENB;
  newtty.c_cflag &= ~CSTOPB;
  newtty.c_cflag &= ~CSIZE;
  newtty.c_cflag |=  CS8;

  //desactiva el flow control por hardware
  newtty.c_cflag &= ~(CRTSCTS);
  //desactiva el flow control por software. Ignora errores de paridad
  newtty.c_iflag &= ~(IXON | IXOFF | IXANY | IGNPAR);
  //desactivo mapeos de caracteres especiales
  newtty.c_iflag &= ~(INLCR | IGNCR | ICRNL);



	//configuración de los mínimos caracteres a recibir para terminar la lectura del puerto
	newtty.c_cc[VTIME] = 2;
  //configuración del tiempo a esperar por el proximo byte. En este caso el timer esta desactivado
	newtty.c_cc[VMIN]  = 6;


  // vacio los buffers de entrada y salida
	result = tcflush(fd,TCIOFLUSH); 
	if(result) perror("falla al hacer flush");
  
  //TCSANOW especifica que todos los cambios realizados arriba deben aplicarse inmediatemente en la linea que sigue sin esperar los datos entrantes o salientes actuales.
	result = tcsetattr(fd, TCSANOW, &newtty);

	return fd;
}


int write_port(int fd, uint8_t * buffer, size_t size){

	ssize_t result = write(fd,buffer,size);

	if(result != (ssize_t)size){
		perror("error al abrir el puerto");
		return -1;
	}

	return 0;
}


ssize_t read_port(int fd,uint8_t * buffer, size_t size){
	
	size_t received = 0;
	while(received < size){
		ssize_t r = read(fd, buffer + received, size - received);
		if(r < 0){
			perror("falla al leer el puerto");
			return -1;
		}
		if(r==0) break;

		received += r;
	}

	return received;
}

