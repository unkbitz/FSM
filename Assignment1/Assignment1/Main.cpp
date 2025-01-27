#include <iostream>
#include <chrono>
#include <thread>
#include <memory>
#include <vector>
#include "Location.h"
#include "Farmer.h"
#include "Dead.h"
#include "EnterBarnAndMilkTheCows.h"


int main()
{
    std::vector<std::unique_ptr<Farmer>> farmers;
    Farmer farmer1(1, "Farmer Jenny");
    Farmer farmer2(2, "Farmer Hank");
    Farmer farmer3(3, "Farmer Hanna");
    Farmer farmer4(4, "Farmer Jim");

    farmers.emplace_back(std::make_unique<Farmer>(farmer1));
    farmers.emplace_back(std::make_unique<Farmer>(farmer2));
    farmers.emplace_back(std::make_unique<Farmer>(farmer3));
    farmers.emplace_back(std::make_unique<Farmer>(farmer4));

    for (auto& farmer : farmers)
    {
        farmer->ChangeState(EnterBarnAndMilkTheCows::Instance());
    }

    // Game loop
    for (int i = 0; i < 100; ++i) {
        //std::cout << "Current state: " << farmer1.GetNameOfCurrentState() << std::endl;
        //std::cout << "Current Thirst level:" << farmer1.GetThirst() << std::endl;
        //std::cout << "Current hunger level:" << farmer1.GetHunger() << std::endl;
        //std::cout << "Current energy level:" << farmer1.GetEnergy() << std::endl;
        //std::cout << "Current number of goods in cart:" << farmer1.GetGoodsInCart() << std::endl;
        std::cout << "Game loop iteration: " << i + 1 << std::endl;

        for (auto& farmer : farmers)
        {
            farmer->Update();  // Pass elapsed time to update
            std::this_thread::sleep_for(std::chrono::milliseconds(100));  // Simulate real-time pacing
            std::cout << std::endl;
            if (farmer->GetHunger() > 34 || farmer1.GetThirst() > 23) {
                std::cout << "Hungerlevel: " << farmer->GetHunger() << std::endl << "Thirstlevel: " << farmer->GetThirst() << std::endl;
                farmer->ChangeState(Dead::Instance());
                std::cout << std::endl;
            }
        }

        // Remove dead farmers from the list
        farmers.erase(
            std::remove_if(
                farmers.begin(),
                farmers.end(),
                [](const std::unique_ptr<Farmer>& farmer)
                {
                    return farmer->GetNameOfCurrentState() == "class Dead";
                }
            ),
            farmers.end()
        );

        // Exit if all farmers are dead
        if (farmers.empty()) {
            std::cout << "All farmers have died. Ending simulation." << std::endl;
            break;
        }
    }

    return 0;
}
