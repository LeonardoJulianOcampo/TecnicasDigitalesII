#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

int main() {
    int serial_port = open("/dev/ttyUSB0", O_RDWR); // Reemplaza "/dev/ttyS0" por el nombre correcto de tu puerto serie (ejemplo: "/dev/ttyUSB0" para un adaptador USB-serial)

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

    char data_received;

    while (1) {
        // Leer los datos del puerto serie
        ssize_t bytes_read = read(serial_port, &data_received, sizeof(data_received));
        if (bytes_read < 0) {
            perror("Error al leer datos del puerto");
            close(serial_port);
            return 1;
        } else if (bytes_read == sizeof(data_received)) {
            // Mostrar los datos recibidos
            printf("Dato recibido: %c\n", data_received);
        }
    }

    close(serial_port);

