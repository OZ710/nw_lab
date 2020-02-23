
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<string.h>

int main()
{
	int p1[2],p2[2];
	char s[]="hala";
	pid_t p;
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
	p = fork();
	if(p<0)
	{
		printf("fork failed\n");
		exit(0);
	}
	else if(p>0)
	{
		close(p1[0]);
		write(p1[1],s,strlen(s)+1);
		close(p1[1]);
		wait(NULL);
		close(p2[1]);
		char op[100];
		read(p2[0],op,100);
		close(p2[0]);
		printf("%s\n",op);
	}

	else
	{
		char out[100];
		
		int i=0;
		close(p1[1]);
		read(p1[0],out,100);
		char t[]="madrid";
		int l = strlen(t);
		int m = strlen(out);
		int j=m,p=(m+l)-1;
		char in[p];
		while(i<m)
		{
			in[i]=out[i];
			i++;
		}
		i=0;
		while(i<l)
		{
			in[j]=t[i];
			i++;
			j++;
		}
		in[j]='\0';
		close(p2[0]);
		write(p2[1],in,strlen(in)+1);
		close(p2[1]);
        exit(0);
	}
}


