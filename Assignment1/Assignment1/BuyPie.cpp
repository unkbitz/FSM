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
	//If farmer can afford ordering pie:
	if (pFarmer->GetGoldCoins() > 12)
	{
		int moneySpent = 13;
		//decrease hunger
		pFarmer->Eat(15);
		std::cout << pFarmer->GetName() << " spent " << moneySpent << " gold coins." << std::endl;
		std::cout << pFarmer->GetName() << " eats pie!" << std::endl;
		//decrease farmers amount of gold
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
	//If farmer is still hungry after eating pie and can't afford more he/she gets home to eat
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
	if (nextState != "GoHomeAndEat")
	{
		std::cout << pFarmer->GetName() << " 'How tasty!'" << std::endl;
	}
}