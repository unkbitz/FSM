#include "GoHomeAndEat.h"
#include "Farmer.h"

GoHomeAndEat* GoHomeAndEat::Instance()
{
    static GoHomeAndEat instance;
    return &instance;
}

void GoHomeAndEat::Enter(Farmer* pFarmer)
{
    if (pFarmer->GetLocation() != &cottage)
    {
        std::cout << pFarmer->GetName() << ": Walking to the cottage" << std::endl;
        pFarmer->ChangeLocation(&cottage);
    }
}

void GoHomeAndEat::Execute(Farmer* pFarmer)
{
	std::cout << "Resources in "<< pFarmer->GetLocation()->GetName() <<": " << pFarmer->GetLocation()->GetResources() << std::endl;
	if (pFarmer->GetLocation()->HasResources())
	{
		std::cout << pFarmer->GetName() << " is eating." << std::endl;
		pFarmer->Eat(8);
		pFarmer->GetLocation()->DecreaseResources();
		pFarmer->GetLocation()->SetHasResources();
		//std::cout << "Resources in " << pFarmer->GetLocation()->GetName() << ": " << pFarmer->GetLocation()->GetResources() << std::endl;
	}
	else
	{
		std::cout << pFarmer->GetName() << ": 'There is no food left, I better get to the market and buy some more.'" << std::endl;
	}
}

std::string GoHomeAndEat::GetEvent(Farmer* pFarmer)
{
	std::string event = "Stay";
	if (pFarmer->GetHunger() < 8)
	{
		if (pFarmer->Thirsty())
		{
			std::cout << pFarmer->GetName() << ": 'I am thirsty, I need to drink'" << std::endl;
			event = "Thirsty";
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
			std::cout << pFarmer->GetName() << ": 'Ah, I feel so much better now that I am full. Time to get back to the barn!'" << std::endl;
			event = "FullBarnAvavible";
		}
		else if (pFarmer->FieldHasResource())
		{
			std::cout << pFarmer->GetName() << ": 'Jum! Now I am full. Time to get back to the field!'" << std::endl;
			event = "FullFieldAvavible";
		}
		else if (pFarmer->GetGoodsInCart() > 0)
		{
			std::cout << pFarmer->GetName() << ": 'It seems everything is done in the barn and at the field. But I have some gtoods in my horse cart to sell!'" << std::endl;
			event = "FullHaveGoodsToSell";
		}
		else
		{
			if (pFarmer->InvitationAccepted() == true)
			{
				std::cout << pFarmer->GetName() << ": 'There is nothing more to do today! Time for fun!'" << std::endl;
				event = "TimeForFun";
			}
			else
			{
				std::cout << pFarmer->GetName() << ": 'There is nothing more to do today! I think I can take it easy now.'" << std::endl;
				event = "TimeToRest";
			}
		}
	}
	else if (!pFarmer->GetLocation()->HasResources())
	{
		if (pFarmer->GetGoldCoins() < 4 && pFarmer->GetGoodsInCart() > 1)
		{
			std::cout << pFarmer->GetName() << ": 'We have no food! And not enough gold to buy more. Better sell what I have in the cart.'" << std::endl;
			event = "OutOfResourcesAndGold";
		}
		else if (pFarmer->GetGoldCoins() < 4)
		{
			if (pFarmer->BarnHasResource())
			{
				std::cout << pFarmer->GetName() << ": 'We have no food! And not enough gold to buy more. Better work to earn some'" << std::endl;
				event = "OutOfResourcesAndGoldAndNoGoodsInCart->Milk";
			}
			else if (pFarmer->FieldHasResource())
			{
				std::cout << pFarmer->GetName() << ": 'We have no food! And not enough gold to buy more. Better work to earn some'" << std::endl;
				event = "OutOfResourcesAndGoldAndNoGoodsInCart->Crops";
			}
		}
		else
		{

			std::cout << pFarmer->GetName() << ": 'We have no food! Better go and buy more.'" << std::endl;
			event = "OutOfResources";
		}
	}
	return event;
}

void GoHomeAndEat::Exit(Farmer* pFarmer, std::string nextState)
{
	if (nextState != "GoHomeAndSleepTilRested" && nextState != "GoHomeChill")
	{
		std::cout << pFarmer->GetName() << " is Leaving the cottage" << std::endl;
	}
}