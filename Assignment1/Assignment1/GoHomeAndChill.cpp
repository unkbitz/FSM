#include "GoHomeAndChill.h"
#include "Farmer.h"

GoHomeAndChill* GoHomeAndChill::Instance()
{
	static GoHomeAndChill instance;
	return &instance;
}

void GoHomeAndChill::Enter(Farmer* pFarmer)
{
	if (pFarmer->GetLocation() != &cottage)
	{
		std::cout << pFarmer->GetName() << " is Walking to the cottage" << std::endl;
		pFarmer->ChangeLocation(&cottage);
	}
}

void GoHomeAndChill::Execute(Farmer* pFarmer)
{
	std::cout << pFarmer->GetName() << " is in the cottage having a calm time." << std::endl;
}

std::string GoHomeAndChill::GetEvent(Farmer* pFarmer)
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
		std::cout << pFarmer->GetName() << ": 'I am tierd, time to sleep.'" << std::endl;
		event = "Tierd";
	}
	return event;
}

void GoHomeAndChill::Exit(Farmer* pFarmer, std::string nextState)
{
	if (nextState != "GoHomeAndEat" && nextState != "GoHomeAndSleepTilRested")
	{
		std::cout << pFarmer->GetName() << " is Leaving the cottage" << std::endl;
	}
}