
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<string.h>

int main()
{
	int p1[2],p2[2];
	char sen[100];
	printf("Enter the sentence\n");
	fgets(sen,100,stdin);
    printf("%s\n",sen);
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
	int ccount=0,wcount=1,lcount=0,i=0;
	p = fork();
	if(p<0)
	{
		printf("fork failed\n");
		exit(0);
	}
	else if(p>0)
	{
		close(p1[0]);
		write(p1[1],sen,strlen(sen));
		close(p1[1]);
		wait(NULL);
		close(p2[1]);
		read(p2[0],&ccount,sizeof(ccount));
		read(p2[0],&wcount,sizeof(wcount));
		read(p2[0],&lcount,sizeof(lcount));
		printf("The character count is %d\n",ccount);
		printf("The word count is %d\n",wcount);
		printf("The line count is %d\n",lcount);
		close(p2[0]);
	}

	else
	{
		char out[100];
		close(p1[1]);
		read(p1[0],out,100);
		
		while(i<strlen(out))
		{
			if(out[i]!=' ')
				ccount++;
			if(out[i]==' ')
				wcount++;
			if(out[i]=='.')
				lcount++;
			i++;
		}
		FILE *f;
		f=fopen("sentences.txt","w");
		fprintf(f, "%d\n%d\n%d\n",ccount,wcount,lcount );
		fclose(f);
		close(p2[0]);
		write(p2[1],&ccount,sizeof(ccount));
		write(p2[1],&wcount,sizeof(wcount));
		write(p2[1],&lcount,sizeof(lcount));
		close(p2[1]);
        exit(0);
	}
}


