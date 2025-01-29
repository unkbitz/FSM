#include <iostream>
#include <chrono>
#include <thread>
#include <memory>
#include <vector>
#include "Location.h"
#include "GameTime.h"
#include "Farmer.h"
#include "Dead.h"

int main()
{
    std::vector<std::unique_ptr<Farmer>> farmers;
    GameTime gameTime(6, 0);

    farmers.emplace_back(std::make_unique<Farmer>(1, "Farmer Jenny", 3));
    farmers.emplace_back(std::make_unique<Farmer>(2, "Farmer Hank", 5));
    farmers.emplace_back(std::make_unique<Farmer>(3, "Farmer Hanna", 8));
    farmers.emplace_back(std::make_unique<Farmer>(4, "Farmer Jim", 7));

    int numbersOfDeadFarmers = 0;
    std::string TimeOfDeath1 = "Time of death for the first farmer: ";
    std::string TimeOfDeath2 = "Time of death for the second farmer: ";
    std::string TimeOfDeath3 = "Time of death for the third farmer: ";
    std::string TimeOfDeath4 = "Time of death for the fourth farmer: ";

    // Game loop
    while (true) 
    {
        gameTime.Update();
        std::cout << "\033[33mCurrent Time: " << gameTime.GetTimeString() << "\033[0m" << std::endl;

        for (auto& farmer : farmers)
        {
            std::string nameOfCurrentState = farmer->GetNameOfCurrentState();
            //std::cout << "Current state: " << nameOfCurrentState << std::endl;
            if (nameOfCurrentState != "Dead")
            {
                //std::cout << "Current Thirst level:" << farmer->GetThirst() << std::endl;
                //std::cout << "Current hunger level:" << farmer->GetHunger() << std::endl;
                //std::cout << "Current energy level:" << farmer->GetEnergy() << std::endl;
                //std::cout << "Current gold level:" << farmer->GetGoldCoins() << std::endl;
                //std::cout << "Current number of goods in cart:" << farmer->GetGoodsInCart() << std::endl;
                farmer->Update(gameTime);
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                std::cout << std::endl;
                if (farmer->GetHunger() > 38 || farmer->GetThirst() > 28) {
                    numbersOfDeadFarmers++;
                    if (numbersOfDeadFarmers == 1)
                    {
                        TimeOfDeath1 += gameTime.GetTimeString();
                    }
                    if (numbersOfDeadFarmers == 2)
                    {
                        TimeOfDeath2 += gameTime.GetTimeString();
                    }
                    if (numbersOfDeadFarmers == 3)
                    {
                        TimeOfDeath3 += gameTime.GetTimeString();
                    }
                    if (numbersOfDeadFarmers == 4)
                    {
                        TimeOfDeath4 += gameTime.GetTimeString();
                    }
                    std::cout << "Hungerlevel: " << farmer->GetHunger() << std::endl << "Thirstlevel: " << farmer->GetThirst() << std::endl;
                    farmer->ChangeState(Dead::Instance());
                    std::cout << std::endl;
                }
            }
        }

        // Remove dead farmers from the list
        farmers.erase(
            std::remove_if(
                farmers.begin(),
                farmers.end(),
                [](const std::unique_ptr<Farmer>& farmer)
                {
                    return farmer->GetNameOfCurrentState() == "Dead";
                }
            ),
            farmers.end()
        );

        // Exit if all farmers are dead
        if (farmers.empty()) {
            std::cout << "All farmers have died. Ending simulation." << std::endl;
            std::cout << TimeOfDeath1 << std::endl;
            std::cout << TimeOfDeath2 << std::endl;
            std::cout << TimeOfDeath3 << std::endl;
            std::cout << TimeOfDeath4 << std::endl;
            break;
        }
    }

    return 0;
}
