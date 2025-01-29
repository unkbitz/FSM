#include "GoHomeAndSleepTilRested.h"
#include "StateFactory.h"
#include "Farmer.h"
#include <iostream>

GoHomeAndSleepTilRested* GoHomeAndSleepTilRested::Instance()
{
	static GoHomeAndSleepTilRested instance;
	return &instance;
}

void GoHomeAndSleepTilRested::Enter(Farmer* pFarmer)
{
    if (pFarmer->GetLocation() != &cottage)
    {
        std::cout << pFarmer->GetName() << " is Walking to the cottage" << std::endl;
        pFarmer->ChangeLocation(&cottage);
    }
}

void GoHomeAndSleepTilRested::Execute(Farmer* pFarmer)
{
	if (pFarmer->GetHunger() > 15 )
	{
		std::cout << pFarmer->GetName() << " is sleeping... But not so well..." << std::endl;
		pFarmer->Sleep(2);
	}
	else if (pFarmer->GetEnergy() < 80)
	{
		std::cout << pFarmer->GetName() << " is sleeping..." << std::endl;
		pFarmer->Sleep(3);
	}
	else
	{
		std::cout << pFarmer->GetName() << " is sleeping..." << std::endl;
	}
}

std::string GoHomeAndSleepTilRested::GetEvent(Farmer* pFarmer)
{
	std::string event = "Stay";
	if (pFarmer->GetEnergy() > 77)
	{
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
		else if (pFarmer->CartIsFull())
		{
			std::cout << pFarmer->GetName() << ": 'My horse cart is full, better get to the market and sell some goods!'" << std::endl;
			event = "CartFull";
		}
		else
		{
			std::cout << pFarmer->GetName() << ": 'Good morning!'" << std::endl;
			event = "Rested";
		}
	}
	return event;
}

void GoHomeAndSleepTilRested::Exit(Farmer* pFarmer, std::string nextState)
{
	std::cout << pFarmer->GetName() << ": 'Time to get to work again!'" << std::endl;
	if (nextState != "GoHomeAndEat")
	{
		std::cout << pFarmer->GetName() << " is Leaving the cottage" << std::endl;
	}
}

int GoHomeAndSleepTilRested::GetTaskDuration() const
{
    return 30;
}