#include "BuyAle.h"

BuyAle* BuyAle::Instance()
{
	static BuyAle instance;
	return &instance;
}

void BuyAle::Enter(Farmer* pFarmer)
{
	std::cout << pFarmer->GetName() << " 'Can I have an ale please?'" << std::endl;
    if (pFarmer->GetLocation() != &pub)
    {
        pFarmer->ChangeLocation(&pub);
    }
}

void BuyAle::Execute(Farmer* pFarmer)
{
	//If farmer can afford ordering ale:
	if (pFarmer->GetGoldCoins() > 9)
	{
		int moneySpent = 10;
		//decrease thirst
		pFarmer->IncreaseThirst(-5);
		std::cout << pFarmer->GetName() << " spent " << moneySpent << " gold coins." << std::endl;
		std::cout << pFarmer->GetName() << " drinks ale!" << std::endl;
		//decrease farmers amount of gold
		pFarmer->SpendGoldCoins(moneySpent);
	}
	else
	{
		std::cout << pFarmer->GetName() << " 'Oh, I can't afford it.. Better get home.'" << std::endl;
	}
}

std::string BuyAle::GetEvent(Farmer* pFarmer)
{
	std::string event = "Stay";
	if (pFarmer->GetThirst() < 8)
	{
		event = "Unthirsty";
	}
	//If farmer is still thirsty after drinking ale and can't afford more he/she gets home to drink
	else if (pFarmer->GetGoldCoins() < 10)
	{
		std::cout << pFarmer->GetName() << ": 'I am still thirsty, but can't afford more ale. I need to go home.'" << std::endl;
		event = "OutOfGold";
	}
	else
	{
		std::cout << pFarmer->GetName() << ": 'I need more!'" << std::endl;
	}
	return event;
}

void BuyAle::Exit(Farmer* pFarmer, std::string nextState)
{
	if (nextState != "QuenchThirst")
	{
		std::cout << pFarmer->GetName() << " 'Ah that was good!'" << std::endl;
	}
}