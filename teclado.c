// Función para leer el teclado en un hilo separado
void *read_keyboard(void *arg) {
    while (keep_reading) {
        int ch = getch();
        if (ch != ERR) {
            last_key = ch;
	if (last_key != ERR) {
	    ch = last_key;
	    last_key = ERR;

	    if      (ch == KEY_F(2)) s = 1;
	    else if (ch == KEY_UP)   time_factor = vel(1);
	    else if (ch == KEY_DOWN) time_factor = vel(0);
	    else                     time_factor = time_factor;
	}

	}
    }
    return NULL;
}


