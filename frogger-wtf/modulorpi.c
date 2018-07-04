 /*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "modulorpi.h"
#include "eventQueue.h"
#include "gameStructs.h"
#include "timer_threads.h"

extern sem_t levelUpSem,collisionSem;

const bool letters[][LENGTH_Y][LENGTH_X] = {
  { {X,X,X,X},
    {X,O,O,X},
    {X,X,X,X},
    {X,O,O,X},
    {X,O,O,X},
  },
  { {X,X,X,O},
    {X,O,X,O},
    {X,X,X,X},
    {X,O,O,X},
    {X,X,X,X},
  },
  { {X,X,X,X},
    {X,O,O,O},
    {X,O,O,O},
    {X,O,O,O},
    {X,X,X,X}
  },                     
  { {X,X,X,O},
    {X,O,O,X},
    {X,O,O,X},
    {X,O,O,X},
    {X,X,X,O}
  },
  { {X,X,X,X},
    {X,O,O,O},
    {X,X,X,O},
    {X,O,O,O},
    {X,X,X,X}
  },      
  { {X,X,X,X},
    {X,O,O,O},
    {X,X,X,O},
    {X,O,O,O},
    {X,O,O,O}
  }, 
  { {X,X,X,X},
    {X,O,O,O},
    {X,O,X,X},
    {X,O,O,X},
    {X,X,X,X}
  }, 
  { {X,O,O,X},
    {X,O,O,X},
    {X,X,X,X},
    {X,O,O,X},
    {X,O,O,X}
  }, 
  { {O,X,X,O},
    {O,X,X,O},
    {O,X,X,O},
    {O,X,X,O},
    {O,X,X,O}
  }, 
  { {O,O,O,X},
    {O,O,O,X},
    {O,O,O,X},
    {X,O,O,X},
    {X,X,X,X}
  }, 
  { {X,O,O,X},
    {X,O,X,O},
    {X,X,O,O},
    {X,O,X,O},
    {X,O,O,X}
  }, 
  { {X,O,O,O},
    {X,O,O,O},
    {X,O,O,O},
    {X,O,O,O},
    {X,X,X,X}
  }, 
  { {O,X,X,O},
    {X,X,X,X},
    {X,O,O,X}, 
    {X,O,O,X},
    {X,O,O,X}
  }, 
  { {X,O,O,X},
    {X,X,O,X},
    {X,O,X,X},
    {X,O,O,X},
    {X,O,O,X}
  }, 
  { {X,X,X,X},
    {X,O,O,X},
    {X,O,O,X},
    {X,O,O,X},
    {X,X,X,X}
  }, 
  { {X,X,X,X},
    {X,O,O,X},
    {X,X,X,X},
    {X,O,O,O},
    {X,O,O,O}
  }, 
  { {X,X,X,O},
    {X,O,X,O},
    {X,O,X,O},
    {X,X,X,O},
    {O,O,O,X}
  }, 
  { {X,X,X,X},
    {X,O,O,X},
    {X,X,X,X},
    {X,O,X,O},
    {X,O,O,X}
  }, 
  { {X,X,X,X},
    {X,O,O,O},
    {X,X,X,X},
    {O,O,O,X},
    {X,X,X,X}
  }, 
  { {X,X,X,X},
    {O,X,X,O},
    {O,X,X,O},
    {O,X,X,O},
    {O,X,X,O}
  }, 
  { {X,O,O,X},
    {X,O,O,X},
    {X,O,O,X},
    {X,O,O,X},
    {X,X,X,X}
  }, 
  { {X,O,O,X},
    {X,O,O,X},
    {X,O,O,X},
    {X,O,O,X},
    {O,X,X,O}
  }, 
  { {X,O,O,X},
    {X,O,O,X},
    {X,O,O,X}, 
    {X,X,X,X},
    {O,X,X,O}
  }, 
  { {X,O,O,X},
    {X,O,O,X},
    {O,X,X,O},
    {X,O,O,X},
    {X,O,O,X}
  }, 
  { {X,O,O,X},
    {X,O,O,X},
    {O,X,X,O},
    {O,X,X,O},
    {O,X,X,O}
  }, 
  { {X,X,X,X},
    {O,O,O,X},
    {O,X,X,O},
    {X,O,O,O},
    {X,X,X,X}
  }          
};

const bool numbers[N_OF_NUMBERS][LENGTH_Y][LENGTH_X] = {
  { {X,X,X,X},
    {X,O,O,X},
    {X,O,O,X},
    {X,O,O,X},
    {X,X,X,X},
  },
  { {O,X,X,O},
    {O,O,X,O},
    {O,O,X,O},
    {O,O,X,O},
    {O,X,X,X},
    },
  { {X,X,X,X},
    {O,O,O,X},
    {X,X,X,X},
    {X,O,O,O},
    {X,X,X,X},
  },
  { {X,X,X,X},
    {O,O,O,X},
    {O,O,X,X},
    {O,O,O,X},
    {X,X,X,X},
  },
  { {X,O,O,X},
    {X,O,O,X},
    {X,X,X,X},
    {O,O,O,X},
    {O,O,O,X}
  },
  { {X,X,X,X},
    {X,O,O,O},
    {X,X,X,X},
    {O,O,O,X},
    {X,X,X,X},
  },
  { {X,X,X,X},
    {X,O,O,O},
    {X,X,X,X},
    {X,O,O,X},
    {X,X,X,X}
  },
  { {X,X,X,X},
    {O,O,O,X},
    {O,O,X,O},
    {O,X,O,O},
    {O,X,O,O}  
  },
  { {X,X,X,X},
    {X,O,O,X},
    {X,X,X,X},
    {X,O,O,X},  
    {X,X,X,X}
  },
  { {X,X,X,X},
    {X,O,O,X},
    {X,X,X,X},
    {O,O,O,X},
    {X,X,X,X}
  }
};

const bool offChar[LENGTH_Y][LENGTH_X] = { 
    {O,O,O,O},
    {O,O,O,O},
    {O,O,O,O},
    {O,O,O,O},
    {O,O,O,O}
  };

const bool initCarsBoard[DISSIZE][DISSIZE] = {
    {X,X,O,X,X,O,X,X,O,X,X,O,X,X,O,X},
    {O,O,X,X,X,X,X,O,O,X,X,X,X,X,X,X},
    {O,O,X,X,X,X,X,O,O,X,X,O,O,X,X,X},
    {X,X,X,X,O,O,O,O,O,X,X,X,X,X,O,O},
    {O,O,O,X,X,X,X,O,O,O,X,X,X,X,X,X},
    {X,X,X,X,O,O,O,X,X,X,X,O,O,O,X,X},
    {X,X,X,X,O,O,O,X,X,X,X,X,X,O,O,O},
    {X,X,X,X,O,O,X,X,X,X,O,O,X,X,X,X},
    {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O},
    {X,X,X,O,O,O,X,X,X,X,O,O,O,O,O,X},
    {O,O,O,X,X,O,O,O,X,X,X,X,O,O,O,O},
    {O,O,X,X,O,O,X,X,O,O,X,X,O,O,O,O},
    {X,X,O,X,X,O,O,O,O,O,O,O,O,O,O,O},
    {O,O,O,O,O,X,X,O,O,O,O,X,X,O,O,O},
    {X,X,O,O,O,X,X,O,O,O,X,X,O,O,O,O},
    {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O}
    };

/*const bool initCarsBoard[DISSIZE][DISSIZE] = {
    {X,X,O,X,X,O,X,X,O,X,X,O,X,X,O,X},
    {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O},
    {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O},
    {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O},
    {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O},
    {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O},
    {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O},
    {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O},
    {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O},
    {X,X,X,O,O,O,X,X,X,O,O,O,X,X,X,O},
    {O,O,O,X,X,O,O,O,O,O,O,O,O,O,O,O},
    {O,O,X,X,O,O,X,X,O,O,X,X,O,O,O,O},
    {X,X,O,X,X,O,O,O,O,O,O,O,O,O,O,O},
    {O,O,O,O,O,X,X,O,O,O,O,X,X,O,O,O},
    {X,X,O,O,O,X,X,O,O,O,X,X,O,O,O,O},
    {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O}
    };*/

