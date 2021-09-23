/*
 * alphabetcount.c - this file implements the alphabetlettercount function.
 */

#include <stdio.h> 
#include "count.h"
#include <dirent.h>
#include <unistd.h>

#include <ctype.h> 

//made by Jason Gumarjadi Sunardi: cssc4353//
/**
  The alphabetlettercount function counts the frequency of each alphabet letter (a-z, case insensitive) in all the .txt files under
  directory of the given path and write the results to a file named as filetowrite.
  
  Input: 
      path - a pointer to a char string [a character array] specifying the path of the directory; and
      filetowrite - a pointer to a char string [a character array] specifying the file where results should be written in.
      alphabetfreq - a pointer to a long array storing the frequency of each alphabet letter from a - z:
      alphabetfreq[0]: the frequency of 'a'
      alphabetfreq[1]: the frequency of 'b'
         ... ...
      alphabetfreq[25]:the frequency of 'z'

  
  Output: a new file named as filetowrite with the frequency of each alphabet letter written in
  
  Steps recommended to finish the function:
  1) Find all the files ending with .txt and store in filelist.
  2) Read all files in the filelist one by one and count the frequency of each alphabet letter only (a - z). The array 
  long alphabetfreq[] always has the up-to-date frequencies of alphabet letters counted so far. If the letter is upper case, convert
  it to lower case first. 
  3) Write the result in the output file: filetowrite in following format: 
  
     letter -> frequency
     
     example:
     a -> 200
     b -> 101
     ... ...
     
  Assumption:  
  1) You can assume there is no sub-directory under the given path so you don't have to search the files 
  recursively.    
  2) Only .txt files are counted and other types of files should be ignored.
  
*/
void alphabetlettercount(char *path, char *filetowrite, long alphabetfreq[])
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
           count_freq(full_path, alphabetfreq);
        }
     }
     closedir(d);
   }

//opens the filetowrite file which is the output of the program
//gives output of the tally of each alphabet character into a text file
   FILE *fp = fopen(filetowrite, "w+");
   int i;
   for (i = 0; i < 26; i++) {
      char c = (char) i + 97;
      fprintf(fp, "%c -> %d\n", c, alphabetfreq[i]);
   }
}

//counts the frequency of every alphabet character within all ".txt" files present in the directory
void count_freq(char *fpath, long alphabetfreq[])
{
   FILE *fp = fopen(fpath, "r");
   char c;
   do {
      c = fgetc(fp);
      if (feof(fp)) break;

      c = tolower(c);
      alphabetfreq[c - 97] += 1;
   } while (1);
}