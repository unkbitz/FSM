#pragma once
#include "State.h"
#include "Farmer.h"

class GoHomeAndChill : public State<Farmer>
{
private:
	GoHomeAndChill() {}
public:
	static GoHomeAndChill* Instance();
	virtual void Enter(Farmer* pFarmer);
	virtual void Execute(Farmer* pFarmer);
	virtual void Exit(Farmer* pFarmer, std::string nextState);
	virtual std::string GetEvent(Farmer* pFarmer);
	virtual std::string GetName() const { return "GoHomeAndSleepTilRested"; }
};