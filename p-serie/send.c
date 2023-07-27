#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>

int main(){

	int serial_port = open("/dev/ttyAMA0", O_RDWR);

	if (serial_port < 0){
		perror("Error al abrir el puerto serie");
		return 1;
	}

	struct termios tty;
	if(tcgetattr(serial_port,&tty) != 0){
		perror("Error al obtener la configuración del puerto serie");
		close(serial_port);
		return 1;
	}

	tty.c_cflag |= CREAD;
	tty.c_cflag |= CLOCAL;

	cfsetispeed(&tty, B9600);
	cfsetospeed(&tty, B9600);

	if(tcsetattr(serial_port, TCSANOW, &tty) != 0){
		perror("Error al aplicar los cambios en la configuración del puerto serie");
		close(serial_port);
		return 1;
	}

	char *msg = "Hola mundo!\n";

	int bytes_written = write(serial_port, msg, strlen(msg));
	if(bytes_written < 0){
		perror("Error de envio de datos");
		close(serial_port);
		return 1;
	}

	close(serial_port);

}


