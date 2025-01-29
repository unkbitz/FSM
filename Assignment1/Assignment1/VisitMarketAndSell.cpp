#include "VisitMarketAndSell.h"
#include "StateFactory.h"
#include "Farmer.h"
#include <iostream>

VisitMarketAndSell* VisitMarketAndSell::Instance()
{
	static VisitMarketAndSell instance;
	return &instance;
}

void VisitMarketAndSell::Enter(Farmer* pFarmer)
{
	if (pFarmer->GetLocation() != &market)
	{
		std::cout << pFarmer->GetName() << " takes the horse cart to the market" << std::endl;
		pFarmer->ChangeLocation(&market);
	}
}

void VisitMarketAndSell::Execute(Farmer* pFarmer)
{
	if (pFarmer->GetGoodsInCart() > 0)
		{
			int earnedCoins = 2 * pFarmer->GetGoodsInCart();
			pFarmer->EmptyCart();
			pFarmer->EarnGoldCoins(earnedCoins);
			std::cout << pFarmer->GetName() << " has earned " << earnedCoins << " coins of gold from selling goods." << std::endl;
		}
	else
	{
		std::cout << pFarmer->GetName() << ": 'Oh, I've got nothing to sell'" << std::endl;
	}
}

std::string VisitMarketAndSell::GetEvent(Farmer* pFarmer)
{
	std::string event = "Stay";
	if (pFarmer->Thirsty())
	{
		std::cout << pFarmer->GetName() << ": 'I am thirsty, I need to go home and drink'" << std::endl;
		event = "Thirsty";
	}
	else if (pFarmer->Hungry())
	{
		std::cout << pFarmer->GetName() << ": 'I am hungry, I need to go home and eat'" << std::endl;
		event = "Hungry";
	}
	else if (pFarmer->Tired())
	{
		std::cout << pFarmer->GetName() << ": 'I am tired, I need to go home and sleep'" << std::endl;
		event = "Tired";
	}
	if (pFarmer->GetGoodsInCart() < 1)
	{
		if (pFarmer->BarnHasResource())
		{
			std::cout << pFarmer->GetName() << ": 'Time to get back to work! I think some cows still needs to be milked.'" << std::endl;
			event = "SoldAll->Milk";
		}
		else if (pFarmer->FieldHasResource())
		{

			std::cout << pFarmer->GetName() << ": 'Time to get back to work! I think there are crops left in the field'" << std::endl;
			event = "SoldAll->Crops";
		}
		else
		{
			std::cout << pFarmer->GetName() << ": 'Finally I am done for the day!'" << std::endl;
			event = "SoldAll";
		}
	}
	return event;
}

void VisitMarketAndSell::Exit(Farmer* pFarmer, std::string nextState)
{
	if (nextState != "VisitTheMarketAndBuy")
	{
		std::cout << pFarmer->GetName() << " is Leaving the market" << std::endl;
	}

}

int VisitMarketAndSell::GetTaskDuration() const
{
	return 20;
}