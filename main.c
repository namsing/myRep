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
     FILE *fd,*fd2;
    char buff1[SIZE],buff2[SIZE],ch;
    fd = fopen("/usr/share/dict/american-english","r");
    fd2 = fopen("p2.txt","w+");
    if(fd == NULL||fd2 == NULL)
    {
        perror("error opening file");
        exit(EXIT_FAILURE);
    }

    fseek(fd,-1L,2);
        long count = ftell(fd);
         
         int i =0;

    while(count!=0)
    {
            ch = fgetc(fd);
            fputc(ch,fd2);
             fseek(fd,-2L,1);
            count--;
            
    }
    rewind(fd2);

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

        sleep(1);
        
        
            while(!feof(fd))
        {

        fscanf(fd,"%s",wrd1);
        printf("child1 word: %s\n",wrd1);
        if(!strcmp(wrd1,buff1))
            {
                printf("child1: FOUND");
                break;
            }

        }
          
             exit(EXIT_SUCCESS);
             //_exit()
        
    }else{
        close(pfd[0]);
        write(pfd[1],"zoos",4);
        close(pfd[1]);

    id2 = fork();
    if(id2 == 0)
    {
        close(pfd2[1]);
        read(pfd2[0],buff2,SIZE);
        printf("child 2 msg recieved : %s\n",buff2);
        close(pfd2[0]);


        char ch,wrdrev[SIZE];

        

     while(!feof(fd2))
        {

        fscanf(fd2,"%s",wrd2);
         int len = strlen(wrd2);
            printf("word2 len = %d\n",len);
            for(i = len-1;i>=0;i--)
        {
            wrdrev[len-i-1] =wrd2[i];
        }
            wrdrev[len] = '\0';
            printf("child2 word: %s\n",wrdrev);
        if(!strcmp(wrdrev,buff2))
            {
                printf("child2: FOUND");
                break;
            }

        }
            exit(EXIT_SUCCESS);
            //_exit()

    }else{


        printf("parent process: \n");
        close(pfd2[0]);
        write(pfd2[1],"zoos",4);
        close(pfd2[1]);

        

    }

    }
    fclose(fd);
return 0;
}