#include "tpo.h"

//funcion que lee constantemente el puerto serie en busca de una clave de un efecto valida.
//cuando se la encuentra, devuelve la clave. En caso de que se la interrumpa mediante F2
//devuelve -1.

int busca_clave(WINDOW *win, int fd,bool cont){

  char buffer[7];
  int value=0;
  int tecla=ERR;
  int c_leidos=0;
  int salir = 0;
  int result;
  int wcol,wrow;
  char title_remoto[] = {"MODO REMOTO ACTIVADO"};

  nodelay(stdscr,TRUE);

  while(!s){
    
    getmaxyx(win,wrow,wcol);
    wclear(win);
    box(win,0,0);
    mvwprintw(win,2,(wcol - strlen(title_remoto))/2,title_remoto);
    wrefresh(win);
 
    if(read)
      c_leidos = read(fd,buffer,sizeof(buffer));

    tecla = getch();
    if (tecla == KEY_F(2)){   //presiono F2. Salgo retornando -1.
      return -1;
    }
   
    if(c_leidos == 7){

    buffer[6]=0;
    value = atoi(buffer);
    wrefresh(win);
    if(value >= 999990 && value <= 999997 || value == 888888)  // se encuentra una clave de efecto valida. retorna
      return value;                                            // la clave    
    }
  }
  nodelay(stdscr,FALSE);
} // fin de funcion busca_clave


void menu_efectos_remoto(WINDOW * win){

  int fd=0;
  int tecla=0;
  int clave_efecto=0;
  bool exit = false; 
  bool cont = true;
  char title_remoto[] = {"MODO REMOTO ACTIVADO"};
  int wcol,wrow;

  getmaxyx(win,wrow,wcol);
  wclear(win);
  box(win,0,0);
  mvwprintw(win,2,(wcol-strlen(title_remoto))/2,title_remoto);
  wrefresh(win);

  nodelay(stdscr,TRUE);


  while(!exit){
  wclear(win);
  box(win,0,0);
  mvwprintw(win,2,(wcol-strlen(title_remoto))/2,title_remoto);
  fd = open_port("/dev/ttyAMA0",115200);    
  clave_efecto = busca_clave(win,fd,cont);
  close(fd);
  wrefresh(win);

  tecla=getch();
  if(tecla == KEY_F(2)) break;

    if(clave_efecto != -1){//si se encuentra una clave valida... 
      switch(clave_efecto){
        case 999990: lacarrera   (win); break;
        case 999991: choque      (win); break;
        case 999992: autofan     (win); break;
        case 999993: apilada     (win); break;
        case 999994: sirena      (win); break;
        case 999995: mov         (win); break;
        case 999996: sos         (win); break;
        case 999997: rafaga      (win); break;
        case 888888: exit=true;         break;
        default:                        break;
      } // fin switch(clave_efecto)
    }   //fin if(clave_efecto != -1)
    else break;//si se presiona F2 durante la busqueda
    wrefresh(win);
    
  }

nodelay(stdscr,FALSE);
}




