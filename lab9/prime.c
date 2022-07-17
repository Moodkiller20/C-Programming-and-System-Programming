/*
    Giovanni Tshibangu
    CS 355 lab 9: write a program that provides a custom handler for the interrupt signal.
    6/27/2022
*/

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include<stdlib.h>

int largestPrime;       // Initialize the largest prime 
int runFlag =1;         // Initialize State  1== keep running 

/////////////////////////   PrimeCheck funcion
void primeCheck(int n){
    int  i, k = 0;          // Initialize counters
    // Loop from 1 to n 
    for (i = 1; i <= n; i++) {
        if (n % i == 0) {   //check if the remainder of n/i is a 0
            k++;    // increment counter
        }
    }
    if (k == 2) {      
            largestPrime=n;    // Set largest number equal to K
    }
}

// forward delaration of a signal handler
void ouch(int);

///////////////////////// MAIN FUNCTION
int main() {
    
    signal(SIGINT, ouch);           // reprograms the interrupt signal handler
    while(runFlag==1){              // Run for as long as the run state is ==1
        int n;                      // initialize counter
        for(n=2;n >0;n++){          // Staring at 2, loop to any number above 0
            primeCheck(n);          // Pass the number as an arg to the primeCheck function one by one.
        }
    }
   return 0; 
}

//////////////////////////////////////////// Signal handler function
void ouch(int signum) {
    char c;     // initialize a character
    printf(" %d     Quit [y/n]?     ",largestPrime);    //  prompt the user with opetion to either quit or not
    system("/bin/stty raw");
    c=getchar();            //  get the user input character
    system("/bin/stty cooked");
    
    // Logic
    if(c == 'n' || c == 'N'){   // if n or N keep running
        printf("\n");
        runFlag = 1;
    }
    else if(c == 'y' || c == 'Y'){ // if y or Y Stop running
        runFlag = 0;
        signal(SIGINT, SIG_DFL);    // restore the default interrupt signal handler
        raise(SIGINT);              // generates an interrupt signal, which kills the process    
    }
    else {  // keep running 
        printf("\n");
        runFlag = 1;    
    }
}