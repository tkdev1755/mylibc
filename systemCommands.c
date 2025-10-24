#include "systemCommands.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#define DEBUG
int mini_touch(char* fName){
    MYFILE* newFile = mini_fopen(fName, 'z');
    if (newFile == NULL){
        return -1;
    }
    else{
        return 0;
    }
}

int mini_echo(char* strDsp){
    mini_printf(strDsp);
}

int mini_cp(char* src, char* dst){
    int fddst = open(dst,O_WRONLY|O_CREAT|O_TRUNC,0);
	int fdsrc = open(src, O_RDONLY);
	int TBUF = 1024;
	char BUFFER[TBUF];
	int nbread = 0;
	while ((nbread = read(fdsrc, BUFFER, TBUF)) > 0){
		write(fddst, BUFFER, nbread);
	}
	close(fddst);
	close(fdsrc);
}

int mini_head(char* fName, int n){

}

int mini_tail(char* fName,int N){
    int d1;
  struct stat fStat;
  d1 = open(fName, O_RDONLY);
  int stt = stat(fName, &fStat);
  int *rLPos = mini_calloc(sizeof(int),1);
  if (d1 == -1 && stt == -1) {
    mini_perror("Fichier non ouvert");
  } else {
    char buffer[fStat.st_size];
    int displayLength = N == 0 ? 4 : N;
    read(d1, buffer, fStat.st_size);
    int size = 0;
    int lS = 1;
    rLPos = mini_calloc(sizeof(char), fStat.st_size/sizeof(char));
    while (size <= fStat.st_size) {
      if (buffer[size] == '\n') {
        lS++;
        rLPos[(lS - 1)] = size;
      }
      size++;
    }
    lseek(d1, rLPos[lS - displayLength], SEEK_SET);
    read(d1, buffer, (size - rLPos[lS - displayLength]));
    write(1, buffer, (size - rLPos[lS - displayLength]));
  }
  close(d1);
  mini_exit;
};

int mini_clean(char* fName){
    int fd = open(fName,O_TRUNC);
    if (fd == -1){
        return -1;
    }
    close(fd);
    return 1;
}

int mini_grep(char* fName, char* pattern){
    MYFILE* file = mini_calloc(sizeof(MYFILE),1);
    file = mini_fopen(fName,'r');
    struct stat fStat;
    int stt = stat(fName, &fStat);
    int rSize = 0;
    int status = 0;
    int patternIndex = 0;
    int lastLine = 0;
    char* buffer = mini_calloc(sizeof(char), fStat.st_size/sizeof(char)); 
    int read = mini_fread(buffer, sizeof(char), fStat.st_size/sizeof(char), file);
    #ifdef DEBUG
    printf("READ Value %s \n", buffer);
    #endif
    while (rSize < fStat.st_size/sizeof(char)){
        if (status && (buffer[rSize] ==  '\n')){
            write(1,"PATTERN + NEWLINE FOUND\n",25);
            write(1,buffer+lastLine+1,rSize-lastLine+1);
            status = 0;
        }
        if (buffer[rSize] == '\n'){
            write(1,"newLine \n", 10);
            lastLine = rSize;
        }
        if (buffer[rSize] == pattern[patternIndex]){
            write(1,"found part pattern\n", 20);
            patternIndex++;
            if (patternIndex == (mini_strlen(pattern, 4096)-1)){
                write(1,"found pattern\n", 15);
                status = 1;
            }
        }
        else { 
            write(1,"pattern broken\n", 16);
            patternIndex = 0;
        }
        
        rSize++;
    }
};

int wc(char* fName){
    MYFILE* file = mini_calloc(sizeof(MYFILE),1);
    file = mini_fopen(fName,'r');
    if (file == NULL){
        mini_perror("Impossible d'ouvrir le fichier");
        return -1;
    }
    struct stat fStat;
    int stt = stat(fName, &fStat);
    char* buffer = mini_calloc(sizeof(char), fStat.st_size/sizeof(char)); 
    int read = mini_fread(buffer, sizeof(char), fStat.st_size/sizeof(char), file);
    int rSize = 0;
    int numberOfWords = 0;
    while (rSize<(fStat.st_size/sizeof(char))){
        if (buffer[rSize] == '\n' || buffer[rSize] == '\0' || buffer[rSize] == ' '){
            mini_printf("New word \n");
           numberOfWords++; 
        }
        mini_printf("nothing");
        rSize++;
    }
    write(1,"Nombre de mots dans le fichier : ",34);
    #ifdef DEBUG
    printf("\n %i \n", numberOfWords);
    #endif
    //write(1,mini_itoa(numberOfWords),4);
    return 1;
};

int mini_ls(){
    
}