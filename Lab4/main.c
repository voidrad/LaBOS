#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <sys/wait.h>


#define FILE1 "f1.txt"
#define FILE2 "f2.txt"

void change_spaces(char* src, int size)
{
    char* res = malloc(size*sizeof(char));
    int j = 0;
    bool flag = true;
    for(int i = 0; i < size ; ++i) {
    if((src[i] == ' ') && (j == 0)){
        j = 1;
    }else{
        if((src[i] == ' ') && (j == 1)){
            src[i] = '\0';
            j = 0;
        }
    }
    
    if((src[i] != ' ') && (j == 1)){
        j = 0;
    }

    }
}

int main()
{


    int fd_0;
    int fd_1;
    char* src;
    struct stat statbuf;

    if((fd_0 = open( FILE1, O_RDWR)) < 0)
    {
        printf("OPEN ERROR\n");
        exit(-1);
    }

    if((fd_1 = open(FILE2 , O_CREAT | O_RDWR, S_IRUSR | S_IWUSR)) < 0)
    {
        printf("OPEN ERROR\n");
        exit(-1);
    }

    if(fstat(fd_0, &statbuf) < 0)
    {
        printf("FSTAT ERROR\n");
        exit(-1);
    }

    if(ftruncate(fd_1, statbuf.st_size) < 0)
    {
        printf("FTRUNCATE ERROR\n");
        exit(-1);
    }

    char buff[statbuf.st_size];
    if(read(fd_0, buff, statbuf.st_size) != statbuf.st_size)
    {
        printf("READ ERROR\n");
        exit(-1);
    }
    if(write(fd_1, buff, statbuf.st_size) != statbuf.st_size)
    {
        printf("READ ERROR\n");
        exit(-1);
    }


    int pid_0 = 0;
    int pid_1 = 0;

 
    if((pid_0 = fork()) > 0) 
    { //Parent
        if((pid_1 = fork()) > 0)
        { //Parent

            sleep(2);

            src = (char*)mmap(0, statbuf.st_size, PROT_READ, MAP_SHARED, fd_1, 0);
            if(src == MAP_FAILED)
            {
                printf("MMAP ERROR\n");
                exit(-1);
            }
            for(int i = 0; i < statbuf.st_size; ++i) { printf("%c", src[i]); }
            printf("\n");
            if(munmap(src, statbuf.st_size) != 0)
            {
                printf("MUNMAP ERROR\n");
                exit(-1);
            }
            sleep(2);
       
        }
        else if(pid_1 == 0)
        { //Child2

            sleep(1);
            src = (char*)mmap(0, statbuf.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd_1, 0);
            if(src == MAP_FAILED)
            {
                printf("MMAP ERROR\n");
                exit(-1);
            }
            change_spaces(src, statbuf.st_size);
            if(munmap(src, statbuf.st_size) != 0)
            {
                printf("MUNMAP ERROR\n");
                exit(-1);
            }
            sleep(1);
 
        }
        else
        {
            printf("FORK ERROR 1\n");
            exit(-1);
        }
    }
    else if (pid_0 == 0)
    { //Clind1

        sleep(1);
        src = (char*)mmap(0, statbuf.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd_1, 0);
        if(src == MAP_FAILED)
        {
            printf("MMAP ERROR\n");
            exit(-1);
        }
        for(int i = 0; i < statbuf.st_size; ++i) { src[i] = toupper(src[i]); }
        if(munmap(src, statbuf.st_size) != 0)
        {
            printf("MUNMAP ERROR\n");
            exit(-1);
        }
        sleep(1);

    }
    else
    {
        printf("FORK ERROR 2\n");
        exit(-1);
    }


    close(fd_0);
    close(fd_1);
    return 0;
}