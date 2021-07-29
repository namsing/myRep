#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

sem_t s;
int count = 2;

void * uart_init(void *data)
{
while(1)
{
if(count>0)
{
    int randint = rand()%6;
    sem_wait(&s);
    count--;
    printf("uart in use by t%d\n",*(int *)data);
    sleep(randint);
    printf("uart returned by t%d\n",*(int *)data);
    count++;
    printf("uarts left : %d\n",count);
    
    sem_post(&s);

}

}
}


void * res_count(void *data)
{
while(1)
{
if(count == 0)
{
    printf("no uarts available \n");
    sem_wait(&s);
}
}

}
int main()
{

sem_init(&s,0,3);

pthread_t tr1,tr2,tr3,tr4;
int t1 = 1,t2 = 2,t3 = 3;

printf("uarts left : %d\n",count);

pthread_create(&tr1,NULL,uart_init,&t1);
pthread_create(&tr2,NULL,uart_init,&t2);
pthread_create(&tr3,NULL,uart_init,&t3);
pthread_create(&tr4,NULL,res_count,NULL);

pthread_join(tr1,NULL);
pthread_join(tr2,NULL);
pthread_join(tr3,NULL);
pthread_join(tr4,NULL);

sem_destroy(&s);

return 0;
}