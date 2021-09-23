/*header files*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /* for fork */
#include <sys/types.h> /* for pid_t */
#include <sys/wait.h> /* for wait */





/*
 This program will fork two child processes running the two programs generated in programming zero in parallel.
 Hint: You mant need to use fork(), exec() family, wait(), exit(), getpid() and etc ...
 
 Requirements:
 
 1) Exactly two child processes are created, one to run testspecial program and the other is to run testalphabet program;
 2) When a program starts to run, print a message to the output screen showing which process (with PID) is running which program, for example:
    "CHILD <16741> process is executing testalphabet program!"
    
 3) When a program is done, the process exits and at the same time, a message should be print to the output screen showing which  process (with PID) is done with the program, for example:
    "CHILD <16741> process has done with testalphabet program !"
    
 4) The messages should match the real execution orders, i.e. when the testspecial program starts/ends, the right message should be print out. So you need to figure out how to get the starting/ending time of each 
 process.
   
   
 The expected screen print out should be similar as follows:
 
 CHILD <16741> process is executing testalphabet program!
 CHILD <16742> process is executing testspecial program!
, -> 745668
. -> 798072
... ...

CHILD <16742> process has done with testspecial program !
a -> 2973036
b -> 556908
... ...

CHILD <16741> process has done with testalphabet program !
 */


int main(void) {
      pid_t child_testalphabet, child_testspecial; //define and assign process id for child process for testalphabet and testspecial

      child_testalphabet = fork(); //create a fork process for testalphabet

      if(child_testalphabet == 0){ /// child
         printf("CHILD <%d> process is executing testalphabet program!\n", getpid()); // print out the banner message for executing testalphabet
         execv("./testalphabet", NULL); //executes the testalphabet file
      }else { // parent
         child_testspecial = fork(); //create a fork process for testspecial
        
         if (child_testspecial == 0){ // child
             printf("CHILD <%d> process is executing testspecial program!\n", getpid()); //print out banner message for executing testspecial
             execv("./testspecial", NULL); //executes the testspecial file
         }
      }

      int status;
      waitpid(child_testalphabet, &status, 0); //wait for the testalphabet process to end and then resume on parent fork
      printf("CHILD <%d> process has done with testalphabet program !\n", child_testalphabet); //prints banner message when testalphabet process ends
      waitpid(child_testspecial, &status, 0); //wait for the testspecial process to end and then resume on parent fork
      printf("CHILD <%d> process has done with testspecial program !\n", child_testspecial); //prints banner message when testspecial process ends

	return 0;
	
}