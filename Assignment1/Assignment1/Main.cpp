#include <conio.h>
#include <chrono>
#include <thread>
#include <memory>
#include "Location.h"
#include "GameTime.h"
#include "Farmer.h"
#include "Dead.h"

int main()
{
    //create a vector of unique pointers to farmers
    std::vector<std::unique_ptr<Farmer>> farmers;
    GameTime gameTime(6, 0);

    //fill vector with farmers
    farmers.emplace_back(std::make_unique<Farmer>(1, "Farmer Jenny", 3));
    farmers.emplace_back(std::make_unique<Farmer>(2, "Farmer Hank", 5));
    farmers.emplace_back(std::make_unique<Farmer>(3, "Farmer Hanna", 8));
    farmers.emplace_back(std::make_unique<Farmer>(4, "Farmer Jim", 7));

    //Create local variables to use for printouts
    int numbersOfDeadFarmers = 0;
    std::string TimeOfDeath1 = "Time of death for ";
    std::string TimeOfDeath2 = "Time of death for ";
    std::string TimeOfDeath3 = "Time of death for ";
    std::string TimeOfDeath4 = "Time of death for ";

    //initialise needed bools and sleepTime
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

        //When simulation is not paused:
        if (pause == false)
        {
            //Update gameTime and print out the current time
            gameTime.Update();
            std::cout << "-------------------------------------------------------------------------------" << std::endl;
            std::cout << "Current Time: " << gameTime.GetTimeString() << std::endl << std::endl;
            //Each iteration the farmers m_hasBeenGreeted bool should be reset so they can be greeted if someone enter their location
            for (auto& farmer : farmers)
            {
                farmer->SetHasBeenGreeted(false);
            }
            for (auto& farmer : farmers)
            {
                std::string nameOfCurrentState = farmer->GetNameOfCurrentState();
                //std::cout << "Current state: " << nameOfCurrentState << std::endl;
                //If farmer is not dead:
                if (nameOfCurrentState != "Dead")
                {
                    //Process messages
                    farmer->ProcessMessages(farmers);
                    //Update
                    farmer->Update(gameTime);
                    //If farmer changed location since last iteration and is not currently sleeping
                    if (farmer->GetLastLocation() != farmer->GetLocation() && farmer->GetNameOfCurrentState() != "GoHomeAndSleepTilRested")
                    {
                        //Look through the pther farmers:
                        for (auto& otherFarmer : farmers)
                        {
                            if (farmer != otherFarmer)
                            {
                                //if farmer and otherFarmer are at the same location and otherFarmer hasn't already been greeted this iteration and otherFarmer is not sleeping:
                                if (farmer->GetLocation() == otherFarmer->GetLocation() && 
                                    otherFarmer->HasBeenGreeted() == false && 
                                    otherFarmer->GetNameOfCurrentState() != "GoHomeAndSleepTilRested")
                                {
                                    //farmer and otherFarmer meets and changes a few words
                                    farmer->Meet(otherFarmer);
                                }
                            }
                        }
                    }
                    //if it's 12:xx and no invitation to the pub has been sent and farmer has enough energy:
                    if (gameTime.GetHour() == 12 && invitationSent == false && farmer->GetEnergy() > 55)
                    {
                        //Farmer send invitations to all other farmers
                        for (auto& otherFarmer : farmers)
                        {
                            if (farmer != otherFarmer)
                            {
                                std::string message = "Hi! You wanna join me at the pub by 20:00?";
                                farmer->SendMessage(*otherFarmer, message);
                            }
                        }
                        invitationSent = true;
                        std::cout << farmer->GetName() << " sent invitations to the pub." << std::endl;
                    }
                    //Reset invitationsSent
                    if (gameTime.GetHour() != 12)
                    {
                        invitationSent = false;
                    }
                    //At 19:30 all farmers notify the other that has accepted to go to the pub if they are to tierd to go or can't afford ale anyway
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
                    //build printouts for dead farmers
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
            farmers.erase
            (
                std::remove_if
                (
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
                if (numbersOfDeadFarmers == 1)
                {
                    std::cout << TimeOfDeath1 << std::endl;
                    std::cout << std::endl;
                }
                else if (numbersOfDeadFarmers == 2)
                {
                    std::cout << TimeOfDeath1 << std::endl;
                    std::cout << TimeOfDeath2 << std::endl;
                    std::cout << std::endl;
                }
                else if (numbersOfDeadFarmers == 3)
                {
                    std::cout << TimeOfDeath1 << std::endl;
                    std::cout << TimeOfDeath2 << std::endl;
                    std::cout << TimeOfDeath3 << std::endl;
                    std::cout << std::endl;
                }
                else if (numbersOfDeadFarmers == 4)
                {
                    std::cout << TimeOfDeath1 << std::endl;
                    std::cout << TimeOfDeath2 << std::endl;
                    std::cout << TimeOfDeath3 << std::endl;
                    std::cout << TimeOfDeath4 << std::endl;
                    std::cout << std::endl;
                }
                statsPrinted = true; // Mark stats as printed
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }

    return 0;
}
