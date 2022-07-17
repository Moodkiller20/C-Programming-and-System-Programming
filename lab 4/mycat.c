// Giovanni Tshibangu
// CS 355 lab4
// 6/13/2022
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>


# define COPYMODE 0644
# define BUFFERSIZE 1024

// Main fucntion #############################################
int main(int ac, char *av[]) {

// Initialize flags and set to 0 or OFF or False  
int flagB=0, flagE=0, flagN=0, flagS=0,flagD=0,flagNoarg=0;
    // Initialize character Option 
    char option;
    // check for user args
    if((option = getopt(ac, av, "bens")) != -1) { // open if
        // switch condition based on the args passed by the user and enable flags accordingly 1/ON/True
        switch(option) {
            case 'b':
                flagB = 1;
                //printf("flag B enabled\n");
                break;
            case 'e':
                flagE = 1;
               // printf("flag E enabled\n");
                break;
            case 'n':
                flagN = 1;
                //printf("flag N enabled\n");
                break;
            case 's':
                flagS = 1;
               // printf("flag S enabled\n");
                break;  
             }
    }
    // close if
    else{// open else 

        // IF NO flag is passed by the user set 'flagNoarg' to ON/TRUE/1
        flagNoarg = 1;
                //printf("no flag\n");

    }// close else
    // Initialize  int and characters
    int fd;
    int numBytes;
    char buffer[BUFFERSIZE];

    // loop for arguments
    for (int i = 1; i < ac; i++) {  
        if(av[i][0] =='-') {
            i++;   // increment counter
        }
        // intialize # of line and characters
        int line = 1;
        char ch;
        const char *str;
        // loop for the file being passed as second arguments by the user
        for (int j = 0; av[i][j] != '\0'; ++j) {//traverses arrray until a nul value

        // open file in READ ONLY MODE
            fd = open(av[j], O_RDONLY);
        
        // WHile the # of is greater than 0 keep reading
            while ((numBytes = read(fd,buffer,BUFFERSIZE))>0)  {

                // Add a null terminated value to the strings
                buffer[numBytes] = '\0';
                // if no flag argumnent is passed, just print the files to console
                    if(flagNoarg){
                        printf("%s", buffer);
                    }

                // else print the file according to the flag 
                    else{
                
                for (int k = 0; k<= numBytes; k++) { // open for loop
                    // '-n' Number the output lines, starting at 1.
                    if (flagN) {
                        if (k==0)
                            printf("%6d\t",line++);
                        if(buffer[k] == '\n'){
                            printf("\n%6d\t",line);
                            line++;
                        }
                        else
                            printf("%c", buffer[k]);
                    }
                    // '-e' Display a dollar sign ('$') at the end of each line
                    if (flagE) {
                        if(buffer[k]== '\n') {
                            printf("\t$");
                        }
                        printf("%c", buffer[k]);
                    }
                    
                    // '-b' Number the non-blank output lines, starting at 1.
                    if (flagB) {
                        if (k==0)
                            printf("%6d\t",line++);                          
                        if((buffer[k] == '\n' && buffer[k-2] == ' ')){
                            printf("\n%6d\t",line);
                            line++;
                            if (buffer[k] == '\n' && buffer[k-2] != ' '){ 
                                printf("\n%6d\t",line);                   
                            }
                        }
                        else
                            printf("%c", buffer[k]);
                    }
                    } // close for loop

                    // close file
                    close(fd);   
					                }
                // add new line
                printf("\n");
            }
        }
    }
}
