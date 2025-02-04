#pragma once
#include "State.h"
#include "Farmer.h"

class AtThePubWithFriends : public State<Farmer>
{
private:
	AtThePubWithFriends() {}
public:
	static AtThePubWithFriends* Instance();
	virtual void Enter(Farmer* pFarmer);
	virtual void Execute(Farmer* pFarmer);
	virtual void Exit(Farmer* pFarmer, std::string nextState);
	virtual std::string GetEvent(Farmer* pFarmer);
	virtual std::string GetName() const { return "AtThePubWithFriends"; }
};