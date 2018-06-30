#include "eventQueue.h"






/**************MAIN DE DEBUG*************************************8*/

/*int main (void)
{
  event_queue_t my_event_queue = create_queue();
  if( (my_event_queue.queue) == NULL)
  {
    printf("No se pudo inicializar la cola de eventos\n");
    return 0;
  }

  if(!emit_event(&my_event_queue , 0))
  {
    printf("no anda esto master2\n");
    return 0;
  }
  if(!emit_event(&my_event_queue , 36))
  {
    printf("no anda esto master2\n");
    return 0;
  }
  if(!emit_event(&my_event_queue , 3))
  {
    printf("no anda esto master2\n");
    return 0;
  }
  printf("%d\n",get_event(&my_event_queue) );
  printf("%d\n",get_event(&my_event_queue) );
  printf("%d\n",get_event(&my_event_queue) );
  if(!emit_event(&my_event_queue , 1))
  {
    printf("no anda esto master2\n");
    return 0;
  }
  printf("%d\n",get_event(&my_event_queue) );
   if(!emit_event(&my_event_queue , 32))
  {
    printf("no anda esto master2\n");
    return 0;
  }
   if(!emit_event(&my_event_queue , 1))
  {
    printf("no anda esto master2\n");
    return 0;
  }
  printf("%d\n",get_event(&my_event_queue) );
  printf("%d\n",get_event(&my_event_queue) );


  destroy_queue(&my_event_queue);

  return 0;
}*/





/*****************************************************************************************************************
 * FUNCION create_queue
 * Devuelve una estructura que en su interior tiene lo necesario para controlar la cola de eventos,
 * un puntero para leer y otro para escribir, el usuario no deberá utilizar esos punteros y se debera acceder a
 * la cola solo a traves de las funciones provistas en este libreria. En caso de error devolvera una estructura cola de eventos que tendra un NULL en
 * el puntero de la cola. IMPORTANTE VERIFICAR ESO
 * ES MUY IMPORTANTE QUE SE DESTRUYAN LAS COLAS CREADAS
 *****************************************************************************************************************/

event_queue_t create_queue ( void )     
{
  event_queue_t newQueue,*p2NQueue = &newQueue;
  event_t *temp = (event_t*) malloc (QUEUE_SIZE * sizeof(event_t));
  int i;
  if(temp == NULL)
  {
    event_queue_t error = {.queue = NULL};// en caso de error con el
    return error;
  }
  event_t *tempaux = temp;
  
  for(i=0; i < QUEUE_SIZE; i++)
  {
    tempaux++ -> ack = true;//debo hacer esto para asegurarme de que todas las celdas de la cola esten habilitadas para ser escritas
  }
  
  p2NQueue->queue = temp; //la cola de eventos
  p2NQueue->p2get = temp;//los punteros para leer y escribir estan en el mismo lugar (cola vacia)
  p2NQueue->p2write = temp;

  return newQueue;
}



/*****************************************************************************************************************
 * FUNCION destroy_queue
 * recibe un puntero a la cola de eventos que se quiere destruir
 * Devuelve un bool que sera un 1 si no hubo ningun error y un 0 en caso de que haya habido algun error en la ejecución
 * de la función
 * ES MUY IMPORTANTE QUE SE DESTRUYAN LAS COLAS CREADAS
 *****************************************************************************************************************/
bool destroy_queue ( event_queue_t* queue )
{
  if( queue == NULL)
  {
    return false;
  }
  free (queue->queue);//se libera el malloc creado
  return true;
}
/*****************************************************************************************************************
 * FUNCION emit_event
 * recibe un puntero a la cola de eventos en la que se quiera escribir y un ID que identifique el evento que se desee crear
 * Devuelve un bool que sera un 1 si no hubo ningun error y un 0 en caso de que haya habido algun error en la ejecución
 * de la función
 *****************************************************************************************************************/
bool emit_event( event_queue_t* queue , uint16_t type )
{
  event_t *temp = queue -> p2write;

  if(queue == NULL)
  {
    return false;  // verificacion si el usuario no lo hizo antes
  }


  if(queue -> p2write -> ack == false)  // si en la cola de eventos no hay mas lugar -> error
  {
    return false;
  }
  else
  {

    queue -> p2write -> type = type; // guardo el ID del evento


    if ((queue -> p2write) == ((queue -> queue) + (QUEUE_SIZE-1))) // movimiento del puntero de write
    {
      queue -> p2write = queue -> queue; // si estoy al final de la cola debo moverlo al principio

    }
    else
    {
      (queue -> p2write) ++; // si no avanza una posicion
    }
    temp -> p2NextEv = (struct EVENT*) queue -> p2write;// guardo en el evento anterior un puntero al evento actual para no tener que problems con el movimiento en get_event
    temp -> p2write -> ack = false;   // marco el lugar como ocupado
    return true;
  }
}

/*****************************************************************************************************************
 * FUNCION get_event
 * Recibe un puntero a la cola de eventos en la que se quiera leer, 
 * Devuelve el ID del proximo evento que se encuentra en la cola
 *****************************************************************************************************************/
uint16_t get_event ( event_queue_t* queue  )
{
  uint16_t retval;
  if(queue_is_empty(queue))
  {
    return 0; // si la cola esta vacia -> error
  }
  retval = queue -> p2get->type; // guardo el ID y muevo el puntero
  queue -> p2get -> ack = true;
  queue -> p2get =(event_t*) queue -> p2get ->p2NextEv;
  return retval;
}

/*****************************************************************************************************************
 * FUNCION queue_is_empty
 * Recibe un puntero a la cola de eventos en la que se quiera chequear 
 * Devuelve un bool que sera un 0 en caso de que no este vacia y un 1 en caso de que si lo este
 *****************************************************************************************************************/
bool queue_is_empty( event_queue_t* queue )
{
  return (queue -> p2get == queue -> p2write && queue -> p2get -> ack == true ); // si ambos punteros estan en la misma posicion y el evento al que apunta read ya ha sido leido entonces la cola esta vacia
}
