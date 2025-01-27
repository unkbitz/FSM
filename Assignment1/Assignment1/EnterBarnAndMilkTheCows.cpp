#include "EnterBarnAndMilkTheCows.h"
#include "AtTheFieldsHarvesting.h"
#include "VisitMarketAndSell.h"
#include <iostream>
#include <chrono>
#include <thread>

EnterBarnAndMilkTheCows* EnterBarnAndMilkTheCows::Instance()
{
	static EnterBarnAndMilkTheCows instance;
	return &instance;
}

void EnterBarnAndMilkTheCows::Enter(Farmer* pFarmer)
{
	if (pFarmer->GetLocation() != &barn)
	{
		StartTaskTimer(0.5f);
		std::cout << pFarmer->GetName() << ": Walking to the barn" << std::endl;
		pFarmer->ChangeLocation(&barn);
	}
}

void EnterBarnAndMilkTheCows::Execute(Farmer* pFarmer)
{
	int jugs = 0;
	if (pFarmer->GetLocation()->HasResources() == false)
	{
		StartTaskTimer(0.5f);
		pFarmer->SetBarnHasResource(false);
		std::cout << "The cows are out of milk, try again tomorrow!" << std::endl;
	}
	else 
	{
		pFarmer->SetBarnHasResource(true);
		std::cout << pFarmer->GetName() << " is milking the cows.." << std::endl;
	}

	while (pFarmer->GetLocation()->HasResources())
	{
		pFarmer->GetLocation()->DecreaseResources();
		pFarmer->AddGoodsToCart();
		pFarmer->DecreaseEnergy(1);
		pFarmer->IncreaseHunger(1);
		pFarmer->IncreaseThirst(1);

		StartTaskTimer(2.0);

		std::cout << "..." << std::endl;
		//std::cout << pFarmer->GetName() << " is Placing a new jug of milk in the horse cart." << std::endl;
		jugs += 1;
		pFarmer->GetLocation()->SetHasResources();
		if (pFarmer->Hungry() || pFarmer->Thirsty() || pFarmer->Tierd() || pFarmer->CartIsFull())
		{
			break;
		}
	}
	if (jugs == 1)
	{
		StartTaskTimer(0.5f);
		std::cout << pFarmer->GetName() << " has placed a new jug of milk in the horse cart." << std::endl;
	}
	if (jugs > 1)
	{
		StartTaskTimer(0.5f);
		std::cout << pFarmer->GetName() << " has placed " << jugs << " new jugs of milk in the horse cart." << std::endl;
	}
	if (pFarmer->GetLocation()->HasResources() == false)
	{
		StartTaskTimer(0.5f);
		std::cout << pFarmer->GetName() << ": 'Ah, that was hard work! But now the cows has no more milk to offer this day.'" << std::endl;
		pFarmer->SetBarnHasResource(false);
		if (pFarmer->FieldHasResource() == false)
		{
			StartTaskTimer(0.5f);
			std::cout << pFarmer->GetName() << ": 'Since there are no crops left on the field either, it's time to get to the market.'" << std::endl;
			pFarmer->ChangeState(VisitMarketAndSell::Instance());
		}
		else
		{
			StartTaskTimer(0.5f);
			std::cout << pFarmer->GetName() << ": 'I think there might still be some crops left to harvest.'" << std::endl;
			pFarmer->ChangeState(AtTheFieldsHarvesting::Instance());
		}
	}
	if (pFarmer->CartIsFull() == true)
	{
		StartTaskTimer(0.5f);
		std::cout << pFarmer->GetName() << ": 'My cart is full, better get to the market and sell some goods!'" << std::endl;
		pFarmer->ChangeState(VisitMarketAndSell::Instance());
	}
}

void EnterBarnAndMilkTheCows::Exit(Farmer* pFarmer)
{
	StartTaskTimer(0.5f);
	std::cout << pFarmer->GetName() << " is Leaving the barn" << std::endl;
}

float EnterBarnAndMilkTheCows::GetTaskDuration() const
{
	return 1.5f;
}
