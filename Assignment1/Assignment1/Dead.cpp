#include <iostream>
#include "Farmer.h"
#include "State.h"
#include "Dead.h"

Dead* Dead::Instance()
{
    static Dead instance;
    return &instance;
}

void Dead::Enter(Farmer* pFarmer)
{
    std::cout << pFarmer->GetName() << " has died." << std::endl;
    if (pFarmer->GetHunger() > 34)
    {
        std::cout << "Cause of death: Hunger" << std::endl;
    }
    if (pFarmer->GetThirst() > 23)
    {
        std::cout << "Cause of death: Thirst" << std::endl;
    }
}

void Dead::Execute(Farmer* pFarmer)
{
    // Dead men do nothing!
    return;
}

void Dead::Exit(Farmer* pFarmer, std::string nextState)
{
    // No coming back from the dead!
}

std::string Dead::GetEvent(Farmer* pFarmer)
{
    return std::string();
}

int Dead::GetTaskDuration() const
{
    return 0;
}