const bool startMenu[DISSIZE][DISSIZE] = {
    {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O},
    {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O},
    {O,O,O,O,X,O,O,O,O,O,O,O,O,O,O,O},
    {O,O,O,X,X,O,O,O,O,O,O,O,O,O,O,O},
    {O,O,X,X,X,X,X,X,X,X,X,X,X,O,O,O},
    {O,O,O,X,X,O,O,O,O,O,O,O,X,O,O,O},
    {O,O,O,O,X,O,O,O,O,O,O,O,X,O,O,O},
    {O,O,O,O,O,O,O,O,O,O,O,O,X,O,O,O},
    {O,O,O,O,O,O,O,O,O,O,O,O,X,O,O,O},
    {O,O,O,O,O,O,O,O,O,O,O,O,X,O,O,O},
    {O,O,O,O,O,O,O,O,O,O,O,O,X,O,O,O},
    {O,O,O,O,O,O,O,O,O,O,O,O,X,O,O,O},
    {O,O,O,O,O,O,O,O,O,O,O,O,X,O,O,O},
    {O,O,O,O,O,X,X,X,X,X,X,X,X,O,O,O},
    {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O},
    {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O}
    };
const bool quit[DISSIZE][DISSIZE] = {
   {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O},
   {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O},
   {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O},
   {O,O,O,O,O,O,O,X,X,O,O,O,O,O,O,O},
   {O,O,O,O,O,O,O,X,X,O,O,O,O,O,O,O},
   {O,O,O,O,O,X,O,X,X,O,X,O,O,O,O,O},
   {O,O,O,O,X,O,O,X,X,O,O,X,O,O,O,O},
   {O,O,O,X,O,O,O,X,X,O,O,O,X,O,O,O},
   {O,O,O,X,O,O,O,X,X,O,O,O,X,O,O,O},
   {O,O,O,X,O,O,O,O,O,O,O,O,X,O,O,O},
   {O,O,O,O,X,O,O,O,O,O,O,X,O,O,O,O},
   {O,O,O,O,O,X,O,O,O,O,X,O,O,O,O,O},
   {O,O,O,O,O,O,X,X,X,X,O,O,O,O,O,O},
   {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O},
   {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O},
   {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O}
};
const bool trophie[DISSIZE][DISSIZE] = {
   {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O},
   {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O},
   {O,O,X,X,X,X,X,X,X,X,X,X,X,X,O,O},
   {O,O,X,X,X,X,X,X,X,X,X,X,X,X,O,O},
   {O,O,O,X,X,X,X,X,X,X,X,X,X,O,O,O},
   {O,O,O,O,X,X,X,X,X,X,X,X,O,O,O,O},
   {O,O,O,O,X,X,X,X,X,X,X,X,O,O,O,O},
   {O,O,O,O,X,X,X,X,X,X,X,X,O,O,O,O},
   {O,O,O,O,X,X,X,X,X,X,X,X,O,O,O,O},
   {O,O,O,O,O,X,X,X,X,X,X,O,O,O,O,O},
   {O,O,O,O,O,O,X,X,X,X,O,O,O,O,O,O},
   {O,O,O,O,O,O,O,X,X,O,O,O,O,O,O,O},
   {O,O,O,O,O,O,O,X,X,O,O,O,O,O,O,O},
   {O,O,O,O,O,O,O,X,X,O,O,O,O,O,O,O},
   {O,O,O,X,X,X,X,X,X,X,X,X,X,O,O,O},
   {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O}
};
const bool play[DISSIZE][DISSIZE] = {
    {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O},
    {O,O,O,O,X,O,O,O,O,O,O,O,O,O,O,O},
    {O,O,O,O,X,X,O,O,O,O,O,O,O,O,O,O},
    {O,O,O,O,X,X,X,O,O,O,O,O,O,O,O,O},
    {O,O,O,O,X,X,X,X,O,O,O,O,O,O,O,O},
    {O,O,O,O,X,X,X,X,X,O,O,O,O,O,O,O},
    {O,O,O,O,X,X,X,X,X,X,O,O,O,O,O,O},
    {O,O,O,O,X,X,X,X,X,X,X,O,O,O,O,O},
    {O,O,O,O,X,X,X,X,X,X,X,X,O,O,O,O},
    {O,O,O,O,X,X,X,X,X,X,X,O,O,O,O,O},
    {O,O,O,O,X,X,X,X,X,X,O,O,O,O,O,O},
    {O,O,O,O,X,X,X,X,X,O,O,O,O,O,O,O},
    {O,O,O,O,X,X,X,X,O,O,O,O,O,O,O,O},
    {O,O,O,O,X,X,X,O,O,O,O,O,O,O,O,O},
    {O,O,O,O,X,X,O,O,O,O,O,O,O,O,O,O},
    {O,O,O,O,X,O,O,O,O,O,O,O,O,O,O,O}
};

