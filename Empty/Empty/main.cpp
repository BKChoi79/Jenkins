#include <windows.h>
#include <excpt.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <memory>
#include "MinidumpHelp.h"
#include <DbgHelp.h>

/** 메모리 누수 체크용 */
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <vector>  
#include <algorithm>
#include <functional>
#include <map>
#include <vector>
#include <set>

#include <time.h>

#include "Child.h"
#include "Common.h"
#include "cJSON/cJSON.h"
#include "Card.h"

using namespace std;

typedef std::vector<Child*> CHILD_VECTOR;
typedef std::map <int, CHILD_VECTOR> CHILD_MAP;

#define CC_STATIC

#if defined(CC_STATIC)
#define CC_DLL
#else
#if defined(_USRDLL)
#define CC_DLL     __declspec(dllexport)
#else         /* use a DLL library */
#define CC_DLL     __declspec(dllexport)
#endif
#endif

// 특정 문자를 교체하는 함수
void ReplaceString(std::string & strCallId, const char * pszBefore, const char * pszAfter)
{
	size_t iPos = strCallId.find(pszBefore);
	size_t iBeforeLen = strlen(pszBefore);

	while (iPos < std::string::npos)
	{
		strCallId.replace(iPos, iBeforeLen, pszAfter);
		iPos = strCallId.find(pszBefore, iPos);
	}
}

void ChangeNumber(string& str)
{
	ReplaceString(str, "%2d", "00");
	ReplaceString(str, "%d", "0" );
	ReplaceString(str, "%s", "0");

	char* p = (char*)str.data();
	int length = str.length();
	for (int i = 0; i < length; i++)
	{
		char c = p[i];
		if (c >= '0' && c <= '9' )
		{
			p[i] = '0';
		}
	}
}

bool CheckString(string code, string multiscene)
{
	int pos = string::npos;
	int lengthCode = code.length();
	int lengthMultiScene = multiscene.length();

	string codeComma = "\"" + code + "\"";
	string multisceneComma = "\"" + multiscene + "\"";

	// 길이가 없는 코드가 검색됨으로 사이즈 체크를 합니다.
	if (lengthCode == 0)
		return false;

	// 길이차이가 너무 심한 경우는 처리하지 않도록 합시다.
	// 예) "rb" "popArrivetourblock" => rb가 포함되었다고 처리가 된다.
	pos = codeComma.find(multisceneComma);

	// 코드에서 못찾은경우. _ 가 포함된 멀티씬이라면.
	if (pos == string::npos &&
		multiscene.find("_") != string::npos)
	{
		if (lengthMultiScene / 2 <= lengthCode)
		{
			pos = multiscene.find(code);
		
			if (pos == string::npos)
			{
				ChangeNumber(multiscene);
				ChangeNumber(code);

				pos = multiscene.find(code);
			}
		}
	}

	// Found!!
	if (pos != string::npos)
	{
		return true;
	}
	else
	{

	}

	return false;
}

void Check()
{
	int n = 0;
	std::string stringTest[] = {
		"buff1_1_2",
		"netmarble_apple_01"
	};

	std::string stringOri = "_apple_%2d";

	for (auto s : stringTest)
	{
		// s 를 유추되는 포맷으로 가공해보자.

		// 핵심은 숫자!!!
		if (CheckString(stringOri, s))
		{
			printf("found\n");
		}
	}

	int a = 1;
	printf("%03d\n", a);
	printf("end");
}

void UseSmartPointer()
{
	//Child* pObj = new Child();
	std::shared_ptr<Child> pObj(new Child());
	//std::shared_ptr<Child> pLarge(new Child());
	
	//pObj->setCallBack(pObj, callfunc_selector(Child::OnCallBack));
	//pObj->setCallBack(pObj, (SEL_CallFunc)&Child::OnCallBack);
	//std::function f = bind(&Child::OnCallBack2, pObj, placeholders::_1, placeholders::_2);
	
	/*
	function< void(float, char*) > callback = [](float f, char* p)
	{
		printf( "%s", "ca" )
	};
	                                                                                                                          
	pObj->setCallBack(callback);;
	*/

	pObj->setCallback(bind(&Child::OnCallBack2, pObj, placeholders::_1, placeholders::_2));

	pObj->GetInline();

	printf("UseSmartPointer done %d\n", pObj.use_count());
}

