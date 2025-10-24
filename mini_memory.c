#include <unistd.h>
#include "mini_lib.h"
#include <stdio.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>


#define DEBUG
struct malloc_element* malloc_list = NULL;

struct malloc_element* checkFreeSpace (){
  struct malloc_element* element = malloc_list;
  if (element == NULL){
    return NULL;
  }
  while (element->status != 0){
    if (element->next_malloc == NULL){
      return NULL;
    }
    element = element->next_malloc;
  }
  return element;
}

int checkSize(size_t a, size_t b){
  return a <= b ? a==b ? 2 : 1  : 0;
}

void * mini_calloc(int size_element, int number_element){
  if (size_element < 0 || number_element < 0){
    mini_perror("Impossible d'allouer un espace mémoire négatif \n");
    return NULL;
  }
  struct rlimit* sysInfo = sbrk(sizeof(struct rlimit));
  int lmCheck = getrlimit(RLIMIT_DATA,sysInfo);
  if (sysInfo->rlim_cur < size_element*number_element && sysInfo->rlim_cur != RLIM_INFINITY){
    mini_perror("Mémoire insuffisante \n");
    return NULL;
  }
  #ifdef DEBUG
  #endif
  struct malloc_element* element = checkFreeSpace();
  void*  result = NULL;
  if (element != NULL){
    if (checkSize(size_element*number_element, element->size) == 2){
      for (int i=0; i<(size_element*number_element)/sizeof(char); i++){
        ((char*) element->addr)[i] = '\0'; 
      }
      return element->addr;
    }
    else if (checkSize(size_element*number_element, element->size) == 1){
      //element->size = size_element*number_element;
      for (int i=0; i<(size_element*number_element)/sizeof(char); i++){
        ((char*) element->addr)[i] = '\0'; 
      }
      return element->addr;
    }
    else{
      void*  result = sbrk(size_element*number_element);
      #ifdef DEBUG
      #endif
      element = sbrk(sizeof(struct malloc_element));
      if (result != (void*)-1){
        element->next_malloc = malloc_list;
        element->addr = result;
        element->size = size_element*number_element;
        element->status = 1;
        malloc_list = element;
        for (int i=0; i<(size_element*number_element)/sizeof(char); i++){
          ((char*) result)[i] = '\0'; 
        }
        return result;
      }
      else{
        write(2, "erreur d'allocation", 20);
      }
      return result;
    }
    #ifdef DEBUG
    #endif
    //write(1,"allocated malloc_list \n ", 22);
  }
  else{
    void*  result = sbrk(size_element*number_element);
    write(1,result,5);
    #ifdef DEBUG
    #endif
    element = sbrk(sizeof(struct malloc_element));
    if (result != (void *) -1){
      element->next_malloc = malloc_list;
      element->addr = result;
      element->size = size_element*number_element;
      element->status = 1;
      malloc_list = element;
      for (int i=0; i<(size_element*number_element)/sizeof(char); i++){
        ((char*) result)[i] = '\0'; 
      }
      return result;
    }
    else{
      write(2, "erreur d'allocation", 20);
      mini_perror("Erreur allocation");
      return NULL;
    }
  }

}
int getSize(void* ptr){
  struct malloc_element* elt = malloc_list;
  while(elt->addr != ptr){
    if (elt->next_malloc == NULL){
      return -1;
    }
    elt = elt->next_malloc;
  }
  return elt->size;
}

void mini_free(void* ptr){
  struct malloc_element* element = malloc_list;
  while(element->addr != ptr){
    if (element->next_malloc == NULL){
      break;
    }
    element = element->next_malloc;
  }
  if (element->next_malloc == NULL && element->addr != ptr){
    #ifdef DEBUG
    write(1, "Address does not exist\n",20);
    #endif
  }
  else{
    
    element->status = 0;
  }
}

void mini_exit(void){
  extern int ind;
  extern char* buffer;
  extern int flistSize;
  extern MYFILE** fList;
  
  if ((ind) != -1){
    #ifdef DEBUG
      write(1,"Need to flush buffer\n", 22);
    #endif
    mini_free(buffer);
  }
  if (flistSize != -1){
    for (int i = 0; i<flistSize; i++){
      //mini_fclose(fList[i]);
    }
  }
  _exit(0);
}
