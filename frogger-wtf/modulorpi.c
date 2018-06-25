 /*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "modulorpi.h"
#include "eventQueue.h"
#include "gameStructs.h"
#include "timer_threads.h"

const bool startMenu[DISSIZE][DISSIZE] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
    {0,0,0,1,1,0,0,0,0,0,0,0,1,0,0,0},
    {0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0},
    {0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    };
const bool quit[DISSIZE][DISSIZE] = {
   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
   {0,0,0,0,0,1,0,1,1,0,1,0,0,0,0,0},
   {0,0,0,0,1,0,0,1,1,0,0,1,0,0,0,0},
   {0,0,0,1,0,0,0,1,1,0,0,0,1,0,0,0},
   {0,0,0,1,0,0,0,1,1,0,0,0,1,0,0,0},
   {0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0},
   {0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0},
   {0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0},
   {0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};
const bool trophie[DISSIZE][DISSIZE] = {
   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
   {0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
   {0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0},
   {0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
   {0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
   {0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
   {0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
   {0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0},
   {0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
   {0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};
const bool play[DISSIZE][DISSIZE] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0},
    {0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0},
    {0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0},
    {0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0},
    {0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
    {0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0},
    {0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0},
    {0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0},
    {0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0},
    {0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

const bool levelUp[DISSIZE][DISSIZE] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {1,0,0,1,1,0,1,0,0,1,0,1,1,0,1,0},
    {1,0,0,1,0,0,1,0,0,1,0,1,0,0,1,0},
    {1,0,0,1,1,0,1,0,0,1,0,1,1,0,1,0},
    {1,0,0,1,0,0,1,0,0,1,0,1,0,0,1,0},
    {1,1,0,1,1,0,0,1,1,0,0,1,1,0,1,1},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,1,0,0,0,0,1,0,1,0,0,0},
    {0,0,0,0,1,1,1,0,0,0,1,0,1,0,0,0},
    {0,0,0,1,0,1,0,1,0,0,1,0,1,0,0,0},
    {0,0,0,0,0,1,0,0,0,0,1,0,1,0,0,0},
    {0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,1,0,0,0,0,1,0,1,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};


const bool oneLive[DISSIZE][DISSIZE] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0},
    {0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0},
    {0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0},
    {0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0},
    {0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

const bool twoLives[DISSIZE][DISSIZE] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0},
    {0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0},
    {0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0},
    {0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0},
    {0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};
 
const bool threeLives[DISSIZE][DISSIZE] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0},
    {0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0},
    {0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0},
    {0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0},
    {0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

const bool fourLives[DISSIZE][DISSIZE] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0},
    {0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0},
    {0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0},
    {0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0},
    {0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

const bool fiveLives[DISSIZE][DISSIZE] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0},
    {0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0},
    {0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0},
    {0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0},
    {0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

const bool noLives[DISSIZE][DISSIZE] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,1,0,1,0,0,1,0,1,0,0,1,0},
    {0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0},
    {0,1,0,0,1,0,1,0,0,1,0,1,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,1,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,1,1,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,1,1,1,1,0,0,0,0,1,0},
    {0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0},
    {0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0},
    {0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

const bool off[DISSIZE][DISSIZE] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    };

static void printBoard(bool p2board[][DISSIZE]);
static bool checkWin(frog_t *frogCoords, bool board[][DISSIZE]);
static bool checkCollision(frog_t *frogCoords,bool board[][DISSIZE]);
static void moveFrog(uint16_t where,frog_t *frogCoords);
static void cars_routine(bool board[][DISSIZE],frog_t *frogCoords);
static void shift_handler(bool board[DISSIZE][DISSIZE], bool way, int row_num);
static void shift_right_row(bool row[DISSIZE][DISSIZE], int row_num);
static void shift_left_row(bool row[DISSIZE][DISSIZE], int row_num);
static void showLives(int lives);

void* input_thread (void* eventQueue)//genera eventos de movimiento del joystick
{
  event_queue_t *my_event_queue = eventQueue; //asigno puntero para no tener que castear pcada vez que quiero usarlo
  jcoord_t my_coordinates;
  jswitch_t my_switch = J_NOPRESS;
  bool trigger_lock_x = false;
  bool trigger_lock_y = false;
  bool switch_lock = false;

  joy_init();
  set_joy_axis(JOY_NORMAL);	// OJO considero que usamos joystick abajo y no a la izq
  set_joy_direction(J_INV_FALSE,J_INV_FALSE);

  infinite_loop
  {
    joystick_update();
    my_switch=joystick_get_switch_value();//recibe valores actuales del joystick y el boton
    my_coordinates = joystick_get_coord();
#define TELEFONOSAMPA 1
    if(TELEFONOSAMPA) //generador de eventos
    {
       if(!trigger_lock_x)
       {
         if(my_coordinates.x > JOY_THRESHOLD )
         {
          if(emit_event(my_event_queue , RIGHT_EVENT))
          {
            trigger_lock_x = true;
            printf("RIGHT EVENT\n");
          }
          else
          {
              printf("EVENT QUEUE IS FULL");
          }
           
         }
         else if(my_coordinates.x < -JOY_THRESHOLD )
         {
          if(emit_event(my_event_queue , LEFT_EVENT))
          {
            trigger_lock_x = true;
            printf("LEFT EVENT\n");
          }
          else
          {
              printf("EVENT QUEUE IS FULL");
          }
         }
       }
       if(!trigger_lock_y)
       {
         if(my_coordinates.y > JOY_THRESHOLD )
         {
           if(emit_event(my_event_queue , UP_EVENT))
           {
            trigger_lock_y = true;
            printf("UP EVENT\n");
           }
           else
          {
              printf("EVENT QUEUE IS FULL");
          }
         }
         else if(my_coordinates.y < -JOY_THRESHOLD )
         {
           if(emit_event(my_event_queue , DOWN_EVENT))
           {
            trigger_lock_y = true;
            printf("DOWN EVENT\n");
           }
          }
       }
       if(my_switch == J_PRESS && !switch_lock)
    	{
            if(emit_event(my_event_queue , ENTER_EVENT))
             {
                switch_lock = true;
                printf("ENTER EVENT\n");
             }
             else
             {
                printf("EVENT QUEUE IS FULL");
             }
         }
    
    }
    if (trigger_lock_x && my_coordinates.x < JOY_THRESHOLD && my_coordinates.x > -JOY_THRESHOLD)  //bloqueo de lectura para evitar que se envie el evento si se mantiene presionado
    {
      trigger_lock_x = false;
      //printf("TRIGGERLOCKX OFF\n");
    }
    if (trigger_lock_y && my_coordinates.y < JOY_THRESHOLD && my_coordinates.y > -JOY_THRESHOLD)  //bloqueo de lectura para evitar que se envie el evento si se mantiene presionado
    {
      trigger_lock_y = false;
      //printf("TRIGGERLOCKY OFF\n");
    }
    if (switch_lock && my_switch == J_NOPRESS)  //bloqueo de lectura para evitar que se envie el evento si se mantiene presionado
    {
      switch_lock = false;
      //printf("SWITCHLOCK OFF\n");
    }
  }
}

/*output_thread (de Raspberry Pi)
Recibe un puntero a la estructura gameData que contiene la informacion del juego
Se encarga de:
-manejar los menús juego
-Mover la rana, los autos y los troncos
-Imprimir todo en el display de 16x16
-Informar al kernel cuando hubo un choque
-Hacer parpadear la rana para diferenciarla de los autos (para eso usa el thread frogTimeThread) */

