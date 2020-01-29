#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>
#include<signal.h>
#include<time.h>
#include<unistd.h>

#define max 4
#define b_size 5
sem_t empty,full,mutex;
int buffer[b_size],end=10,beg=0,in=0,out=0;

void *producer(void *arg)
{
    srand(time(0));
    int id = *((int *) arg);
    int nextProduced=rand()%10;
    while(beg<end)
    {
        sem_wait(&empty);
        sem_wait(&mutex);
        if(buffer[in]!=-1)
        {
            printf("synchronization error\n");
            exit(1);
        }
        sleep(2);
        nextProduced=rand()%10;
        buffer[in] = nextProduced;
        printf("producer %d has produced %d in slot %d\n",id,nextProduced,in);
        in=(in+1)%b_size;
        sem_post(&mutex);
        sem_post(&full);
        beg++;
        sleep(2);
    }
    pthread_exit(0);
}

void *consumer(void *arg)
{
    srand(time(0));
    int id = *((int *) arg);
    int nextConsumed;
    while(beg<end)
    {
        sem_wait(&full);
        sem_wait(&mutex);
        nextConsumed=buffer[out];
        if(nextConsumed==-1)
        {
            printf("synchronization error\n");
            exit(1);
        }
        sleep(2);
        printf("consumer %d has consumed %d in slot %d\n",id,nextConsumed,out);
        buffer[out]=-1;
        out=(out+1)%b_size;
        sem_post(&mutex);
        sem_post(&empty);
        beg++;
        sleep(2);
    }
    pthread_exit(0);
}
int main()
{
    int id[max],i;
    pthread_t tid[max];
    sem_init(&empty,0,10);
    sem_init(&full,0,0);
    sem_init(&mutex,0,1);
    
        id[0]=0;
        id[1]=0;
        id[2]=1;
        id[3]=1;
    for(i=0;i<b_size;i++)
    {
        buffer[i]=-1;
    }

    pthread_create(&tid[0],NULL,producer,(void *) &id[0]);
    printf("Producer %d created\n",id[0]);
    pthread_create(&tid[1],NULL,consumer,(void *) &id[1]);
    printf("Consumer %d created\n",id[1]);
    pthread_create(&tid[2],NULL,producer,(void *) &id[2]);
    printf("Producer %d created\n",id[2]);
    pthread_create(&tid[3],NULL,consumer,(void *) &id[3]);
    printf("Consumer %d created\n",id[3]);

    for(i=0;i<max;i++)
        pthread_join(tid[i],NULL);

       return 0;

}