const bool levelUp[DISSIZE][DISSIZE] = {
    {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O},
    {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O},
    {X,O,O,X,X,O,X,O,O,X,O,X,X,O,X,O},
    {X,O,O,X,O,O,X,O,O,X,O,X,O,O,X,O},
    {X,O,O,X,X,O,X,O,O,X,O,X,X,O,X,O},
    {X,O,O,X,O,O,X,O,O,X,O,X,O,O,X,O},
    {X,X,O,X,X,O,O,X,X,O,O,X,X,O,X,X},
    {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O},
    {O,O,O,O,O,X,O,O,O,O,X,O,X,O,O,O},
    {O,O,O,O,X,X,X,O,O,O,X,O,X,O,O,O},
    {O,O,O,X,O,X,O,X,O,O,X,O,X,O,O,O},
    {O,O,O,O,O,X,O,O,O,O,X,O,X,O,O,O},
    {O,O,O,O,O,X,O,O,O,O,O,O,O,O,O,O},
    {O,O,O,O,O,X,O,O,O,O,X,O,X,O,O,O},
    {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O},
    {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O}
};


const bool oneLive[DISSIZE][DISSIZE] = {
    {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O},
    {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O},
    {O,O,O,O,O,O,X,X,O,X,X,O,O,O,O,O},
    {O,O,O,O,O,X,X,X,X,X,X,X,O,O,O,O},
    {O,O,O,O,O,X,X,X,X,X,X,X,O,O,O,O},
    {O,O,O,O,O,O,X,X,X,X,X,O,O,O,O,O},
    {O,O,O,O,O,O,O,X,X,X,O,O,O,O,O,O},
    {O,O,O,O,O,O,O,O,X,O,O,O,O,O,O,O},
    {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O},
    {O,O,O,O,O,O,O,X,X,O,O,O,O,O,O,O},
    {O,O,O,O,O,O,O,O,X,O,O,O,O,O,O,O},
    {O,O,O,O,O,O,O,O,X,O,O,O,O,O,O,O},
    {O,O,O,O,O,O,O,O,X,O,O,O,O,O,O,O},
    {O,O,O,O,O,O,O,O,X,O,O,O,O,O,O,O},
    {O,O,O,O,O,O,O,O,X,O,O,O,O,O,O,O},
    {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O}
};

