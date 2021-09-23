/*
 * The code is not part of the real application, and just used to 
 * illustrate the bounded-buffer problem using Semaphore and/or mutexes. 
 * Detailed requirements please refer to the assignment documentation.
 * 
*/

#include <stdio.h> 
#include <stdlib.h> 
#include "bbuffer.h"
#include <pthread.h>
#include <dirent.h>
#include <semaphore.h>


pthread_mutex_t mutexBuffer; //declaring mutex
sem_t vacantBuffer; //declaring semaphore for vacant buffer
sem_t occupiedBuffer; // declaring semaphore for occupied buffer

void initilization()
{
    pthread_mutex_init(&mutexBuffer, NULL); //initializing Mutexes
    sem_init(&vacantBuffer, 0, 5); //initializing semaphore for vacant buffer
    sem_init(&occupiedBuffer, 0, 0);//initializing semaphore for occupied buffer
}

/* *
 * insert_item - thread safe(?) function to insert items to the bounded buffer
 * @param item the value to be inserted
 * @return 0 in case of sucess -1 otherwise
 */
  
int insert_item(int item, long int id)
{
    /* TODO: Check and wait if the buffer is full. Ensure exclusive
     * access to the buffer and may use the existing code to insert an item.
     */   
    sem_wait(&vacantBuffer); //semaphore to check if buffer is full
    pthread_mutex_lock(&mutexBuffer); //mutex lock to ensure exclusive access to the buffer

    buffer.value[buffer.next_in] = item;
    
      
    printf("producer %ld: inserted item %d into buffer index %d\n", id, item, buffer.next_in);
       
    buffer.next_in = (buffer.next_in + 1) % BUFFER_SIZE;

    pthread_mutex_unlock(&mutexBuffer); //unlock the mutex 
    sem_post(&occupiedBuffer); //use semaphore to post recently occupied buffers

    return 0;
}

/**
 * remove_item - thread safe(?) function to remove items to the bounded buffer
 * @param item the address of the variable that the removed value will be written
 * @return 0 in case of sucess -1 otherwise
 */
int remove_item(int *item, long int id)
{
    /* TODO: Check and wait if the buffer is empty. Ensure exclusive
     * access to the buffer and use the existing code to remove an item.
     */
    sem_wait(&occupiedBuffer); //semaphore to check if buffer is empty
    pthread_mutex_lock(&mutexBuffer); // mutex to ensure exclusive access to the buffer
    
    
    *item = buffer.value[buffer.next_out];
    buffer.value[buffer.next_out] = -1;    
    
   
    printf("consumer %ld: removed item %d from buffer index %d\n", id, *item, buffer.next_out);
       
    buffer.next_out = (buffer.next_out + 1) % BUFFER_SIZE;

    pthread_mutex_unlock(&mutexBuffer);//unlock the mutex
    sem_post(&vacantBuffer);//use semaphore to post recently vacant buffer

    return 0;
}




/**
 * producer - will iterate PRODUCER_ITERATION times and call the corresponding
 * function to insert an integer to the bounded buffer
 * @param param an integer id of the producer used to distinguish between the
 * multiple producer threads
 * @return nothing
 */
void * producer(void *param)
{
    int item, i;
    long int id = (long int)param;

    printf("producer %d started!\n", id);
    i = PRODUCER_ITERATIONS;
    while (i--) {
	  sleep(rand() % 3);

	item = rand() % 10000;
	if (insert_item(item, id))
	    printf("Error while inserting to buffer\n");
    }

    pthread_exit(0);
}

/**
 * consumer - will iterate CONSUMER_ITERATION times and call the corresponding
 * function to remove an integer from the bounded buffer
 * @param param an integer id of the producer used to distinguish between the
 * multiple consumer threads
 * @return nothing
 */
void * consumer(void *param)
{
    int item, i;
    long int id = (long int)param;

    printf("consumer %d started!\n", id);
    i = CONSUMER_ITERATIONS;
    while (i--) {
	sleep(rand() % 3);

	if (remove_item(&item, id))
	    printf("Error while removing from buffer\n");
    }

    pthread_exit(0);
}
