#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include<stdlib.h>


#define SIZE 64
int main()
{
    pid_t id1,id2;
    char wrd1[SIZE],wrd2[SIZE];
    FILE *fd;
    char buff1[SIZE],buff2[SIZE];
    fd = fopen("/usr/share/dict/american-english","r");
    if(fd == NULL)
    {
        perror("error opening file");
        exit(EXIT_FAILURE);
    }

    int pfd[2],pfd2[2];
    pipe(pfd);
    pipe(pfd2);
    id1 = fork();

    if(id1 == 0)
    {
        close(pfd[1]);
        read(pfd[0],buff1,SIZE);
        printf(" child 1 msg recieved : %s\n",buff1);
        close(pfd[0]);   
        int i =0;
        char ch;

        while((ch = fgetc(fd)) != EOF)
        {
            //fscanf(fd, " %s",wrd1);
            if(ch == ' '|| ch == '\n')
            {
                i = 0;
            }
          wrd1[i] = ch;
          i++;
            printf("%s\n",wrd1);
            if(!strcmp(wrd1,buff1))
            {
                printf("child1: FOUND");
                break;
            }
            exit(EXIT_SUCCESS);
        }

        
    }else{
        close(pfd[0]);
        write(pfd[1],"hello",6);
        close(pfd[1]);

    id2 = fork();
    if(id2 == 0)
    {
        close(pfd2[1]);
        read(pfd2[0],buff2,SIZE);
        printf("child 2 msg recieved : %s\n",buff2);
        close(pfd2[0]);

        char ch,wrd2[SIZE],wrdrev[SIZE];

 fseek(fd,-1L,SEEK_END);
         int i =0;

    while(ftell(fd)!=0)
    {
        i = 0;
        while((ch = fgetc(fd)!= ' ')||(ch = getc(fd)!= '\n'))
        {
            wrd2[i] = ch;
            i++;
            fseek(fd,-1L,SEEK_END);
        }
        int len = strlen(wrd2);
        for(i = len-1;i>=0;i--)
{
wrdrev[len-i-1] =wrd2[i];
}
wrdrev[len] = '\0';
        if(!strcmp(wrdrev,buff2))
        {
             printf("child2: FOUND");
                break;
            }
            exit(EXIT_SUCCESS);
    }


    }else if(id2 !=0){


        printf("parent process: \n");
        close(pfd2[0]);
        write(pfd2[1],"hello",6);
        close(pfd2[1]);

        

    }

    }
    fclose(fd);
return 0;
}