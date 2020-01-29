#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<time.h>
#include<inttypes.h>

#define r 3
#define n 4
#define c 3
int a[r][n],b[n][c],ans[r][c];

struct val
    {
        int i,j;
    };

void* mult(void  *arg)
{
    struct val *data =arg;
    
    int k=0,sum=0;
    for(k=0;k<n;k++)
    {
        sum=sum+a[data->i][k] * b[k][data->j];
    }
    ans[data->i][data->j]=sum;
    pthread_exit(0);
}

int main()
{
    
    int i,j;
    srand(time(0));
    for(i=0;i<r;i++)
        for(j=0;j<n;j++)
            a[i][j]=(rand()%5);
    for(i=0;i<n;i++)
        for(j=0;j<c;j++)
            b[i][j]=(rand()%5);

    printf("Arrays are:\n");
    for(i=0;i<r;i++)
        {
            for(j=0;j<n;j++)
                printf("%d ",a[i][j]);
            printf("\n");    
        }
    printf("\n");
    for(i=0;i<n;i++)
        {
            for(j=0;j<c;j++)
                printf("%d ",b[i][j]);
            printf("\n");    
        }    
    printf("\n");
    int x=r*c;
    int y=0;
    pthread_t tid[x];
    for(i=0;i<r;i++)
    {
        for(j=0;j<c;j++)
        {
            struct val *mat=(struct val*) malloc(sizeof(struct val));
            
                mat->i=i;
                mat->j=j;
                
                pthread_create(&tid[y],NULL,mult,(void *)mat );
                y++;
                
                
        }
        
    }
    for(i=0;i<x;i++)
    	pthread_join(tid[i],NULL);
    printf("Product: \n");
    for(i=0;i<r;i++)
        {
            for(j=0;j<c;j++)
                printf("%d ",ans[i][j]);
                    
            printf("\n");    
        }  
    return 0;         
}
