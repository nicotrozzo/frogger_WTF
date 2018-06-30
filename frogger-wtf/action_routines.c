/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "action_routines.h"

extern sem_t levelUpSem;

static void letter_up(void *pArg, int letter);
static void letter_down(void *pArg, int letter);
static void printIncPositions(FILE *p2read,FILE *p2write );
static bool copyLine(FILE *p2read,FILE *p2write );


void non_act_routine(void *pArg)
{
  
}

void load_scoreboard(void *pArg)
{
    gameData_t *pData = pArg;
    pData->scoreFile = fopen(SCORE_FILE,"r");
    pData->position = 0;
}

void close_scoreboard(void *pArg)
{
    fclose(((gameData_t *)pArg)->scoreFile);
    ((gameData_t *)pArg)->scoreFile = NULL;
}
    
void showNextScore(void *pArg)
{
  //cargar info siguiente linea
    
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

void load_scores(void *pArg)
{
    int i;
    for( i=0 ; i < NOFCHARS ; i++ )
    {    
        ((gameData_t *)pArg)->player[i]='A';
    }
    ((gameData_t *)pArg)->player[i]='\0';   //terminador
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
    printf("LEVEL UP!, score: %u\n",((gameData_t*)pArg)->score);
    times = 0;
  }
  else      //si no subio de nivel significa que solo llego arriba
  {
    ((gameData_t*)pArg)->score += ARRIVE_SCORE;  
    ((gameData_t*)pArg)->levelUp = false;
    sem_post(&levelUpSem);
    printf("ARRIVED!, score: %u\n",((gameData_t*)pArg)->score);
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
    bool done = false;
    gameData_t* pGameData = pArg;
    char charedScore[MAXNUMBERS + 1 + 5];
    unsigned int otherScore;
    int i,positionLen = 0,position = 1; 
    char command[30];
    FILE *readFile = fopen(SCORE_FILE,"r");  
    FILE *writeFile = fopen(SCORE_AUX_FILE,"w");    //abre archivo para escribir puntajes
    
    while(!done)
    {
        i = -1;
        positionLen = 0;
        while(fgetc(readFile) != ' ')
        {
            positionLen++;    //avanza hasta el primer espacio, o sea que saltea la posicion y obtiene su largo
        }    
        fseek(readFile, NOFCHARS + 1, SEEK_CUR);  //saltea el nombre y el espacio
        do
        {
            charedScore[++i] = fgetc(readFile);   //levanta todos los caracteres del puntaje de la linea actual
        }
        while(charedScore[i] != '\n');
        charedScore[i] = '\0';  //terminador al final del string, i tiene el valor del largo del puntaje
        fseek(readFile, -1, SEEK_CUR);  //queda apuntando a la ultima posicion de la linea
        sscanf(charedScore,"%d",&otherScore);   //obtiene el puntaje de la posicion siendo analizada
        fseek(readFile, -i-NOFCHARS-positionLen-2, SEEK_CUR); //vuelve hasta el principio de la linea. -i-1 para volver del puntaje  
                                                              //y el espacio,-NOFCHARS-1 para volver del nombre y el espacio, -positionLen para volver del puntaje 
        if(otherScore < pGameData->score)   
        {
            fprintf(writeFile,"%d %s %u\n",position,pGameData->player,pGameData->score);
            printIncPositions(readFile,writeFile);        //escribe todo el resto de las posiciones, sumandoles 1 porque bajan un lugar
            done = true;
        }
        else
        {
            copyLine(readFile,writeFile);
            position++;
        }        
    }    
    fclose(readFile);
    fclose(writeFile);
    
    sprintf(command,"rm %s",SCORE_FILE);    
    system(command);        //borra el archivo viejo
    sprintf(command,"mv %s %s",SCORE_AUX_FILE,SCORE_FILE);       
    system(command); //renombra el nuevo para que se llame como el viejo
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

void letter_up(void *pArg, int letter)
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

void letter_down(void *pArg, int letter)
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


/*Recibe un puntero al inicio de la linea de un archivo de lectura y otro al inicio de la linea de un archivo de escritura
 Cada linea del archivo de lectura comienza con algun numero, la funcion escribe en el archivo de lectura dicho numero 
 * incrementado en 1 de la linea apuntada para abajo*/
void printIncPositions(FILE *p2read,FILE *p2write )
{
    unsigned int position;
    fscanf(p2read,"%u",&position);
    do
    {
        while(fgetc(p2read) != ' ');  //saltea la posicion
        fprintf(p2write,"%u ",++position);
    }    
    while(!copyLine(p2read,p2write));
}

/*copyLine:
 Recibe dos punteros a archivos, lee de uno y escribe en el otro, copia la linea del de lectura al de escritura, incluido el '\n'
Devuelve 1 si el caracter siguiente al enter es EOF*/
bool copyLine(FILE *p2read,FILE *p2write )
{
    int caracter;
    do
    {
        caracter = fgetc(p2read);
        fputc(caracter,p2write);
    }    
    while( caracter != '\n');
    if( (caracter = fgetc(p2read)) == EOF)
    {
        return 1;
    }    
    else
    {
        ungetc(caracter,p2read);
        return 0;
    }    
}

/*Inicializacion del output*/
void output_init(void)
{
    display_init();
    display_clear();
    display_update();
}

