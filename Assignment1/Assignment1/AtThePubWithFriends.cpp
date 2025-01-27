#include <iostream>
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
		StartTaskTimer(0.5);
		std::cout << pFarmer->GetName() << "is Riding to the pub" << std::endl;
		pFarmer->ChangeLocation(&pub);
	}
}

void AtThePubWithFriends::Execute(Farmer* pFarmer)
{
		pFarmer->DecreaseEnergy(1);
		pFarmer->IncreaseHunger(3);
		pFarmer->IncreaseThirst(4);
		StartTaskTimer(1.5f);
		std::cout << pFarmer->GetName() << " is having fun with his friends at the pub!" << std::endl;
		//while(pFarmer->Thirsty())
		//{
		//	StartTaskTimer(1.5f);
		//	pFarmer->Drink(5);
		//	std::cout << pFarmer->GetName() << " drinks ale!" << std::endl;
		//	pFarmer->IncreaseHunger(2);
		//}
		//while (pFarmer->Hungry())
		//{
		//	StartTaskTimer(2.0f);
		//	pFarmer->Eat(10);
		//	std::cout << pFarmer->GetName() << " eats pie!" << std::endl;
		//	pFarmer->IncreaseThirst(3);
		//}
}

void AtThePubWithFriends::Exit(Farmer* pFarmer)
{
	StartTaskTimer(0.5f);
	std::cout << pFarmer->GetName() << " is Leaving the pub" << std::endl;
}

float AtThePubWithFriends::GetTaskDuration() const
{
	return 1.0f;
}