const bool twoLives[DISSIZE][DISSIZE] = {
    {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O},
    {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O},
    {O,O,O,O,O,O,X,X,O,X,X,O,O,O,O,O},
    {O,O,O,O,O,X,X,X,X,X,X,X,O,O,O,O},
    {O,O,O,O,O,X,X,X,X,X,X,X,O,O,O,O},
    {O,O,O,O,O,O,X,X,X,X,X,O,O,O,O,O},
    {O,O,O,O,O,O,O,X,X,X,O,O,O,O,O,O},
    {O,O,O,O,O,O,O,O,X,O,O,O,O,O,O,O},
    {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O},
    {O,O,O,O,O,O,X,X,X,X,O,O,O,O,O,O},
    {O,O,O,O,O,O,O,O,O,X,O,O,O,O,O,O},
    {O,O,O,O,O,O,X,X,X,X,O,O,O,O,O,O},
    {O,O,O,O,O,O,X,O,O,O,O,O,O,O,O,O},
    {O,O,O,O,O,O,X,O,O,O,O,O,O,O,O,O},
    {O,O,O,O,O,O,X,X,X,X,O,O,O,O,O,O},
    {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O}
};

const bool threeLives[DISSIZE][DISSIZE] = {
    {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O},
    {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O},
    {O,O,O,O,O,O,X,X,O,X,X,O,O,O,O,O},
    {O,O,O,O,O,X,X,X,X,X,X,X,O,O,O,O},
    {O,O,O,O,O,X,X,X,X,X,X,X,O,O,O,O},
    {O,O,O,O,O,O,X,X,X,X,X,O,O,O,O,O},
    {O,O,O,O,O,O,O,X,X,X,O,O,O,O,O,O},
    {O,O,O,O,O,O,O,O,X,O,O,O,O,O,O,O},
    {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O},
    {O,O,O,O,O,O,X,X,X,X,O,O,O,O,O,O},
    {O,O,O,O,O,O,O,O,O,X,O,O,O,O,O,O},
    {O,O,O,O,O,O,X,X,X,X,O,O,O,O,O,O},
    {O,O,O,O,O,O,O,O,O,X,O,O,O,O,O,O},
    {O,O,O,O,O,O,O,O,O,X,O,O,O,O,O,O},
    {O,O,O,O,O,O,X,X,X,X,O,O,O,O,O,O},
    {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O}
};

const bool fourLives[DISSIZE][DISSIZE] = {
    {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O},
    {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O},
    {O,O,O,O,O,O,X,X,O,X,X,O,O,O,O,O},
    {O,O,O,O,O,X,X,X,X,X,X,X,O,O,O,O},
    {O,O,O,O,O,X,X,X,X,X,X,X,O,O,O,O},
    {O,O,O,O,O,O,X,X,X,X,X,O,O,O,O,O},
    {O,O,O,O,O,O,O,X,X,X,O,O,O,O,O,O},
    {O,O,O,O,O,O,O,O,X,O,O,O,O,O,O,O},
    {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O},
    {O,O,O,O,O,O,X,O,O,X,O,O,O,O,O,O},
    {O,O,O,O,O,O,X,O,O,X,O,O,O,O,O,O},
    {O,O,O,O,O,O,X,X,X,X,O,O,O,O,O,O},
    {O,O,O,O,O,O,O,O,O,X,O,O,O,O,O,O},
    {O,O,O,O,O,O,O,O,O,X,O,O,O,O,O,O},
    {O,O,O,O,O,O,O,O,O,X,O,O,O,O,O,O},
    {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O}
};

const bool fiveLives[DISSIZE][DISSIZE] = {
    {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O},
    {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O},
    {O,O,O,O,O,O,X,X,O,X,X,O,O,O,O,O},
    {O,O,O,O,O,X,X,X,X,X,X,X,O,O,O,O},
    {O,O,O,O,O,X,X,X,X,X,X,X,O,O,O,O},
    {O,O,O,O,O,O,X,X,X,X,X,O,O,O,O,O},
    {O,O,O,O,O,O,O,X,X,X,O,O,O,O,O,O},
    {O,O,O,O,O,O,O,O,X,O,O,O,O,O,O,O},
    {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O},
    {O,O,O,O,O,O,X,X,X,X,O,O,O,O,O,O},
    {O,O,O,O,O,O,X,O,O,O,O,O,O,O,O,O},
    {O,O,O,O,O,O,X,X,X,X,O,O,O,O,O,O},
    {O,O,O,O,O,O,O,O,O,X,O,O,O,O,O,O},
    {O,O,O,O,O,O,O,O,O,X,O,O,O,O,O,O},
    {O,O,O,O,O,O,X,X,X,X,O,O,O,O,O,O},
    {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O}
};

