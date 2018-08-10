/****************************************************************************
Copyright (c) 2010-2011 bkchoi79

bkchoi79@gmail.com

공용 디파인
****************************************************************************/
#ifndef __Common_h__
#define __Common_h__

//#define _DEBUG

#if 1
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW 
#endif


typedef vector<function< void() >> FUNCTION_VECTOR;
typedef vector<int> NUM_VECTOR;
typedef vector<string> STR_VECOTR;


class DisplayInfo
{
public:
	enum ITEM_TYPE
	{
		ITEM_DEFAULT = 0,
		ITEM_CARD,
		ITEM_LUCKY,
		ITEM_JEWEL,
	};

	DisplayInfo()
	{
		m_displayOrder = 0;
		m_grade = 0;
	};

	~DisplayInfo(){};

	static DisplayInfo* create(const DisplayInfo &info)
	{
		DisplayInfo* pInfo = new DisplayInfo();
		if (pInfo)
		{
			pInfo->setDisplayOrder(info.getDisplayOrder());
			pInfo->setGrade(info.getGrade());
			return pInfo;
		}

		return nullptr;
	};

private:

	int m_displayOrder;
	int m_grade;
	
public:
	void setDisplayOrder(int displayOrder){ m_displayOrder = displayOrder; };
	int getDisplayOrder() const { return m_displayOrder; };

	void setGrade(int grade){ m_grade = grade; };
	int getGrade() const { return m_grade; };

};
typedef vector<DisplayInfo*> DisplayItemList;


#endif