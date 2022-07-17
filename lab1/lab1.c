// Programmer: Giovanni Tshibangu 
// Date: 5/31/2022

#include <stdio.h>

// Initialize function 
int FizzBuzz(int);

// main function 
int main(){

    //Initialize int Variable 
    int iNumber=0;

    // Print to the console
    printf("Please enter an integer: \n");

    // Get value entered from the console and store it in iNumber
    scanf("%d",&iNumber);

    // Call FizzBuzz function and pass iNumber as parameter
    int temp = FizzBuzz(iNumber);                     
    return 0;
    }

int FizzBuzz(int iNumber) {
    
    // Iterate through the number from 0 to iNumber (Included)
    for (int i = 0; i <= iNumber; i++) {

        // Check if the value is a multiple of 5 and 3
        if ((i%5 == 0)&&(i%3 == 0)){
            printf("FizzBuzz\n");
            } 

        // Check if the value is a multiple of 5
        else if (i%5 == 0) {
            printf("Buzz\n");
            }

        // Check if the value is a multiple of 3    
        else if(i%3 == 0){
            printf("Fizz\n");
            }

        // If none of the above conditions are met, just print the integer.    
        else{
            printf("%d\n",i);
            }
}
return 0;
}

