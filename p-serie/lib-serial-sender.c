#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <termios.h>
#include <ncurses.h>

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

	const char * device = "/dev/ttyUSB0";
	
	uint8_t up[] = {"a"};
	uint8_t dw[] = {"b"};

	int fd;
	int wp;
	int ch;
	int exit = 0;

	initscr();
	raw();
	keypad(stdscr,TRUE);
	noecho();
	nodelay(stdscr,TRUE);
	curs_set(0);


	fd = open_port(device,9600);
	if (fd<0) return 1;

	exit = 1;
	
	while(exit){

	ch = getch();

	switch(ch){

		case KEY_UP  : write_port(fd,up,sizeof(up)); break;
		case KEY_DOWN: write_port(fd,dw,sizeof(dw)); break;
		case KEY_F(2): exit = 0; endwin(); break;
		default : break;	
	}

	if (wp == -1)
		printf("Error al escribir el puerto");

	}
	close(fd);
}




