
/* 
 * File:   action_routines.h
 * Author: nico
 *
 * Created on June 24, 2018, 12:29 AM
 */

#ifndef ACTION_ROUTINES_H
#define ACTION_ROUTINES_H

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

#define LEVEL_UP_SCORE 100
#define FORWARD_SCORE 10
#define EMPTY_SPACES 5
#define LIVES 5

enum charManage {CURR = -1, NEXT = 0, PREV, START}; // esto se usa para las funciones que mueven la letras para guardar puntaje


#endif /* ACTION_ROUTINES_H */

