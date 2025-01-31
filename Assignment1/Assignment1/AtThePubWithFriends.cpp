#include <algorithm> // for std::min
#include "AtThePubWithFriends.h"

AtThePubWithFriends* AtThePubWithFriends::Instance()
{
	static AtThePubWithFriends instance;
	return &instance;
}

void AtThePubWithFriends::Enter(Farmer* pFarmer)
{
	if (pFarmer->GetLocation() != &pub)
	{
		if (pFarmer->GetThirst() < 24)
		{
			int currentThirst = pFarmer->GetThirst();
			int newThirst = std::min(currentThirst + 18, 25);
			pFarmer->SetThirst(newThirst);
		}
		std::cout << pFarmer->GetName() << " is Riding to the pub" << std::endl;
		pFarmer->ChangeLocation(&pub);
	}
}


void AtThePubWithFriends::Execute(Farmer* pFarmer)
{
	std::cout << pFarmer->GetName() << " is at the pub having fun!" << std::endl;
	pFarmer->SetBarnHasResource(false);
	pFarmer->SetFieldHasResource(false);
	pFarmer->SetInvitationAccepted(false);
}

std::string AtThePubWithFriends::GetEvent(Farmer* pFarmer)
{
	std::string event = "TimeForFun";
	if (pFarmer->Thirsty())
	{
		if (pFarmer->GetGoldCoins() < 10)
		{
			std::cout << pFarmer->GetName() << ": 'I am thirsty, but can't afford ale. I need to go home.'" << std::endl;
			event = "Thirsty";
		}
		else
		{
			std::cout << pFarmer->GetName() << ": 'I am thirsty'" << std::endl;
			event = "ThirstyAndRich";
		}
	} 
	else if (pFarmer->Hungry())
	{
		if (pFarmer->GetGoldCoins() < 13)
		{
			std::cout << pFarmer->GetName() << ": 'I am hungry, but can't afford pie. I need to go home'" << std::endl;
			event = "Hungry";
		}
		else
		{
			std::cout << pFarmer->GetName() << ": 'I am hungry'" << std::endl;
			event = "HungryAndRich";
		}
	}
	else if (pFarmer->Tired())
	{
		std::cout << pFarmer->GetName() << ": 'I am tired, I need to sleep'" << std::endl;
		event = "Tired";
	}
	return event;
}

void AtThePubWithFriends::Exit(Farmer* pFarmer, std::string nextState)
{
	if (nextState != "BuyAle" && nextState != "BuyPie")
	{
		std::cout << pFarmer->GetName() << " is Leaving the pub" << std::endl;
	}
}
