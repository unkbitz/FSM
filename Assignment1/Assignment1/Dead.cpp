#include "Farmer.h"
#include "Dead.h"

Dead* Dead::Instance()
{
    static Dead instance;
    return &instance;
}

void Dead::Enter(Farmer* pFarmer)
{
    //Change location simply so that a dead farmer doesn't greet his friends if in the same location
    pFarmer->ChangeLocation(&heaven);
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