#include "VisitMarketAndBuy.h"
#include "Farmer.h"
#include "StateFactory.h"
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
		std::cout << pFarmer->GetName() << " takes the horse cart to the market" << std::endl;
		pFarmer->ChangeLocation(&market);
	}
}



void VisitMarketAndBuy::Execute(Farmer* pFarmer)
{
	pFarmer->ChangeLocation(&cottage);
	int currentFoodAmount = pFarmer->GetLocation()->GetResources();
	//std::cout << "CurrentFoodAmount = " << currentFoodAmount << std::endl;

	if (pFarmer->GetGoldCoins() > 9)
	{
		int maxAmount = pFarmer->GetLocation()->GetMilkMax();
		int amount = maxAmount - currentFoodAmount;
		pFarmer->GetLocation()->ReplennishReshources(maxAmount);
		int moneySpent = amount/2;
		pFarmer->GetLocation()->SetHasResources();
		currentFoodAmount = pFarmer->GetLocation()->GetResources();
		std::cout << pFarmer->GetName() << " spent " << moneySpent << " gold coins on food." << std::endl;

		//std::cout << "CurrentFoodAmount = " << currentFoodAmount << std::endl;
		pFarmer->SpendGoldCoins(moneySpent);
	}

	else if (pFarmer->GetGoldCoins() > 2)
	{
		
		int amount = pFarmer->GetLocation()->GetMilkMax();
		pFarmer->GetLocation()->ReplennishReshources(amount);
		int moneySpent = 3;
		pFarmer->GetLocation()->IncreaseResources(6);
		pFarmer->GetLocation()->SetHasResources();
		currentFoodAmount = pFarmer->GetLocation()->GetResources();
		std::cout << pFarmer->GetName() << " spent " << moneySpent << " gold coins on food." << std::endl;

		//std::cout << "CurrentFoodAmount = " << currentFoodAmount << std::endl;
		pFarmer->SpendGoldCoins(moneySpent);
	}
	else
	{
		std::cout << pFarmer->GetName() << " 'Oh, I can't afford it.. Better earn some more first.'" << std::endl;
	}
	pFarmer->ChangeLocation(&market);
}

std::string VisitMarketAndBuy::GetEvent(Farmer* pFarmer)
{
	std::string event = "Stay";
	pFarmer->ChangeLocation(&cottage);
	if (pFarmer->Thirsty())
	{
		std::cout << pFarmer->GetName() << ": 'I am thirsty, I need to go home and drink'" << std::endl;
		event = "Thirsty";
	}
	else if (pFarmer->Tired())
	{
		std::cout << pFarmer->GetName() << ": 'I am tired, I need to go home and sleep'" << std::endl;
		event = "Tired";
	}
	else if (pFarmer->GetLocation()->GetResources() > 20 || pFarmer->GetGoldCoins() < 3)
	{
		if (pFarmer->Hungry())
		{
			if (pFarmer->GetLocation()->GetResources() > 2)
			{
				std::cout << pFarmer->GetName() << ": 'I am hungry, I need to go home and eat'" << std::endl;
				event = "Hungry";
			}
		}
		if (pFarmer->GetGoodsInCart() > 0)
		{
			std::cout << pFarmer->GetName() << ": 'I do have some goods to sell in my cart!'" << std::endl;
			event = "CartFull";
		}
		else if (pFarmer->BarnHasResource())
		{
			std::cout << pFarmer->GetName() << ": 'Time to get back to work!'" << std::endl;
			event = "DoneShoping->Milk";
		}
		else if (pFarmer->FieldHasResource())
		{
			std::cout << pFarmer->GetName() << ": 'Time to get back to work!'" << std::endl;
			event = "DoneShoping->Crops";
		}
		else
		{
			std::cout << pFarmer->GetName() << ": 'The work is all done for the day! Time for fun!'" << std::endl;
			event = "DoneShoping->Pub";
		}
	}
	pFarmer->ChangeLocation(&market);
	return event;
}

void VisitMarketAndBuy::Exit(Farmer* pFarmer, std::string nextState)
{
	if (nextState != "VisitTheMarketAndSell")
	{
		std::cout << pFarmer->GetName() << " is Leaving the market" << std::endl;
	}
}

int VisitMarketAndBuy::GetTaskDuration() const
{
	return 15;
}