#include "tpo.h"

/*void menu_efectos_remoto(WINDOW * win){

  int fd;
  int s_time;
  int key;
  char buffer[7];
  int tecla;
  bool exit = false;
  bool exit_read_key = false;
  
  nodelay(stdscr,TRUE);
  
  fd = open_port("/dev/ttyAMA0",115200); 
  exit = false;
  exit_read_key = false;

  while(!exit){
    box(win,0,0);
    mvwprintw(win,2,2,"Modo remoto activado. Esperando clave acceso");
    wrefresh(win);
    key = 0;

    
    tecla=getch();
    
    if (tecla == KEY_F(2)){
      exit=true; 
      break;
    }
    else{
        while(!exit_read_key){
           
          read(fd,buffer,sizeof(buffer));
          
          buffer[6]=0;
          key = atoi(buffer);
          mvwprintw(win,3,2,"key:%06d",key);
          
          if(key == 999999){break;}
          
          tecla = getch();
          if(tecla == KEY_F(2)){exit = true; break;}

          wrefresh(win);
          
          if(key > 999990 && key <= 999997){
            mvwprintw(win,4,2,"Clave ingresada!: %d",key);
            wrefresh(win);
            break;
            }
        }//fin while(!exit_read_key)
        
        if (exit == true) break;

        switch(key){
          case 999994: apilada(win); 
                       wclear(win);
                        break;
          default     : break;
        }
      }//fin while(!exit)
  }
  close(fd);


nodelay(stdscr,FALSE);
  

} // fin de menu_efectos_remoto
*/

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
    wrefresh(win);

    c_leidos = read(fd,buffer,sizeof(buffer));

    tecla = getch();
    if (tecla == KEY_F(2)){   //presiono F2. Salgo retornando -1.
      return -1;
    }
   
    if(c_leidos == 7){

    buffer[6]=0;
    value = atoi(buffer);
    mvwprintw(win,4,2,"value en busca_clave: %06d",value);
    wrefresh(win);
    if(value > 999990 && value <= 999997)  // se encuentra una clave de efecto valida. retorna
      return value;                        // la clave    
    }
  }
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
        case 999994: apilada(win); break;
        default:                   break;
      } // fin switch(clave_efecto)
    }   //fin if(clave_efecto != -1)
    else break;//si se presiona F2 durante la busqueda
    wrefresh(win);
    
  }


nodelay(stdscr,FALSE);
close(fd);
}




