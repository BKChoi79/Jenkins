#include "Object.h"

Object::Object()
{
	m_pTarget = nullptr;
	m_pfnCallBack = nullptr;
}

Object::~Object()
{

}

void Object::setCallBack(Object* pTarget, SEL_CallFunc func)
{
	m_pTarget = pTarget;
	m_pfnCallBack = func;

	foo();
}

void Object::setCallback(function< void(float, char*) > callback)
{
	m_callback = callback;

	foo();
}


void Object::foo()
{
	if (nullptr != m_pTarget && nullptr != m_pfnCallBack)
	{
		(m_pTarget->*m_pfnCallBack)();
	}

	if (m_callback != nullptr)
	{
		m_callback(0.1f, "hi~~");
	}
}


