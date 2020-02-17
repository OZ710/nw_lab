#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>
#include<signal.h>
#include<time.h>
#include<unistd.h>

#define max 6
int rc=0;
sem_t mutex,wrt;

void *reader(void *arg)
{
    srand(time(0));
    int id = *((int *) arg);
    FILE *f;
    while(1)
    {
        
        int t=(rand()%3)+1;
        sem_wait(&mutex);
        rc++;
        if(rc==1)
            sem_wait(&wrt);
        sem_post(&mutex);

        f = fopen("Object.txt","r");
        sleep(1);
        char str[100];
        if( fgets (str, 60, f)!=NULL ) {
            printf("Reader %d reads %s from the file\n",id,str);
        }
        fclose(f);
        
        sem_wait(&mutex);
        rc--;
        if(rc==0)
            sem_post(&wrt);
        sem_post(&mutex);    
        sleep(t);
        
    }
    pthread_exit(0);
}

void *writer(void *arg)
{
     srand(time(0));
    int id = *((int *) arg);
    FILE *f;
    while(1)
    {
       
        int t=(rand()%3)+2;
        sem_wait(&wrt);
        f = fopen("Object.txt","w");
         sleep(1);
        int n=rand()%10;
        fprintf(f,"%d",n);
        printf("Writer %d writes %d to the file\n",id,n);
        fclose(f);
        sem_post(&wrt);
        sleep(t);
    }
    pthread_exit(0);
}
int main()
{
    srand(time(0));
    int id[max],i;
    FILE *f;
    pthread_t tid[max];
    sem_init(&wrt,0,1);
    sem_init(&mutex,0,1);
    
        id[0]=0;
        id[1]=0;
        id[2]=1;
        id[3]=1;
        id[4]=2;
        id[5]=2;
    f = fopen("Object.txt","w");
    int n=rand();
    fprintf(f,"%d",n);
    fclose(f);
    pthread_create(&tid[0],NULL,writer,(void *) &id[0]);
    printf("Writer %d created\n",id[0]);
    pthread_create(&tid[1],NULL,reader,(void *) &id[1]);
    printf("Reader %d created\n",id[1]);
    pthread_create(&tid[2],NULL,writer,(void *) &id[2]);
    printf("Writer %d created\n",id[2]);
    pthread_create(&tid[3],NULL,reader,(void *) &id[3]);
    printf("Reader %d created\n",id[3]);
    pthread_create(&tid[4],NULL,writer,(void *) &id[4]);
    printf("Writer %d created\n",id[4]);
    pthread_create(&tid[5],NULL,reader,(void *) &id[5]);
    printf("Reader %d created\n",id[5]);
    for(i=0;i<max;i++)
        pthread_join(tid[i],NULL);

       return 0;

}
