#pragma once
#include "State.h"
#include "Farmer.h"

class EnterBarnAndMilkTheCows : public State<Farmer>
{
private:
	EnterBarnAndMilkTheCows() {}
	/* copy ctor and assignment op omitted */
public:
	static EnterBarnAndMilkTheCows* Instance();
	virtual void Enter(Farmer* pFarmer);
	virtual void Execute(Farmer* pFarmer);
	virtual void Exit(Farmer* pFarmer);
	virtual float GetTaskDuration() const;
};