#ifndef __Card_h__
#define __Card_h__

#include <functional>
using namespace std;

/**
* 정보 관련 변수 모음.
*/
typedef struct _INFO
{
	typedef enum _HANDS
	{
		NONE = 0,
		PLAYER_1,
		PLAYER_2
	} HANDS;

	int seq_no;
	HANDS hands;
} INFO;

/**
* 
*/
class CardBase
{
protected:
	INFO info;

public:
	CardBase();
	virtual ~CardBase();
};

/**
*
*/
class Card : public CardBase
{
public:
	Card();
	virtual ~Card();

	static Card* create();
	bool init();

	const INFO* getInfo()
	{
		return &info;
	}

private:

};

#endif