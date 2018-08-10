/****************************************************************************
Copyright (c) 2010-2011 bkchoi79

bkchoi79@gmail.com

클래스를 설명합니다.
****************************************************************************/

#ifndef __Object_h__
#define __Object_h__

#include <functional>

class Object;

using namespace std;

/** 함수 포인터 매크로 */
#define callfunc_selector(_SELECTOR) (SEL_CallFunc)(&_SELECTOR)

/** 함수 포인터 정의 */
typedef void (Object::*SEL_CallFunc)();

class Object
{
public:
	Object();
	~Object();

	void setCallBack(Object* pTarget, SEL_CallFunc func );
	void setCallback(function< void(float, char*) > callback);
protected:

	/** 함수 포인터 멤버 변수
	- protected로 처리되어 하위 클래스에서 사용한다.
	- 멤버를 직접 핸들링 할 일은 없을 것.

	@since v0.0
	*/
	Object*			m_pTarget;
	SEL_CallFunc	m_pfnCallBack;
	/** stl을 활용한 함수 포인터 */
	function< void(float, char*) > m_callback;

	void foo();
};






#endif