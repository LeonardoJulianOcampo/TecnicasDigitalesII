#include "tpo.h"
#include <stdio.h>
#include <ncurses.h>

#define STEPS 10

int vel(void){
	
	static int step_vel=0;
	noecho();
	nodelay(stdscr,TRUE);
	curs_set(0);
	
	switch(getch()){
	case KEY_UP:
		if (step_vel < STEPS)
			step_vel ++;
			break;
	case KEY_DOWN:
		if (step_vel > 0)
			step_vel --;
			break;
	default :
		break;
	}
	return step_vel;
}
