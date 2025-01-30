#include "BuyPie.h"

BuyPie* BuyPie::Instance()
{
    static BuyPie instance;
    return &instance;
}

void BuyPie::Enter(Farmer* pFarmer)
{
	std::cout << pFarmer->GetName() << " 'Can I have a pie please?'" << std::endl;
	if (pFarmer->GetLocation() != &pub)
    {
        pFarmer->ChangeLocation(&pub);
    }
}

void BuyPie::Execute(Farmer* pFarmer)
{
	if (pFarmer->GetGoldCoins() > 12)
	{
		int moneySpent = 13;
		pFarmer->Eat(15);
		std::cout << pFarmer->GetName() << " spent " << moneySpent << " gold coins." << std::endl;
		std::cout << pFarmer->GetName() << " eats pie!" << std::endl;
		pFarmer->SpendGoldCoins(moneySpent);
	}
	else
	{
		std::cout << pFarmer->GetName() << " 'Oh, I can't afford it.. Better get home.'" << std::endl;
	}
}

std::string BuyPie::GetEvent(Farmer* pFarmer)
{
	std::string event = "Stay";
	if (pFarmer->GetHunger() < 8)
	{
		event = "Full";
	}
	else if (pFarmer->GetGoldCoins() < 13)
	{
		std::cout << pFarmer->GetName() << ": 'I am still hungry, but can't afford more pie. I need to go home.'" << std::endl;
		event = "OutOfGold";
	}
	else
	{

		std::cout << pFarmer->GetName() << ": 'I need more!'" << std::endl;
	}
	return event;
}

void BuyPie::Exit(Farmer* pFarmer, std::string nextState)
{
    std::cout << pFarmer->GetName() << " 'How tasty!'" << std::endl;
}