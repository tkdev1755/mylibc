

#include <stddef.h>
void* mini_calloc(int size_element, int number_element);
int getSize(void* ptr);
void mini_free(void* ptr);
void mini_exit(void);
char* mini_itoa(int number);
void mini_printf(char* str);
int mini_scanf(char* buffer, int size_buffer);
int mini_strlen(char* s,int maxlen);
int mini_strcpy(char* s, char* d, int dstSize);
int mini_strcmp(char* s1, char* s2,int n);
void mini_perror(char* message);

struct malloc_element{
  void* addr;
  size_t size;
  int status;
  struct malloc_element* next_malloc;
};

typedef struct{
    int fd;
    void* buffer_read;
    void* buffer_write;
    int ind_read;
    int ind_write;
} MYFILE;

MYFILE* mini_fopen(char* file, char mode);

int mini_fread(void* buffer , int size_element, int number_element, MYFILE* file); 

int mini_fwrite(void* buffer, int size_element, int number_element, MYFILE* file);

int mini_fflush(MYFILE* file);

int mini_fclose(MYFILE* file);

int mini_fgetc(MYFILE* file);

int mini_fputc(MYFILE* file,char c);
