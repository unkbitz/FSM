#include "FarmerGlobalState.h"
#include "QuenchThirst.h"
#include "GoHomeAndSleepTilRested.h"
#include "GoHomeAndEat.h"
#include "Farmer.h"

FarmerGlobalState* FarmerGlobalState::Instance()
{
    static FarmerGlobalState instance;
    return &instance;
}

void FarmerGlobalState::Execute(Farmer* pFarmer) {
    int moneySpent = 0;
    // Check thirst and drink if necessary
    if (pFarmer->Thirsty()) {
        if (pFarmer->GetNameOfCurrentState() != "class QuenchThirst")
        {
            if (pFarmer->GetNameOfCurrentState() == "class AtThePubWithFriends")
            {
                if (pFarmer->GetGoldCoins() > 4)
                {
                    moneySpent = 5;
                    StartTaskTimer(0.5f);
                    std::cout << pFarmer->GetName() << ": 'I'm thirsty, can I have an ale please?'" << std::endl;
                    StartTaskTimer(1.5f);
                    pFarmer->Drink(10);
                    std::cout << pFarmer->GetName() << " drinks ale!" << std::endl;
                    pFarmer->SpendGoldCoins(moneySpent);
                    StartTaskTimer(0.5f);
                    std::cout << pFarmer->GetName() << " spent " << moneySpent << " gold coins." << std::endl;
                }
                else
                {
                    StartTaskTimer(0.5f);
                    std::cout << pFarmer->GetName() << " is thirsty, but can't afford ale." << std::endl;
                    pFarmer->ChangeState(QuenchThirst::Instance());
                }
            }
            else
            {
                StartTaskTimer(0.5f);
                std::cout << pFarmer->GetName() << ": 'I'm thirsty, I need water.'" << std::endl;
                pFarmer->ChangeState(QuenchThirst::Instance());
            }
        }
    }

    else if (pFarmer->Hungry()) {
        if (pFarmer->GetNameOfCurrentState() != "class GoHomeAndEat")
        {
            if (pFarmer->GetNameOfCurrentState() == "class AtThePubWithFriends")
            {
                moneySpent = 7;
                if (pFarmer->GetGoldCoins() > 6)
                {
                    StartTaskTimer(0.5f);
                    std::cout << pFarmer->GetName() << ": 'I'm hungry, can I have a pie please?'" << std::endl;
                    StartTaskTimer(2.0f);
                    pFarmer->Eat(10);
                    std::cout << pFarmer->GetName() << " eats pie!" << std::endl;
                    pFarmer->SpendGoldCoins(moneySpent);
                    StartTaskTimer(0.5f);
                    std::cout << pFarmer->GetName() << " spent " << moneySpent << " gold coins." << std::endl;
                }
                else
                {
                    StartTaskTimer(0.5f);
                    std::cout << pFarmer->GetName() << " is hungry, but can't afford a pie." << std::endl;
                    pFarmer->ChangeState(GoHomeAndEat::Instance());
                }
            }
            else
            {
                StartTaskTimer(0.5f);
                std::cout << pFarmer->GetName() << ": 'I'm hungry, I need food.'" << std::endl;
                pFarmer->ChangeState(GoHomeAndEat::Instance());
            }
        }
    }

    // Monitor energy
    else if (pFarmer->Tierd()) 
    {
        if (pFarmer->GetNameOfCurrentState() != "class GoHomeAndSleepTilRested")
        {
            if (pFarmer->GetNameOfCurrentState() == "class AtThePubWithFriends")
            {
                StartTaskTimer(0.5f);
                std::cout << pFarmer->GetName() << ": 'I'm tierd, Time to get home.'" << std::endl;
            }
            else 
            {
                StartTaskTimer(0.5f);
                std::cout << pFarmer->GetName() << ": 'I'm tired, I need to rest soon.'" << std::endl;
            }
            pFarmer->ChangeState(GoHomeAndSleepTilRested::Instance());
        }
    }
}

float FarmerGlobalState::GetTaskDuration() const
{
    return 1.0f;
}