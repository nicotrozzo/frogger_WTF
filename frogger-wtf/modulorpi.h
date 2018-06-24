#ifndef MODULO_RPI_H
#define MODULO_RPI_H

#include <stdbool.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <time.h>

#include "termlib.h"
#include "joydrv.h"
#include "disdrv.h"
#include "gameStructs.h"

#define infinite_loop while(1)
#define JOY_THRESHOLD 70     // 10-100 Joystick threshold (sensitivity)
#define DISSIZE 16
#define INIT_X 7
#define INIT_Y 15
#define FROG_REFRESH 5

enum movefrog { FROG_UP, FROG_DOWN, FROG_RIGHT, FROG_LEFT };

void* input_thread (void* event);
void* output_thread(void* p2gameData);


#endif /* MODULO_RPI_H*/

