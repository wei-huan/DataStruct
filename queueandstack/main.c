#include<stdio.h>
#include<stdlib.h>

#include "cyclequeue.h"

int main()
{
    double ccr=0,temp1=0,temp2=0,temp3=0,temp4=0;
	int result=0;
    int i=2;
	//0.3927i
	temp1=1/2*0.3927*0.3927*(i*i-(i+1)*(i+1));
	temp2=1/24*0.3927*0.3927*0.3927*0.3927*(i*i*i*i-(i+1)*(i+1)*(i+1)*(i+1));
	temp3=1/720*0.3927*0.3927*0.3927*0.3927*0.3927*0.3927*(i*i*i*i*i*i-(i+1)*(i+1)*(i+1)*(i+1)*(i+1)*(i+1));
	temp4=1/40320*0.3927*0.3927*0.3927*0.3927*0.3927*0.3927*0.3927*0.3927*(i*i*i*i*i*i*i*i-(i+1)*(i+1)*(i+1)*(i+1)*(i+1)*(i+1)*(i+1)*(i+1));
	ccr=temp2-temp1+temp4-temp3;
	
	result=2548.46*ccr;

    printf("result=%d\n",result);
    return 0;
}