#ifndef __Child_h__
#define __Child_h__

#include "Object.h"
#include <functional>
using namespace std;

class Child : public Object
{
public:
	int m_a;

	Child();
	Child(int a){ m_a = a; };
	~Child();

	void OnCallBack2(float fPercent, char* pBuff);
	void OnCallBack();

	inline char* GetInline()
	{
		return "i'm inline function.\n";
	}

	void printA()
	{
		printf("a = %d\n", m_a );
	}

	void Call(int n);

private:

};


#endif