void UseSmartPointerCjson()
{
	cJSON* pJson1 = cJSON_Parse("[]");
	cJSON* pJson2 = cJSON_Parse("[]");
	//std::shared_ptr<cJSON> pJson(cJSON_Parse("[]"));
	// 스택에서 나갈시 자동 파괴

	auto f1 = [](cJSON* pJson )
	{
		if (nullptr != pJson)
		{
			cJSON_Delete(pJson);
		}
	};

	auto f2 = [](cJSON* pJson)
	{
		if (nullptr != pJson)
		{
			cJSON_Delete(pJson);
		}
	};

	std::shared_ptr<cJSON> closer1(pJson1, f1 );
	std::shared_ptr<cJSON> closer2(pJson2, f1 );

	/*
	std::shared_ptr<cJSON> a(pJson, [](cJSON* pData)
	{
		if (nullptr != pData)
		{
			cJSON_Delete(pData);
		}
	});
	*/

	//cJSON* Value = cJSON_GetObjectItem(pJson, "purchaseDataOrigin");


	int num = 1;
	
	auto f = [](int n1)  -> int {
		return n1 + 2;
	};

	num = f(num);

	return;

	printf("UseSmartPointerCjson done %d\n");
}


void fooo()
{
	vector<int> a;
}

void inparam(const char* p)
{
	//p[0] = 'a'; // const 변수에 할당 할 수 없습니다.
	printf("%s", p);
}

void foo()
{
	//Check();
	//UseSmartPointer();
	//UseSmartPointerCjson();

	auto fnAttack = []()
	{
		printf("1\n");
	};

	auto fnMove = []()
	{
		printf("2\n");
	};

	auto fnAvoid = []()
	{
		printf("3\n");
	};

	auto fnDeffence = []()
	{
		printf("4\n");
	};

	FUNCTION_VECTOR functions;
	functions.push_back(fnAttack);
	functions.push_back(fnMove);
	functions.push_back(fnAvoid);
	functions.push_back(fnDeffence);
	functions.push_back([](){ printf("oh my god~!!\n"); });
	for (auto fn : functions)
	{
		fn();
	}

	NUM_VECTOR n;
	n.push_back(1);
	n.emplace_back(2);
	n.push_back(4);

	for (auto& num : n)
	{
		num = 0;
	}

	for (auto num : n)
	{
		printf("%d\n", num);
	}


	printf("----------------------------------\n");
	int index = 2;
	auto fn = functions.at(index);
	fn();


	int num1 = 100;
	int num2 = 100;
	auto fnA = [&num1, num2](){
		num1 = 1;
		//num2 = 2;
	};

	auto fnB = [&]() mutable {
		num1 = 1;
		num2 = 2;
	};

	auto fnC = [num1, num2]()
	{
		int a = num1;
		int b = num2;
	};

	//fnA();
	fnB();

	char* pBuff = new char[200];

	printf("%d\n", num1);
	printf("%d\n", num2);

	printf("end");
}

template <class T>
void Delete(T* item)
{
	delete item;
	item = nullptr;
}


class DeleteItem
{
public:
	template<typename T>
	void operator()(T* ptr) const
	{
		delete ptr;
		ptr = nullptr;
	}
};

