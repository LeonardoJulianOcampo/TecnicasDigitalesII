#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <ncurses.h>


int main() {
    int serial_port = open("/dev/ttyAMA0", O_RDWR); // Reemplaza "/dev/ttyS0" por el nombre correcto de tu puerto serie (ejemplo: "/dev/ttyUSB0" para un adaptador USB-serial)
    int exit = 1;
    int ch; 

	initscr();
	raw();
	keypad(stdscr,TRUE);
	noecho();
	nodelay(stdscr,TRUE);


    if (serial_port < 0) {
        perror("Error al abrir el puerto serie");
        return 1;
    }

    struct termios tty;

    // Configuración del puerto serie
    if (tcgetattr(serial_port, &tty) != 0) {
        perror("Error al obtener la configuración del puerto");
        close(serial_port);
        return 1;
    }

    cfsetispeed(&tty, B9600); // Velocidad de recepción (puedes ajustarla según el dispositivo)
    cfsetospeed(&tty, B9600); // Velocidad de transmisión (puedes ajustarla según el dispositivo)
    tty.c_cflag &= ~PARENB; // Sin paridad
    tty.c_cflag &= ~CSTOPB; // 1 bit de stop
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8; // 8 bits de datos
    tty.c_cflag &= ~CRTSCTS; // Sin control de flujo

    // Establecer las opciones del puerto serie
    if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
        perror("Error al establecer la configuración del puerto");
        close(serial_port);
        return 1;
    }

    uint32_t data_to_send = 123456; // Valor que queremos enviar
    
    while(exit){
    // Enviamos el valor de uint32_t en modo raw (bytes sin procesar)
    if (write(serial_port, &data_to_send, sizeof(data_to_send)) < 0) {
	printw("Error al abrir el puerto");
	refresh();
	exit=0;
   	 }
    ch = getch();
    if(ch == KEY_F(2))	
	exit = 0;
    }
    close(serial_port);
    endwin();
    return 0;
}