const bool noLives[DISSIZE][DISSIZE] = {
    {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O},
    {O,X,X,X,X,X,X,X,X,X,X,X,X,X,X,O},
    {O,X,O,O,O,O,O,O,O,O,O,O,O,O,X,O},
    {O,X,O,O,X,O,X,O,O,X,O,X,O,O,X,O},
    {O,X,O,O,O,X,O,O,O,O,X,O,O,O,X,O},
    {O,X,O,O,X,O,X,O,O,X,O,X,O,O,X,O},
    {O,X,O,O,O,O,O,O,O,O,O,O,O,O,X,O},
    {O,X,O,O,O,O,O,X,O,O,O,O,O,O,X,O},
    {O,X,O,O,O,O,O,X,X,O,O,O,O,O,X,O},
    {O,X,O,O,O,O,O,O,O,O,O,O,O,O,X,O},
    {O,X,O,O,O,O,X,X,X,X,O,O,O,O,X,O},
    {O,X,O,O,O,X,O,O,O,O,X,O,O,O,X,O},
    {O,X,O,O,O,X,O,O,O,O,X,O,O,O,X,O},
    {O,X,O,O,O,O,O,O,O,O,O,O,O,O,X,O},
    {O,X,X,X,X,X,X,X,X,X,X,X,X,X,X,O},
    {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O}
};

