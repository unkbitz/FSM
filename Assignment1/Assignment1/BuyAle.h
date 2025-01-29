#pragma once
#include "State.h"
#include "Farmer.h"

class BuyAle : public State<Farmer>
{
private:
	BuyAle() {}
	/* copy ctor and assignment op omitted */
public:
	//this is a singleton
	static BuyAle* Instance();
	virtual void Enter(Farmer* pFarmer);
	virtual void Execute(Farmer* pFarmer);
	virtual void Exit(Farmer* pFarmer, std::string nextState);
	virtual std::string GetEvent(Farmer* pFarmer);
	virtual int GetTaskDuration() const;
	virtual std::string GetName() const { return "BuyAle"; }
};