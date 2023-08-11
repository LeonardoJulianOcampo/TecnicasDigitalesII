#include "tpo.h"
#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <stdint.h>
#define STEPS 400000


uint32_t vel(int up_down) {
    static uint32_t step_vel = STEPS;
    curs_set(0);

    switch (up_down) {
        case 0:
            if (step_vel < STEPS - 10000) {
                step_vel = step_vel + 10000;
            }
            return step_vel; 
            break;
        case 1:
            if (step_vel > 20000) {
                step_vel = step_vel - 10000;
                return step_vel;
            } 
            else 
                return step_vel;
            break;
        default:
            return step_vel;
    }
}

