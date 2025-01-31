#include <iostream>
#include "StateFactory.h"

State<Farmer>* StateFactory::GetState(const std::string& stateName) 
{
    if (stateName == "EnterBarnAndMilkTheCows") return EnterBarnAndMilkTheCows::Instance();
    if (stateName == "GoHomeAndSleepTilRested") return GoHomeAndSleepTilRested::Instance();
    if (stateName == "AtTheFieldsHarvesting") return AtTheFieldsHarvesting::Instance();
    if (stateName == "VisitMarketAndSell") return VisitMarketAndSell::Instance();
    if (stateName == "VisitMarketAndBuy") return VisitMarketAndBuy::Instance();
    if (stateName == "AtThePubWithFriends") return AtThePubWithFriends::Instance();
    if (stateName == "BuyAle") return BuyAle::Instance();
    if (stateName == "BuyPie") return BuyPie::Instance();
    if (stateName == "Dead") return Dead::Instance();
    if (stateName == "GoHomeAndEat") return GoHomeAndEat::Instance();
    if (stateName == "GoHomeAndChill") return GoHomeAndChill::Instance();
    if (stateName == "QuenchThirst") return QuenchThirst::Instance();

    return nullptr;
}

std::string StateFactory::GetStateName(const State<Farmer>* stateName)
{
    if (stateName == EnterBarnAndMilkTheCows::Instance()) return "EnterBarnAndMilkTheCows";
    if (stateName == GoHomeAndSleepTilRested::Instance()) return "GoHomeAndSleepTilRested";
    if (stateName == AtTheFieldsHarvesting::Instance()) return "AtTheFieldsHarvesting";
    if (stateName == VisitMarketAndSell::Instance()) return "VisitMarketAndSell";
    if (stateName == VisitMarketAndBuy::Instance()) return "VisitMarketAndBuy";
    if (stateName == AtThePubWithFriends::Instance()) return "AtThePubWithFriends";
    if (stateName == BuyAle::Instance()) return "BuyAle";
    if (stateName == BuyPie::Instance()) return "BuyPie";
    if (stateName == Dead::Instance()) return "Dead";
    if (stateName == GoHomeAndEat::Instance()) return "GoHomeAndEat";
    if (stateName == GoHomeAndChill::Instance()) return "GoHomeAndChill";
    if (stateName == QuenchThirst::Instance()) return "QuenchThirst";

    return "Statename not found";
}