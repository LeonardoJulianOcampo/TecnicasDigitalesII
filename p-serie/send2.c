#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <ncurses.h>

int main() {
    int serial_port = open("/dev/ttyUSB0", O_RDWR); // Reemplaza "/dev/ttyS0" por el nombre correcto de tu puerto serie (ejemplo: "/dev/ttyUSB0" para un adaptador USB-serial)

    if (serial_port < 0) {
        perror("Error al abrir el puerto serie");
        return 1;
    }

    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    nodelay(stdscr, TRUE);

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

    int ch;
    char data_to_send;

    while (1) {
        // Leer el carácter ingresado usando ncurses
        ch = getch();

        // Detectar la tecla presionada
        if (ch == KEY_UP) {
            data_to_send = '1'; // Enviar '1' si se presionó la tecla Up
        } else if (ch == KEY_DOWN) {
            data_to_send = '0'; // Enviar '0' si se presionó la tecla Down
        } else if (ch == 'q' || ch == 'Q') {
            break; // Salir del bucle si se presiona 'q' o 'Q'
        } else {
            continue; // Continuar con el siguiente ciclo si no se presionó una tecla válida
        }

        // Enviar el carácter a través del puerto serie
        if (write(serial_port, &data_to_send, sizeof(data_to_send)) < 0) {
            perror("Error al enviar datos por el puerto serie");
            close(serial_port);
            endwin(); // Finalizar la ventana ncurses antes de salir
            return 1;
        }
    }

    close(serial_port);
    endwin();

    return 0;
}
