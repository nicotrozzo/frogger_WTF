/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "action_routines.h"

extern sem_t levelUpSem;

static void letter_up(void *pArg, int letter);
static void letter_down(void *pArg, int letter);
//static int getScoreChar(int whatToDo);



void non_act_routine(void *pArg)
{
  
}

void load_scoreboard(void *pArg)
{
    ((gameData_t *)pArg)->scoreFile = fopen(SCORE_FILE,"r");
    ((gameData_t *)pArg)->position = 0;
}

void close_scoreboard(void *pArg)
{
    fclose(((gameData_t *)pArg)->scoreFile);
    ((gameData_t *)pArg)->scoreFile = NULL;
}

void load_scores(void *pArg)
{
    int i;
    ((gameData_t *)pArg)->scoreFile = fopen(SCORE_FILE,"r+");
    for( i=0 ; i < NOFCHARS ; i++ )
    {    
        ((gameData_t *)pArg)->player[i]='A';
    }
    ((gameData_t *)pArg)->position = 0;
}

void frog_up(void *pArg)
{
  gameData_t *pData = pArg;
  if(pData->move.flag == false)
  {    
    pData->move.flag = true;
    pData->move.where = FROG_UP;
  }  
}

void frog_down(void *pArg)
{
  gameData_t *pData = pArg;
  if(pData->move.flag == false)
  {    
    pData->move.flag = true;
    pData->move.where = FROG_DOWN;
  }  
}

void frog_left(void *pArg)
{
  gameData_t *pData = pArg;
  if(pData->move.flag == false)
  {    
    pData->move.flag = true;
    pData->move.where = FROG_LEFT;
  }  
}

void frog_right(void *pArg)
{
  gameData_t *pData = pArg;
  if(pData->move.flag == false)
  {
    pData->move.flag = true;
    pData->move.where = FROG_RIGHT;
  } 
}

void start_game(void *pArg)
{
  gameData_t *pData = pArg;
  pData->lives = LIVES;
  pData->quitGame = false;
  pData->levelUp = false;
  pData->score = 0;
  checkLevelUp(NULL);
  pData->move.flag = false;
  int letter;
  for(letter = 0; letter < 3; letter++)
  {
    pData->player[letter] = 'A';
  }
}

void f_letter_up(void *pArg)
{
  letter_up(pArg, ((gameData_t*)pArg)->position);
}

void f_letter_down(void *pArg)
{
  letter_down(pArg, ((gameData_t*)pArg)->position);
}

void previousChar(void *pArg)
{
    if(((gameData_t*)pArg)->position > MIN_POSITION)
    {    
        ((gameData_t*)pArg)->position--;
    }
    else
    {
        ((gameData_t*)pArg)->position = MAX_POSITION;
    }    
}

void nextChar(void *pArg)
{
    if(((gameData_t*)pArg)->position < MAX_POSITION)
    {    
        ((gameData_t*)pArg)->position++;
    }
    else
    {
        ((gameData_t*)pArg)->position = MIN_POSITION;
    } 
}


void showNextScore(void *pArg)
{
  if(!((gameData_t*)pArg)->move.flag)   //OJO POSIBLE PERDIDA DE EVENTOS
  {    
    ((gameData_t*)pArg)->move.flag = true;  
    ((gameData_t*)pArg)->move.where = FROG_DOWN;
  }
}


void showPreviousScore(void *pArg)
{
  if(!((gameData_t*)pArg)->move.flag)
  {    
    ((gameData_t*)pArg)->move.flag = true;  
    ((gameData_t*)pArg)->move.where = FROG_UP;
  }
}

/*checkLevelUp:
 Recibe un puntero a gameData o NULL
 Si recibe un puntero a gameData, se fija si subio de nivel. Si subio de nivel, suma el puntaje respectivo, y avisa en gameData
 Si no subio de nivel, suma el puntaje correspondiente a llegar arriba de todo
 Si recibe NULL, reinicia el contador de veces(se usa en end_game y start_game)*/

void checkLevelUp(void *pArg)
{
  static int8_t times = 0;
  if(!pArg) //si la llaman con el NULL significa que tiene que reiniciar el contador
  {
      times = 0;
  }    
  else if(++times >= EMPTY_SPACES)  //sino se fija si subio de nivel
  {
    ((gameData_t*)pArg)->score += LEVEL_UP_SCORE;
    ((gameData_t*)pArg)->levelUp = true;
    sem_post(&levelUpSem);
    printf("LEVEL UP!, score: %d\n",((gameData_t*)pArg)->score);
    times = 0;
  }
  else      //si no subio de nivel significa que solo llego arriba
  {
    ((gameData_t*)pArg)->score += ARRIVE_SCORE;  
    ((gameData_t*)pArg)->levelUp = false;
    sem_post(&levelUpSem);
    printf("ARRIVED!, score: %d\n",((gameData_t*)pArg)->score);
  }
}

void checkLives(void *pArg)
{
  gameData_t *pGameData = pArg;  
  if(!pGameData-> lives)
  {
    emit_event(pGameData->pEventQueue,GAME_OVER_EVENT);  //DESPUES VER QUE HACER CAPAZ EMIT_EVENT CON OTRO EVENTO
  }
}

void update_score(void *pArg)
{
  gameData_t* pGameData = pArg;
  pGameData->score += FORWARD_SCORE;
}

void saveScore(void *pArg)
{
    gameData_t* pGameData = pArg;
    printf("banca que estoy quemado, ahora lo escribo\n");
    
    
    fclose(pGameData->scoreFile);
    ((gameData_t *)pArg)->scoreFile = NULL;
}




/* end_game:
 * Recibe un puntero a gameData y avisa que termino el juego, ademas, reinicia el contador con la cantidad de veces que llego la rana 
 arriba de todo*/
void end_game(void *pArg)
{
    gameData_t *pData = pArg;
    checkLevelUp(NULL);
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
    else if(pData->player[letter] == 'A')
    {
        pData->player[letter] = 'Z';
    }        
}

static void letter_down(void *pArg, int letter)
{
    gameData_t *pData = pArg;
    if( pData->player[letter] < 'Z')
    {
        pData->player[letter]++;
    }
    else if(pData->player[letter] == 'Z')
    {
        pData->player[letter] = 'A';
    }    
}

/*static int getScoreChar(int whatToDo)
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
} */

void output_init(void)
{
    display_init();
    display_clear();
    display_update();
}

void output_clear(void)
{
    display_clear();
    display_update();
}