void foo2()
{
	const int MAX_TIMES = 4;
	int* pArry[MAX_TIMES] = { nullptr, };
	vector<int*> list;

	// 데이터가 들어 찼다.
	for (int i = 0; i < MAX_TIMES; i++)
	{
		pArry[i] = new int;
		*pArry[i] = 100;
		list.push_back(pArry[i]);
	}
	
	// 맵에 로드된 벡터 리스트에서 추출해 넣었다.
	/*
	std::map<int, vector<int*>> mapNum;
	for (auto obj : list )
	{
		mapNum[100].push_back(obj);
	}
	


	// 사용자 A가 벡터 0번째 오브젝트를 삭제한다.
	delete pArry[0];
	list.erase(list.begin());

	// 사용자 B가 동일한 오브젝트가 포함된 맵의 오브젝트들을 참조한다.
	for (auto obj : mapNum[100])
	{
		int* p = obj;
		printf(">>> %d\n", *p);
	}
	*/

	//for_each(list.begin(), list.end(), DeleteItem());

	for (auto item : list)
	{
		if (nullptr != item)
		{
			delete item;
			item = nullptr;
		}
	}

	//m_itemList.clear();

	int a1, a2, b1, b2 = 0;
	a1 = 1;
	a2 = 2;
	b1 = 2;
	b2 = 1;
	if (a1 == b1 && a2 == b2 || a1 == b2 && a2 == b1)
	{
		printf("event!!! A\n");
	}

	if ((a1 == b1 && a2 == b2) || (a1 == b2 && a2 == b1))
	{
		printf("event!!! B\n");
	}

	if ((a1 == b1 && a2 == b2 || a1 == b2 && a2 == b1))
	{
		printf("event!!! C\n");
	}

	if (nullptr == 0)
	{
		printf("nullptr == 0\n");
	}

	if (NULL == 0)
	{
		printf("NULL == 0\n");
	}

	list.clear();
}

struct OWNED_SKILL_INFO
{
	__int64 ownedSkillUID;
	int SkillUID;
	int enchantNum;
	int subType;
	int subValue;

	__int64 ExpireDate;	//#PERIOD_ITEM  만료일시
	int	RemainCount;	//#PERIOD_ITEM 잔여횟수
};

void foo3()
{
	struct {
		string layerName;
		int title;
	}TITLETABLE[] = {
		{ "title_01", 1 },
		{ "title_02", 2 },
		{ "title_03", 3 },
		{ "title_04", 4 }
	};

	for (int i = 0; i < 10; i++)
	{
		const int a = i;
		printf("a = %d\n", a);
	}

	float f = 0 / 2;
	float f2 = 1.0f;
	f2 = 0.0f;
	f = 2 / f2;
	int myints[] = { 10, 20, 30, 40, 50 };
	std::set<int> myset(myints, myints + 5);        // range

	printf("\n\n\n");

	for (auto n : myset)
	{
		int num = n;
		printf("%d\n", num);
	}

	int a = -1;
	if (0 > a)
	{
		printf("0>a\n");
	}
	if (-1 >= a)
	{
		printf("-1>=a\n");
	}

	OWNED_SKILL_INFO data;
	memset(&data, 0, sizeof(OWNED_SKILL_INFO));

	printf("end");

}


/****************************************************************************
FUNCTION       : SortItem
DESCRIPTION    : 등급이 높은 순으로 동일 하다면 디스플레이오더가 낮은 순으로
PARAMETERS     : NONE
RETURN VALUE   : NONE
SIDE EFFECTS   : NONE
****************************************************************************/
bool SortItem(const DisplayInfo* a, const DisplayInfo* b)
{
	int valueA = a->getGrade() * 100000 - a->getDisplayOrder();
	int valueB = b->getGrade() * 100000 - b->getDisplayOrder();
	if (valueA > valueB)
	{
		return true;
	}

	return false;
}

void foo4()
{
	DisplayItemList m_itemList;

	for (int i = 0; i < 10; i++)
	{
		DisplayInfo info;

		info.setGrade(rand()%6);
		info.setDisplayOrder(rand()%100);
		
		DisplayInfo* pInfo = DisplayInfo::create(info);
		if (nullptr != pInfo)
		{
			m_itemList.push_back(pInfo);
		}
	}

	printf(" :: before\n");
	for ( auto item : m_itemList )
	{
		printf("dorder : %d, grade : %d\n", item->getDisplayOrder(), item->getGrade());
	}

	stable_sort(m_itemList.begin(), m_itemList.end(), SortItem );

	printf(" :: after\n");
	for (auto item : m_itemList)
	{
		printf("dorder : %d, grade : %d\n", item->getDisplayOrder(), item->getGrade());
	}

}

