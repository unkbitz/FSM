#include "AtTheFieldsHarvesting.h"


AtTheFieldsHarvesting* AtTheFieldsHarvesting::Instance()
{
	static AtTheFieldsHarvesting instance;
	return &instance;
}

void AtTheFieldsHarvesting::Enter(Farmer* pFarmer)
{
	// If the Farmer is not already in the fields; Change location to fields
	if (pFarmer->GetLocation() != &field)
	{
		std::cout << pFarmer->GetName() << " is Walking to the field" << std::endl;
		pFarmer->ChangeLocation(&field);
	}
}

void AtTheFieldsHarvesting::Execute(Farmer* pFarmer)
{
	//std::cout << "Resources " << pFarmer->GetLocation()->GetName() << ": " << pFarmer->GetLocation()->GetResources() << std::endl;
	//If the location has resources, in this case crops:
	if (pFarmer->GetLocation()->HasResources())
	{
		//Farmer gets more hungry and thirsty and looses enegry from working and goods in farmers cart is increased 
		pFarmer->AddGoodsToCart();
		pFarmer->DecreaseEnergy(1);
		pFarmer->IncreaseHunger(1);
		pFarmer->IncreaseThirst(1.5);
		std::cout << pFarmer->GetName() << " is harvesting crops." << std::endl;

		//The resouces of the location is decreased
		pFarmer->GetLocation()->DecreaseResources();
		//m_hasResources may be flipped to false
		pFarmer->GetLocation()->SetHasResources();
	}
	//If the the location is out of recouses:
	else
	{
		std::cout << "There are no crops to harvest, come back tomorrow." << std::endl;
	}
	//The farmer knows if there are still resources left or not
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
		//If location ran out of resources:
		if (!pFarmer->BarnHasResource())
		{
			//if farmers cart is empty:
			if (pFarmer->GetGoodsInCart() < 1)
			{
				//If Farmer has accepted an invitation to the pub:
				if (pFarmer->InvitationAccepted() == true)
				{
					std::cout << pFarmer->GetName() << ": 'There is nothing more to do today! Time for fun!'" << std::endl;
					event = "TimeForFun"; // No resources in barn and field and Cart is empty
				}
				//If farmer did not accept any invitation to the pub
				else
				{
					std::cout << pFarmer->GetName() << ": 'There is nothing more to do today! I think I can take it easy now.'" << std::endl;
					event = "TimeToRest";
				}
			}
			//If farmer has Goods to sell:
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
