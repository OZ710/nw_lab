#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>
#include<signal.h>
#include<time.h>
#include<unistd.h>

#define PNUM 5
#define thinking 1
#define hungry 2
#define eating 3
#define left (pno +4)%PNUM
#define right (pno +1)%PNUM
sem_t mutex,S[PNUM];
int phil[PNUM] = {0,1,2,3,4},state[PNUM]={0,0,0,0,0};
void test(int pno)
{
    if(state[pno]==hungry && state[left]!=eating && state[right]!=eating)
    {
        state[pno]=eating;
        
        printf("Philosopher %d takes forks %d and %d\n",pno+1,left+1,pno+1);
        printf("Philosopher %d is eating\n",pno+1);
        sleep(2);
        sem_post(&S[pno]);
    }

}
void take_fork(int pno)
{
    sem_wait(&mutex);
    state[pno]=hungry;
    printf("Philosopher %d is hungry\n",pno+1);
    test(pno);
    sem_post(&mutex);

    sem_wait(&S[pno]);
    sleep(1);
}
void put_fork(int pno)
{
    sem_wait(&mutex);
    state[pno]=thinking;
    printf("Philosopher %d puts down forks %d and %d\n",pno+1,left+1,pno+1);
    printf("Philosopher %d is thinking\n",pno+1);
    test(left);
    test(right);
    sem_post(&mutex);
}
void *philosopher(void *arg)
{
    while(1)
    {
        int *p = arg;
        sleep(1);
        take_fork(*p);
        sleep(1);
        put_fork(*p);
    }
}

int main()
{
    int i;
    pthread_t tid[PNUM];
    sem_init(&mutex,0,1);
    for(int i=0;i<PNUM;i++)
        sem_init(&S[i],0,0);
    for(int i=0;i<PNUM;i++)
    {
        pthread_create(&tid[i],NULL,philosopher,&phil[i]);
        printf("Philosopher %d is thinking\n",i+1);
    }
    for(i=0;i<PNUM;i++)
        pthread_join(tid[i],NULL);
    return 0;
}