/*
 *  Implementation of FIFO and LRU page replacement algorithm
 *  Please add appropriate level of comments in this file 
 */

#include "vmalgorithm.h"
#include <stdbool.h>


/* Generate an access pattern
 * Example: 3, 2, 2, 1, 1  indicates the page 3, 2, 2, 1, 1 in order
 */
void generateAccessPattern()
{
   int i;
   srand(time(0));
   accessPattern = (int *)malloc( sizeof(int) * AccessPatternLength);   
   printf("The randomized Access Pattern: ");
   for(i=0; i< AccessPatternLength; i++)
   {
		     accessPattern[i] = rand() % ReferenceSZ;
        printf("%d ", accessPattern[i]);       
   }
   printf("\n");
}

/*
 * Initialize the parameters of simulated memory
 */
void initializePageFrame()
{
   int i;
   memory.PageFrameList = (int *)malloc( sizeof(int)* FrameNR );    // dynamic allocated FrameNR frames to be used in memory
   memory.nextToReplaced = 0;          // indicate the new frame to be replaced as 0
   for(i=0; i< FrameNR; i++)
   {
			memory.PageFrameList[i] = -1;  // initialization to -1 indicating all frames are unused 
   }

}

// Print the pages loaded in memory
void printPageFrame()
{
   int i;
   for(i=0; i< FrameNR; i++)
   {
			printf("%2d ",memory.PageFrameList[i]);       
   }
   printf("\n");
}


/*
 *  Print the access pattern in order
 */
void printAccessPattern()
{
   int i;
   printf("The Same Access Pattern: ");
   for(i=0; i< AccessPatternLength; i++)
   {
        printf("%d ", accessPattern[i]);       
   }
   printf("\n");

}

/** This function loops throug the entire memory.PageFrameList to see if the elemetn in accessPattern matches**/
int ElemFound(int page){
   int j;
   for (j = 0; j < FrameNR; j++){
      if (accessPattern [page] == memory.PageFrameList[j])
      return 1;
   }
   return 0;
}


/*
 * Return: number of the page fault using FIFO page replacement algorithm
 */
int FIFO()
{

   int page_faults = 0;
   int i;
   memory.nextToReplaced = 0;
   
   for (i = 0; i < AccessPatternLength; i++ ){
      //if the element does not match anywhere, then it is a page fault therefore we increment the page fault and also the slot for next to be replaced
      if(!ElemFound(i)){ 
         memory.PageFrameList[memory.nextToReplaced % FrameNR] = accessPattern [i]; //we insert the element at index defined by memory.nextToReplaced % FrameNR
         memory.nextToReplaced++;
         page_faults++;
      }
   printPageFrame();
   }
 return page_faults;
}


/** This function keeps track of the least used slot in PageFrameList**/
int leastUsed(int * list){
   if(memory.PageFrameList[0] == -1) {
      return 0; //return zero if there is an available slot
   }
   int minimum = list[memory.PageFrameList[0]];
   int minimumIndex = 0;
   int g;

   for(g = 0; g < FrameNR; g++){
      if(memory.PageFrameList[g] == -1){
         return g; //return index g where PageFrameList is vacant
      }
      if (list[memory.PageFrameList[g]] < minimum) {
      minimum = list[memory.PageFrameList[g]];
      minimumIndex = g; //update the minimum index to the least used slot
      }
   }
   return minimumIndex;
}

/*
 * Return: number of the page fault using LRU page replacement algorithm
 */

int LRU()
{

   int clockArray[ReferenceSZ]; //clock array that keeps track of which pages are being accessed
   int p;
   int clock;
   for(p = 0; p < ReferenceSZ; p++){
      clockArray[p] = 0; //iterate to make sure that the clock array is empty
   }
   int page_faults = 0;
   int k;
   for(k = 0; k < AccessPatternLength; k++){
      clockArray[accessPattern[k]] = k;
      memory.nextToReplaced = leastUsed(clockArray); //define nextToReplaced to the least used slot
      //if element is not matched anywhere then it is a page fault and we will insetrt it in the least used slot
      if(!ElemFound(k)){
         memory.PageFrameList[memory.nextToReplaced] =  accessPattern[k];
         page_faults++;  
      }

   
      printPageFrame();
   }
return page_faults;

}
  