void* output_thread(void* pointer)
{
    bool carsBoard[DISSIZE][DISSIZE] = {
        {1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1},
        {0,0,1,1,1,1,1,0,0,1,1,1,1,1,1,1},
        {0,0,1,1,1,1,1,0,0,1,1,0,0,1,1,1},
        {1,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0},
        {0,0,0,1,1,1,1,0,0,0,1,1,1,1,1,1},
        {1,1,1,1,0,0,0,1,1,1,1,0,0,0,1,1},
        {1,1,1,1,0,0,0,1,1,1,1,1,1,0,0,0},
        {1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0},
        {0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0},
        {1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0},
        {1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
        };
                                            
    frog_t frogCoords = {7,15};
    uint8_t frogCounter = FROG_REFRESH;
    gameData_t *pGameData = pointer;
    int maxPosition = INIT_Y;

    /*display_init(); // inicializacion del display
    set_display_axis(NORMAL);
    display_clear();
    display_update();*/
    printBoard(off);    //apaga el display   
    display_update();

    bool carsTimer = false, dispTimer = false;
    pthread_t frogTid, dispTid;
    pthread_create(&frogTid,NULL,carsTimeThread,&carsTimer);    //creacion de timer para parpadeo de la rana
    pthread_create(&dispTid,NULL,dispTimeThread,&dispTimer);
    bool toggle = false;    //variable para el parpadeo de la rana

    infinite_loop
//    while(!pGameData->quitGame)
    {
        while(pGameData->currentState->stateID == START_PLAY_ID || pGameData->currentState->stateID == START_QUIT_ID || pGameData->currentState->stateID == START_SCOREBOARD_ID) //mientras esta en los estados del startmenu
        {
            switch(pGameData->currentState->stateID)
            {
                case START_PLAY_ID:
                    printBoard(play);
                    break;
                case START_SCOREBOARD_ID:
                    printBoard(trophie);
                    break;
                case START_QUIT_ID:
                    printBoard(quit);
                    break;
            }
            if(dispTimer)
            {
              display_update();
              dispTimer = false;
            }
        }

        while( pGameData->currentState->stateID == SCORE_BOARD_ID )
        {
            printf("Aca estaria el scoreboard si tan solo lo tuviera\n");
            /*showName( *(pGameData->pTop10 + i) );
            if(!timer)
            {
                showScore( *(pGameData->pTop10 + i) );
            }
            if()
            estadoActual = pGameData->currentState->stateID;*/
        }

        while( pGameData->currentState->stateID == GAME_ID )//mover autos,VER CARS_ROUTINE
        {
            if(carsTimer)
            {
              cars_routine(carsBoard,&frogCoords);  //mueve los autos y si hace falta la rana
              carsTimer = false;
            }
            if(pGameData->moveFrog.flag)
            {
                moveFrog(pGameData->moveFrog.where,&frogCoords); //HABRIA QUE CAMBIAR GAMEDATA
                if(maxPosition > frogCoords.y)
                {
                    maxPosition = frogCoords.y;     //se fija si avanzo mas que antes, en caso afirmativo le avisa al main para actualizar el puntaje
                    if( !emit_event(pGameData->pEventQueue,FORWARD_EVENT) )
                    {
                        printf("Coludn't emit event\n");
                    }
                }
                pGameData->moveFrog.flag = false;
            }

            printBoard(carsBoard);  //Escribe en el display el estado actual de autos y troncos
            
            if(dispTimer)
            {
                if(!frogCounter--)
                {
                    frogCounter = FROG_REFRESH;
                    //toggle = !toggle;
                    display_write(frogCoords.y,frogCoords.x,0);  //prende/apaga la posicion de la rana
                }
                else
                {
                    display_write(frogCoords.y,frogCoords.x,1);
                }
                display_update();     
                dispTimer = false;
            }
            
            if( checkCollision(&frogCoords,carsBoard) )         //FIJARSE EL ORDEN! SI PERDIO CAPAZ HAYA QUE PONER UN BREAK
            {
                maxPosition = INIT_Y;
                if( !emit_event(pGameData->pEventQueue,COLLISION_EVENT) )   //si la rana choco, le avisa al main
                {
                    printf("Coludn't emit event\n");
                }
                showLives(--pGameData->lives);  //muestra al jugador la cantidad de vidas restantes
                display_update();
                sleep(1);       
            }
            else if( checkWin(&frogCoords,carsBoard) )
            {
                maxPosition = INIT_Y;
                if( !emit_event(pGameData->pEventQueue,ARRIVE_EVENT) )
                {
                    printf("Coludn't emit event\n");
                }
                //SEM WAIT LEVEL UP O PREGUNTAR EN OTRO LADO LEVEL UP, POR EJEMPLO ANTES DE MOVER LOS AUTOS
                if(pGameData->levelUp)
                {
                    cars_routine(NULL,&frogCoords);
                    printBoard(levelUp);    //avisa al jugador que subio de nivel
                    pGameData->levelUp = 0;
                    display_update();
                    sleep(1);
                }

            }

            
            /*if(pGameData->quitGame)
            {
                printBoard(off);
                display_update();
            }    */
        }
        while( pGameData->currentState->stateID == PAUSE_RESUME_ID || pGameData->currentState->stateID == PAUSE_RESTART_ID )
        {
            if( pGameData->currentState->stateID == PAUSE_RESUME_ID)
            {
              printBoard(play);
            }
            else if( pGameData->currentState->stateID == PAUSE_RESTART_ID)
            {
              printBoard(startMenu);
            }
            if(dispTimer)
            {
              display_update();
              dispTimer = false;
            }
        }
        while( pGameData->currentState->stateID == SAVE_SCORE_ID )
        {
            printf("Ahora estarias guardando tu puntaje si pudieras, puto\n");
        }    
        
    }
    /*printf("SALI DEL WHILE!\n");
    printBoard(off);
    display_update();*/
    return NULL;
}

/*checkCollision:
Recibe: posicion de la rana y puntero al arreglo con la posicion de los autos
Devuelve 1 si la rana choco, 0 si no choco.
    Ademas, si choco la devuelve a su posicion inicial */
bool checkCollision(frog_t *frogCoords,bool board[][DISSIZE])
{
  if(board[frogCoords->y][frogCoords->x]) //OJO X E Y!!!
  {
      frogCoords->x = INIT_X;
      frogCoords->y = INIT_Y;
      return true;
  }
  else
  {
      return false;
  }
}

/*checkWin:
Recibe: puntero a la posicion de la rana y puntero al arreglo con los autos, troncos, y posiciones donde puede llegar al final
Devuelve: 1 si llego al final, 0 si no.
Funcionamiento: Se fija si la rana esta en la ultima fila, si esta gano porque se acaba de fijar que no haya chocado */

bool checkWin(frog_t *frogCoords, bool board[][DISSIZE])
{
  if(!frogCoords->y)   //si la rana esta en la ultima fila(fila 0)
  {
    board[frogCoords->y][frogCoords->x] = 1;    //OJO X E Y//deja prendido el lugar adonde llego la rana
    frogCoords->y = INIT_Y;    //OJO!!
    frogCoords->x = INIT_X;     //devuelve la rana a su posicion inicial
    return true;
  }
  else
  {
    return false;
  }

}

/*printBoard:
Recibe un puntero al primer elemento de un arreglo de bools
Escribe en un display de 16x16 el contenido de ese arreglo
Nota: debe estar inicializado el display con las herramientas de <disdrv.h> */
void printBoard(bool p2board[][DISSIZE])
{
  int i,j;
  for( i=0 ; i < DISSIZE ; i++ )
  {
    for( j=0 ; j < DISSIZE ; j++)
    {
      display_write(i,j,p2board[i][j]);
    }
  }
}

void moveFrog(uint16_t where,frog_t *frogCoords)
{
  switch(where)
  {        
      case FROG_UP:
          if(frogCoords->y > FROG_Y_MIN)
          {
              frogCoords->y--;
          }
          else if(frogCoords->y < FROG_Y_MIN)
          {
              frogCoords->y = FROG_Y_MIN;
          }
          break;
      case FROG_DOWN:
          if(frogCoords->y < FROG_Y_MAX)
          {
              frogCoords->y++;
          }
          else if(frogCoords->y > FROG_Y_MAX)
          {
              frogCoords->y = FROG_Y_MAX;
          }    
          break;
      case FROG_RIGHT:
          if(frogCoords->x < FROG_X_MAX)
          {
              frogCoords->x++;
          }      
          else if(frogCoords->x > FROG_X_MAX)
          {
              frogCoords->x = FROG_X_MAX; 
          }    
          break;
      case FROG_LEFT:
          if(frogCoords->x > FROG_X_MIN)
          {
              frogCoords->x--;
          }
          else if(frogCoords->x < FROG_X_MIN)   //programacion defensiva
          {
              frogCoords->x = FROG_X_MIN;
          }    
          break;
   }      
}

static void showLives(int lives)
{
    switch(lives)
    {
        case 0:
            printBoard(noLives);
            break;
        case 1:
            printBoard(oneLive);    
            break;
        case 2:
            printBoard(twoLives);
            break;
        case 3:    
            printBoard(threeLives);
            break;
        case 4:
            printBoard(fourLives);
            break;
        default:
            printf("Cuantas vidas queres que tenga?\n");
    }
}






/****************************MOVIMIENTO DE AUTOS*********************************/

/*cars_routine
 * Recibe un puntero a un arreglo con la posicion de los autos y un puntero a la posicion de la rana 
 * Si se subio de nivel (enviar NULL como primer parametro), aumenta la velocidad del movimiento de los autos
 * Sino, mueve los autos (se fija si en este llamado los tiene que mover o no)
 * Recibe NULL si se subio de nivel*/

void cars_routine(bool carsBoard[][DISSIZE],frog_t *frogCoords)
{
    static int dividersMax[DISSIZE] = {0, 15, 20, 8, 15, 20, 8, 15, 0, 12, 7, 12, 10, 7, 10, 0}; // Cuando se suba de nivel, estos máximos se decrementarán para hacer que el ciclo de avance de carril sea más rápido.
    static int dividers[DISSIZE] = {0, 15, 20, 8, 15, 20, 8, 15, 0, 12, 7, 12, 10, 7, 10, 0}; // Ante un evento de timer, se decrementa el divider de cada carril, logrando así que cada carril tenga su ciclo de timer, cuando el divider llega a 0.
    bool ways[DISSIZE] = {0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0};
    int row = 0;

    if(!carsBoard) // Si se tiene que subir de nivel, se efectua un cambio en el máximo de los divisores.
    {
        for(row = 0 ; row < DISSIZE ; row++)
        {
            if(dividersMax[row] > 1)
            {
                dividersMax[row]--;
            }
        }
        frogCoords->x = INIT_X;
        frogCoords->y = INIT_Y; // Se reinicia la posición de la rana.
    }
    else // En cambio, si la rutina fue llamada por evento de timer, se realiza el decremento de los dividers.
    {
        for(row = 0; row < DISSIZE; row++)
        {
            if(dividersMax[row]) // Si no se está en una fila con divider maximo 0...
            {
                dividers[row]--;
                if(!dividers[row]) // Si se cumplió el ciclo, se mueven los autos.
                {
                    shift_handler(carsBoard, ways[row], row);
                    dividers[row] = dividersMax[row]; // Se resetea el ciclo con el maximo de cada divider.
                    if(frogCoords->y == row && row > 0 && row < 8 )
                    {
                        if(ways[row])
                        {
                          if(frogCoords->x != FROG_X_MAX)
                          {
                            frogCoords->x++;     //si ademas esta moviendo troncos, mueve la rana junto con los troncos
                          }
                        }
                        else
                        {
                          if(frogCoords->x != FROG_X_MIN)
                          {
                            frogCoords->x--;
                          }
                        }
                    }
                }
            }
        }
    }
}


void shift_handler(bool board[DISSIZE][DISSIZE], bool way, int row_num)
{
    if(way) // Si way es 1, se gira a la derecha.
    {
        shift_right_row(board, row_num);
    }
    else // Se gira a la izquierda.
    {
        shift_left_row(board, row_num);
    }
}

void shift_right_row(bool row[DISSIZE][DISSIZE], int row_num)
{
    bool aux1 = row[row_num][DISSIZE-1], aux2;
    int i;
    for(i = 0; i < DISSIZE; i++)
    {
        aux2 = row[row_num][i];
        row[row_num][i] = aux1;
        aux1 = aux2;
    }
}

void shift_left_row(bool row[DISSIZE][DISSIZE], int row_num)
{
    bool aux1 = row[row_num][0], aux2;
    int i;
    for(i = 0; i < DISSIZE; i++)
    {
        aux2 = row[row_num][15-i];
        row[row_num][15-i] = aux1;
        aux1 = aux2;
    }
}
