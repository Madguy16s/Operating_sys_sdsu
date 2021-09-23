/*
 * specialcharcount.c - this file implements the specialcharcount function.
 */
//made by Jason Gumarjadi Sunardi: cssc4353//

#include <stdio.h> 
#include "count.h"
#include <dirent.h>

#include <ctype.h> 




void specialcharcount(char *path, char *filetowrite, long charfreq[])
{
   //Open the specified directory and files within path that has the ".txt" extention
   DIR *d;
   struct dirent *dir;
   d = opendir(path);
   if (d) {
     while ((dir = readdir(d)) != NULL) {
        char *fname = dir->d_name;
        int length = strlen(dir -> d_name);
        if (strncmp(dir->d_name + length - 4, ".txt", 4) == 0){
           char full_path[strlen(path) + 50];
           memset(full_path, 0, strlen(path) + 50);
           strcpy(full_path, path);
           strcat(full_path, "/");
           strcat(full_path, fname);
           count_special(full_path, charfreq);
      
        }
        
     }
     closedir(d);
   }

//opens the filetowrite file which is the output of the program
//gives output of the tally of each special character into a text file
   FILE *f = fopen(filetowrite, "w+");
   fprintf(f," , -> %ld\n",charfreq[0]);  
   fprintf(f," . -> %ld\n",charfreq[1]);  
   fprintf(f," : -> %ld\n",charfreq[2]);  
   fprintf(f," ; -> %ld\n",charfreq[3]);  
   fprintf(f," ! -> %ld\n",charfreq[4]);
}


//counts the frequency of every alphabet character within all ".txt" files present in the directory
void count_special(char *fname, long charfreq[]){
   FILE *f = fopen(fname, "r");
   char c;

   while(!feof(f)){
      fscanf(f,"%c", &c);
      if(c == ','){
         charfreq[0]++;
      }
      if(c == '.'){
         charfreq[1]++;
      }
      if(c == ':'){
         charfreq[2]++;
      }
      if(c == ';'){
         charfreq[3]++;
      }
      if(c == '!'){
         charfreq[4]++;
      }
   }
   fclose(f);
   
}





/**
  The specialcharcount function counts the frequency of the following 5 special characters:
  ','   '.'   ':'    ';'    '!'
   
  in all the .txt files under directory of the given path and write the results to a file named as filetowrite.
  
  Input: 
  
      path - a pointer to a char string [a character array] specifying the path of the directory; and
      filetowrite - a pointer to a char string [a character array] specifying the file where results should be written in.
      alphabetfreq - a pointer to a long array storing the frequency of the above 5 special characters
      
      charfreq[0]: the frequency of ','
      charfreq[1]: the frequency of '.'
      charfreq[2]: the frequency of ':'
      charfreq[3]: the frequency of ';'
      charfreq[4]: the frequency of '!'

  
  Output: a new file named as filetowrite with the frequency of the above special characters written in
  
  Steps recommended to finish the function:
  1) Find all the files ending with .txt and store in filelist.
  2) Read all files in the filelist one by one and count the frequency of each alphabet letter only (a - z). The array 
  long alphabetfreq[] always has the up-to-date frequencies of alphabet letters counted so far. If the letter is upper case, convert
  it to lower case first. 
  3) Write the result in the output file: filetowrite in following format: 
  
     character -> frequency
     
     example:
     , -> 20
     . -> 11
     : -> 20
     ; -> 11
     ! -> 12     
     
  Assumption:  
  1) You can assume there is no sub-directory under the given path so you don't have to search the files 
  recursively.    
  2) Only .txt files are counted and other types of files should be ignored.
  
*/

