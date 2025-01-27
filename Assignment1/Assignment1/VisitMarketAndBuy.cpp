#include "VisitMarketAndBuy.h"
#include "GoHomeAndEat.h"
#include "Farmer.h"
#include <iostream>

VisitMarketAndBuy* VisitMarketAndBuy::Instance()
{
	static VisitMarketAndBuy instance;
	return &instance;
}

void VisitMarketAndBuy::Enter(Farmer* pFarmer)
{
	if (pFarmer->GetLocation() != &market)
	{
		StartTaskTimer(0.5f);
		std::cout << pFarmer->GetName() << " rides to the market" << std::endl;
		pFarmer->ChangeLocation(&market);
	}
}

void VisitMarketAndBuy::Execute(Farmer* pFarmer)
{
	StartTaskTimer(1.0f);
	std::cout << pFarmer->GetName() << " is buying more food at the market" << std::endl;
	int moneySpent = 20;
	pFarmer->SpendGoldCoins(moneySpent);
	StartTaskTimer(1.0f);
	std::cout << pFarmer->GetName() << " spent " << moneySpent << " gold coins." << std::endl;
	pFarmer->RevertToPreviousState();
}

void VisitMarketAndBuy::Exit(Farmer* pFarmer)
{
	StartTaskTimer(0.5f);
	std::cout << pFarmer->GetName() << " is Leaving the market" << std::endl;
}

float VisitMarketAndBuy::GetTaskDuration() const
{
	return 2.0f;
}