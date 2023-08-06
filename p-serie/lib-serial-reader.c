#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <termios.h>
#include <string.h>
#include <stdlib.h>

int open_port(const char * device, uint32_t baud_rate){

	int fd = open(device, O_RDWR | O_NOCTTY);
	if(fd == -1){
		perror(device);
		return -1;
	}

	int result = tcflush(fd,TCIOFLUSH);
	
	if(result) perror("falla al hacer flush");
	
	struct termios tty;
	
	result = tcgetattr(fd,&tty);

	if(result){
		perror("tcgetattr falló");
		close(fd);
		return -1;
	}
	
	//Desactiva cualquier opción que pueda interferir con la capacidad de enviar datos en modo raw

	tty.c_iflag &= ~(INLCR | IGNCR | ICRNL | IXON | IXOFF);
	tty.c_oflag &= ~(ONLCR | OCRNL );
	tty.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);

	//configuracion de los timeouts: Las llamadas a la funcion read() retornan un valor tan pronto como haya al menos 6 bytes disponibles, sin timeout.
	
	tty.c_cc[VTIME] = 0;
	tty.c_cc[VMIN]  = 6;                    // leo 6 caracteres, luego existo


	//configuración de la velocidad del puerto. 9600 baudios
	
	cfsetospeed(&tty,B115200);
	cfsetispeed(&tty,B115200);

	result = tcsetattr(fd, TCSANOW, &tty);

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
		ssize_t r = read(fd, buffer,sizeof(buffer));
		if(r < 0){
			perror("falla al leer el puerto");
			return -1;
		}
		if(r==0) break;

		received += r;
	}

	return received;
}


int main(void){

	const char * device = "/dev/ttyAMA0";
	char buffer[7];
	int fd;
	int value;
  
  memset(buffer,0,sizeof(buffer));
	fd = open_port(device,115200);
	if (fd<0) return 1;

	while(1){
		//read_port(fd,buffer,sizeof(buffer));
    read(fd,buffer,sizeof(buffer));
    buffer[6]='\0';
		value = atoi(buffer);
		printf("valor convertido:%d\n",value);
    //memset(buffer,0,sizeof(buffer));
    if(value == 9999999) break;
	  }
	close(fd);
}





