/*
 * alphabetcountmulthreads.c - this file implements the alphabetcountmulthreads function.
 */

#include <stdio.h> 
#include "count.h"
#include <pthread.h>
#include <stdlib.h>
#include <dirent.h>
#include <pthread.h>

/**
  The alphabetcountmulthreads function counts the frequency of each alphabet letter (a-z, case insensitive) in all the .txt files under
  directory of the given path and write the results to a file named as filetowrite. Different with programming assignment#0, you need to implement the program using mutithreading.
  
  Input: 
      path - a pointer to a char string [a character array] specifying the path of the directory; and
      filetowrite - a pointer to a char string [a character array] specifying the file where results should be written in.
      alphabetfreq - a pointer to a long array storing the frequency of each alphabet letter from a - z, which should be already up-to-date;
      num_threads - number of the threads running in parallel to process the files
      
       
  Output: a new file named as filetowrite with the frequency of each alphabet letter written in
  
  Requirements:
1)	Multiple threads are expected to run in parallel to share the workload, i.e. suppose 3 threads to process 30 files, then each thread should process 10 files;
2)	When a thread is created, a message should be print out showing which files this thread will process, for example:
Thread id = 274237184 starts processing files with index from 0 to 10!
3)	When a file is being processed, a message should be print out showing which thread (thread_id = xxx) is processing this file, for example:
Thread id = 265844480 is processing file input_11.txt
4)	When a thread is done with its workload, a message should be print out showing which files this thread has done with work, for example:
      Thread id = 274237184 is done !
5)	The array: long alphabetfreq[ ] should always be up-to-date, i.e. it always has the result of all the threads counted so far.  [You may need to use mutexes to protect this critical region.]


You should have the screen printing should be similar as follows:

 Thread id = 274237184 starts processing files with index from 0 to 10!
 Thread id = 265844480 starts processing files with index from 11 to 22!
 Thread id = 257451776 starts processing files with index from 23 to 31!

 Thread id = 265844480 is processing file input_11.txt
 Thread id = 257451776 is processing file input_22.txt
 Thread id = 274237184 is processing file input_00.txt
  � � 

 Thread id = 274237184 is done !
 Thread id = 265844480 is done !
 Thread id = 257451776 is done !

 The results are counted as follows:
 a -> 2973036
 b -> 556908
 c -> 765864
 �  � 
*/

//Make a typdef struct for variable i and j to act as a counter for the interval of files being opened per thread
typedef struct args {
  int i; int j;
} thread_args;

pthread_mutex_t lock; //initializing mutex lock
long *global_freqs; //initializing global variable global_freqs
char *fpaths[100]; //initializing file path


//function will count how many file per thre
void count_freqs(thread_args* args)
{
  int i = args->i; //starting index of opening file
  int j = args->j;//ending index of opening file
  printf("Thread id = %d starts processing files with index from %d to %d!\n", pthread_self(), i, j);

  int k = 0;
  for (k = i; k <= j; k++) { //loop through the given interval of file to open per thread
    char* fpath = fpaths[k];
    printf("Thread id = %d is processing file %s\n", pthread_self(), fpath);
    FILE *fp = fopen(fpath, "r"); //open the individual text files
    char c;
    do {
        c = fgetc(fp);
        if (feof(fp)) break; //end of file condition

        c = tolower(c);
        if (c < 97 || c > 122) continue;
        // MUTEX Acquire
        pthread_mutex_lock(&lock); //mutex lock to prevent stale data
        global_freqs[c - 97] += 1;
        // MUTEX Release
        pthread_mutex_unlock(&lock); //mutex unlock to resume oeperations within the thread
    } while (1);
  }
  printf("Thread id = %d is done !\n", pthread_self());
}


void alphabetcountmulthreads(char *path, char *filetowrite, long alphabetfreq[], int num_threads)
{
  //when mutex initialization have failed
    if (pthread_mutex_init(&lock, NULL) != 0) {
      printf("\n mutex init has failed\n");
      return 1;
    }
  global_freqs = alphabetfreq;
  alphabetfreq[8] = 10;
  //open the specified directory and the file within it
  DIR * d;
  struct dirent * dir;

   d = opendir (path);

   int i = 0;
  while ((dir = readdir(d)) != NULL){
    char *fname = dir->d_name;
    int length = strlen(dir-> d_name);
    if (strncmp(dir->d_name + length - 4, ".txt", 4) == 0){
      //define the full path of the files within the directory
      char *full_path = calloc(50, strlen(path));
      strcpy(full_path, path);
      strcat(full_path, "/");
      strcat(full_path, fname);
      fpaths[i++] = full_path;
    }
  }

  int num_files = i; //define the total number of files
  int file_per_thread = num_files / num_threads; //define the number of file per thread based on the total number of file and thread

  pthread_t threads[num_threads]; //initialize the thread

  

  for (i = 0; i < num_threads; i++) {
    int a = i * file_per_thread;  
    int b = a + file_per_thread-1;  

    if (i == num_threads - 1) {
      b = num_files - 1;
    }
    
    //allocate memory to thread based on the size of the interval
    thread_args *args = malloc(sizeof(thread_args));
    args->i = a;
    args->j = b;

    pthread_create(&threads[i], NULL, count_freqs, (void*) args); //create the threads
    realloc (args, 0); //free memory used by thread
  }

  //join all the threads together and close the directory
  for (i = 0; i < num_threads; i++) 
    pthread_join(threads[i], NULL);
    closedir(d);
   


   //write the results to a file called results.txt
   FILE *fp = fopen(filetowrite, "w+");
   for (i = 0; i < 26; i++) {
      char c = (char) i + 97;
      fprintf(fp, "%c -> %d\n", c, alphabetfreq[i]);
   }

}
