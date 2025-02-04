#include "QuenchThirst.h"
#include "Farmer.h"

QuenchThirst* QuenchThirst::Instance()
{
	static QuenchThirst instance;
	return &instance;
}

void QuenchThirst::Enter(Farmer* pFarmer)
{
	//if location is not already well:
    if (pFarmer->GetLocation() != &well)
    {
        std::cout << pFarmer->GetName() << ": Walking to the well" << std::endl;
        pFarmer->ChangeLocation(&well);
    }
}

void QuenchThirst::Execute(Farmer* pFarmer)
{
	std::cout << pFarmer->GetName() << " is drinking." << std::endl;
	pFarmer->Drink();
}


std::string QuenchThirst::GetEvent(Farmer* pFarmer)
{
	std::string event = "Stay";
	if (pFarmer->Hungry())
	{
		std::cout << pFarmer->GetName() << ": 'I am hungry, I need to eat'" << std::endl;
		event = "Hungry";
	}
	else if (pFarmer->Tired())
	{
		std::cout << pFarmer->GetName() << ": 'I am tired, I need to sleep'" << std::endl;
		event = "Tired";
	}
	//if cart is full go and sell
	else if (pFarmer->CartIsFull())
	{
		std::cout << pFarmer->GetName() << ": 'My horse cart is full, better get to the market and sell some goods!'" << std::endl;
		event = "CartFull";
	}
	//if farmer thiunks there are still resources in the barn:
	else if (pFarmer->BarnHasResource())
	{
		std::cout << pFarmer->GetName() << ": 'Cold water makes me wanna work! I am going back to the barn!'" << std::endl;
		event = "UnThirstyBarnAvavible";
	}
	//if farmer thiunks there are still resources in the field:
	else if (pFarmer->FieldHasResource())
	{
		std::cout << pFarmer->GetName() << ": 'Cold water makes me wanna work! I am going back to the field!'" << std::endl;
		event = "UnThirstyFieldAvavible";
	}
	//No resources left in barn or field, sell whats in the cart:
	else if (pFarmer->GetGoodsInCart() > 0)
	{
		std::cout << pFarmer->GetName() << ": 'Noting more to do in the field or barn, but I'll sell the goods in my cart!'" << std::endl;
		event = "UnthirstyGoodsToSell";
	}
	//if there so no more work to be done:
	else
	{
		//if farmer has accpected an invitation to the pub:
		if (pFarmer->InvitationAccepted() == true)
		{
			std::cout << pFarmer->GetName() << ": 'No more work to be done today! Time for fun!'" << std::endl;
			event = "TimeForFun";
		}
		//if farmer has not accpected any invitation to the pub:
		else
		{
			std::cout << pFarmer->GetName() << ": 'There is nothing more to do today! I think I can take it easy now.'" << std::endl;
			event = "TimeToRest";
		}
	}
	return event;
}

void QuenchThirst::Exit(Farmer* pFarmer, std::string nextState)
{
    std::cout << pFarmer->GetName() << " is leaving the well." << std::endl;
}