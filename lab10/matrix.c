/*
    Giovanni Tshibangu
    CS355  :In this assignment, you will write a program that uses curses library and timer to create a Matrix-style effect.
    6/30/2022
*/

#include <curses.h>
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

// Random number generator function prototype.
char rand_value();

// Main Function
int main(int ac, char* av[]){
     // init window
    initscr();
    // Init Speed
    int speed =1;   
    // Check for Second args 
    if(ac ==2)
        speed =atoi(av[1]); // set speed to args passed by the user
    // Create a Matrix, using the current terminal LINES and COLS size.
    char myMatrix[COLS][LINES];

        // iterate through columns and columns
        // Y  =COLS or columns and X = LINES or ROWS
    for (int y = 0; y < COLS; y += 1) {
        for (int x = 0; x < LINES; x += 1) {
            myMatrix[y][x] = rand_value();
        }
    }
    /* This loop will run untill the user presses CTRL-C */
    while (true) {
        // Loop through columns
        for (int i = 0; i < COLS; i++) {
            for (int j = LINES - 1; j > 0; j--) {
                myMatrix[i][j] = myMatrix[i][j - 1];
            }
            // randomly set character to matrix
            myMatrix[i][0] = rand_value();

            // Print  column to the screen
            for (int k = 0; k < LINES; k++) {
                move(k, i);
                addch(myMatrix[i][k]);
            }
        }
        // refresh the screen
        refresh();
        // sleep for speed time
        usleep(speed);
    }
    // reset terminal
    endwin();
    return 0;
}

// Returns Random value between 0-1 and a space
char rand_value(){
    switch (rand()%3) { // To get three random characters.
        case 0: return '0';
        case 1: return '1';
        case 2: return ' ';
    }

    return ' ';
}
