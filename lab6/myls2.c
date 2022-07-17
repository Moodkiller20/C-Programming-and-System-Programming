/*  Giovanni Tshibangu 
    CS 355 lab 6: Objective: Write a C program myls2 whose behavior resembles that of the system command ls. myls2 must 
                print the names of files in the current directory in columns of equal width. myls2 
    6/15/2022
 */

# include <stdio.h>
# include <dirent.h>
#include <fcntl.h>	 
# include <stdlib.h>
#include <string.h>
#include <unistd.h>	




struct dirent **list;


int flagA=0, flagS=0,flagR=0,flagNoarg=0;   // Initialize flags      

char filesList[20000][50];  // Initialize the file list sting arrray
char *d[26][26] ={0};       // Initialize 2D array

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
            int i,j,count = 0;
            while((dirent_ptr = readdir(dir_ptr))!=0){
                if((dirent_ptr->d_name[1] != '\0') || (dirent_ptr->d_name[1] != '.')){
                strcpy(filesList[count],dirent_ptr->d_name); 
                count++; // Increment counter
                }
            }
            int l,m,k=0; // Initialize counters
            //////// Copy Mutlidimension
            for(l=0; l<count;l++){
                for(m=0; m<count;m++){
                    d[m][l] = filesList[ 3 *  m+l];
            }
        }
        ///////////// Prints Multidimensions
        for(i=0; i<3; i++) { 
            printf("\n"); 
            for(j=0; j<count; j++) // inner loop
                printf("%s      ", d[j][i]); 
        } // close loop
        printf("  \n"); 
        printf("\n"); 
    }   //clsoe if
        if(flagNoarg){  // Works as "ls" without hidden files
            int i,j,count = 0;
            while((dirent_ptr = readdir(dir_ptr))!=0){
                if((dirent_ptr->d_name[0] != '.')){ //  Check if the filename begins with a "."
                   strcpy(filesList[count],dirent_ptr->d_name); 
                    count++; // Increment counter
                     }
            }
        int l,m,k=0; 
        //////// Copy Mutlidimension
        for(l=0; l<count;l++){
            for(m=0; m<count;m++){
                d[m][l] = filesList[ 3 *  m+l];
            }
        }
        ///////////// Prints Multidimensions
        for(i=0; i<3; i++) { 
            printf("\n"); 
            for(j=0; j<count; j++){
                printf("%s      ", d[j][i]);
            }       
        } 
        printf("  \n"); 
        printf("\n");  
        
    }   //clsoe if
        if(flagS){  // Works as "ls-a " but sort the file in order
            int i,j,count = 0;  // counter
            while((dirent_ptr = readdir(dir_ptr))!=0){
                strcpy(filesList[count],dirent_ptr->d_name);    // copy string from the list of dir name into the "filesList" array
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
            int l,m,k=0; 
            for(l=0; l<count;l++){
                for(m=0; m<count;m++){
                    d[m][l] = filesList[ 3 *  m+l];
            }
        }
        ///////////// Prints Multidimensions
        for(i=0; i<3; i++) { 
            printf("\n"); 
            for(j=0; j<count; j++) 
                printf("%s      ", d[j][i]); 
        }   
        printf("  \n"); 
        printf("\n"); 
    } // CLOSE IF CASE    
        if(flagR){  // Works as "ls-a " but sort the file in reversed order
            int i,j,count = 0;
            while((dirent_ptr = readdir(dir_ptr))!=0){
                strcpy(filesList[count],dirent_ptr->d_name);     // copy string from the list of dir name into the "filesList" array
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
        int o,p,k=0; 
        for(o=0; o<count;o++){
            for(p=0; p<count;p++){
                d[p][o] = filesList[ 3 *  p+o];
            }
        }
        ///////////// Prints Multidimensions
        for(i=0; i<3; i++) { 
            printf("\n"); 
            for(j=0; j<count; j++) 
                printf("%s      ", d[j][i]);   
        } 
        printf("  \n"); 
        printf("\n"); 
         closedir(dir_ptr); // CLOSE DIRECTORY
        }  
    } // Close outmost else.
    return 0;   // end the program
}