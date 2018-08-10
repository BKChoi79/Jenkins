#include "Card.h"

/**
*
*/
CardBase::CardBase()
{
	memset(&info, 0, sizeof(_INFO));

	info.seq_no = 100;

	printf("CardBase is called.\n");
}

CardBase::~CardBase()
{
	printf("~CardBase is called.\n");
};

/**
*
*/
Card::Card()
{
	printf("Card is called.\n");
}

Card::~Card()
{
	printf("~Card is called.\n");
}

Card* Card::create()
{
	Card* pRet = new Card();
	if (nullptr != pRet && true == pRet->init())
	{
		return pRet;
	}

	delete pRet;
	return nullptr;
}

bool Card::init()
{
	info.seq_no = 200;

	return true;
}