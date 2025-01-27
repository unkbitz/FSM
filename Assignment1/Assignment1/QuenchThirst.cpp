#include "QuenchThirst.h"
#include "Farmer.h"
#include <iostream>

QuenchThirst* QuenchThirst::Instance()
{
	static QuenchThirst instance;
	return &instance;
}

void QuenchThirst::Enter(Farmer* pFarmer)
{
    if (pFarmer->GetLocation() != &well)
    {
        StartTaskTimer(0.5f);
        std::cout << pFarmer->GetName() << ": Walking to the well" << std::endl;
        pFarmer->ChangeLocation(&well);
    }
}

void QuenchThirst::Execute(Farmer* pFarmer)
{
    StartTaskTimer(0.5);
    std::cout << pFarmer->GetName() << " is drinking water." << std::endl;
    while (pFarmer->GetThirst() > 4)
    {
        StartTaskTimer(1.0);
        std::cout << "..." << std::endl;
        pFarmer->Drink(5);
        //std::cout << pFarmer->GetName() << "s Thirst-level: " << pFarmer->GetThirst() << std::endl;
    }
    StartTaskTimer(0.5f);
    std::cout << pFarmer->GetName() << " is no longer thirsty." << std::endl;
    pFarmer->RevertToPreviousState();
}

void QuenchThirst::Exit(Farmer* pFarmer)
{
    StartTaskTimer(0.5f);
    std::cout << pFarmer->GetName() << " is leaving the well." << std::endl;
}

float QuenchThirst::GetTaskDuration() const
{
    return 1.0f;
}