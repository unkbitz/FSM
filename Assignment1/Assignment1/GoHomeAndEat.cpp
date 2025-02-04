#include "GoHomeAndEat.h"
#include "Farmer.h"

GoHomeAndEat* GoHomeAndEat::Instance()
{
    static GoHomeAndEat instance;
    return &instance;
}

void GoHomeAndEat::Enter(Farmer* pFarmer)
{
	//if farmers location is not already cottage
    if (pFarmer->GetLocation() != &cottage)
    {
        std::cout << pFarmer->GetName() << ": Walking to the cottage" << std::endl;
        pFarmer->ChangeLocation(&cottage);
    }
}

void GoHomeAndEat::Execute(Farmer* pFarmer)
{
	//std::cout << "Resources in "<< pFarmer->GetLocation()->GetName() <<": " << pFarmer->GetLocation()->GetResources() << std::endl;
	//If cottage has food left:
	if (pFarmer->GetLocation()->HasResources())
	{
		//dercrease hunger
		std::cout << pFarmer->GetName() << " is eating." << std::endl;
		pFarmer->Eat(8);
		//decreace aount of food left
		pFarmer->GetLocation()->DecreaseResources();
		//m_hasResources may be set to false
		pFarmer->GetLocation()->SetHasResources();
		//std::cout << "Resources in " << pFarmer->GetLocation()->GetName() << ": " << pFarmer->GetLocation()->GetResources() << std::endl;
	}
	//if there is not food left
	else
	{
		std::cout << pFarmer->GetName() << ": 'There is no food left, I better get to the market and buy some more.'" << std::endl;
	}
}

std::string GoHomeAndEat::GetEvent(Farmer* pFarmer)
{
	std::string event = "Stay";
	//If farmer is not hungry anymore:
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
		//If farmer is neither tierd or thirsty maybe he/she can sell goods or work more
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
			std::cout << pFarmer->GetName() << ": 'It seems everything is done in the barn and at the field. But I have some goods in my horse cart to sell!'" << std::endl;
			event = "FullHaveGoodsToSell";
		}
		//If there is nothing more to do:
		else
		{
			//if farmer has accpected an invitation to the pub:
			if (pFarmer->InvitationAccepted() == true)
			{
				std::cout << pFarmer->GetName() << ": 'There is nothing more to do today! Time for fun!'" << std::endl;
				event = "TimeForFun";
			}
			//if farmer has not accpected any invitation to the pub:
			else
			{
				std::cout << pFarmer->GetName() << ": 'There is nothing more to do today! I think I can take it easy now.'" << std::endl;
				event = "TimeToRest";
			}
		}
	}
	//if there is no food left in the cottage and farmer is hungry:
	else if (!pFarmer->GetLocation()->HasResources())
	{
		//If farmer cant afford to buy any more food, but has goods in the cart to sell:
		if (pFarmer->GetGoldCoins() < 4 && pFarmer->GetGoodsInCart() > 1)
		{
			std::cout << pFarmer->GetName() << ": 'We have no food! And not enough gold to buy more. Better sell what I have in the cart.'" << std::endl;
			event = "OutOfResourcesAndGold";
		}
		//If farmer can't afford to buy any more food, and doesn't have goods in the cart to sell:
		else if (pFarmer->GetGoldCoins() < 4)
		{
			//go to barn if it has resources:
			if (pFarmer->BarnHasResource())
			{
				std::cout << pFarmer->GetName() << ": 'We have no food! And not enough gold to buy more. Better work to earn some'" << std::endl;
				event = "OutOfResourcesAndGoldAndNoGoodsInCart->Milk";
			}
			//go to field  if it has resources
			else if (pFarmer->FieldHasResource())
			{
				std::cout << pFarmer->GetName() << ": 'We have no food! And not enough gold to buy more. Better work to earn some'" << std::endl;
				event = "OutOfResourcesAndGoldAndNoGoodsInCart->Crops";
			}
		}
		// if farmer can afford food:
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
	//Basically if farmer doesn't stay in cottage:
	if (nextState != "GoHomeAndSleepTilRested" && nextState != "GoHomeChill")
	{
		std::cout << pFarmer->GetName() << " is Leaving the cottage" << std::endl;
	}
}