void foo5()
{
	vector<__int64> listHave;
	listHave.push_back(100);
	listHave.push_back(101);
	listHave.push_back(102);
	listHave.push_back(103);
	listHave.push_back(104);
	listHave.push_back(105);

	vector<__int64> listSelected;
	listSelected.push_back(103);
	listSelected.push_back(102);

	vector<__int64>::reverse_iterator rit;
	vector<__int64>::iterator it;
	//listHave.erase(listHave.begin(), listHave.end(), fun(listSelected) );
	for (rit = listHave.rbegin(); rit != listHave.rend(); ++rit)
	{
		__int64 ownedSkillUID = (*rit);
		printf("%lld\n", ownedSkillUID);
	}

	printf("\n");
	printf("end. \n");

	for (auto selectedOwnedSkillUID : listSelected)
	{
		for (rit = listHave.rbegin(); rit != listHave.rend(); ++rit)
		{
			//it = rit.base();
			__int64 ownedSkillUID = (*rit);
			if (selectedOwnedSkillUID == ownedSkillUID)
			{
				listHave.erase(rit.base());
				listHave.insert(listHave.begin(), ownedSkillUID);
				break;
			}
		}
	}

	printf("end");
}

int a = 100;
void foo6( int** p )
{
	*p = &a;
}


void make_minidump(EXCEPTION_POINTERS* e)
{
	auto hDbgHelp = LoadLibraryA("dbghelp");
	if (hDbgHelp == nullptr)
		return;
	auto pMiniDumpWriteDump = (decltype(&MiniDumpWriteDump))GetProcAddress(hDbgHelp, "MiniDumpWriteDump");
	if (pMiniDumpWriteDump == nullptr)
		return;

	char name[MAX_PATH];
	{
		auto nameEnd = name + GetModuleFileNameA(GetModuleHandleA(0), name, MAX_PATH);
		SYSTEMTIME t;
		GetSystemTime(&t);
		wsprintfA(nameEnd - strlen(".exe"),
			"_%4d%02d%02d_%02d%02d%02d.dmp",
			t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond);
	}

	auto hFile = CreateFileA(name, GENERIC_WRITE, FILE_SHARE_READ, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	if (hFile == INVALID_HANDLE_VALUE)
		return;

	MINIDUMP_EXCEPTION_INFORMATION exceptionInfo;
	exceptionInfo.ThreadId = GetCurrentThreadId();
	exceptionInfo.ExceptionPointers = e;
	exceptionInfo.ClientPointers = FALSE;

	auto dumped = pMiniDumpWriteDump(
		GetCurrentProcess(),
		GetCurrentProcessId(),
		hFile,
		MINIDUMP_TYPE(MiniDumpWithIndirectlyReferencedMemory | MiniDumpScanMemory),
		e ? &exceptionInfo : nullptr,
		nullptr,
		nullptr);

	CloseHandle(hFile);

	return;
}

LONG WINAPI UnhandledExcepFilter(PEXCEPTION_POINTERS pExcepPointers)
{
	SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)pExcepPointers->ContextRecord->Eax);
	pExcepPointers->ContextRecord->Eip += 2;

	/// dump file 남기자.
	make_minidump(pExcepPointers);


	return EXCEPTION_CONTINUE_EXECUTION;
}

void foo_dobuldPoint()
{
	foo5();

	int* p = nullptr;
	//int** pNum = &p;

	foo6(&p);
	printf("입력 : %d\n", (int)*p);

	int* p1 = nullptr;

	int* pEmptyAddress = nullptr;
	*pEmptyAddress = 1;
}
void CC_DLL foo_time()
{
	int timeZone = 9999999999999999999;
	__int64 serverTime = 0;
	__int64 timeDiffTime = 0;

	timeDiffTime = difftime((time_t)serverTime, time(0));

	time_t nowTime = timeDiffTime + time(0); // 서버 시간을 가져 온다
	nowTime += timeZone * 60 * 60;

	tm* pTime = nullptr;
	pTime = gmtime(&nowTime); // 현재 시간을 여러 정보로 나눈다.	
	 


	printf("%d-%d-%d\n", 1900 + pTime->tm_year, 1 + pTime->tm_mon, pTime->tm_mday);

}

void foo_CardTest()
{
	Card* pCard = Card::create();

	if (nullptr != pCard)
	{
		int seq_no = pCard->getInfo()->seq_no;

		delete pCard;
	}

	printf("test is done.");
}

void main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	SetUnhandledExceptionFilter(UnhandledExcepFilter);


	foo_CardTest();


	_CrtDumpMemoryLeaks();
	printf("끝!!!.\n");
	system("pause");
}


