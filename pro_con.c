#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>
#include<signal.h>
#include<time.h>
#include<unistd.h>

#define max 6
#define r_size 3
#define c_size 3
sem_t empty,full,mutex;
int buffer[r_size][c_size],in[r_size]={0,0,0},out[r_size]={0,0,0},count[r_size]={0,0,0},val;

void *producer(void *arg)
{
    srand(time(0));
    int id = *((int *) arg);
    int nextProduced;
    while(1)
    {
    	 nextProduced=rand()%3;
    	 val=nextProduced;
    	if(count[nextProduced]==3)
    		printf("Buffer of item %d is full, producer waiting\n",nextProduced);
        sem_wait(&empty);
        sem_wait(&mutex);
        int k=in[nextProduced];
        if(buffer[nextProduced][k]!=-1)
        {
            while(buffer[nextProduced][k]==-1)
            	k=(k+1)%3;
        }
        sleep(1);
        buffer[nextProduced][k] = nextProduced;
        printf("producer %d has produced item %d in slot %d\n",id,nextProduced,in[nextProduced]);
        in[nextProduced]=(in[nextProduced]+1)%c_size;
        count[nextProduced]++;
        sem_post(&mutex);
        sem_post(&full);
        
        sleep(2);
    }
    pthread_exit(0);
}

void *consumer(void *arg)
{
    srand(time(0));
    int id = *((int *) arg);
    int nextConsumed=val;
    while(1)
    {
    	if(count[nextConsumed]==0)
    		printf("Buffer is empty, consumer waiting\n");
        sem_wait(&full);
        sem_wait(&mutex);
        int k=out[nextConsumed];
        nextConsumed=buffer[nextConsumed][k];
        if(nextConsumed==-1)
        {
            while(nextConsumed==-1)
            	nextConsumed=(nextConsumed+1)%3;
            
        }
        sleep(3);
        printf("consumer %d has consumed item %d in slot %d\n",id,nextConsumed,out[nextConsumed]);
        buffer[nextConsumed][k]=-1;
        out[nextConsumed]=(out[nextConsumed]+1)%c_size;
        count[nextConsumed]--;
        sem_post(&mutex);
        sem_post(&empty);
       
        sleep(3);
    }
    pthread_exit(0);
}
int main()
{
    int id[max],i,j;
    pthread_t tid[max];
    sem_init(&empty,0,3);
    sem_init(&full,0,0);
    sem_init(&mutex,0,1);
    
        id[0]=0;
        id[1]=0;
        id[2]=1;
        id[3]=1;
        id[4]=2;
        id[5]=2;
    for(i=0;i<r_size;i++)
    {
    	for(j=0;j<c_size;j++)
        	buffer[i][j]=-1;
    }

    pthread_create(&tid[0],NULL,producer,(void *) &id[0]);
    printf("Producer %d created\n",id[0]);
    pthread_create(&tid[1],NULL,consumer,(void *) &id[1]);
    printf("Consumer %d created\n",id[1]);
    pthread_create(&tid[2],NULL,producer,(void *) &id[2]);
    printf("Producer %d created\n",id[2]);
    pthread_create(&tid[3],NULL,consumer,(void *) &id[3]);
    printf("Consumer %d created\n",id[3]);
     pthread_create(&tid[0],NULL,producer,(void *) &id[4]);
    printf("Producer %d created\n",id[4]);
    pthread_create(&tid[1],NULL,consumer,(void *) &id[5]);
    printf("Consumer %d created\n",id[5]);

    for(i=0;i<max;i++)
        pthread_join(tid[i],NULL);

       return 0;

}
