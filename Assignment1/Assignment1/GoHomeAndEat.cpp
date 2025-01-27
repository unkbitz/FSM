#include "GoHomeAndEat.h"
#include "VisitMarketAndBuy.h"
#include "Farmer.h"
#include <iostream>

GoHomeAndEat* GoHomeAndEat::Instance()
{
    static GoHomeAndEat instance;
    return &instance;
}

void GoHomeAndEat::Enter(Farmer* pFarmer)
{
    if (pFarmer->GetLocation() != &cottage)
    {
        StartTaskTimer(0.5f);
        std::cout << pFarmer->GetName() << ": Walking to the cottage" << std::endl;
        pFarmer->ChangeLocation(&cottage);
    }
}

void GoHomeAndEat::Execute(Farmer* pFarmer)
{
    if (pFarmer->GetLocation()->HasResources() == true)
    {
        StartTaskTimer(0.5);
        std::cout << pFarmer->GetName() << " is eating." << std::endl;
        while (pFarmer->GetHunger() > 7)
        {
            if (pFarmer->GetLocation()->HasResources() == true)
            {
                StartTaskTimer(1.0f);
                std::cout << "..." << std::endl;
                pFarmer->Eat(8); // Restore energy gradually
                pFarmer->GetLocation()->DecreaseResources();
                pFarmer->GetLocation()->SetHasResources();
                if (pFarmer->GetLocation()->HasResources() == false)
                {
                    break;
                }
            }
        }
    }
    if (pFarmer->Hungry() == false)
    {
        StartTaskTimer(0.5f);
        std::cout << pFarmer->GetName() << " is full." << std::endl;
    }
    if (pFarmer->GetLocation()->HasResources() == false)
    {
        if (pFarmer->GetGoldCoins() > 19)
        {
            StartTaskTimer(0.5f);
            std::cout << pFarmer->GetName() << ": 'I have no food left, better get to the market and buy more.'" << std::endl;
            pFarmer->GetLocation()->ReplennishReshources(20);
            pFarmer->GetLocation()->SetHasResources();
            pFarmer->ChangeState(VisitMarketAndBuy::Instance());
            
        }
        else
        {
            StartTaskTimer(0.5f);
            std::cout << pFarmer->GetName() << "'I have no food left, and I can't afford more, better get to work.'" << std::endl;
            pFarmer->RevertToPreviousState();
        }
    }
    else
    {
        pFarmer->RevertToPreviousState();
    }
}

void GoHomeAndEat::Exit(Farmer* pFarmer)
{
    StartTaskTimer(0.5f);
    std::cout << pFarmer->GetName() << ": Leaving the cottage" << std::endl;
}

float GoHomeAndEat::GetTaskDuration() const
{
    return 1.0f;
}