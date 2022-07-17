// Giovanni Thsibangu
// CS 355 : Lab3 


# include <stdio.h>
# include <string.h>
# include <utmp.h>
# include <unistd.h>
# include <fcntl.h>
# include <time.h> // this helps me format the time.

/*
open utmp
repeat
    read utmp record
    display utmp record
close utmp
*/

void formatTime(long t);

int main(){
    // initialize utmp record
    struct utmp currentRecord;

    // Variables 
    int IntUTMPfile;
    int IntUTMPlength = sizeof(currentRecord);
   
    //"open()" System call. This call give control to the OS itself
    IntUTMPfile = open(UTMP_FILE, O_RDONLY );

    // if the file does not open correctly 
    if(IntUTMPfile==-1){
        // print the error.
        perror(UTMP_FILE); // "perror will interpret the error code and print it on the screen"
        // return -1 to stop the programm.
        return -1;
    } 
    // else continue with the file.
    else{

    //"read()" System call. This call give control to the OS itself
    while(read(IntUTMPfile,&currentRecord,IntUTMPlength)== IntUTMPlength){
        printf("%s %s   \t", currentRecord.ut_user,currentRecord.ut_line);
        //printf("%s ", currentRecord.ut_user,currentRecord.ut_line, currentRecord.ut_host);
        formatTime(currentRecord.ut_time );
        printf("(%s) ", currentRecord.ut_host);
        printf("\n");

        }// close loop
    } // close case

    //"close()" System call. This call give control to the OS itself
    close(IntUTMPfile);
    return 0;
}

// This function format the value passed in as a parameter to a more readable time.
void formatTime(long unformated_time){
    char timeBuff[BUFSIZ];

    // tm is a struct and it holds time and date.
    struct tm *timeDetail = localtime(&unformated_time);

    // Helps format the time to the format specified 
    strftime(timeBuff,sizeof(timeBuff), "%Y-%m-%d %H:%M", timeDetail);
    
    // Here I am printing the time.
    printf("%s", timeBuff);

   

}