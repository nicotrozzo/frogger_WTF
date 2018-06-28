
/* 
 * File:   action_routines.h
 * Author: nico
 *
 * Created on June 24, 2018, 12:29 AM
 */

#ifndef ACTION_ROUTINES_H
#define ACTION_ROUTINES_H

#include <semaphore.h>
#include "gameStructs.h"
#include "modulorpi.h"

void non_act_routine(void *pArg);
void frog_up(void *pArg);
void frog_down(void *pArg);
void frog_left(void *pArg);
void frog_right(void *pArg);
void start_game(void *pArg);
void f_letter_up(void *pArg);
void f_letter_down(void *pArg);
void previousChar(void *pArg);
void nextChar(void *pArg);
void end_game(void *pArg);
void saveScore(void *pArg);
void update_score(void *pArg);
void checkLives(void *pArg);
void checkLevelUp(void *pArg);
void showPreviousScore(void *pArg);
void showNextScore(void *pArg);
void load_scoreboard(void *pArg);
void close_scoreboard(void *pArg);
void load_scores(void *pArg);


void output_init(void);
void output_clear(void);

#define LEVEL_UP_SCORE 100
#define ARRIVE_SCORE 30
#define FORWARD_SCORE 10
#define EMPTY_SPACES 5
#define LIVES 5
#define SCORE_FILE "scoreBoard.txt"
#define MAX_POSITION 2
#define MIN_POSITION 0

enum charManage {CURR = -1, NEXT = 0, PREV, START}; // esto se usa para las funciones que mueven la letras para guardar puntaje


#endif /* ACTION_ROUTINES_H */

