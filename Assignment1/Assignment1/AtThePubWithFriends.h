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
	virtual void Exit(Farmer* pFarmer);
	virtual float GetTaskDuration() const;
};