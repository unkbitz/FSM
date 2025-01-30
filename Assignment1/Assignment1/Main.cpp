#include <conio.h>
#include <chrono>
#include <thread>
#include <memory>
#include "Location.h"
#include "GameTime.h"
#include "Farmer.h"
#include "Dead.h"


// Define ANSI escape codes
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

int main()
{
    std::vector<std::unique_ptr<Farmer>> farmers;
    GameTime gameTime(6, 0);

    farmers.emplace_back(std::make_unique<Farmer>(1, "Farmer Jenny", 3));
    farmers.emplace_back(std::make_unique<Farmer>(2, "Farmer Hank", 5));
    farmers.emplace_back(std::make_unique<Farmer>(3, "Farmer Hanna", 8));
    farmers.emplace_back(std::make_unique<Farmer>(4, "Farmer Jim", 7));

    int numbersOfDeadFarmers = 0;
    std::string TimeOfDeath1 = "Time of death for ";
    std::string TimeOfDeath2 = "Time of death for ";
    std::string TimeOfDeath3 = "Time of death for ";
    std::string TimeOfDeath4 = "Time of death for ";

    bool pause = false;
    bool statsPrinted = false;
    int sleepTime = 1000;
    bool invitationSent = false;

    // Game loop
    while (true) 
    {
        // Check for keypress dynamically
        if (_kbhit()) // Non-blocking input check
        {
            char key = _getch(); // Get the pressed key

            if (key == '1') sleepTime = 1000; // Slow simulation
            if (key == '2') sleepTime = 100;  // Faster simulation
            if (key == '3') sleepTime = 0;    // Fastest simulation (no sleep)
            if (key == ' ')
            {
                pause = !pause;   // Toggle pause
                statsPrinted = false;
            }
        }

        if (pause == false)
        {
            gameTime.Update();
            std::cout << "\033[33mCurrent Time: " << gameTime.GetTimeString() << "\033[0m" << std::endl;

            for (auto& farmer : farmers)
            {
                std::string nameOfCurrentState = farmer->GetNameOfCurrentState();
                //std::cout << "Current state: " << nameOfCurrentState << std::endl;
                if (nameOfCurrentState != "Dead")
                {
                    farmer->ProcessMessages(farmers);
                    farmer->Update(gameTime);

                    for (auto& otherFarmer : farmers)
                    {
                        if (farmer != otherFarmer)
                        {
                            if (farmer->GetLastLocation() != farmer->GetLocation())
                            {
                                if (farmer->GetLocation() == otherFarmer->GetLocation())
                                {
                                    farmer->Meet(otherFarmer);
                                }
                            }
                        }
                    }

                    if (gameTime.GetHour() == 12 && invitationSent == false && farmer->GetEnergy() > 55)
                    {
                        for (auto& otherFarmer : farmers)
                        {
                            if (farmer != otherFarmer)
                            {
                                std::string message = "Hi! You wanna join me at the pub by 20:00?";
                                farmer->SendMessage(*otherFarmer, message);
                            }
                        }
                        invitationSent = true;
                        std::cout << "\033[32m" << farmer->GetName() << " sent invitations to the pub." << "\033[0m" << std::endl;
                    }
                    if (gameTime.GetHour() != 12)
                    {
                        invitationSent = false;
                    }
                    if (gameTime.GetHour() == 19 && gameTime.GetMinute() == 30 && farmer->InvitationAccepted() == true)
                    {
                        if (farmer->GetEnergy() < 5)
                        {
                            for (auto& otherFarmer : farmers)
                            {
                                if (farmer != otherFarmer)
                                {
                                    if (otherFarmer->InvitationAccepted() == true)
                                    {
                                        std::string message = "Sorry, but I am exhasted, I'll stay at home.";
                                        farmer->SendMessage(*otherFarmer, message);
                                    }
                                }
                            }
                        }
                        else if (farmer->GetGoldCoins() < 10)
                        {
                            for (auto& otherFarmer : farmers)
                            {
                                if (farmer != otherFarmer)
                                {
                                    if (otherFarmer->InvitationAccepted() == true)
                                    {
                                        std::string message = "Sorry, but I can't afford to come tonight.";
                                        farmer->SendMessage(*otherFarmer, message);
                                    }
                                }
                            }
                        }
                    }
                    std::cout << std::endl;
                    if (farmer->GetNameOfCurrentState() == "Dead") {
                        numbersOfDeadFarmers++;
                        if (numbersOfDeadFarmers == 1)
                        {
                            TimeOfDeath1 = TimeOfDeath1 + farmer->GetName() + ": " + gameTime.GetTimeString();
                        }
                        else if (numbersOfDeadFarmers == 2)
                        {
                            TimeOfDeath2 = TimeOfDeath2 + farmer->GetName() + ": " + gameTime.GetTimeString();
                        }
                        else if (numbersOfDeadFarmers == 3)
                        {
                            TimeOfDeath3 = TimeOfDeath3 + farmer->GetName() + ": " + gameTime.GetTimeString();
                        }
                        else if (numbersOfDeadFarmers == 4)
                        {
                            TimeOfDeath4 = TimeOfDeath4 + farmer->GetName() + ": " + gameTime.GetTimeString();
                        }
                        std::cout << "Hungerlevel: " << farmer->GetHunger() << std::endl << "Thirstlevel: " << farmer->GetThirst() << std::endl;
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
            if (farmers.empty()) 
            {
                std::cout << "All farmers have died. Ending simulation." << std::endl;
                std::cout << TimeOfDeath1 << std::endl;
                std::cout << TimeOfDeath2 << std::endl;
                std::cout << TimeOfDeath3 << std::endl;
                std::cout << TimeOfDeath4 << std::endl;
                break;
            }

            // Sleep for the current simulation speed
            if (sleepTime > 0)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
            }
        }   
        else
        {
            // Print stats only once
            if (!statsPrinted)
            {
                std::cout << "Simulation paused. Farmer stats:\n";
                for (const auto& farmer : farmers)
                {
                    std::cout << farmer->GetName() << "'s current thirst: " << farmer->GetThirst() << std::endl;
                    std::cout << farmer->GetName() << "'s current hunger: " << farmer->GetHunger() << std::endl;
                    std::cout << farmer->GetName() << "'s current energy: " << farmer->GetEnergy() << std::endl;
                    std::cout << farmer->GetName() << "'s gold: " << farmer->GetGoldCoins() << std::endl;
                    std::cout << farmer->GetName() << "'s goods: " << farmer->GetGoodsInCart() << std::endl;
                    std::cout << std::endl;
                }
                statsPrinted = true; // Mark stats as printed
            }
            // Avoid busy-waiting, add a small sleep
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }

    return 0;
}
