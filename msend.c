#include "fcntl.h"
#include "sys/stat.h"
#include "mqueue.h"
#include <stdio.h>
#include <string.h>
int main()
{
    mqd_t q1;
    char *a="sending",*b="the",*c="message";
    q1=mq_open("/rw_q",O_CREAT|O_RDWR,0666,NULL);
    if(q1==-1)
        printf("Error");
    mq_send(q1,a,strlen(a),3);
    mq_send(q1,b,strlen(b),1);
    mq_send(q1,c,strlen(c),2);
}