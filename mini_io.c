#include <fcntl.h>
#include "mini_lib.h"
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/resource.h>
 #include <sys/resource.h>
#define IOBUFFER_SIZE 2048

MYFILE** fList;

int flistSize = -1;

MYFILE* mini_fopen(char* name, char mode){
    // Ici je vérifie si un fichier à déjà été ouvert
    if (flistSize == -1){
        struct rlimit* sysInfo = mini_calloc(sizeof(struct rlimit), 1);
        int fLimit = getrlimit(RLIMIT_NOFILE,sysInfo);
        fList = mini_calloc(sizeof(MYFILE*),sysInfo->rlim_cur != RLIM_INFINITY ? sysInfo->rlim_cur: 128);
        #define DEBUG
        printf("Limite de fichiers %i\n",sysInfo->rlim_cur);
        if (fList != NULL){
         flistSize = 0;
        }
        else{
            mini_perror("Erreur lors de la création de la liste des fichiers ouverts");
            return NULL;
        }        
    }

    // Ici je check quel est le mode d'ouverture
    int oMode = 0;
    switch (mode)
    {
    case 'r':
        oMode = O_RDONLY;
        break;
    case 'w':
        oMode = O_WRONLY;
        break;
    case 'b':
        oMode = O_RDWR;
        break;
    case 'a':
        oMode = O_APPEND;
        break;
    case 'z':
        oMode = O_RDONLY | O_CREAT;
        break;
    default:
        mini_perror("Mode d'ouverture non reconnu");
        return NULL;
        break;
    }


    MYFILE* file = mini_calloc(sizeof(MYFILE), 1);
    int fd;
    if ((fd = open(name,oMode))  == -1){
        mini_perror("Impossible d'ouvrir le fichier");
        return NULL;
    }
    file->fd = fd;
    file->buffer_read = NULL;
    file->buffer_write = NULL;
    file->ind_read = -1;
    file->ind_write = -1;
    fList[flistSize] = file;
    flistSize++;
    return file;
}

int mini_fread(void* buffer, int size_element, int number_element, MYFILE* file){
    // Je m'assure que le Buffer passé en paramètre est suffisamment grand pour prendre ce que l'utilisateur veut lire
    if (getSize(buffer) < size_element*number_element){
        mini_perror("Buffer passé en paramètre trop petit");
        return -1;
    }
    int bSize = 0;
    int readStatus = 0;
    int sizeToRead = IOBUFFER_SIZE > size_element*number_element ? size_element*number_element : IOBUFFER_SIZE;
    if (file->ind_read == -1){
        #ifdef DEBUG
        write(1,"Initializing buffer\n",21);
        #endif
        file->buffer_read = mini_calloc(sizeToRead+1, 1);
        file->ind_read = 0;
    }
    while(bSize < size_element*number_element){
        // Si buffer plein je flush
        if (file->ind_read == IOBUFFER_SIZE){
            #ifdef DEBUG
            write(1,"Buffer full, flushing it \n",27);
            #endif
            mini_free(file->buffer_read);
            file->ind_read = -1;
            file->buffer_read = mini_calloc(sizeToRead+1,1);
        }
        // si le fichier est fini d'être lu avant que le buffer soit plein je l'indique
        if (readStatus == 1){
            #ifdef DEBUG
            write(1,"Ended File read \n",18);
            #endif
            char* tempBuf = buffer;
            tempBuf[bSize+1] = '\0';

            return bSize;
        }
        // Lecture du fichier nominale
        else{
            file->ind_read = read(file->fd, file->buffer_read,sizeToRead);
            readStatus = file->ind_read < IOBUFFER_SIZE ? 1 : 0;
            #ifdef DEBUG
            printf("Size of ind_read %i \n", file->ind_read);
            printf("readStatus %i \n", readStatus);
            printf("Size of THINGS %i", (size_element*number_element));
            #endif
            for (int i = 0;i < (file->ind_read); i++){
                char* tempBuf = buffer;
                char* bufRead = file->buffer_read;
                tempBuf[bSize+i] = bufRead[i]; 
            }
            bSize += file->ind_read;
        }
    }
    char* tempBufF = buffer;
    tempBufF[bSize] = '\0';
    return bSize;
}