const bool off[DISSIZE][DISSIZE] = {
    {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O},
    {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O},
    {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O},
    {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O},
    {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O},
    {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O},
    {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O},
    {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O},
    {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O},
    {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O},
    {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O},
    {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O},
    {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O},
    {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O},
    {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O},
    {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O}
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
static void showName(char name[],int pos_y);
static void showScore(char charedScore[]);
static void init_dividers(int divMax[],int div[]);
static void getLineInfo(FILE *scoreFile,char positionChars[],char name[],char charedScore[]);
static void init_play(bool carsBoard[][DISSIZE],const bool initCarsBoard[][DISSIZE],frog_t *frogCoords, char *maxPosition);
static void firstLinePosition(FILE *p2file);
static int getTotalScores(FILE *p2file);
static void showPosition(char positionChars[]);

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
    char maxPosition = INIT_Y;
    printBoard(off);    //apaga el display
    display_update();

    bool carsTimer = false, dispTimer = false;
    pthread_t frogTid, dispTid;
    pthread_create(&frogTid,NULL,carsTimeThread,&carsTimer);    //creacion de timer para parpadeo de la rana
    pthread_create(&dispTid,NULL,dispTimeThread,&dispTimer);
    bool toggle = false;    //variable para el parpadeo de la rana

    /*variables de estado scoreboard*/
    char name[NOFCHARS + 1];      
    char charedScore[MAXNUMBERS + 1 + 5];   //arreglo para levantar los puntajes de los archivos como strings (+5 de seguridad por si hacen MUCHOS puntos)
    char positionChars[4];                //arreglo para la posicion del jugador
    int i;
    //int totalScores;    //variable para saber cuantos puntajes hay
    unsigned int waitCounter = CHANGE_SCORE_TIMES;
    bool change = true,firstTime = true;

    while(!pGameData->quitGame)
    {
        /*ESTADOS INICIALES, MENU DE INICIO: EMPEZAR A JUGAR, MOSTRAR SCOREBOARD O SALIR DEL JUEGO*/
        while( (pGameData->currentState->stateID == START_PLAY_ID || pGameData->currentState->stateID == START_QUIT_ID || pGameData->currentState->stateID == START_SCOREBOARD_ID) && !pGameData->quitGame )//mientras esta en los estados del startmenu
        {
            switch(pGameData->currentState->stateID)    //muestra el bitmap correspondiente a cada estado
            {
                case START_PLAY_ID:
                    printBoard(play);
                    init_play(carsBoard,initCarsBoard,&frogCoords,&maxPosition);    //inicializa siguiente estado
                    break;
                case START_SCOREBOARD_ID:
                    printBoard(trophie);
                    firstTime = true;            
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
                if(firstTime)
                {
                    waitCounter = CHANGE_SCORE_TIMES;  
                    change = true;
                    firstTime = false;
                }
                if(!pGameData->move.flag)  //si no pidieron ver otro puntaje
                {
                    if(change)
                    {
                        getLineInfo(pGameData->scoreFile,positionChars,name,charedScore);                     
                        waitCounter = CHANGE_SCORE_TIMES; //reinicia contador para muestra del nombre o puntaje
                        change = false;
                    }

                    if(waitCounter)   //si todavia tiene que mostrar el nombre, lo hace
                    {
                        printBoard(off);
                        //printChar(numbers[charedPosition - '0'],POSITION_X,POSITION_Y);
                        showPosition(positionChars);
                        showName(name,LETTER_POS_Y);   
                    }
                    else  //sino, debe mostrar el puntaje
                    {
                        printBoard(off);
                        showScore(charedScore);  
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
                        if(pGameData->position > 0) //es ciclico
                        {
                            pGameData->position--; //posicion anterior en el top
                            fseek(pGameData->scoreFile, 0, SEEK_SET);//voy al principio de archivo
                            for( i=0 ; i < pGameData->position ; i++)
                            {    
                                while( fgetc(pGameData->scoreFile) != '\n' );
                            }
                        }
                        else // si la posicion actual es 0
                        {
                            if( (pGameData->position = getTotalScores(pGameData->scoreFile)-1) > 999)
                            {
                                pGameData->position = 999;      
                                for( i=0 ; i < 999 ; i++)
                                {
                                    while(fgetc(pGameData->scoreFile) != '\n'); //avanza hasta la maxima posicion
                                }
                                fseek(pGameData->scoreFile,-1,SEEK_CUR);    //apunta al ultimo caracter de la linea
                            }    
                            else
                            {    
                                fseek(pGameData->scoreFile,-2, SEEK_END);    //va al final del archivo                                
                            }
                            if(pGameData->position)   //va al principio de la ultima linea 
                            {    
                                firstLinePosition(pGameData->scoreFile);    
                            }
                            else   
                            {
                                rewind(pGameData->scoreFile);    
                            }
                            
                            /*while((charedPosition = fgetc(pGameData->scoreFile)) != '5' ) // busco el numero 5
                            {
                                while( fgetc(pGameData->scoreFile) != '\n' );   //avanza hasta la siguiente linea
                            }
                            fseek(pGameData->scoreFile, -1, SEEK_CUR);//como tome el caracter que queria el cursor avanzo, asi lo hago retroceder una posicion*/
                        }
                    }
                    else if ( pGameData->move.where == FROG_DOWN)
                    {
                        if(pGameData->position < (getTotalScores(pGameData->scoreFile)-1) )
                        {
                            pGameData->position ++;
                            while( fgetc(pGameData->scoreFile) != '\n'); //voy a la siguiente posicion en el top
                        }
                        else
                        {
                            pGameData->position = 0;
                            fseek(pGameData->scoreFile, 0, SEEK_SET);//voy al principio del archivo
                        }
                    }
                    pGameData->move.flag = false;   //pongo el flag de move en 0 para avisar que ya termine                    
                    change = true;  //avisa a la parte que muestra todo que se cambio de posicion
                }
            }
        }
        /*ESTADO DE JUEGO*/
        while( pGameData->currentState->stateID == GAME_ID )
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
            if( checkCollision(&frogCoords,carsBoard) )         
            {
                maxPosition = INIT_Y;
                if( !emit_event(pGameData->pEventQueue,COLLISION_EVENT) )   //si la rana choco, le avisa al kernel
                {
                    printf("Couldn't emit event\n");
                }
                
                showLives(--pGameData->lives);  //muestra al jugador la cantidad de vidas restantes
                display_update();
                sleep(1);
                if(!pGameData->lives)   //si perdio, muestra el puntaje
                {
                    if(pGameData->score <= MAXSCORE)
                    {    
                        sprintf(charedScore,"%u",pGameData->score); //guarda en charedScore el puntaje pasado a string
                    }
                    else
                    {
                        sprintf(charedScore,"%d",MAXSCORE);     //en el display no se pueden mostrar mas de 6 digitos
                    }    
                    printBoard(off);    //borra lo que hubiera en el display
                    showScore(charedScore); //muestra el puntaje del jugador 
                    display_update();
                    sleep(3);               //durante 3 segundos
                    pGameData->move.flag = false;   //si movieron el joystick durante ese tiempo no interesa
                    waitCounter = WAIT_NAME_BLINK;  //inicializa variable para parpadeo de la letra seleccionada
                    firstTime = false;
                    toggle = true;
                }    
                sem_post(&collisionSem);
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
                sem_wait(&levelUpSem);  //espera que el nucleo del juego se fije si subio de nivel
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
            if(pGameData -> lives) //si el jugador no perdio, imprime si es que haya que imprimir
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
            printBoard(off);
            showName(pGameData->player,SCORE_NAME_Y);   //muestra las letras guardadas en su nombre                
            if(pGameData->move.flag)    //si cambiaron, reinicia el parpadeo
            {
                toggle = true;
                waitCounter = WAIT_NAME_BLINK;
                pGameData->move.flag = false;
            }    
            if(dispTimer)
            {
                if(!--waitCounter)
                {
                    toggle = !toggle;
                    waitCounter = WAIT_NAME_BLINK;
                }
                if(!toggle) //si toca apagar, apaga la posicion seleccionada para que parpadee
                {    
                    switch(pGameData->position)    
                    {
                        case 0:
                            printChar(offChar,X_SEPARATION,SCORE_NAME_Y);
                            break;
                        case 1:
                            printChar(offChar,2*X_SEPARATION+LENGTH_X,SCORE_NAME_Y);
                            break;
                        case 2:
                            printChar(offChar,3*X_SEPARATION+2*LENGTH_X,SCORE_NAME_Y);
                            break;  
                        default:
                            pGameData->position = 0;
                    }
                }
                display_update();
                dispTimer = false;                
            }                                        
        }
    }
    display_clear();
    return NULL;
}

