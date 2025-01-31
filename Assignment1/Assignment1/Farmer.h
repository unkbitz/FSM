#pragma once
#include <vector>
#include <string>
#include "BaseEntity.h"
#include "State.h"
#include "Location.h"
#include "StateMachine.cpp"
#include <queue>
#include <iostream>

struct StateTransition {
	std::string currentState;
	std::string event;
	std::string nextState;
};

class Farmer : public BaseEntity
{
private:
	static const std::vector<StateTransition> m_stateTransitionTable;
	StateMachine<Farmer>* m_pStateMachine;
	std::string m_name;
	std::queue<std::string> m_messages;
	//std::string m_cowName;
	int m_imilkLeft;
	int m_icropsLeft;
	Location* m_location;
	Location* m_lastLocation;

	//a pointer to an instance of a State
	State<Farmer>* m_pCurrentState;

	bool m_fieldHasResource;
	bool m_barnHasResource;
	bool m_invitationAccepted;
	bool m_hasBeenGreeted;
	int m_iGoldCoins;
	int m_icart;
	float m_fHunger;//the higher the value, the hungrier the agent
	float m_fThirst;//the higher the value, the thirstier the agent
	float m_fEnergy;//the lower the value, the more tired the agent

public:
	Farmer(int ID, std::string name, int startCondition);
	~Farmer();

	void Update(GameTime gameTime);
	void ChangeState(State<Farmer>* pNewState);
	void ChangeLocation(Location* newLocation);
	void changeLastLocation(Location* Location) { m_lastLocation = Location; }
	void SendMessage(Farmer& recipient, const std::string& message) const;
	void ReceiveMessage(const std::string& message);
	void ProcessMessages(std::vector<std::unique_ptr<Farmer>>& farmers);
	void Meet(std::unique_ptr<Farmer>& otherFarmer);
	std::string getNextState(const std::string& currentState, const std::string& event);

	// Getters
	StateMachine<Farmer>* GetFSM() const { return m_pStateMachine; }
	static std::vector<StateTransition> GetStateTransitionTable() { return m_stateTransitionTable; }
	Location* GetLocation() const { return m_location; }
	Location* GetLastLocation() const { return m_lastLocation; }
	std::string GetName() const { return m_name; }
	std::string GetNameOfCurrentState() const;
	float GetThirst() const { return m_fThirst; }
	float GetHunger() const { return m_fHunger; }
	float GetEnergy() const { return m_fEnergy; }
	int GetGoodsInCart() const { return m_icart; }
	int GetGoldCoins() const { return m_iGoldCoins; }

	// Setters
	void SetName(const std::string& name) { m_name = name; }
	void AddGoodsToCart() { m_icart += 1; }
	void DecreaseEnergy(float energyLoss) { m_fEnergy -= energyLoss; }
	void EmptyCart() { m_icart = 0; }
	void SetBarnHasResource(bool hasResource) { m_barnHasResource = hasResource; }
	void SetFieldHasResource(bool hasResource) { m_fieldHasResource = hasResource; }
	void SetHasBeenGreeted(bool hasBeenGreeted) { m_hasBeenGreeted = hasBeenGreeted; }
	void Drink() { m_fThirst = 0; }
	void SetThirst(int newThirstLevel) { m_fThirst = newThirstLevel; }
	void Sleep(int energyRegained) { m_fEnergy += energyRegained; }
	void Eat(int hungerDeccreased) { m_fHunger -= hungerDeccreased; }
	void IncreaseThirst(float fluidLoss) { m_fThirst += fluidLoss; }
	void IncreaseHunger(float kcalLoss) { m_fHunger += kcalLoss; }
	void EarnGoldCoins(int coinsEarned) { m_iGoldCoins += coinsEarned; }
	void SpendGoldCoins(int coinsSpent) { m_iGoldCoins -= coinsSpent; }
	void SetInvitationAccepted(bool canCome) { m_invitationAccepted = canCome; }

	// Bools
	bool CartIsFull() const;
	bool Thirsty() const { return m_fThirst > 23; }
	bool Tired() const { return m_fEnergy < 5; }
	bool Hungry() const { return m_fHunger > 32; }
	bool FieldHasResource() const { return m_fieldHasResource; }
	bool BarnHasResource() const { return m_barnHasResource; }
	bool InvitationAccepted() const { return m_invitationAccepted; }
	bool HasBeenGreeted() const { return m_hasBeenGreeted; }
	bool Only1Going(std::vector<std::unique_ptr<Farmer>>& farmers);
};