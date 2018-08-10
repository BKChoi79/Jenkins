/****************************************************************************
Copyright (c) 2010-2011 bkchoi79

bkchoi79@gmail.com

Ŭ������ �����մϴ�.
****************************************************************************/

#ifndef __Object_h__
#define __Object_h__

#include <functional>

class Object;

using namespace std;

/** �Լ� ������ ��ũ�� */
#define callfunc_selector(_SELECTOR) (SEL_CallFunc)(&_SELECTOR)

/** �Լ� ������ ���� */
typedef void (Object::*SEL_CallFunc)();

class Object
{
public:
	Object();
	~Object();

	void setCallBack(Object* pTarget, SEL_CallFunc func );
	void setCallback(function< void(float, char*) > callback);
protected:

	/** �Լ� ������ ��� ����
	- protected�� ó���Ǿ� ���� Ŭ�������� ����Ѵ�.
	- ����� ���� �ڵ鸵 �� ���� ���� ��.

	@since v0.0
	*/
	Object*			m_pTarget;
	SEL_CallFunc	m_pfnCallBack;
	/** stl�� Ȱ���� �Լ� ������ */
	function< void(float, char*) > m_callback;

	void foo();
};






#endif