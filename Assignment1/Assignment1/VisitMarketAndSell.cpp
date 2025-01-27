#include "VisitMarketAndSell.h"
#include "Farmer.h"
#include <iostream>
#include "AtThePubWithFriends.h"
#include "AtTheFieldsHarvesting.h"
#include "EnterBarnAndMilkTheCows.h"
#include "GoHomeAndSleepTilRested.h"

VisitMarketAndSell* VisitMarketAndSell::Instance()
{
	static VisitMarketAndSell instance;
	return &instance;
}

void VisitMarketAndSell::Enter(Farmer* pFarmer)
{
	if (pFarmer->GetLocation() != &market)
	{
		StartTaskTimer(0.5f);
		std::cout << pFarmer->GetName() << " takes the horse cart to the market" << std::endl;
		pFarmer->ChangeLocation(&market);
	}
}

void VisitMarketAndSell::Execute(Farmer* pFarmer)
{
	if (pFarmer->GetGoodsInCart() > 0)
	{
		int earnedCoins = 2 * pFarmer->GetGoodsInCart();
		StartTaskTimer(0.5f);
		pFarmer->EmptyCart();
		std::cout << pFarmer->GetName() << " is selling goods." << std::endl;
		pFarmer->EarnGoldCoins(earnedCoins);
		std::cout << pFarmer->GetName() << " has earned " << earnedCoins << " coins of gold." << std::endl;
	}
	StartTaskTimer(0.5f);
	std::cout << pFarmer->GetName() << " has no more goods to sell." << std::endl;

	if (pFarmer->BarnHasResource())
	{
		StartTaskTimer(0.5f);
		std::cout << pFarmer->GetName() << ": 'Better get home and work some more!'" << std::endl;
		pFarmer->ChangeState(EnterBarnAndMilkTheCows::Instance());
	}
	else if (pFarmer->FieldHasResource())
	{
		StartTaskTimer(0.5f);
		std::cout << pFarmer->GetName() << ": 'Better get home and work some more!'" << std::endl;
		std::cout << pFarmer->GetName() << ": 'Since the cows were out of milk earlier, I'll do some harvesting!'" << std::endl;
		pFarmer->ChangeState(AtTheFieldsHarvesting::Instance());
	}
	else
	{
		if (pFarmer->GetEnergy() < 6) 
		{
			StartTaskTimer(0.5f);
			std::cout << pFarmer->GetName() << ": 'Done for the day! I am to tierd to visit the pub tonight.'" << std::endl;
			pFarmer->ChangeState(GoHomeAndSleepTilRested::Instance());
		}
		else
		{
			StartTaskTimer(0.5f);
			std::cout << pFarmer->GetName() << ": 'Finially! Some money and time to spend on having fun!'" << std::endl;
			pFarmer->ChangeState(AtThePubWithFriends::Instance());
		}
	}
}

void VisitMarketAndSell::Exit(Farmer* pFarmer)
{
	StartTaskTimer(0.5f);
	std::cout << pFarmer->GetName() << " is Leaving the market" << std::endl;
}

float VisitMarketAndSell::GetTaskDuration() const
{
	return 2.0f;
}