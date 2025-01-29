#pragma once
#include "State.h"
#include "Farmer.h"

class GoHomeAndEat : public State<Farmer>
{
private:
	GoHomeAndEat() {}
	/* copy ctor and assignment op omitted */
public:
	//this is a singleton
	static GoHomeAndEat* Instance();
	virtual void Enter(Farmer* pFarmer);
	virtual void Execute(Farmer* pFarmer);
	virtual void Exit(Farmer* pFarmer, std::string nextState);
	virtual std::string GetEvent(Farmer* pFarmer);
	virtual int GetTaskDuration() const;
	virtual std::string GetName() const { return "GoHomeAndEat"; }
};