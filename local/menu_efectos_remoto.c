#include "tpo.h"

//funcion que lee constantemente el puerto serie en busca de una clave de un efecto valida.
//cuando se la encuentra, devuelve la clave. En caso de que se la interrumpa mediante F2
//devuelve -1.

int busca_clave(WINDOW *win, int fd){

  char buffer[7];
  int value=0;
  int tecla=ERR;
  bool exit = false;
  int c_leidos=0;

  nodelay(stdscr,TRUE);
  while(!exit){
    wclear(win);
    mvwprintw(win,3,2,"Leyendo puerto (en busca clave)");
    nodelay(stdscr,TRUE);
    wrefresh(win);

    c_leidos = read(fd,buffer,sizeof(buffer));

    tecla = getch();
    if (tecla == KEY_F(2)){   //presiono F2. Salgo retornando -1.
      return -1;
    }
   
    if(c_leidos == 7){

    buffer[6]=0;
    value = atoi(buffer);
    wrefresh(win);
    if(value >= 999990 && value <= 999997)  // se encuentra una clave de efecto valida. retorna
      return value;                         // la clave    
    }
  }
  nodelay(stdscr,FALSE);
} // fin de funcion busca_clave


void menu_efectos_remoto(WINDOW * win){

  int fd=0;
  int tecla=0;
  int clave_efecto=0;
  bool exit = false; 

  box(win,0,0);
  wclear(win);
  mvwprintw(win,2,2,"Modo remoto activado. Esperando clave acceso");
  wrefresh(win);

  nodelay(stdscr,TRUE);

  //fd = open_port("/dev/ttyAMA0",115200); 

  while(!exit){ 
  fd = open_port("/dev/ttyAMA0",115200);    
  clave_efecto = busca_clave(win,fd);
  close(fd);
  mvwprintw(win,4,2,"Comparando valores de claves (%06d)",clave_efecto);
  wrefresh(win);

  tecla=getch();
  if(tecla == KEY_F(2)) break;

    if(clave_efecto != -1){//si se encuentra una clave valida... 
      switch(clave_efecto){
        case 999990: lacarrera(win); break;
        case 999991: choque(win);    break;
        case 999992: autofan(win);   break;
        case 999993: apilada(win);   break;
        case 999994: sirena(win);    break;
        case 999995: mov(win);       break;
        default:                     break;
      } // fin switch(clave_efecto)
    }   //fin if(clave_efecto != -1)
    else break;//si se presiona F2 durante la busqueda
    wrefresh(win);
    
  }

nodelay(stdscr,FALSE);
close(fd);
}




