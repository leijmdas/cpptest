#include "stdafx.h"
#include "itestdiameter.h"


REGAPI(1,test1);
REGAPI(2,test2);
REGAPI(3,test3);

void test1(int appid)
{
	int a=1;
printf ("test1\n");
}
void test2(int appid) 
{
	printf ("test2\n");
}
void test3(int appid)
{
	
	int b1=1;
	printf("Hello test3 !\n");
	int b11=1;
	//	REGAPI(3,test3);
}

//itestdiameter itest(3,test3);
