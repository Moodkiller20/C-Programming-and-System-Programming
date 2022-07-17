#include<dirent.h>
#include<errno.h>
#include<stdio.h>
#include<string.h>

int main(int argc, char *argv[]){

struct dirent *direntp;
DIR *d;
char path[50];
char opt[3];
char data[20000][50];
char temp[50];
int i,j;
strcpy(opt,"");
if (argc == 1){
strcpy(path,".");
}
if (argc == 2){
if (argv[1][0] == '-'){
strcpy(opt,argv[1]);
strcpy(path,".");
}
else {
strcpy(path,argv[1]);
}
}

if (argc == 3){
strcpy(opt, argv[1]);
strcpy(path, argv[2]);
}

if ((d = opendir(path)) == NULL){
perror("Failed to open directory");
return 1;
}
int count = 0;
while((direntp = readdir(d)) != NULL){
//printf("%s %d\n",direntp->d_name,count);
strcpy(data[count],direntp->d_name);
count++;

}

while((closedir(d) == -1) && (errno == EINTR));

if (strcmp(opt,"-a") == 0){
for (i = 0; i<count; i++)
printf("%s\n",data[i]);
}
else if (strcmp(opt,"-s") == 0){
for (i = 0; i<count; i++){
for (j=i+1; j<count; j++){
if (strcmp(data[i],data[j]) > 0){
strcpy(temp,data[i]);
strcpy(data[i],data[j]);
strcpy(data[j],temp);
}
}
}
for (i = 0; i<count; i++)
if (data[i][0] != '.')
printf("%s\n",data[i]);

}
else if (strcmp(opt,"-r") == 0){

for (i = 0; i<count; i++){
for (j=i+1; j<count; j++){
if (strcmp(data[i],data[j]) < 0){
strcpy(temp,data[i]);
strcpy(data[i],data[j]);
strcpy(data[j],temp);
}
}
}
for (i = 0; i<count; i++)
if (data[i][0] != '.')
printf("%s\n",data[i]);

}
else {

for (i = 0; i<count; i++)
if (data[i][0] != '.')
printf("%s\n",data[i]);

}

return 0;
}