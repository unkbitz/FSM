#include "VisitMarketAndSell.h"
#include "Farmer.h"

VisitMarketAndSell* VisitMarketAndSell::Instance()
{
	static VisitMarketAndSell instance;
	return &instance;
}

void VisitMarketAndSell::Enter(Farmer* pFarmer)
{
	//if location is not already market
	if (pFarmer->GetLocation() != &market)
	{
		std::cout << pFarmer->GetName() << " takes the horse cart to the market" << std::endl;
		pFarmer->ChangeLocation(&market);
	}
}

void VisitMarketAndSell::Execute(Farmer* pFarmer)
{
	//if farmer has any goods to sell:
	if (pFarmer->GetGoodsInCart() > 0)
		{
			//increase farmes gold and empy cart
			int earnedCoins = 0.5 * pFarmer->GetGoodsInCart();
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
	//If farmer has nothing more to sell
	else if (pFarmer->GetGoodsInCart() < 1)
	{
		//if farmer think there are still resouces in the barn:
		if (pFarmer->BarnHasResource())
		{
			std::cout << pFarmer->GetName() << ": 'Time to get back to work! I think some cows still needs to be milked.'" << std::endl;
			event = "SoldAll->Milk";
		}
		//if farmer think there are still resouces in the field:
		else if (pFarmer->FieldHasResource())
		{

			std::cout << pFarmer->GetName() << ": 'Time to get back to work! I think there are crops left in the field'" << std::endl;
			event = "SoldAll->Crops";
		}
		else
		{
			//if farmer has accpected an invitation to the pub:
			if (pFarmer->InvitationAccepted() == true)
			{
				std::cout << pFarmer->GetName() << ": 'The work is all done for the day! Time for fun!'" << std::endl;
				event = "TimeForFun";
			}
			//if farmer has not accpected any invitation to the pub:
			else
			{
				std::cout << pFarmer->GetName() << ": 'Finally I am done for the day!! I think I can take it easy now.'" << std::endl;
				event = "TimeToRest";
			}
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