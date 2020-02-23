#include "fcntl.h"
#include "sys/stat.h"
#include "mqueue.h"
#include <stdio.h>
#include <stdlib.h>
int main()
{
    mqd_t q2;
    char *out1,*out2,*out3;
    struct mq_attr *attr;
    int prio;
    attr = malloc(sizeof(struct mq_attr));
    q2=mq_open("/rw_q",O_RDWR);
    if(q2==-1)
        printf("Error");
    out1 = malloc(10 * sizeof(char));
    out2 = malloc(10 * sizeof(char));
    out3 = malloc(10 * sizeof(char));
    mq_getattr(q2,attr);
    mq_receive(q2,out1,attr->mq_msgsize,&prio);
    printf("%s ",out1);
    mq_receive(q2,out2,attr->mq_msgsize,&prio);
    printf("%s ",out2);
    mq_receive(q2,out3,attr->mq_msgsize,&prio);
    printf("%s\n",out3);

}