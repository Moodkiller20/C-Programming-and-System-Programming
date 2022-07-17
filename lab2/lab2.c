// Giovanni Tshibangu
// 6/6/2022

# include <stdio.h>
//to get the string length


// This function gets the length 
int strLength(char *str){
    // initialize counter 
    int i=0;
    for(i=0;str[i]!='\0';i++);
    return i;
}

// Main Function
int main(int argc, char *argv[]){
    char chr,n;

    // return nothing if nothing is passed
    if(argc==0){
        return 0;
    }
// initialize counter 
int i,k,j;

    for(int i=1;i<argc;i++){
       //from 0 to strlen of that argument
       for( j=0; j< strLength(argv[i]); j++){
           //from 0 to j
           for( k=0; k<j+1; k++){
               n = argv[i][0];
               chr = argv[i][k];
               //checking if the character is an alphabet 
               if((chr>=97 && chr<=122) || (chr>=65 && chr<=90)){
                printf("%c",chr);    
               }
           }
           printf("\n");
       }
    }
    return 0;
}


