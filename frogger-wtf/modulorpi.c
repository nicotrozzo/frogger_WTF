 /*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "modulorpi.h"
#include "eventQueue.h"
#include "gameStructs.h"
#include "timer_threads.h"

extern sem_t levelUpSem;

const bool letters[N_OF_LETTERS][LENGHT_Y][LENGHT_X] = {
  { {1,1,1,1},
    {1,0,0,1},
    {1,1,1,1},
    {1,0,0,1},
    {1,0,0,1},
  },
  { {1,1,1,0},
    {1,0,1,0},
    {1,1,1,1},
    {1,0,0,1},
    {1,1,1,1},
  },
  { {1,1,1,1},
    {1,0,0,0},
    {1,0,0,0},
    {1,0,0,0},
    {1,1,1,1}
  }                     //HACER LETRASSSSSSSSSS
};

const bool numbers[N_OF_NUMBERS][LENGHT_Y][LENGHT_X] = {
  { {1,1,1,1},
    {1,0,0,1},
    {1,0,0,1},
    {1,0,0,1},
    {1,1,1,1},
  },
  { {0,1,1,0},
    {0,0,1,0},
    {0,0,1,0},
    {0,0,1,0},
    {0,1,1,1},
    },
  { {1,1,1,1},
    {0,0,0,1},
    {1,1,1,1},
    {1,0,0,0},
    {1,1,1,1},
  },
  { {1,1,1,1},
    {0,0,0,1},
    {0,0,1,1},
    {0,0,0,1},
    {1,1,1,1},
  },
  { {1,0,0,1},
    {1,0,0,1},
    {1,1,1,1},
    {0,0,0,1},
    {0,0,0,1}
  },
  { {1,1,1,1},
    {1,0,0,0},
    {1,1,1,1},
    {0,0,0,1},
    {1,1,1,1},
  },
  { {1,1,1,1},
    {1,0,0,0},
    {1,1,1,1},
    {1,0,0,1},
    {1,1,1,1}
  },
  { {1,1,1,1},
    {0,0,0,1},
    {0,0,1,0},
    {0,1,0,0},
    {0,1,0,0}  
  },
  { {1,1,1,1},
    {1,0,0,1},
    {1,1,1,1},
    {1,0,0,1},  
    {1,1,1,1}
  },
  { {1,1,1,1},
    {1,0,0,1},
    {1,1,1,1},
    {0,0,0,1},
    {1,1,1,1}
  }
};

const bool initCarsBoard[DISSIZE][DISSIZE] = {
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

/*const bool initCarsBoard[DISSIZE][DISSIZE] = {
    {1,1,0,1,1,0,1,1,0,1,1,0,1,1,0,1},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0},
    {0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0},
    {1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0},
    {1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    };*/

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
    {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
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
    {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0}
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

static void printBoard(const bool p2board[][DISSIZE]);
static void printCars(bool p2board[][DISSIZE]);
static bool checkWin(frog_t *frogCoords, bool board[][DISSIZE]);
static bool checkCollision(frog_t *frogCoords,bool board[][DISSIZE]);
static void moveFrog(uint8_t where,frog_t *frogCoords);
static void cars_routine(bool board[][DISSIZE],frog_t *frogCoords);
static void shift_handler(bool board[DISSIZE][DISSIZE], bool way, int row_num);
static void shift_right_row(bool row[DISSIZE][DISSIZE], int row_num);
static void shift_left_row(bool row[DISSIZE][DISSIZE], int row_num);
static void showLives(int lives);
static void copyBoard(bool destination[][DISSIZE],const bool source[][DISSIZE]);
static void printChar(const bool p2Letters[5][4], int init_x, int init_y);

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
    bool carsBoard[DISSIZE][DISSIZE];

    frog_t frogCoords = {7,15};
    uint8_t frogCounter = FROG_REFRESH;
    gameData_t *pGameData = pointer;
    int maxPosition = INIT_Y;
    printBoard(off);    //apaga el display
    display_update();
    
    bool carsTimer = false, dispTimer = false;
    pthread_t frogTid, dispTid;
    pthread_create(&frogTid,NULL,carsTimeThread,&carsTimer);    //creacion de timer para parpadeo de la rana
    pthread_create(&dispTid,NULL,dispTimeThread,&dispTimer);
    bool toggle = false;    //variable para el parpadeo de la rana
    
    /*variables de estado escorbord*/
    char name[4];
    char charedScore[7];//hacer DEFINES DE TOTODODODODODODO
    char charedPosition;
    //int i,position,waitCounter = CHANGE_SCORE_TIMES;
    int i,waitCounter = CHANGE_SCORE_TIMES;
    bool change = true;

    while(!pGameData->quitGame)
    {
        /*ESTADOS INICIALES, MENU DE INICIO: EMPEZAR A JUGAR, MOSTRAR SCOREBOARD O SALIR DEL JUEGO*/
        while( (pGameData->currentState->stateID == START_PLAY_ID || pGameData->currentState->stateID == START_QUIT_ID || pGameData->currentState->stateID == START_SCOREBOARD_ID) && !pGameData->quitGame )//mientras esta en los estados del startmenu
        {
            switch(pGameData->currentState->stateID)    //muestra el bitmap correspondiente a cada estado
            {
                case START_PLAY_ID:
                    printBoard(play);
                    copyBoard(carsBoard,initCarsBoard); //va a pasar al estado de juego, carga el estado inicial de los autos
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
         /*ESTADO DE MOSTRAR EL SCOREBOARD*/
        while( pGameData->currentState->stateID == SCORE_BOARD_ID )
        {
            if(pGameData->scoreFile)  //si no se cargo el archivo no hace nada
            {
                if(!pGameData->move.flag)  //si no pidieron ver otro puntaje
                {
                  if(change)
                  {
                      charedPosition = fgetc(pGameData->scoreFile); //obtiene la posicion en el scoreBoard (primer caracter de la linea)
                      while( (name[0] = fgetc(pGameData->scoreFile)) == ' ');  //avanza hasta que no haya espacios y queda guardada la primera letra en el arreglo
                      fgets(&name[1],3,pGameData->scoreFile); //CUIDADO PUEDE ESTAR SOBREESCRIBIENDO ALGO O NO ALCANZARLE EL LUGAR PARA EL TERMINADOR//carga el nombre de la posicion actual
                      while( (charedScore[0] = fgetc(pGameData->scoreFile)) == ' '); //avanza hasta que no haya espacios y queda guardado el primer numero en el arreglo
                      i = 0;
                      while(charedScore[i] != '\n')
                      {
                          charedScore[++i] = fgetc(pGameData->scoreFile);
                      }
                      charedScore[i] = '\0';
                      fseek(pGameData->scoreFile, -1, SEEK_CUR);
                      change = false;
                  }
                  if(waitCounter)   //si todavia tiene que mostrar el nombre, lo hace
                  {
                      printBoard(off);
                      printChar(numbers[charedPosition - '0'],POSITION_X,POSITION_Y);
                      showName(name);   //OJO NO ESTA PROBADOOOOOOOO
                  }
                  else  //sino, debe mostrar el puntaje
                  {
                      printBoard(off);
                      showScore(charedScore);   //OJO ESTO NO ESTA PROBADO
                  }
                  if(dispTimer)   //entra cada un determinado tiempo
                  {
                    if(waitCounter)
                    {
                      waitCounter--; //espera a tener que mostrar el puntaje
                    }
                    dispTimer = false;  //avisa que ya vio el evento de timer;
                    display_update();
                  }
                }
                else
                {
                    if(pGameData->move.where == FROG_UP)
                    {
                        if(pGameData->position != 0) //es ciclico
                        {
                            pGameData->position--; //posicion anterior en el top
                            fseek(pGameData->scoreFile, 0, SEEK_SET);//voy al principio de archivo

                            while((fgetc(pGameData->scoreFile)) != ('1' + pGameData->position) )  // busco en la primer posicion de cada renglon el numero deseado
                            {
                                while( (charedPosition = fgetc(pGameData->scoreFile)) != '\n' );
                            }
                            fseek(pGameData->scoreFile, -1, SEEK_CUR);//como tome el caracter que queria el cursor avanzo, asi lo hago retroceder una posicion
                        }
                      else // si la posicion actual es 0
                      {
                          pGameData->position = 4;//voy al ultimo lugar
                          while((charedPosition = fgetc(pGameData->scoreFile)) != '5' )
                          {
                              while( (charedPosition = fgetc(pGameData->scoreFile)) != '\n' );// busco el numero 5
                          }
                          fseek(pGameData->scoreFile, -1, SEEK_CUR);//como tome el caracter que queria el cursor avanzo, asi lo hago retroceder una posicion
                      }
                    }
                    else if ( pGameData->move.where == FROG_DOWN)
                    {
                        if(pGameData->position != 4)
                        {
                            pGameData->position ++;
                            while( (charedPosition = fgetc(pGameData->scoreFile)) != '\n'); //voy a la siguiente posicion en el top
                        }
                        else
                        {
                            pGameData->position = 0;
                            fseek(pGameData->scoreFile, 0, SEEK_SET);//voy al principio del archivo
                        }
                    }
                    pGameData->move.flag = 0;//pongo el flag de move en 0 para avisar que ya termine
                    waitCounter = CHANGE_SCORE_TIMES;
                    change = true;
                }
            }
        }
        /*ESTADO DE JUEGO*/
        while( pGameData->currentState->stateID == GAME_ID )//mover autos,VER CARS_ROUTINE
        {
            if(carsTimer)
            {
              cars_routine(carsBoard,&frogCoords);  //mueve los autos
              carsTimer = false;
            }
            if(pGameData->move.flag)
            {
                moveFrog(pGameData->move.where,&frogCoords);    //mueve la rana si hay que moverla
                pGameData->move.flag = false;
            }
            if( checkCollision(&frogCoords,carsBoard) )         //FIJARSE EL ORDEN! SI PERDIO CAPAZ HAYA QUE PONER UN BREAK
            {
                maxPosition = INIT_Y;
                if( !emit_event(pGameData->pEventQueue,COLLISION_EVENT) )   //si la rana choco, le avisa al kernel
                {
                    printf("Couldn't emit event\n");
                }
                showLives(--pGameData->lives);  //muestra al jugador la cantidad de vidas restantes
                display_update();
                sleep(1);
                pGameData->move.flag = false; //no interesa si quisieron mover la rana mientras se mostraba el mensaje, se tira ese evento
            }
            else if( checkWin(&frogCoords,carsBoard) )
            {
                maxPosition = INIT_Y;
                if( !emit_event(pGameData->pEventQueue,ARRIVE_EVENT) )
                {
                    printf("Couldn't emit event\n");
                }
                //ALLEGRO TIENE QUE TENER ESTE MISMO SEMAFORO
                sem_wait(&levelUpSem);
                if(pGameData->levelUp)
                {
                    copyBoard(carsBoard,initCarsBoard);
                    cars_routine(NULL,&frogCoords);
                    printBoard(levelUp);    //avisa al jugador que subio de nivel
                    pGameData->levelUp = 0;
                    display_update();
                    sleep(1);
                    pGameData->move.flag = false; //no interesa si quisieron mover la rana mientras se mostraba el mensaje, se tira ese evento
                }
            }
            else if(maxPosition > frogCoords.y)
            {
                maxPosition = frogCoords.y;     //se fija si avanzo mas que antes, si lo hizo le avisa al main para actualizar el puntaje
                if( !emit_event(pGameData->pEventQueue,FORWARD_EVENT) )
                {
                    printf("Couldn't emit event\n");
                }
            }
            if(pGameData -> lives ) //si el jugador no perdio, imprime si es que haya que imprimir
            {
                printCars(carsBoard);  //Escribe en el display el estado actual de autos y troncos
                if(dispTimer)
                {
                    if(!frogCounter--)
                    {
                        frogCounter = FROG_REFRESH;
                        //toggle = !toggle;
                        display_write(frogCoords.y,frogCoords.x,0);  //apaga la posicion de la rana, una cada FROG_REFRESH veces
                    }
                    else
                    {
                        display_write(frogCoords.y,frogCoords.x,1);
                    }
                    display_update();
                    dispTimer = false;
                }
            }
        }
        /*ESTADOS DE PAUSA: SEGUIR JUGANDO O VOLVER AL MENU DE INICIO*/
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
        /*ESTADO DE GUARDAR PUNTAJE*/
        while( pGameData->currentState->stateID == SAVE_SCORE_ID )
        {
            showScore(itoa(pGameData->score,charedScore,10); //VER QUE PASA CON EL NULL!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            sleep(3);//mostrar puntaje y pedir letras
            pGameData->move.flag = false;
            while(!enter)
            {
                showName(pGameData->player);
                //display_update();
                if(carsTimer);
                
                    
                switch(pGameData->position)
                {
                    case 0:
                        break;
                    case 1:
                        break;
                    case 2:
                        break;
                
                
                }        
                //imprimir las 3 letras del arreglo, hacer parpadear la que esta seleccionada
            
                //PARPADEO
            
            }
            
            
            
            
            if(pGameData->scoreFile);
                
        }

    }
    display_clear();
    //printBoard(off);
    display_update();
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
void printBoard(const bool p2board[][DISSIZE])
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

void printCars(bool p2board[][DISSIZE])
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

/*printChar:
Recibe:
  -Puntero a un arreglo de bools de 3 dimensiones
  -Numero de elemento del arreglo al que se quiere acceder
  -Coordenadas iniciales (tener en cuenta que arranca en 0)
Funcion: Escribe en el display el contenido del arreglo en las posiciones pedidas
Cuidado: las coordenadas deben tener en cuenta que la primera posicion es {0,0}
*/

void printChar(const bool p2Letters[5][4], int init_x, int init_y)
{
  int i,j;
  for( i = 0 ; i < LENGHT_Y ; i++ )
  {
    for( j = 0 ; j < LENGHT_X ; j++)
    {
      display_write(i+init_y,j+init_x,p2Letters[i][j]);
    }
  }
}

void moveFrog(uint8_t where,frog_t *frogCoords)
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

void showLives(int lives)
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



/*copyBoard:
 Copia todos los elementos de un arreglo a otro, de tamano DISSIZE*/
void copyBoard(bool destination[][DISSIZE],const bool source[][DISSIZE])
{
    int i,j;
    for( i=0; i<DISSIZE ; i++ )
    {
        for(j=0 ; j<DISSIZE ; j++)
        {
            destination[i][j]=source[i][j];
        }
    }
}
/*showScore: recibe un arreglo de numeros y los imprime en el display, arriba los 3 primeros y abajo los 3 siguientes. Si tiene mas de 6 numeros 
 ignora los restantes.
 DEBE ESTAR DEFINIDO EL ARREGLO NUMBERS[10][5][4] CON LO QUE SE QUIERE QUE SE MUESTRE CON CADA NUMERO
 Usa la funcion printChar */
void showScore(char charedScore[])
{
    int i;
    for( i=0 ; (i < MAXNUMBERS) && (i < strlen(charedScore)) ; i++) //el largo de charedScore debe ser MENOR O IGUAL A MAXNUMBERS para que funcione
    {
        if(i < DISPLAY_MIDDLE)  //distingue si hay que imprimir en la primera o segunda fila
        {
            printChar(numbers[charedScore[i]-'0'], (LENGHT_X + 1)*i + 1 , FIL1); //imprime en el display cada numero del arreglo score
        }
        else
        {
            printChar(numbers[charedScore[i]-'0'], (LENGHT_X + 1)*(i-DISPLAY_MIDDLE) + 1 , FIL2);
        }
    }
}    
/*showName: recibe un arreglo de letras MAYUSCULAS y las imprime en el display
 DEBE ESTAR DEFINIDIO EL ARREGLO LETTER CON TODAS LAS LETRAS DEL ABECEDARIO (26)*/
void showName(char name[])
{
    int i;
    for( i=0 ; i < NOFCHARS ; i++)
    {
        printChar(letters[name[i]-'A'], (LENGHT_X + 1)*i + 1 , LETTER_POS_Y); //imprime en el display cada letra del arreglo nombre, supone que estan todas en mayuscula
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
