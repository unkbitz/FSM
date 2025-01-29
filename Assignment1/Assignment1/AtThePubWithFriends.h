#pragma once
#include "State.h"
#include "Farmer.h"

class AtThePubWithFriends : public State<Farmer>
{
private:
	AtThePubWithFriends() {}
	/* copy ctor and assignment op omitted */
public:
	static AtThePubWithFriends* Instance();
	virtual void Enter(Farmer* pFarmer);
	virtual void Execute(Farmer* pFarmer);
	virtual void Exit(Farmer* pFarmer, std::string nextState);
	virtual std::string GetEvent(Farmer* pFarmer);
	virtual int GetTaskDuration() const;
	virtual std::string GetName() const { return "AtThePubWithFriends"; }
};