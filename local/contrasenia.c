#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#define MAX_ATTEMPTS 3
#define PASSWORD "123"

int row, col;

void printCentered(const char* str, int row, int col) {
    mvprintw(row / 2, (col - strlen(str)) / 2, "%s", str);
}

int contrasenia() {
    initscr();
    raw();
    noecho();
    curs_set(0);
    int attempts = 0;
    char input[50];
    int ch;
    int pos = 0;
    getmaxyx(stdscr, row, col);
    int asterisk_pos[50];

    while (attempts < MAX_ATTEMPTS) {
        clear();
        printCentered("Ingrese la contraseña:", row, col);
        refresh();

        while ((ch = getch()) != '\n') {
            if (ch == 127 || ch == KEY_BACKSPACE) { // Manejar el caso de la tecla de retroceso
                if (pos > 0) {
                    pos--;
                    // Borra el asterisco previo en la posición correspondiente
                    mvprintw(row / 2 + 3, (col - strlen(PASSWORD)) / 2 + asterisk_pos[pos], " ");
                    refresh();
                }
            } else {
                input[pos] = ch;
                mvprintw(row / 2 + 3, (col - strlen(PASSWORD)) / 2 + pos, "*"); // Imprime el caracter como *
                asterisk_pos[pos] = pos; // Almacena la posición x donde se imprimió el asterisco
                refresh();
                pos++;
            }
        }

        input[pos] = '\0'; // Agregar el carácter de terminación de cadena

        if (strcmp(input, PASSWORD) == 0) {
            clear();
            printCentered("Contraseña correcta. Bienvenido!", row, col);
            refresh();
            getch();
	    return 1;
            break;
        } else {
            attempts++;
            pos = 0;

            if (attempts < MAX_ATTEMPTS) {
                clear();
                printCentered("Contraseña incorrecta. Intentos restantes: ", row, col);
		refresh();
                mvprintw(row, col + 2, "%d", MAX_ATTEMPTS - attempts);
                refresh();
                getch();
		halfdelay(1);
            }
        }
    }

    if (attempts == MAX_ATTEMPTS) {
        clear();
        printCentered("Ha excedido el número máximo de intentos.", row, col);
        printCentered("El programa se cerrará.", row + 3, col);
        refresh();
        getch();
	return 0;
    }

    endwin();
}

