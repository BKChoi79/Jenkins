#include "Child.h"
#include <stdio.h>

Child::Child()
{

}

Child::~Child()
{
	printf("소멸자 호출!\n");
}

void Child::OnCallBack()
{
	printf("call back is called.\n");
}

void Child::OnCallBack2(float fPercent, char* pBuff)
{
	printf("call back is called. 2\n");
}

void Child::Call(int n)
{
	printf("Call 호출!\n");

}