#include "Farmer.h"
#include "Location.h"
#include "Dead.h"
#include "GoHomeAndSleepTilRested.h"
#include "FarmerGlobalState.h"
#include <cassert>

Farmer::Farmer(int ID, std::string name) :
	m_icart(0),
	m_iJugs(0),
	m_name(name),
	m_imilkLeft(10),
	m_icropsLeft(10),
	m_Location(&cottage),
	m_ftaskTimer(0.0f),
	m_iGoldCoins(15),
	m_fThirst(0),
	m_fHunger(0),
	m_fEnergy(40),
	m_fieldHasResource(true),
	m_barnHasResource(true),
	BaseEntity(ID),
	m_pCurrentState(GoHomeAndSleepTilRested::Instance()),
	m_pPreviousState(GoHomeAndSleepTilRested::Instance()),
	m_pGlobalState(FarmerGlobalState::Instance())
{
	//set up state machine
	m_pStateMachine = new StateMachine<Farmer>(this);
	m_pStateMachine->SetCurrentState(GoHomeAndSleepTilRested::Instance());
	m_pStateMachine->SetGlobalState(FarmerGlobalState::Instance());
}

const std::vector<StateTransition> Farmer::stateTransitionTable = {
	{"EnterBarnAndMilkTheCows", "CartFull", "VisitMarketAndSell"},
	{"EnterBarnAndMilkTheCows", "Hungry", "GoHomeAndEat"},
	{"GoHomeAndEat", "FinishedEating", "EnterBarnAndMilkTheCows"},
};

std::string Farmer::GetNameOfCurrentState() const
{
	return typeid(*m_pCurrentState).name();
}

void Farmer::Update()
{
	if (m_pCurrentState == Dead::Instance()) {
		return; // Skip updates if the farmer is dead
	}

	if (m_pGlobalState)
	{
		m_pGlobalState->Execute(this);
	}
	if (m_pCurrentState)
	{
		m_pCurrentState->Execute(this);
	}

	IncreaseThirst(1);
	IncreaseHunger(1);
	DecreaseEnergy(1);
}

std::string Farmer::getNextState(const std::string& currentState, const std::string& event) {
	for (const auto& transition : stateTable) {
		if (transition.currentState == currentState && transition.event == event) {
			return transition.nextState;
		}
	}
	return currentState;  // Return the current state if no transition is found
}

void Farmer::ChangeState(State<Farmer>* pNewState)
{
	//std::cout << "Transitioning from "
	//	<< (m_pCurrentState ? typeid(*m_pCurrentState).name() : "null")
	//	<< " to "
	//	<< (pNewState ? typeid(*pNewState).name() : "null") << std::endl;

	assert(m_pCurrentState && pNewState);

	if (m_Location->GetName() != "Well" && m_Location->GetName() != "Cottage" && m_Location->GetName() != "Pub")
	{
		m_pPreviousState = m_pCurrentState;
	}
	//std::cout << "Setting previous state to: " << typeid(*m_pPreviousState).name() << std::endl;
	m_pCurrentState->Exit(this);
	m_pCurrentState = pNewState;
	m_pCurrentState->Enter(this);
}

void Farmer::RevertToPreviousState()
{
	ChangeState(m_pPreviousState);
}

void Farmer::ChangeLocation(Location* newLocation)
{
	m_Location = newLocation;
}

bool Farmer::CartIsFull() const
{
	if (m_icart > 11)
	{
		return true;
	}
	return false;
}

void Farmer::AddGoodsToCart()
{
	m_icart += 1;
}

void Farmer::EmptyCart()
{
	m_icart = 0;
}

void Farmer::DecreaseEnergy(float energyLoss)
{
	m_fEnergy -= energyLoss;
}

void Farmer::IncreaseThirst(float fluidLoss)
{
	m_fThirst += fluidLoss;
}

void Farmer::IncreaseHunger(float kcalLoss)
{
	m_fHunger += kcalLoss;
}

void Farmer::EarnGoldCoins(int coinsEarned)
{
	m_iGoldCoins += coinsEarned;
}

void Farmer::SpendGoldCoins(int coinsSpent)
{
	m_iGoldCoins -= coinsSpent;
}

void Farmer::SetFieldHasResource(bool hasResource)
{
	m_fieldHasResource = hasResource;
}
void Farmer::SetBarnHasResource(bool hasResource)
{
	m_barnHasResource = hasResource;
}

void Farmer::Drink(int thirstDecreased) 
{
	m_fThirst -= thirstDecreased;
}

void Farmer::Sleep(int energyRegained)
{
	m_fEnergy += energyRegained;
}

void Farmer::Eat(int hungerDeccreased)
{
	m_fHunger -= hungerDeccreased;
}
