/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: nico
 *
 * Created on June 22, 2018, 5:43 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "gameStructs.h"
#include "eventQueue.h"
#include "modulorpi.h"
#include "actionRoutines.h"

state_t* fsm_handler(state_t *currentState, uint16_t newEvent, void *pActRoutineData);

/*Forward declarations*/
extern state_t startMenuViewScoreBoard[3+1];
extern state_t startMenuQuit[3+1];
extern state_t scoreBoard[3+1];
extern state_t game[8+1];
extern state_t pauseMenuResume[3+1];
extern state_t pauseMenuBackToStart[3+1];
extern state_t saveScoreChar[5+1];


int main(void) 
{
    /*INICIALIZACION DE TABLAS DE ESTADOS*/
    state_t startMenuPlayGame[3+1] = {
        {DOWN_EVENT,startMenuViewScoreBoard,non_act_routine,START_PLAY_ID},
        {UP_EVENT,startMenuQuit,non_act_routine,START_PLAY_ID},
        {ENTER_EVENT,game,start_game,START_PLAY_ID},
        {END_TABLE,startMenuPlayGame,non_act_routine,START_PLAY_ID}
    };        
    state_t startMenuViewScoreBoard[3+1] = {
        {DOWN_EVENT,startMenuQuit,non_act_routine,START_SCOREBOARD_ID},
        {UP_EVENT,startMenuPlayGame,non_act_routine,START_SCOREBOARD_ID},
        {ENTER_EVENT,scoreBoard,non_act_routine,START_SCOREBOARD_ID},
        {END_TABLE,startMenuViewScoreBoard,non_act_routine,START_SCOREBOARD_ID}
    };
    state_t startMenuQuit[3+1] = {
        {DOWN_EVENT,startMenuPlayGame,non_act_routine,START_QUIT_ID},
        {UP_EVENT,startMenuViewScoreBoard,non_act_routine,START_QUIT_ID},
        {ENTER_EVENT,NULL,end_game,START_QUIT_ID},
        {END_TABLE,startMenuQuit,non_act_routine,START_QUIT_ID}
    };
    state_t scoreBoard[3+1] = {
        {DOWN_EVENT,scoreBoard,showNextScore,SCORE_BOARD_ID},
        {UP_EVENT,scoreBoard,showPreviousScore,SCORE_BOARD_ID},
        {ENTER_EVENT,startMenuViewScoreBoard,non_act_routine,SCORE_BOARD_ID},
        {END_TABLE,scoreBoard,non_act_routine,SCORE_BOARD_ID}
    };
    state_t game[8+1] = {
        {DOWN_EVENT,game,frog_down,GAME_ID},
        {UP_EVENT,game,frog_up,GAME_ID},
        {LEFT_EVENT,game,frog_left,GAME_ID},
        {RIGHT_EVENT,game,frog_right,GAME_ID},
        {ENTER_EVENT,pauseMenuResume,non_act_routine,GAME_ID},
        {ARRIVE_EVENT,game,checkLevelUp,GAME_ID},
        {COLLISION_EVENT,game,checkLives,GAME_ID},
        {FORWARD_EVENT,game,update_score,GAME_ID},
        {END_TABLE,game,non_act_routine,GAME_ID}
    };
    state_t pauseMenuResume[3+1] = {
        {DOWN_EVENT,pauseMenuBackToStart,non_act_routine,PAUSE_RESUME_ID},
        {UP_EVENT,pauseMenuBackToStart,non_act_routine,PAUSE_RESUME_ID},
        {ENTER_EVENT,game,non_act_routine,PAUSE_RESUME_ID},
        {END_TABLE,pauseMenuResume,non_act_routine,PAUSE_RESUME_ID}
    };
    state_t pauseMenuBackToStart[3+1] = {
        {UP_EVENT,pauseMenuResume,non_act_routine,PAUSE_RESTART_ID},
        {DOWN_EVENT,pauseMenuResume,non_act_routine,PAUSE_RESTART_ID},
        {ENTER_EVENT,startMenuPlayGame,non_act_routine,PAUSE_RESTART_ID},
        {END_TABLE,pauseMenuBackToStart,non_act_routine,PAUSE_RESTART_ID}
    };
    state_t saveScoreChar[5+1] = {
        {DOWN_EVENT,saveScoreChar,f_letter_down,SAVE_SCORE_ID},
        {UP_EVENT,saveScoreChar,f_letter_up,SAVE_SCORE_ID},
        {LEFT_EVENT,saveScoreChar,previousChar,SAVE_SCORE_ID},
        {RIGHT_EVENT,saveScoreChar,nextChar,SAVE_SCORE_ID},
        {ENTER_EVENT,startMenuPlayGame,saveScore,SAVE_SCORE_ID},
        {END_TABLE,saveScoreChar,non_act_routine,SAVE_SCORE_ID}
    };
    uint16_t event;
    gameData_t gameData;
    gameData.currentState = startMenuPlayGame;  //estado inicial
    gameData.quitGame = false;
    gameData.cabeza = saveScoreChar;
    
    *(gameData.pEventQueue) = create_queue();   //creacion de la cola de eventos

    pthread_t input_id,output_id;   
    pthread_create(&input_id,NULL,input_thread,gameData.pEventQueue);  //creacion de threads de input y output
    pthread_create(&output_id,NULL,output_thread,&gameData);
    
    while( !gameData.quitGame )
    {
        if( event = get_event(gameData.pEventQueue) )
        {
            gameData.currentState = fsm_handler(gameData.currentState,event,&gameData);
        }    
    }    
    
    pthread_join(input_id,NULL);
    return (EXIT_SUCCESS);
}


/****************************** FSM_HANDLER FUNCTION *********************************/
state_t* fsm_handler(state_t *currentState, uint16_t newEvent, void *pActRoutineData)
{
    
    while(currentState->eventType != newEvent && currentState->eventType != END_TABLE)
    {
        currentState++;
    }

    (*currentState->actionRoutine)(pActRoutineData);
    currentState = currentState->nextState;
    return currentState;
    
}