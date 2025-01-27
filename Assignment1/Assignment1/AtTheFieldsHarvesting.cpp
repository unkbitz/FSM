#include "AtTheFieldsHarvesting.h"
#include "VisitMarketAndSell.h"
#include "EnterBarnAndMilkTheCows.h"
#include <iostream>

AtTheFieldsHarvesting* AtTheFieldsHarvesting::Instance()
{
	static AtTheFieldsHarvesting instance;
	return &instance;
}

void AtTheFieldsHarvesting::Enter(Farmer* pFarmer)
{
	if (pFarmer->GetLocation() != &field)
	{
		StartTaskTimer(0.5f);
		std::cout << pFarmer->GetName() << " is Walking to the field" << std::endl;
		pFarmer->ChangeLocation(&field);
	}
}

void AtTheFieldsHarvesting::Execute(Farmer* pFarmer)
{
	int sacks = 0;
	if (pFarmer->GetLocation()->HasResources() == false)
	{
		pFarmer->SetFieldHasResource(false);
		StartTaskTimer(0.5f);
		std::cout << "No crops ready to harvest, try again tomorrow!" << std::endl;
	}
	else
	{
		pFarmer->SetFieldHasResource(true);
		std::cout << pFarmer->GetName() << " is harvesting crops.." << std::endl;
	}

	while (pFarmer->GetLocation()->HasResources() == true)
	{
		pFarmer->GetLocation()->DecreaseResources();
		pFarmer->AddGoodsToCart();
		pFarmer->DecreaseEnergy(1);
		pFarmer->IncreaseHunger(1);
		pFarmer->IncreaseThirst(1);
		
		StartTaskTimer(2.0f);
		std::cout << "..." << std::endl;
		
		sacks += 1;
		pFarmer->GetLocation()->SetHasResources();
		if (pFarmer->Hungry() || pFarmer->Thirsty() || pFarmer->Tierd() || pFarmer->CartIsFull())
		{
			break;
		}
	}
	if (sacks == 1)
	{
		StartTaskTimer(0.5f);
		std::cout << pFarmer->GetName() << " has placed a new sack of crops in the horse cart." << std::endl;
	}
	if (sacks > 1)
	{
		StartTaskTimer(0.5f);
		std::cout << pFarmer->GetName() << " has placed " << sacks << " new sacks of crops in the horse cart." << std::endl;
	}
	if (pFarmer->GetLocation()->HasResources() == false)
	{
		StartTaskTimer(0.5f);
		std::cout << pFarmer->GetName() << ": 'My back is hurting after all that work! But I am done harvesting for the day!'" << std::endl;
		pFarmer->SetFieldHasResource(false);
		if (pFarmer->BarnHasResource() == false)
		{
			StartTaskTimer(0.5f);
			std::cout << pFarmer->GetName() << ": 'Since the cows are out os milk as well, it's time to get to the market.'" << std::endl;
			pFarmer->ChangeState(VisitMarketAndSell::Instance());
		}
		else
		{
			StartTaskTimer(0.5f);
			std::cout << pFarmer->GetName() << ": 'I think the cows might still have milk to offer.'" << std::endl;
			pFarmer->ChangeState(EnterBarnAndMilkTheCows::Instance());
		}

	}
	if (pFarmer->CartIsFull() == true)
	{
		StartTaskTimer(0.5f);
		std::cout << pFarmer->GetName() << ": 'My cart is full, better get to the market and sell some goods!'" << std::endl;
		pFarmer->ChangeState(VisitMarketAndSell::Instance());
	}
}

void AtTheFieldsHarvesting::Exit(Farmer* pFarmer)
{
	StartTaskTimer(0.5f);
	std::cout << pFarmer->GetName() << " is Leaving the field" << std::endl;
}

float AtTheFieldsHarvesting::GetTaskDuration() const
{
	return 1.5f;
}