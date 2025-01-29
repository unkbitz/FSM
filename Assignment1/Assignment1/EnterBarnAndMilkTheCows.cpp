#include "EnterBarnAndMilkTheCows.h"
#include "StateFactory.h"
#include "Farmer.h"
#include <iostream>

EnterBarnAndMilkTheCows* EnterBarnAndMilkTheCows::Instance()
{
	static EnterBarnAndMilkTheCows instance;
	return &instance;
}

void EnterBarnAndMilkTheCows::Enter(Farmer* pFarmer)
{
	if (pFarmer->GetLocation() != &barn)
	{
		std::cout << pFarmer->GetName() << ": Walking to the barn" << std::endl;
		pFarmer->ChangeLocation(&barn);
	}
}

void EnterBarnAndMilkTheCows::Execute(Farmer* pFarmer)
{
    std::cout << "Resources " << pFarmer->GetLocation()->GetName() << ": " << pFarmer->GetLocation()->GetResources() << std::endl;
    // Normal logic for milking the cows
    if (pFarmer->GetLocation()->HasResources())
    {
        pFarmer->AddGoodsToCart();
        pFarmer->DecreaseEnergy(0.5);
        pFarmer->IncreaseHunger(1);
        pFarmer->IncreaseThirst(1);
        std::cout << pFarmer->GetName() << " is milking the cows." << std::endl;
        pFarmer->GetLocation()->DecreaseResources();
        pFarmer->GetLocation()->SetHasResources();
    }
    else
    {
        std::cout << "There is no milk left, try again tomorrow." << std::endl;
    }
    pFarmer->SetBarnHasResource(pFarmer->GetLocation()->HasResources());
}

std::string EnterBarnAndMilkTheCows::GetEvent(Farmer* pFarmer)
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
        pFarmer->SetBarnHasResource(pFarmer->GetLocation()->HasResources());
        if (!pFarmer->FieldHasResource())
        {
            if (pFarmer->GetGoodsInCart() < 1)
            {
                std::cout << pFarmer->GetName() << ": 'There is nothing more to do today! Time for fun!'" << std::endl;
                event = "OutOfResourcesEmptyCart"; // No resources in barn and field and Cart is empty
            }
            else
            {
                std::cout << pFarmer->GetName() << ": 'No more crops to harvest, and no more cows to milk, better sell what I've got.'" << std::endl;
                event = "OutOfResources"; // No resources in barn or field
            }
        }
        else
        {
            std::cout << pFarmer->GetName() << ": 'There is no more cows to milk, but i think there are some crops left to harvest!'" << std::endl;
            event = "OutOfResourcesFieldAvailable"; // No resources in barn, but field has resources
        }
    }
    return event;
}

void EnterBarnAndMilkTheCows::Exit(Farmer* pFarmer, std::string nextState)
{
	std::cout << pFarmer->GetName() << " is Leaving the barn" << std::endl;
}

int EnterBarnAndMilkTheCows::GetTaskDuration() const
{
	return 15;
}
