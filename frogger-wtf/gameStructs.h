/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   gameStructs.h
 * Author: nico
 *
 * Created on June 22, 2018, 5:54 PM
 */

#ifndef GAMESTRUCTS_H
#define GAMESTRUCTS_H

#include <stdbool.h>
#include "eventQueue.h"

typedef struct STATE
{
    uint16_t eventType;
    struct STATE *nextState;
    void (*actionRoutine)(void *);
    int stateID;
} state_t;

typedef struct
{
    char player[3];
    uint score;
} scorer_t;

typedef struct
{
    uint8_t x;
    uint8_t y;
}frog_t;

typedef struct
{
    bool flag;
    uint8_t where;
}move_t;

typedef struct
{
    int lives;
    char position;
    bool levelUp; 
    bool quitGame;
    move_t move; 
    char player[3];
    unsigned int score;
    FILE *scoreFile;
   // scorer_t (*pTop10)[10];     //pensar si conviene
    state_t *currentState;
    event_queue_t *pEventQueue;
}gameData_t;

enum ids {
    START_PLAY_ID,
    START_SCOREBOARD_ID,
    START_QUIT_ID,
    SCORE_BOARD_ID,
    GAME_ID,
    PAUSE_RESUME_ID,
    PAUSE_RESTART_ID,
    SAVE_SCORE_ID
};

enum events {
    RIGHT_EVENT = 1024,
    UP_EVENT,
    DOWN_EVENT,
    LEFT_EVENT,
    ENTER_EVENT,
    ARRIVE_EVENT,
    COLLISION_EVENT,
    GAME_OVER_EVENT,
    FORWARD_EVENT,
    END_TABLE
};    


#endif /* GAMESTRUCTS_H */
