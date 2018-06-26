#ifndef MODULO_RPI_H
#define MODULO_RPI_H

#include <stdbool.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <semaphore.h>

#include "termlib.h"
#include "joydrv.h"
#include "disdrv.h"
#include "gameStructs.h"

#define infinite_loop while(1)
#define JOY_THRESHOLD 70     // 10-100 Joystick threshold (sensitivity)
#define DISSIZE 16
#define INIT_X 7
#define INIT_Y 15
#define FROG_REFRESH 3
#define FROG_X_MAX 15
#define FROG_Y_MAX 15
#define FROG_X_MIN 0
#define FROG_Y_MIN 0

/*PARA ESTADO DE SHOW SCOREBOARD*/
#define POSITION_X 1
#define POSITION_Y 1
#define NOFCHARS 3
#define INIT_Y 8
#define FIL1 3
#define Y_SEPARATION 2
#define FIL2 (FIL1+Y_SEPARATION)
#define LENGHT_X 4
#define LENGHT_Y 5
#define MAXNUMBERS 6
#define DISPLAY_MIDDLE 3
#define CHANGE_SCORE_TIMES 5

enum movefrog { FROG_UP, FROG_DOWN, FROG_RIGHT, FROG_LEFT };

void* input_thread (void* event);
void* output_thread(void* p2gameData);


#endif /* MODULO_RPI_H*/

