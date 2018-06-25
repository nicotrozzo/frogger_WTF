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
#include "action_routines.h"
#include "fsm.h"

state_t* fsm_handler(state_t *currentState, uint16_t newEvent, void *pActRoutineData);


int main(void) 
{
    
    uint16_t event;
    gameData_t gameData;
    gameData.currentState = startMenuPlayGame;  //estado inicial
    gameData.quitGame = false;
    event_queue_t queue = create_queue();
    gameData.pEventQueue = &queue;   //creacion de la cola de eventos

    pthread_t input_id,output_id;   
    pthread_create(&input_id,NULL,input_thread,gameData.pEventQueue);  //creacion de threads de input y output
    pthread_create(&output_id,NULL,output_thread,&gameData);
    
    while( !gameData.quitGame )
    {
        if( (event = get_event(gameData.pEventQueue)) )
        {
            gameData.currentState = fsm_handler(gameData.currentState,event,&gameData);
        }    
    }       
    pthread_join(output_id,NULL);
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