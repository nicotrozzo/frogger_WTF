
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
void game_over(void *pArg);
void letter_up(void *pArg, int letter);
void letter_down(void *pArg, int letter);
void saveScore(void *pArg);
void update_score(void *pArg);
void checkLives(void *pArg);
void checkLevelUp(void *pArg);
void showPreviousScore(void *pArg);
void showNextScore(void *pArg);

#endif /* ACTION_ROUTINES_H */

