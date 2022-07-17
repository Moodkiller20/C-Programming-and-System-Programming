/*
    Giovanni Tshibangu
    CS 355 lab8:  write a program that can send a message to another user logged into a Unix computer.
    6/23/2022

*/
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <utmp.h>

# define BUFSIZE 1024   // Define the buffer size

int main(int ac, char* av[]) {
    // Initialize  Sender and Reciepient Strings holders
    char* recevier;
    char* sender;
    // initialize utmp record
    struct utmp currentRecord;
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
    //Read
    read(IntUTMPfile,&currentRecord,IntUTMPlength);
    // if the number of arguments is not 2, print an error
    if(ac!=2){
        fprintf(stderr," usage %s ttyname\n", av[0]);
        printf("Try mywrite <'username'> \n");
    }  
    else{

        int ret;
        // compare if the username passed in the terminal is a the currrent logged in user.
        ret = strcmp(&currentRecord.ut_user[0], av[1]); 
        if(ret!=0){     // if username does not match the logged in user, print error
            fprintf(stderr," User %s is not logged in \n",av[1]);
        }
        else{
            recevier = "/dev/pts/4";
            sender = av[1];
            printf("Connected with @%s, Start typing... \n",sender);
            
        // Init file descriptor
        int fd = open(recevier, O_WRONLY);
        if(fd ==-1){    // if file doesnt open, print error
            printf(" User %s is not logged in or \n",av[1]);
            perror(av[1]);
            return 1;
        }
        else{
            char buf[BUFSIZE];
            char hiMessage[] ="Message from yourname@yourhost on yourtty at hh:mm... \n";
            char byMessage[] = "EOF \n";
            write(fd,hiMessage,strlen(hiMessage));  // Write on the receipient console 
            while(fgets(buf, BUFSIZE,stdin)!=0) // Write on the receipient console 
                if(write(fd,buf,strlen(buf))==-1)   // Write on the receipient console 
                    break;  // Break out of the loop
            write(fd,byMessage,strlen(byMessage));  // Write on the receipient console
            close(fd);  // close file or console
        }
    }
}
    return 0;
}