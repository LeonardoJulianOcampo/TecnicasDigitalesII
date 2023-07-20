/*no recibe ningun valor. Imprime las opciones disponibles. Cuando se selecciona un valor correcto
 se devuelve ese valor como entero para ser tomado por la funcion 'efecto'*/


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#define OPTIONS 3

int counter(int select) {
    static int count = 0;

    if (select == 1 && count < OPTIONS - 1)
        count++;
    else if (select == 1 && count == OPTIONS - 1)
        count = 0;
    else if (select == 0 && count > 0)
        count--;
    else if (select == 0 && count == 0)
        count = OPTIONS - 1;
    else
        count = count;

    return count;
}

void menu(void) {
    int op, row, col;
    int exit = 0;
    char mesg[] = "   MENU PRINCIPAL   ";
    char options[OPTIONS][30] = {
        "Selección de Efectos",
        "      Ajustes       ",
	"       Salir        ",
    };

    initscr();
    getmaxyx(stdscr, row, col);
    raw();
    keypad(stdscr, TRUE);
    noecho();
    nodelay(stdscr, FALSE); // Importante para que getch() espere a que se presione una tecla

    while (!exit) {
        clear();
        mvprintw(row / 2, (col - strlen(mesg)) / 2, mesg);

        for (int i = 0; i < OPTIONS; i++) {
            if (i == counter(-1)) {
                attron(A_STANDOUT); // Resaltar opción seleccionada
                mvprintw(row / 2 + i + 1, (col - strlen(options[i])) / 2, "-> %s", options[i]);
                attroff(A_STANDOUT);
            } else {
                mvprintw(row / 2 + i + 1, (col - strlen(options[i])) / 2, "   %s", options[i]);
            }
        }

        refresh();
        op = getch();

        switch (op) {
            case KEY_UP:
                counter(0);
                break;
            case KEY_DOWN:
                counter(1);
                break;
            case 10: // Enter key
                if (counter(-1) == OPTIONS - 1)
                    exit = 1;
                else
                    mvprintw(row, 0, "Opción seleccionada: %s", options[counter(-1)]);
                refresh();
                //getch(); // Esperar a que el usuario presione una tecla para continuar
                break;
            case 27: // Escape key
                exit = 1;
                break;
            default:
                break;
        }
    }

    endwin();

}


