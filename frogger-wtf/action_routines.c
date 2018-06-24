/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "gameStructs.h"
#include "modulorpi.h"
/*ESTO TIENE QUE IR EN EL .H PERO NETBEANS NO QUIERE*/
#define LEVEL_UP_SCORE 100
#define FORWARD_SCORE 10
#define EMPTY_SPACES 5

enum charManage {CURR = -1, NEXT = 0, PREV, START}; // esto se usa para las funciones que mueven la letras para guardar puntaje

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
/*ESTO TIENE QUE IR EN EL .H PERO NETBEANS NO QUIERE*/

static void letter_up(void *pArg, int letter);
static void letter_down(void *pArg, int letter);
static int getScoreChar(int whatToDo);

void non_act_routine(void *pArg)
{
  
}

void frog_up(void *pArg)
{
  gameData_t *pData = pArg;
  pData->moveFrog.flag = true;
  pData->moveFrog.where = FROG_UP;
}

void frog_down(void *pArg)
{
  gameData_t *pData = pArg;
  pData->moveFrog.flag = true;
  pData->moveFrog.where = FROG_DOWN;
}

void frog_left(void *pArg)
{
  gameData_t *pData = pArg;
  pData->moveFrog.flag = true;
  pData->moveFrog.where = FROG_LEFT;
}

void frog_right(void *pArg)
{
  gameData_t *pData = pArg;
  pData->moveFrog.flag = true;
  pData->moveFrog.where = FROG_RIGHT;
}

void start_game(void *pArg)
{
  gameData_t *pData = pArg;
  pData->lives = LIVES;
  pData->quitGame = false;
  pData->levelUp = false;
  pData->score = 0;
  pData->moveFrog.flag = false;
  int letter;
  for(letter = 0; letter < 3; letter++)
  {
    pData->player[letter] = 'A';
  }
}

void f_letter_up(void *pArg)
{
  letter_up(pArg, getScoreChar(CURR));
}

void f_letter_down(void *pArg)
{
  letter_down(pArg, getScoreChar(CURR));
}

void previousChar(void *pArg)
{
  getScoreChar(PREV);
}

void nextChar(void *pArg)
{
  getScoreChar(NEXT);
}


void showNextScore(void *pArg)
{
  printf("NOT YET MY MAN\n");
}


void showPreviousScore(void *pArg)
{
  printf("NOT YET MY MAN\n");
}

void checkLevelUp(void *pArg)
{
  static int8_t times = 0;
  if(++times >= EMPTY_SPACES)
  {
    update_score(NULL);
    ((gameData_t*)pArg)->levelUp = true;
    times = 0;
  }
  else
  {
    ((gameData_t*)pArg)->levelUp = false;
  }
}

void checkLives(void *pArg)
{
  gameData_t *pGameData = pArg;  
  if(!(--(pGameData-> lives)))
  {
    pGameData->currentState = pGameData->cabeza;  //DESPUES VER QUE HACER
  }
}

void update_score(void *pArg)
{
  gameData_t* pGameData = pArg;
  if(!pGameData)
  {
    pGameData->score += LEVEL_UP_SCORE;
  }
  else
  {
    pGameData->score += FORWARD_SCORE;
  }
}

void saveScore(void *pArg)
{

}





void end_game(void *pArg)
{
    gameData_t *pData = pArg;
    pData->quitGame = 1;
}



/*AUX FUNCTIONS*/

static void letter_up(void *pArg, int letter)
{
    gameData_t *pData = pArg;
    if(pData->player[letter] > 'A')
    {
        pData->player[letter]--;
    }
}

static void letter_down(void *pArg, int letter)
{
    gameData_t *pData = pArg;
    if( pData->player[letter] < 'Z')
    {
        pData->player[letter]++;
    }
}

static int getScoreChar(int whatToDo)
{
  static int scoreChar = 0;
  switch(whatToDo)
  {
    case CURR:
        return scoreChar;
    case PREV:
        if(--scoreChar >= 0);
        else
        {
          scoreChar = 2;
        }
        break;
    case NEXT:
        if(++scoreChar <= 2);
        else
        {
          scoreChar = 0;
        }
        break;
    default:
        scoreChar = 0;
        return scoreChar;    
  }  
  return scoreChar; //esto no se usa, solo para evitar warning
} 