int mini_fwrite(void* buffer, int size_element, int number_element, MYFILE* file){
    int wSize = 0;
    int wStatus = 0;
    int sizeToWrite = IOBUFFER_SIZE > size_element*number_element ? size_element*number_element : IOBUFFER_SIZE;
    // vérification d
    if (file->ind_write == -1){
        #ifdef DEBUG
        write(1,"Initializing buffer\n",21);
        printf("Size of sizeToWrite = %i",sizeToWrite);
        #endif
        file->buffer_write = mini_calloc(sizeToWrite, 1);
        file->ind_write = 0;
    }
    while (wSize < size_element*number_element){
        // Si buffer plein, flusher le buffer
        if (file->ind_write == IOBUFFER_SIZE){
            #ifdef DEBUG
            write(1,"Buffer full, flushing it \n",27);
            char* bufWrite = file->buffer_write;
            printf("BUFWRITE NUL OU NON ? de  : %i \n",bufWrite[1] == '\0' );
            #endif
            wSize = write(file->fd, file->buffer_write, sizeToWrite);
            write(1,"Written to file \n",18);
            mini_free(file->buffer_write);
            write(1,"Freed memory \n",15);
            file->ind_write = -1;
            file->buffer_write = mini_calloc(sizeToWrite,1);
            file->ind_read = 0;
        }
        // si j'ai écrit tout les caractères avant que le buffer soit plein
        if (wStatus){
            wStatus = wSize;
            wSize = size_element*number_element;
            write(1,"Written all the characters\n",28);
        }
        // remplissage du buffer en temps normal
        else{
            #ifdef DEBUG
            printf("Size of THINGS %i\n", (size_element*number_element));
            #endif
            for (int i = 0; i < sizeToWrite; i++){
                char* tempBuf = buffer;
                char* bufWrite = file->buffer_write;
                #ifdef DEBUG
                
                printf("buffer à l'index %i : %c \nEt bufWrite à l'index %i : %c\n", wSize+i, tempBuf[wSize+i],i-1, ((char*)file->buffer_write)[(i-1>=0 ? i-1 : 0)]);
                //printf("%c", bufWrite[(i-1>=0 ? i-1 : 0)]);
                #endif
                if (tempBuf[wSize+i] == '\0'){
                    wStatus = 1;
                    i = 1023;
                }
                bufWrite[i] = tempBuf[wSize+i];
                file->ind_write++;
            }
            write(1,"\n",2);
            #ifdef DEBUG
            write(1,"Ended Bcopy\n", 12);
            printf("buffer write value %s \n", file->buffer_write, wSize);
            #endif
            wSize += file->ind_write;
        }
    }
    #ifdef DEBUG
    #endif
    return wStatus>0 ? wStatus : wSize;
}

int mini_fflush(MYFILE* file){
    if (file->ind_write == -1){
        #ifdef DEBUG
        write(1,"Buffer already flushed\n",24);
        #endif
        return -1;
    }
    else{
        #ifdef DEBUG
        write(1, "Displaying write value ", 24);
        #endif
        int writtenBytes = write(file->fd, file->buffer_write, file->ind_write);
        #ifdef DEBUG
        write(1, mini_itoa(writtenBytes),4);
        #endif
        #ifdef DEBUG
        printf("BUFFER VALUE %i\n", writtenBytes);
        #endif
        if (writtenBytes != -1){
            mini_free(file->buffer_write);
            file->ind_write = -1;
            #ifdef DEBUG
            write(1,"Flushed buffer Successfully \n", 30);
            #endif
        } 
        return writtenBytes;
    }
}

int mini_fclose(MYFILE* file){
    int i = 0;
    while(file != fList[i] && i < flistSize){
        fList++;
    }
    mini_fflush(file);
    if (i<flistSize){
        for(int j = i; j<flistSize ; j++){
            fList[j] = j+1<flistSize ? fList[j+1] : NULL;
        }
    }
    close(file->fd);
}

int mini_fgetc(MYFILE* file){
    char* buffer = mini_calloc(sizeof(char), 1);
    int readBytes = mini_fread(buffer, sizeof(char), 1, file);
    if (1){
        return *buffer;
    }
    else{
        return -1;
    }
}

int mini_fputc(MYFILE* file,char c){
    #ifdef DEBUG
    write(1, "Started file write \n", 21);
    #endif
    if (file->ind_write != -1){
        #ifdef DEBUG
        write(1, "Flushing buffer \n", 18);
        #endif
        mini_fflush(file);
    }
    int writtenbytes = write(file->fd, &c, 1);
    return writtenbytes;
}