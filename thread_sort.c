#include<stdio.h>
#include<pthread.h>
int arr[20],n,part=0;
void merge(int arr[],int l,int m,int r)
{
    int i,j,k,n1,n2,a[r-l+1];
    n1 = m-l+1;
    n2 = r-m;
    int L[n1],R[n2];
    for(i=0;i<n1;i++)
    {
        L[i] = arr[l+i];
    }
    for(j=0;j<n2;j++)
    {
        R[j] = arr[m+j+1];
    }
    i=0;
    j=0;
    k=0;
    while(i<n1 && j<n2)
    {
        if(L[i]<=R[j])
        {
            a[k]=L[i];
            i++;
        }
        else
        {
            a[k]=R[j];
            j++;
        }
        k++;
    }
    while(i<n1)
    {
        a[k]=L[i];
        k++;
        i++;
    }
    while(j<n2)
    {
        a[k]=R[j];
        k++;
        j++;
    }
    for(i=0;i<k;i++)
    {
        arr[l++]=a[i];
    }
}
void mergesort(int arr[],int l,int r)
{
    int m;
    if(l<r)
    {
        m = l + (r-l)/2;
        mergesort(arr,l,m);
        mergesort(arr,m+1,r);
        merge(arr,l,m,r);
    }
}
void* merge_sort(void* arg)
{
    int tpart = part++;
    int l,r;
    if(part==1)
    {
        l=0;
        r=n/2-1;
    }    
    else
    {
        l=n/2;
        r=n-1;
    }
    mergesort(arr,l,r);
}
void* merge_(void* arg)
{
    merge(arr,0,n/2-1,n-1);
}
int main()
{
    printf("Array size: ");
    scanf("%d",&n);
    printf("Array: ");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&arr[i]);
    }

    pthread_t threads[3];
    for(int i=0;i<2;i++)
    {
        pthread_create(&threads[i],NULL,merge_sort,(void*) NULL);
    }
     pthread_create(&threads[2],NULL,merge_,(void*) NULL);

    for(int i=0;i<3;i++)
    {
        pthread_join(threads[i],NULL);
    } 
    printf("Sorted Array: ");
    for(int i=0;i<n;i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
}