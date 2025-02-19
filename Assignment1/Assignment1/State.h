#pragma once
#include <iostream>
#include <chrono>
#include <thread>

template<class entity_type>
class State
{
public:
	virtual ~State() {}
	//this will execute when the state is entered
	virtual void Enter(entity_type* entity) = 0;
	//this is called by the miner�s update function each update step
	virtual void Execute(entity_type* entity) = 0;
	//this will execute when the state is exited
	virtual void Exit(entity_type* entity, std::string nextState) = 0;
	virtual std::string GetEvent(entity_type* entity) = 0;
	virtual std::string GetName() const { return ""; }
};