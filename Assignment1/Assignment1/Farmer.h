#pragma once
#include <vector>
#include <string>
#include "BaseEntity.h"
#include "State.h"
#include "Location.h"
#include "StateMachine.cpp"

struct StateTransition {
	std::string currentState;
	std::string event;
	std::string nextState;
};

class Farmer : public BaseEntity
{
private:
	static const std::vector<StateTransition> stateTransitionTable;
	StateMachine<Farmer>* m_pStateMachine;
	std::string m_name;
	//std::string m_cowName;
	int m_imilkLeft;
	int m_icropsLeft;
	Location* m_Location;
	float m_ftaskTimer;

	//a pointer to an instance of a State
	State<Farmer>* m_pCurrentState;
	State<Farmer>* m_pPreviousState;
	State<Farmer>* m_pGlobalState;
	
	bool m_fieldHasResource;
	bool m_barnHasResource;
	int m_iGoldCoins;
	int m_icart;
	int m_iJugs;
	float m_fHunger;//the higher the value, the hungrier the agent
	float m_fThirst;//the higher the value, the thirstier the agent
	float m_fEnergy;//the lower the value, the more tired the agent

public:
	Farmer(int ID, std::string name);
	~Farmer() { delete m_pStateMachine; }

	void Update();
	void ChangeState(State<Farmer>* pNewState);
	void RevertToPreviousState();
	void ChangeLocation(Location* newLocation);
	std::string getNextState(const std::string& currentState, const std::string& event);

	// Getters
	StateMachine<Farmer>* GetFSM()const { return m_pStateMachine; }
	Location* GetLocation() const { return m_Location; }
	State<Farmer>*  GetPreviousState() const { return m_pPreviousState; }
	std::string GetName() const { return m_name; }
	std::string GetNameOfCurrentState() const;
	float GetThirst() const { return m_fThirst; }
	float GetHunger() const { return m_fHunger; }
	float GetEnergy() const { return m_fEnergy; }
	int GetGoodsInCart() const { return m_icart; }
	int GetGoldCoins() const { return m_iGoldCoins; }
	int GetNumberOfJugs() const { return m_iJugs; }

	// Setters
	void SetName(const std::string& name) { m_name = name; }
	void AddGoodsToCart();
	void DecreaseEnergy(float energyLoss);
	void EmptyCart();
	void SetBarnHasResource(bool hasResource);
	void SetFieldHasResource(bool hasResource);
	void Drink(int thirstDecreased);
	void Sleep(int energyRegained);
	void Eat(int hungerDeccreased);
	void IncreaseThirst(float fluidLoss);
	void IncreaseHunger(float kcalLoss);
	void EarnGoldCoins(int coinsEarned);
	void SpendGoldCoins(int coinsSpent);

	// Bools
	bool CartIsFull() const;
	bool Thirsty() const { return m_fThirst > 18; }
	bool Tierd() const { return m_fEnergy < 5; }
	bool Hungry() const { return m_fHunger > 28; }
	bool FieldHasResource() const { return m_fieldHasResource; }
	bool BarnHasResource() const { return m_barnHasResource; }
};