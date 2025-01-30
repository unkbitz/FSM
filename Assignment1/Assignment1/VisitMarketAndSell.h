#pragma once
#include "State.h"
#include "Farmer.h"

class VisitMarketAndSell : public State<Farmer>
{
private:
	VisitMarketAndSell() {}
	/* copy ctor and assignment op omitted */
public:
	//this is a singleton
	static VisitMarketAndSell* Instance();
	virtual void Enter(Farmer* pFarmer);
	virtual void Execute(Farmer* pFarmer);
	virtual void Exit(Farmer* pFarmer, std::string nextState);
	virtual std::string GetEvent(Farmer* pFarmer);
	virtual std::string GetName() const { return "VisitMarketAndSell"; }
};