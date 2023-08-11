/* Funcion que lee el adc por i2c y determina en base a las mediciones una velocidad inicial de los efectos cuando se es llamada */
#include "tpo.h"

#define pcf8591_address 0x48

void s_intl_cond(WINDOW *win){


  int wcol,wrow;
  int i;
  int r;
  int data;
  int tecla;
  bool exit;
  unsigned char control_byte[1];
  unsigned char value;
  unsigned char str[8];
  char title[] = "CONDICIONES INICIALES";
  char info_msg[] = "Valor actual de lectura:";
  int j;
  int key;
  
  float v;
  const float pendiente = -1.0/3900;
  const float offset = 102.56;
  float input_value;
  float output_value;
  float time;
  float velocidad;


  if (gpioInitialise() < 0) 
    exit = true;
  else 
    exit = false;


  wclear(win);
  getmaxyx(win,wrow,wcol);
  box(win,0,0);
  nodelay(stdscr,TRUE);

  
  data = i2cOpen(1,pcf8591_address,0);

  while(!exit){
  
  mvwprintw(win,2,2,title);
  mvwprintw(win,18,2,"ENTER: Seleccionar cond. inicial.");


  i2cWriteDevice(data,&control_byte,1);

  usleep(20000);

  value = i2cReadByte(data);
  time = (int)(-1567.62*value + 400000);
  
  velocidad = time;

  output_value = (pendiente * velocidad) + offset;
  
  if(output_value > 100)
    output_value = 100;
  
  if(output_value < 0)
    output_value = 0;

  mvwprintw(win,4,2,"                                ");
  mvwprintw(win,4,2,"%s %.1f %%",info_msg,output_value);
  wrefresh(win); 
  tecla = getch();

  if(tecla == 10){
    i2cClose(data);
    time_factor = time;
    break;
  }


  }

  nodelay(stdscr,FALSE);
  i2cClose(data);
}
