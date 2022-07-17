/*  Giovanni Tshibangu
    CS 355 Lab7 : Write a C program myfind whose behavior resembles that of the system command find.
    6/20/2022
*/

# include <stdio.h>
# include <dirent.h>
# include <sys/stat.h>
# include <string.h>
# include <limits.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <utmp.h>
/*


*/
// initialize utmp record
struct utmp currentRecord;

    // Variables 
int IntUTMPfile;
int IntUTMPlength = sizeof(currentRecord);
char modestring[11];
char* p; 
void mode_to_string(int mode, char str[]){
    strcpy(str,"----------");
    if(S_ISDIR(mode)) str[0]='d';
    if(S_ISCHR(mode)) str[0]='c';
    if(S_ISBLK(mode)) str[0]='b';
    if(S_ISLNK(mode)) str[0]='l';
    // read bit in the user bites
    if(mode &S_IRUSR) str[1]='r';
    if(mode &S_IWUSR) str[2]='w';
    if(mode &S_IWUSR) str[3]='x';
    // read bit in the group bites
    if(mode &S_IRGRP) str[4]='r';
    if(mode &S_IWGRP) str[5]='w';
    if(mode &S_IWGRP) str[6]='x';
    // read bit in the other bites    
    if(mode &S_IROTH) str[7]='r';
    if(mode &S_IWOTH) str[8]='w';
    if(mode &S_IWOTH) str[9]='x';
}
int proccess_Dir(char *filename,char *dir_entry_name){
    // initialize
    DIR *dir_ptr1;
    struct dirent *dirent_ptr1;
    struct stat info;   
    dir_ptr1 = opendir(dir_entry_name); // open file 
    if(dir_ptr1 ==0){   //check for error
        perror(dir_entry_name);
    }
    else{
        while((dirent_ptr1 = readdir(dir_ptr1))!=0){
            mode_to_string(info.st_mode, modestring); // Translate User mode through Bitwise operation
            IntUTMPfile = open(UTMP_FILE, O_RDONLY );
            p =strstr(dirent_ptr1->d_name, filename);   // Check for match 
            if((p)&&(S_ISDIR(info.st_mode)==0)&&(IntUTMPfile!=-1)){    // Check for the substing match in the file name.
                printf("    %s  (%d/%s)\n", dirent_ptr1->d_name, info.st_uid,modestring);  // print file name, userID, and userMode  
            }  
        }  
    } 
    closedir(dir_ptr1); // close directory
   return 0;
}

int main(int ac, char** av){
    DIR *dir_ptr;
    struct dirent *dirent_ptr;
    struct stat info;
    char* filename; // Substing to match 
    char *dir_name ;    // Staring directory

    while(ac!=0){   //Open while
        if(av[1]){  //open if
           filename = av[1]; // Set file name to user input 
        }   //close if 
        if(av[2]){  //open if
            dir_name = av[2];   // Set starting directory to user input 
        }   //close if
        else{   //open else
           dir_name ="." ;  // else start at current direcotry.
        }   //close else
        break;
    }   //close while loop
    dir_ptr = opendir(dir_name);    // oppen directory
    if(dir_ptr ==0){    // check if open successfully
        perror(dir_name);   // print error if not open
    }   // close if 
    else{   //open else
        while((dirent_ptr = readdir(dir_ptr))!=0){  // pen while
            if(stat(dirent_ptr->d_name, &info) ==-1){ 
                perror(dirent_ptr->d_name); // print error if directory fail to read
            }   // close if
            else {  // open else
                p =strstr(dirent_ptr->d_name, filename);    // Check for the substing match in the file name.
                if(p){    // Check for the substing match in the file name.
                    //printf(" %s is a File\n", dirent_ptr->d_name);
                    mode_to_string(info.st_mode, modestring); // Translate User mode through Bitwise operation
                    printf("    %s (%d/%s)\n", dirent_ptr->d_name, info.st_uid,modestring);
                } 
            }
            IntUTMPfile = open(UTMP_FILE, O_RDONLY );   //"open()" System call. This call give control to the OS itself
            if((S_ISDIR(info.st_mode))&& (IntUTMPfile!=-1)){   // Check for the substing match in the file name.
                read(IntUTMPfile,&currentRecord,IntUTMPlength); //"read()" System call. This call give control to the OS itself
                printf("/users/%s/home/%s/%s\n",currentRecord.ut_user,dir_name,dirent_ptr->d_name);  // print the file path
                
                proccess_Dir(filename,dirent_ptr->d_name);  // calling a function to read file from directores 
            }
        }
    }
    return 0;
}