/*checkCollision:
Recibe: posicion de la rana y puntero al arreglo con la posicion de los autos
Devuelve 1 si la rana choco, 0 si no choco.
    Ademas, si choco la devuelve a su posicion inicial */
bool checkCollision(frog_t *frogCoords,bool board[][DISSIZE])
{
    if(board[frogCoords->y][frogCoords->x]) //si la posicion de la rana esta prendida (1) en el tablero de los autos, significa que choco
    {
        frogCoords->x = INIT_X;   //devuelve la rana a su posicion inicial
        frogCoords->y = INIT_Y;
        return true;  //avisa que choco
    }
    else
    {
        return false; //avisa que no choco
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
    board[frogCoords->y][frogCoords->x] = 1;    //deja prendido el lugar adonde llego la rana
    frogCoords->y = INIT_Y;    //devuelve la rana a su posicion inicial
    frogCoords->x = INIT_X;     
    return true;    //avisa que gano
  }
  else
  {
    return false;   //avisa que todavia no llego
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
  -Puntero a una matriz de bools con filas de largo LENGTH_X(tamano de bitmaps de las letras) 
  -Numero de elemento del arreglo al que se quiere acceder
  -Coordenadas iniciales (tener en cuenta que arranca en 0)
Funcion: Escribe en el display el contenido del arreglo en las posiciones pedidas
Cuidado: las coordenadas deben tener en cuenta que la primera posicion es {0,0}
*/

void printChar(const bool p2Letters[][LENGTH_X], int init_x, int init_y)
{
  int i,j;
  for( i = 0 ; i < LENGTH_Y ; i++ )
  {
    for( j = 0 ; j < LENGTH_X ; j++)
    {
      display_write(i+init_y,j+init_x,p2Letters[i][j]);
    }
  }
}


/*moveFrog:
 Recibe un entero con identificador para saber adonde mover la rana y un puntero a las coordenadas de la rana
 Si el movimiento pedido de la rana no excede el display, la mueve adonde corresponda*/
void moveFrog(uint8_t where,frog_t *frogCoords)
{
  switch(where)
  {
      case FROG_UP:
          if(frogCoords->y > FROG_Y_MIN)
          {
              frogCoords->y--;
          }
          else if(frogCoords->y < FROG_Y_MIN)   //saturacion, si es el minimo queda igual
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
          else if(frogCoords->x < FROG_X_MIN)  
          {
              frogCoords->x = FROG_X_MIN;
          }
          break;          
   }
}

/*showLives:
 Recibe la cantidad de vidas que le quedan al jugador y en funcion de eso imprime algo distinto*/
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
    }
}



/*copyBoard:
 Copia todos los elementos de un arreglo a otro, de tamano DISSIZE*DISSIZE*/
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

/*getLineInfo:
 Recibe: -Puntero al archivo con el scoreboard, apuntando al principio de alguna linea
         -Puntero a un char donde se guardara la posicion de la linea
         -Arreglo donde guardara el nombre de la linea
         -Arreglo donde se guarda el puntaje de la linea 
 Deja el cursor en el final de la linea*/
void getLineInfo(FILE *scoreFile,char positionChars[],char name[],char charedScore[])
{
    int i = -1;
    do
    {    
        positionChars[++i] = fgetc(scoreFile); //obtiene la posicion en el scoreBoard (primeros caracteres de la linea)
    }
    while(positionChars[i] != ' ');
    positionChars[i]='\0';
    //fseek(scoreFile, 1, SEEK_CUR);  //avanza el espacio
    fgets(name,NOFCHARS + 1,scoreFile); //carga el nombre de la posicion actual, con un terminador
    fseek(scoreFile, 1, SEEK_CUR);  //avanza el espacio                      
    i = -1;
    do
    {
        charedScore[++i] = fgetc(scoreFile);   //levanta todos los caracteres del puntaje
    }
    while(charedScore[i] != '\n');
    charedScore[i] = '\0';
    fseek(scoreFile, -1, SEEK_CUR);    //deja el cursor en el final de la linea
}

/*firstLinePosition:
 Recibe un puntero a un archivo y coloca el cursor al principio de la linea en la que este*/
void firstLinePosition(FILE *p2file)    //VER QUE PASA EN LA PRIMERA LINEA
{
    int caracter = '\0';
    while( caracter != '\n')    //busca el fin de la linea anterior
    {
        fseek(p2file,-2,SEEK_CUR);  
        caracter = fgetc(p2file);
    }    
}
/*getTotalScores:
 Recibe puntero al archivo de scoreboard
 Devuelve cantidad de puntajes que hay(usa que cada linea termina en '\n')*/
int getTotalScores(FILE *p2file)
{
    int totalScores = 0;
    fpos_t initpos;
    fgetpos(p2file,&initpos);      //obtiene posicion actual del cursor
    rewind(p2file);
    do
    {
        while(fgetc(p2file) != '\n');   //avanza una linea
        totalScores++;
    }   
    while(fgetc(p2file) != EOF);
    fsetpos(p2file,&initpos);  //devuelve a la posicion inicial el cursor
    return totalScores;
}

