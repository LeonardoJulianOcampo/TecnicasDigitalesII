#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>

#define MAX_BUFFER_SIZE 100

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






int main() {
    int fd = open_port("/dev/ttyAMA0", 9600);
    if (fd == -1) {
        printf("Error al abrir el puerto serie.\n");
        return 1;
    }

    uint8_t buffer[MAX_BUFFER_SIZE];
    ssize_t bytes_read;
    bool is_reading = true;

    while (is_reading) {
        // Leer desde el puerto serie
        bytes_read = read_port(fd, buffer, sizeof(buffer) - 1);
        if (bytes_read > 0) {
            buffer[bytes_read] = '\0'; // Agregar terminador nulo al final del buffer

            // Procesar el mensaje recibido
            if (buffer[0] == '1') {
                // Mensaje de acceso
                printf("Mensaje de acceso recibido: %c\n", buffer[0]);
            } else if (buffer[0] == '!') {
                // Mensaje de salida
                printf("Mensaje de salida recibido: F2 presionado. Saliendo del bucle.\n");
                is_reading = false;
            } else {
                // Mensaje de dígitos de time_factor
                printf("Mensaje de dígitos de time_factor recibido: %s\n", buffer);
            }
        }
    }

    close(fd);
    return 0;
}

