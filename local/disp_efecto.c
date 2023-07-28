/*la funcion hace uso de ncurses para mostrar en pantalla el efecto seleccionado y mostrar datos como las condiciones iniciales y la velocidad actual
 Funciones que usa:

 ncurses
 stdlib
 stdio
 */ 


void disp(int op){
  
  char op1[] = "Auto Fantastico";
  char op2[] = "La Carrera";
  char op3[] = "Choque";
  char op4[] = "Apilada";
  
  int ch;

  initscr();
  raw();
  keypad(stdscr,TRUE);
  noecho();
  
  swich (op){
    op 1:
      system("clear");
      printw("\nPresione F2 para detener y volver al menu anterior");
      printw("\nEl efecto es: %s",op1);
      autofan();
      break;
    op 2: printw("El efecto es: %s",op2); 
    op 3: printw("El efecto es: %s",op3);
    op 4: printw("El efecto es: %s",op4);
  }



}
