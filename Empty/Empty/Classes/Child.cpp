#include "Child.h"
#include <stdio.h>

Child::Child()
{

}

Child::~Child()
{
	printf("�Ҹ��� ȣ��!\n");
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
	printf("Call ȣ��!\n");

}