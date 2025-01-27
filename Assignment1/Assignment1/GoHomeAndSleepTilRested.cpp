#include "GoHomeAndSleepTilRested.h"
#include "EnterBarnAndMilkTheCows.h"
#include "GoHomeAndEat.h"
#include "QuenchThirst.h"
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
        StartTaskTimer(0.5f);
        std::cout << pFarmer->GetName() << ": Walking to the cottage" << std::endl;
        pFarmer->ChangeLocation(&cottage);
    }
}

void GoHomeAndSleepTilRested::Execute(Farmer* pFarmer)
{
    if (pFarmer->Tierd())
    {
        while (pFarmer->GetEnergy() < 33)
        {
            StartTaskTimer(2.0f);
            pFarmer->Sleep(8); // Restore energy gradually
            std::cout << pFarmer->GetName() << " is sleeping..." << std::endl;
        }
        pFarmer->ChangeLocation(&field);
        pFarmer->GetLocation()->ReplennishReshources(10);
        pFarmer->GetLocation()->SetHasResources();
        pFarmer->SetFieldHasResource(true);
        pFarmer->ChangeLocation(&barn);
        pFarmer->GetLocation()->ReplennishReshources(10);
        pFarmer->GetLocation()->SetHasResources();
        pFarmer->SetBarnHasResource(true);
        pFarmer->ChangeLocation(&cottage);
    }
    StartTaskTimer(0.5f);
    std::cout << pFarmer->GetName() << ": 'Good morning! Time to get to work again!'" << std::endl;
    if (pFarmer->GetHunger() > 25)
    {
        pFarmer->ChangeState(GoHomeAndEat::Instance());
    }
    else if (pFarmer->GetThirst() > 15)
    {
        pFarmer->ChangeState(QuenchThirst::Instance());
    }
    else
    {
        pFarmer->ChangeState(EnterBarnAndMilkTheCows::Instance());
    }
}

void GoHomeAndSleepTilRested::Exit(Farmer* pFarmer)
{
    StartTaskTimer(0.5f);
    std::cout << pFarmer->GetName() << ": Leaving the cottage" << std::endl;
}

float GoHomeAndSleepTilRested::GetTaskDuration() const
{
    return 2.0f;
}