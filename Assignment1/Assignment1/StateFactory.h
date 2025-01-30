#pragma once
#include <iostream>
#include "State.h"
#include "Farmer.h"
#include "EnterBarnAndMilkTheCows.h"
#include "AtThePubWithFriends.h"
#include "GoHomeAndSleepTilRested.h"
#include "AtTheFieldsHarvesting.h"
#include "VisitMarketAndSell.h"
#include "Dead.h"
#include "GoHomeAndEat.h"
#include "QuenchThirst.h"
#include "VisitMarketAndBuy.h"
#include "BuyAle.h"
#include "BuyPie.h"

class StateFactory
{
public:
    static State<Farmer>* GetState(const std::string& stateName);
    static std::string GetStateName(const State<Farmer>* stateName);
};