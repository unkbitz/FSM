
#pragma once
#include "State.h"
#include "Farmer.h"

class Dead : public State<Farmer>
{
private:
	Dead() {}
	/* copy ctor and assignment op omitted */
public:
	//this is a singleton
	static Dead* Instance();
	virtual void Enter(Farmer* pFarmer);
	virtual void Execute(Farmer* pFarmer);
	virtual void Exit(Farmer* pFarmer);
	virtual float GetTaskDuration() const;
};