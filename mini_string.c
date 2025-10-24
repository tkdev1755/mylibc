#include "mini_lib.h"
#include <unistd.h>
#include <stdio.h>
#include <errno.h> 
#define BUF_SIZE 1024

char* buffer;

int ind = -1;
char* mini_itoa(int number){
  int i = 0; 
  int size;
  int nbCpy  = number;
  int negative = number < 0;
  
  while (nbCpy%10 > 1){
    nbCpy = nbCpy%10;
    size++;
  }
  char* str = mini_calloc(sizeof(char), size);
  
  do {
    str[i++] = (number%10) + '0';
    number /= 10; 
  } while (number>0);
  str[i] = '\0';
  for (int j = 0; j < i/2; j++){
    char temp = str[j];
    str[j] = str[i-j-1];
    str[i-j-1] = temp;
  }
  return str;
}

void mini_printf(char* str){
  ind = 0;
  int sSize = 0;
  buffer = mini_calloc(sizeof(char), BUF_SIZE);
  while (str[sSize] != '\0'){
    #ifdef DEBUG
    #endif
    if (ind == BUF_SIZE || (ind != 0 && buffer[ind-1] == '\n') || str[sSize+1]== '\0'){
      //write(1, "Entering displaying buffer state\n",34 );
      write(1, buffer, ind);
      mini_free(buffer);
      buffer = mini_calloc(sizeof(char), BUF_SIZE);
      ind = 0;
      if (str[sSize+1] == '\0') sSize++;     
    }
    else{
      //write(1, "Entering copying to buffer state \n",34 );
      for (int i = 0; i<BUF_SIZE; i++){
        #ifdef DEBUG
        printf("Attempt n°%i \n", ind);
        #endif
        if (str[sSize] == '\n'){
          i = 1023;
        }
        buffer[ind] = str[sSize];
        if (str[sSize+1] == '\0'){
          i = 1023;
          sSize--;  
        }
        ind++; sSize++;
      
      }
    }
    
  }
}

int mini_scanf(char* buffer, int size_buffer){
  int s = 0;
  ssize_t d = read(0, buffer, size_buffer);
  int finalSize = d/sizeof(char);
  return 0;
}

int mini_strlen(char* s,int maxlen){
  int sSize = 0;
  while (s[sSize] != '\0' && sSize < maxlen){
    sSize++;
  }
  return sSize+1;
}

int mini_strcpy(char* s, char* d, int dstSize){
  int sSize = 0;
  while(s[sSize] != '\0' && sSize < dstSize){
    d[sSize] = s[sSize];
    sSize++;
  }
  d[sSize] = s[sSize];
  return sSize+1;
}
int mini_strcmp(char* s1, char* s2, int n){
  int equality = 0;
  int s1Size = 0;
  int s2Size = 0;
  while(s1[s1Size] != '\0' || s2[s2Size] != '\0' && s1Size < n){
    if (s1[s1Size] == s2[s2Size]) {
      equality++;
    }
    if (s1[s1Size] != '\0') {
      s1Size++;
    }
    if (s2[s2Size] != '\0') {
      s2Size++;
    }
  }
  #ifdef DEBUG
    printf("Equality value : %i \n", equality);
    printf("S1 size %i, S2 size %i \n", s1Size, s2Size);
  #endif

  return equality == s1Size && equality == s2Size ? 0 : s1Size-s2Size; 
}

void mini_perror(char* message){
  mini_printf(message);
  mini_printf(": ");
  extern int errno;
  mini_printf(mini_itoa(errno));
}