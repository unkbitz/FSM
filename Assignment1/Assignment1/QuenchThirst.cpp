#include "QuenchThirst.h"
#include "Farmer.h"

QuenchThirst* QuenchThirst::Instance()
{
	static QuenchThirst instance;
	return &instance;
}

void QuenchThirst::Enter(Farmer* pFarmer)
{
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
	if (pFarmer->GetThirst() < 5)
	{
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
		else if (pFarmer->CartIsFull())
		{
			std::cout << pFarmer->GetName() << ": 'My horse cart is full, better get to the market and sell some goods!'" << std::endl;
			event = "CartFull";
		}
		else if (pFarmer->BarnHasResource())
		{
			std::cout << pFarmer->GetName() << ": 'Cold water makes me wanna work! I am going back to the barn!'" << std::endl;
			event = "UnThirstyBarnAvavible";
		}
		else if (pFarmer->FieldHasResource())
		{
			std::cout << pFarmer->GetName() << ": 'Cold water makes me wanna work! I am going back to the field!'" << std::endl;
			event = "UnThirstyFieldAvavible";
		}
		else if (pFarmer->GetGoodsInCart() > 0)
		{
			std::cout << pFarmer->GetName() << ": 'Noting more to do in the field or barn, but I'll sell the goods in my cart!'" << std::endl;
			event = "UnthirstyGoodsToSel";
		}
		else
		{
			if (pFarmer->InvitationAccepted() == true)
			{
				std::cout << pFarmer->GetName() << ": 'No more work to be done today! Time for fun!'" << std::endl;
				event = "TimeForFun";
			}
			else
			{
				std::cout << pFarmer->GetName() << ": 'There is nothing more to do today! I think I can take it easy now.'" << std::endl;
				event = "TimeToRest";
			}
		}
	}
	return event;
}

void QuenchThirst::Exit(Farmer* pFarmer, std::string nextState)
{
    std::cout << pFarmer->GetName() << " is leaving the well." << std::endl;
}