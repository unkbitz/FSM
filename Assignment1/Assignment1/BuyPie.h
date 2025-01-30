#pragma once
#include "State.h"
#include "Farmer.h"

class BuyPie : public State<Farmer>
{
private:
	BuyPie() {}
	/* copy ctor and assignment op omitted */
public:
	//this is a singleton
	static BuyPie* Instance();
	virtual void Enter(Farmer* pFarmer);
	virtual void Execute(Farmer* pFarmer);
	virtual void Exit(Farmer* pFarmer, std::string nextState);
	virtual std::string GetEvent(Farmer* pFarmer);
	virtual std::string GetName() const { return "BuyPie"; }
};