#include "AtTheFieldsHarvesting.h"


AtTheFieldsHarvesting* AtTheFieldsHarvesting::Instance()
{
	static AtTheFieldsHarvesting instance;
	return &instance;
}

void AtTheFieldsHarvesting::Enter(Farmer* pFarmer)
{
	if (pFarmer->GetLocation() != &field)
	{
		std::cout << pFarmer->GetName() << " is Walking to the field" << std::endl;
		pFarmer->ChangeLocation(&field);
	}
}

void AtTheFieldsHarvesting::Execute(Farmer* pFarmer)
{
	std::cout << "Resources " << pFarmer->GetLocation()->GetName() << ": " << pFarmer->GetLocation()->GetResources() << std::endl;

	if (pFarmer->GetLocation()->HasResources())
	{
		pFarmer->AddGoodsToCart();
		pFarmer->DecreaseEnergy(1);
		pFarmer->IncreaseHunger(1);
		pFarmer->IncreaseThirst(1.5);
		std::cout << pFarmer->GetName() << " is harvesting crops." << std::endl;

		pFarmer->GetLocation()->DecreaseResources();
		pFarmer->GetLocation()->SetHasResources();
	}
	else
	{
		std::cout << "There are no crops to harvest, come back tomorrow." << std::endl;
	}
	pFarmer->SetFieldHasResource(pFarmer->GetLocation()->HasResources());
}

std::string AtTheFieldsHarvesting::GetEvent(Farmer* pFarmer)
{
	std::string event = "Stay";
	if (pFarmer->Thirsty())
	{
		std::cout << pFarmer->GetName() << ": 'I am thirsty, I need to drink'" << std::endl;
		event = "Thirsty";
	}
	else if (pFarmer->Hungry())
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
	else if (!pFarmer->GetLocation()->HasResources())
	{
		if (!pFarmer->BarnHasResource())
		{
			if (pFarmer->GetGoodsInCart() < 1)
			{
				if (pFarmer->InvitationAccepted() == true)
				{
					std::cout << pFarmer->GetName() << ": 'There is nothing more to do today! Time for fun!'" << std::endl;
					event = "TimeForFun"; // No resources in barn and field and Cart is empty
				}
				else
				{
					std::cout << pFarmer->GetName() << ": 'There is nothing more to do today! I think I can take it easy now.'" << std::endl;
					event = "TimeToRest";
				}
			}
			else
			{
				std::cout << pFarmer->GetName() << ": 'No more crops to harvest, and no more cows to milk, better sell what I've got.'" << std::endl;
				event = "OutOfResources"; // No resources in barn and field
			}
		}
		else
		{
			std::cout << pFarmer->GetName() << ": 'There is no more Crops to harvest, but i think some cows still have milk to give!'" << std::endl;
			event = "OutOfResourcesBarnAvailable"; // No resources in field, but barn has resources
		}
	}
	return event;
}

void AtTheFieldsHarvesting::Exit(Farmer* pFarmer, std::string nextState)
{
	std::cout << pFarmer->GetName() << " is Leaving the field" << std::endl;
}