/*showScore: recibe un arreglo de numeros y los imprime en el display, arriba los 3 primeros y abajo los 3 siguientes. Si tiene mas de 6 numeros 
 muestra 999.999
 DEBE ESTAR DEFINIDO EL ARREGLO NUMBERS[10][5][4] CON UN BITMAP PARA CADA NUMERO
 Usa la funcion printChar */
void showScore(char charedScore[])
{
    int i;
    if(strlen(charedScore) > MAXNUMBERS)    //si el puntaje es mas grande que 999999, muestra 999999 que es lo maximo que entra en el display
    {
        for( i=0 ; i < MAXNUMBERS ; i++)
        {
            charedScore[i] = '9';   
        }
    }    
    for( i=0 ; (i < MAXNUMBERS) && (i < strlen(charedScore)) ; i++) //el largo de charedScore debe ser MENOR O IGUAL A MAXNUMBERS para que funcione
    {
        if(i < DISPLAY_MIDDLE)  //distingue si hay que imprimir en la primera o segunda fila
        {
            printChar(numbers[charedScore[i]-'0'], (LENGTH_X + 1)*i + 1 , FIL1); //imprime en el display cada numero del arreglo score
        }
        else
        {
            printChar(numbers[charedScore[i]-'0'], (LENGTH_X + 1)*(i-DISPLAY_MIDDLE) + 1 , FIL2);
        }
    }
}    
/*showName: recibe un arreglo de letras MAYUSCULAS y las imprime en el display, en la fila que se indique con el segundo parametro
 DEBE ESTAR DEFINIDIO EL ARREGLO LETTER CON TODAS LAS LETRAS DEL ABECEDARIO (26)*/
void showName(char name[],int pos_y)
{
    int i;
    for( i=0 ; i < NOFCHARS ; i++)
    {
        printChar(letters[name[i]-'A'], (LENGTH_X + 1)*i + 1 , pos_y); //imprime en el display cada letra del arreglo nombre, supone que estan todas en mayuscula
    }
}
/*showPosition: recibe arreglo con el string de las posiciones y las imprime en el display*/
void showPosition(char positionChars[])
{
    int i;
    for( i=0 ; (i < strlen(positionChars)) && (i < 3) ; i++)
    {
        printChar(numbers[positionChars[i]-'0'], (LENGTH_X + 1)*i + 1 , POSITION_Y); //imprime en el display cada carcter del arreglo nombre
    }
}
/*Inicializa el estado de game*/
void init_play(bool carsBoard[][DISSIZE],const bool initCarsBoard[][DISSIZE],frog_t *frogCoords,char *maxPosition)
{
    copyBoard(carsBoard,initCarsBoard); //va a pasar al estado de juego, carga el estado inicial de los autos
    cars_routine(NULL,NULL);            //inicializa velocidad de los autos
    frogCoords->x = INIT_X;
    frogCoords->y = INIT_Y;
    *maxPosition = INIT_Y;
}
/****************************MOVIMIENTO DE AUTOS*********************************/

/*cars_routine
 * Recibe un puntero a un arreglo con la posicion de los autos y un puntero a la posicion de la rana
 * Si se subio de nivel (enviar NULL como primer parametro), aumenta la velocidad del movimiento de los autos
 * Sino, mueve los autos (se fija si en este llamado los tiene que mover o no)
 * Recibe NULL en el segundo parametro si hay que inicializar los dividers
 * Recibe NULL en el primer parametro si se subio de nivel*/

void cars_routine(bool carsBoard[][DISSIZE],frog_t *frogCoords)
{
    static int dividersMax[DISSIZE]; // Cuando se suba de nivel, estos máximos se decrementarán para hacer que el ciclo de avance de carril sea más rápido.
    static int dividers[DISSIZE];  // Ante un evento de timer, se decrementa el divider de cada carril, logrando así que cada carril tenga su ciclo de timer, cuando el divider llega a 0.
    bool ways[DISSIZE] = {0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0};
    int row = 0;


    if(!frogCoords)
    {
        init_dividers(dividersMax,dividers);
    }  
    else if(!carsBoard) // Si se tiene que subir de nivel, se efectua un cambio en el máximo de los divisores.
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

void init_dividers(int divMax[],int div[])
{
    int i;
    divMax[0] = 0;
    divMax[1] = 15;
    divMax[2] = 20;
    divMax[3] = 8;
    divMax[4] = 15;
    divMax[5] = 20;
    divMax[6] = 8;
    divMax[7] = 15;
    divMax[8] = 0;
    divMax[9] = 15;
    divMax[10] = 5;
    divMax[11] = 15;
    divMax[12] = 10;
    divMax[13] = 20;
    divMax[14] = 10;
    divMax[15] = 0;
    for( i=0 ; i < DISSIZE ; i++)
    {    
        div[i] = divMax[i];
    }            
}