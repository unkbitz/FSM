#include "VisitMarketAndBuy.h"
#include "Farmer.h"

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
	//retrieve amount of resources in the cottage
	pFarmer->ChangeLocation(&cottage);
	int currentFoodAmount = pFarmer->GetLocation()->GetResources();
	//std::cout << "CurrentFoodAmount = " << currentFoodAmount << std::endl;
	int maxAmount = pFarmer->GetLocation()->GetFoodMax();
	// amount is the amount of food that should be bought
	int amount = maxAmount - currentFoodAmount;

	//"one food" costs one gold coin
	//therefore the farmer can go ahead a shop if farmers amount of gold >= amount
	if (pFarmer->GetGoldCoins() >= amount)
	{
		//replennish resources in cottage
		pFarmer->GetLocation()->ReplennishReshources(maxAmount);
		int moneySpent = amount; 
		//reset m_hasResources to true
		pFarmer->GetLocation()->SetHasResources();
		//Update currentFoodAmount
		currentFoodAmount = pFarmer->GetLocation()->GetResources();
		std::cout << pFarmer->GetName() << " spent " << moneySpent << " gold coins on food." << std::endl;

		std::cout << "CurrentFoodAmount = " << currentFoodAmount << std::endl;
		//decrease farmers gold
		pFarmer->SpendGoldCoins(moneySpent);
	}
	//If farmer can't afford to buy all needed food but can buy some food:
	else if (pFarmer->GetGoldCoins() > 5)
	{
		int amount = 6;
		pFarmer->GetLocation()->ReplennishReshources(amount);
		int moneySpent = 6;
		pFarmer->GetLocation()->IncreaseResources(6);
		pFarmer->GetLocation()->SetHasResources();
		currentFoodAmount = pFarmer->GetLocation()->GetResources();
		std::cout << pFarmer->GetName() << " spent " << moneySpent << " gold coins on food." << std::endl;

		std::cout << "CurrentFoodAmount = " << currentFoodAmount << std::endl;
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
	int currentFoodAmount = pFarmer->GetLocation()->GetResources();
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
	else if (currentFoodAmount > 5 && pFarmer->Hungry())
	{
		std::cout << pFarmer->GetName() << ": 'I am hungry, I need to go home and eat'" << std::endl;
		event = "Hungry";
	}
	//If food still needs to be bought, but farmer can't afford it
	else if (currentFoodAmount < 20 && pFarmer->GetGoldCoins() < 6)
	{
		//check if farmer has any goods to sell
		if (pFarmer->GetGoodsInCart() > 0)
		{
			std::cout << pFarmer->GetName() << ": 'I do have some goods to sell in my cart!'" << std::endl;
			event = "CartFull";
		}
		//else check if farmer thinks there are any resources in the barn
		else if (pFarmer->BarnHasResource())
		{
			std::cout << pFarmer->GetName() << ": 'Time to get back to work!'" << std::endl;
			event = "DoneShoping->Milk";
		}
		//else check if farmer thinks there are any resources in the field
		else if (pFarmer->FieldHasResource())
		{
			std::cout << pFarmer->GetName() << ": 'Time to get back to work!'" << std::endl;
			event = "DoneShoping->Crops";
		}
		//if there is no way for tha farmer to earn money he/she might as well go to the pub/rest
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
	//if there is enough food in the cottage
	else if (currentFoodAmount > 19)
	{
		// sell goods in cart if farmer has any
		if (pFarmer->GetGoodsInCart() > 0)
		{
			std::cout << pFarmer->GetName() << ": 'I'll sell what I have in my cart since I am at the market now!'" << std::endl;
			event = "CartFull";
		}
		//else go work in barn if farmer thinks there is milk left
		else if (pFarmer->BarnHasResource())
		{
			std::cout << pFarmer->GetName() << ": 'Time to get back to work!'" << std::endl;
			event = "DoneShoping->Milk";
		}
		//else go work in field if farmer thinks there is crops left
		else if (pFarmer->FieldHasResource())
		{
			std::cout << pFarmer->GetName() << ": 'Time to get back to work!'" << std::endl;
			event = "DoneShoping->Crops";
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