/*  Giovanni Tshibangu 
    CS 355 lab 5: Objective: write a program that can print the names of files in the current directory.
    6/15/2022
 */

# include <stdio.h>
# include <dirent.h>
#include <fcntl.h>	 
# include <stdlib.h>
#include <string.h>
#include <unistd.h>	

// intiialize constant
# define MaxWords 8
# define MaxWordLength 30


struct dirent **list;


int flagA=0, flagS=0,flagR=0,flagNoarg=0;   // Initialize flags      

char filesList[20000][50];  // Initialize the file list sting arrray

char tempList[50];  // Temp array to help in sorting

//======================== myStringCompare Function  ===================================
int myStringCompare(const void *a, const void *b){
    return strcmp(a, b);
}

//======================== MAIN Function  aka Entry point ================================
int main(int ac, char* av[]){
    
    char option; // Init option string variable
    
    if((option = getopt( ac, av, " asr") )==-1 ){   // if no flag arguments are passed, do 'ls' (only print non-hidden files)
        flagNoarg =1;
    }   // clsoe if  
    else{   //  Switch throup the options based the flag passed in the cmd and set  the flag to ON/1/TRUE
         switch(option) {   // Open Swicth cases
            case 's':
            flagS =1;
            break;
            case 'a':
           flagA =1;
            break;  
            case 'r':
           flagR =1;
            break;  
        }   // close Switch cases 
    }   // Close else

    char *dir_name; // Init directroy name variable or holder
    if(ac >2){  // if agurment >2 which means that the user passed the flag args and also the directory name
        dir_name =av[2];    // Set the directory name to the 3 args from the cmd  eg. ' ./aout -s dirA '
    }   //clsoe if
    else{   // Else if the args count <2 , which means that  the user only passed either "./aout"  or "./aout -s". the user didnt passed the directory name.
        dir_name =".";  // Set the directory name to "." this means that our program will start by reading file in the current directory and just there.
    }   // close else

    // Initialise     
    DIR *dir_ptr;
    struct dirent *dirent_ptr;

    dir_ptr =opendir(dir_name); // Open directory then check status
    if(dir_ptr ==0){    // check for error on open()
        perror(dir_name);   // Print error.
    }   // close if
    else{   //If no error is found do_ls based on the flags args.

        // Here I am printing based on the flags.
        if(flagA){  // Works as "ls -a" with hidden files
            while((dirent_ptr = readdir(dir_ptr))!=0){
                if((dirent_ptr->d_name[1] != '\0') || (dirent_ptr->d_name[1] != '.')){
                printf("%s \n", dirent_ptr->d_name ); 
                }}
        }   //clsoe if
        if(flagNoarg){  // Works as "ls" without hidden files
            while((dirent_ptr = readdir(dir_ptr))!=0){
                if((dirent_ptr->d_name[0] != '.')){ //  Check if the filename begins with a "."
                    printf("%s \n", dirent_ptr->d_name ); 
                    }
            }
        }   //clsoe if
        if(flagS){  // Works as "ls-a " but sort the file in order
            int i,j,count = 0;  // counter
            while((dirent_ptr = readdir(dir_ptr))!=0){
                strcpy(filesList[count],dirent_ptr->d_name);    // copy string from the list of dir name into the "filesList" array
                //printf("Test passed");
                count++;    // Increment counter
            } // close while loop
            for (i = 0; i<count; i++){  // loop for number of strings
                for (j=i+1; j<count; j++){  // inner loop
                    if (strcmp(filesList[i],filesList[j]) > 0){ // Check if two string are equal.
                        strcpy(tempList,filesList[i]);  // if not equal exchange
                        strcpy(filesList[i],filesList[j]);
                        strcpy(filesList[j],tempList);
                    }   // close if
                } // close inner loop
            }   // close outer loop

            // print from array of string.
            for (i = 0; i<count; i++)
            if (filesList[i][0] != '.')
            printf("%s\n",filesList[i]);
        } // CLOSE IF CASE
        
        if(flagR){  // Works as "ls-a " but sort the file in reversed order
            int i,j,count = 0;
            while((dirent_ptr = readdir(dir_ptr))!=0){
                strcpy(filesList[count],dirent_ptr->d_name);     // copy string from the list of dir name into the "filesList" array
                //printf("Test passed");
                count++;    // Increment counter
            }   // close while loop
            for (i = 0; i<count; i++){  // loop for number of strings
                for (j=i+1; j<count; j++){  // inner loop
                    if (strcmp(filesList[i],filesList[j]) < 0){ // Check if two string are equal.
                        strcpy(tempList,filesList[i]);  // if not equal exchange
                        strcpy(filesList[i],filesList[j]);
                        strcpy(filesList[j],tempList);
                    }   // close if
                }   // close inner loop
            }   // close outer loop

            // print from array of string.
            for (i = 0; i<count; i++)
            if (filesList[i][0] != '.')
            printf("%s\n",filesList[i]);
            }    // CLOSE IF CASE

         closedir(dir_ptr); // CLOSE DIRECTORY
        }   // Close outmost else.

    return 0;   // end the program
}