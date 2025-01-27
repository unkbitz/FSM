#pragma once
#include "State.h"
#include "Farmer.h"
#include <iostream>

class FarmerGlobalState : public State<Farmer> {
public:
    static FarmerGlobalState* Instance();

    virtual void Enter(Farmer* pFarmer) {} // No specific action when entering the global state
    virtual void Execute(Farmer* pFarmer);
    virtual void Exit(Farmer* pFarmer) {} // No specific action when exiting the global state
    virtual float GetTaskDuration() const;
};
