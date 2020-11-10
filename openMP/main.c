# include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int main(void){
    struct queue *q= Allocate();

    int src,msg;
    printf(" Src? Msg?\n");
    scanf("%d%d",&src,&msg);
    enqueue(q,src,msg);
    Print(q);
    dequeue(q,&src,&msg);
    Print(q);

    

    return 0;
}
