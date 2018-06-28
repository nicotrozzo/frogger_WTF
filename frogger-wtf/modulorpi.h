#ifndef MODULO_RPI_H
#define MODULO_RPI_H

#include <stdbool.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <semaphore.h>
#include <string.h>

#include "termlib.h"
#include "joydrv.h"
#include "disdrv.h"
#include "gameStructs.h"

#define infinite_loop while(1)
#define JOY_THRESHOLD 70     // 10-100 Joystick threshold (sensitivity)
#define DISSIZE 16
#define INIT_X 7
#define INIT_Y 15
#define FROG_REFRESH 2
#define FROG_X_MAX 15
#define FROG_Y_MAX 15
#define FROG_X_MIN 0
#define FROG_Y_MIN 0

/*PARA ESTADOS DE SCOREBOARD*/
#define POSITION_X 1
#define POSITION_Y 1
#define NOFCHARS 3
#define MAXNUMBERS 6
#define LETTER_POS_Y 8
#define FIL1 1
#define X_SEPARATION 1
#define Y_SEPARATION 2
#define FIL2 (FIL1+LENGTH_Y+Y_SEPARATION)
#define LENGTH_X 4
#define LENGTH_Y 5
#define DISPLAY_MIDDLE 3
#define CHANGE_SCORE_TIMES 50
#define N_OF_LETTERS 26
#define N_OF_NUMBERS 10
#define SCORE_NAME_Y 5
#define WAIT_NAME_BLINK 10
#define MAXSCORE 999999

enum movefrog { FROG_UP, FROG_DOWN, FROG_RIGHT, FROG_LEFT };

void* input_thread (void* event);
void* output_thread(void* p2gameData);


#endif /* MODULO_RPI_H*/