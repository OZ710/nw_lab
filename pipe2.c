
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<string.h>
#include<time.h>

int main()
{
	srand(time(0));
	int p1[2],p2[2],p3[2],p4[2],m,n,a,b,sum1,sum2,sum;
	a=rand()%10;
	b=rand()%10;
	m=rand()%10;
	n=rand()%10;
	
	pid_t c1,c2;
	if(pipe(p1)==-1)
	{
		printf("pipe failed\n");
		exit(0);
	}
	if(pipe(p2)==-1)
	{
		printf("pipe failed\n");
		exit(0);
	}
	if(pipe(p3)==-1)
	{
		printf("pipe failed\n");
		exit(0);
	}
	if(pipe(p4)==-1)
	{
		printf("pipe failed\n");
		exit(0);
	}
	c1 = fork();
	if(c1<0)
	{
		printf("fork failed\n");
		exit(0);
	}
	else if(c1>0)
	{
		close(p1[0]);
		write(p1[1],&m,sizeof(m));
		write(p1[1],&n,sizeof(n));
		printf("Parent has sent %d and %d to child1\n",m,n);
		//wait(NULL);
		close(p2[1]);
		read(p2[0],&sum1,sizeof(sum1));
		printf("The output from child1 is the sum of %d and %d :%d\n",m,n,sum1);
		c2=fork();
		if(c2<0)
		{
			printf("fork failed\n");
			exit(0);
		}
		else if(c2>0)
		{
			int x;
			close(p3[0]);
			write(p3[1],&a,sizeof(a));
			write(p3[1],&b,sizeof(b));
			printf("Parent has sent %d and %d to child2\n",a,b);
			//wait(NULL);
			
			close(p4[1]);
			read(p4[0],&sum2,sizeof(sum2));
			printf("The output from child2 is the sum of %d and %d :%d\n",a,b,sum2);
		}
		
		else
		{
			
			close(p3[1]);
			read(p3[0],&a,sizeof(a));
			read(p3[0],&b,sizeof(b));
			sum2=a+b;
			close(p4[0]);
			write(p4[1],&sum2,sizeof(sum2));
			close(p4[1]);
			read(p2[0],&sum1,sizeof(sum1));
			
			sum=sum1+sum2;
			printf("The final sum of %d and %d is: %d\n",sum1,sum2,sum);
		    exit(0);
		    
		}	
	}
	else
	{
		close(p1[1]);
		read(p1[0],&m,sizeof(m));
		read(p1[0],&n,sizeof(n));
		sum1=m+n;
		close(p2[0]);
		write(p2[1],&sum1,sizeof(sum1));
		close(p2[1]);
        exit(0);
	}
}


