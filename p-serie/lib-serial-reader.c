#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <termios.h>
#include <string.h>

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

	//configuracion de los timeouts: Las llamadas a la funcion read() retornan un valor tan pronto como haya al menos un byte disponible o hayan transcurrido 100 ms.
	
	tty.c_cc[VTIME] = 1;
	tty.c_cc[VMIN]  = 0;


	//configuración de la velocidad del puerto. 9600 baudios
	
	cfsetospeed(&tty,B9600);
	cfsetispeed(&tty,B9600);

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



int main(void){

	const char * device = "/dev/ttyAMA0";
	uint8_t buffer[2] = {0};
	int fd;
	int wp;

	fd = open_port(device,9600);
	if (fd<0) return 1;

	while(1){
		read_port(fd,buffer,sizeof(buffer));
		printf("%s\n",buffer);
		memset(buffer,0,sizeof(buffer));
	}
	close(fd);
}





