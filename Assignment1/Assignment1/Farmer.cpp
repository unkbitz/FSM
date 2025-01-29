#include "StateFactory.h"
#include <cassert>

Farmer::Farmer(int ID, std::string name, int startCondition) :
	m_icart(0),
	m_iJugs(0),
	m_name(name),
	m_imilkLeft(10),
	m_icropsLeft(10),
	m_Location(&barn),
	m_ftaskTimer(0.0f),
	m_iGoldCoins(15),
	m_fThirst(2 * startCondition),
	m_fHunger(1 * startCondition),
	m_fEnergy(10 * startCondition),
	m_fieldHasResource(true),
	m_barnHasResource(true),
	BaseEntity(ID),
	m_pCurrentState(EnterBarnAndMilkTheCows::Instance()),
	m_pPreviousState(AtTheFieldsHarvesting::Instance()),
	m_pStateMachine(new StateMachine<Farmer>(this))
{
	//set up state machine
	m_pStateMachine->SetCurrentState(GoHomeAndSleepTilRested::Instance());
}

Farmer::~Farmer()
{
	if (m_pStateMachine)
	{
		delete m_pStateMachine;
		m_pStateMachine = nullptr;
	}
}

const std::vector<StateTransition> Farmer::m_stateTransitionTable = 
{
	{"EnterBarnAndMilkTheCows", "CartFull", "VisitMarketAndSell"},  //if the cart if full, go to the market
	{"EnterBarnAndMilkTheCows", "Hungry", "GoHomeAndEat"},  //if hungry go eat
	{"EnterBarnAndMilkTheCows", "Thirsty", "QuenchThirst"},  //if thirsty go drink
	{"EnterBarnAndMilkTheCows", "Tired", "GoHomeAndSleepTilRested"},  //if tired go sleep
	{"EnterBarnAndMilkTheCows", "NightTime", "GoHomeAndSleepTilRested"},  //if it's nighttime, go sleep
	{"EnterBarnAndMilkTheCows", "OutOfResources", "VisitMarketAndSell"},  //if the resources of the location runs out and the resources of the field is also out, go to market and sell goods
	{"EnterBarnAndMilkTheCows", "OutOfResourcesFieldAvailable", "AtTheFieldsHarvesting"},  //if the resources of the location runs out but there are still crops left in field, go to field and harvest
	{"EnterBarnAndMilkTheCows", "OutOfResourcesEmptyCart", "AtThePubWithFriends"},
	{"EnterBarnAndMilkTheCows", "DieFromThrist", "Dead"},
	{"EnterBarnAndMilkTheCows", "Stay", "EnterBarnAndMilkTheCows"},

	{"AtTheFieldsHarvesting", "CartFull", "VisitMarketAndSell"},
	{"AtTheFieldsHarvesting", "Hungry", "GoHomeAndEat"},
	{"AtTheFieldsHarvesting", "Thirsty", "QuenchThirst"},
	{"AtTheFieldsHarvesting", "Tired", "GoHomeAndSleepTilRested"},
	{"AtTheFieldsHarvesting", "NightTime", "GoHomeAndSleepTilRested"},
	{"AtTheFieldsHarvesting", "OutOfResources", "VisitMarketAndSell"},
	{"AtTheFieldsHarvesting", "OutOfResourcesEmptyCart", "AtThePubWithFriends"},
	{"AtTheFieldsHarvesting", "OutOfResourcesBarnAvailable", "EnterBarnAndMilkTheCows"},
	{"AtTheFieldsHarvesting", "Die", "Dead"},
	{"AtTheFieldsHarvesting", "Stay", "AtTheFieldsHarvesting"},

	{"VisitMarketAndSell", "Hungry", "GoHomeAndEat"},
	{"VisitMarketAndSell", "Thirsty", "QuenchThirst"},
	{"VisitMarketAndSell", "Tired", "GoHomeAndSleepTilRested"},
	{"VisitMarketAndSell", "NightTime", "GoHomeAndSleepTilRested"},
	{"VisitMarketAndSell", "SoldAll", "AtThePubWithFriends"},
	{"VisitMarketAndSell", "SoldAll->Milk", "EnterBarnAndMilkTheCows"},
	{"VisitMarketAndSell", "SoldAll->Crops", "AtTheFieldsHarvesting"},
	{"VisitMarketAndSell", "TimeForFun", "AtThePubWithFriends"},
	{"VisitMarketAndSell", "Die", "Dead"},
	{"VisitMarketAndSell", "Stay", "VisitMarketAndSell"},

	{"VisitMarketAndBuy", "Hungry", "GoHomeAndEat"},
	{"VisitMarketAndBuy", "Thirsty", "QuenchThirst"},
	{"VisitMarketAndBuy", "Tired", "GoHomeAndSleepTilRested"},
	{"VisitMarketAndBuy", "NightTime", "GoHomeAndSleepTilRested"},
	{"VisitMarketAndBuy", "CartFull", "VisitMarketAndSell"},
	{"VisitMarketAndBuy", "DoneShoping->Milk", "EnterBarnAndMilkTheCows"},
	{"VisitMarketAndBuy", "DoneShoping->Crops", "AtTheFieldsHarvesting"},
	{"VisitMarketAndBuy", "DoneShoping->Pub", "AtThePubWithFriends"},
	{"VisitMarketAndBuy", "TimeForFun", "AtThePubWithFriends"},
	{"VisitMarketAndBuy", "Die", "Dead"},
	{"VisitMarketAndBuy", "Stay", "VisitMarketAndBuy"},

	{"GoHomeAndEat", "Thirsty", "QuenchThirst"},
	{"GoHomeAndEat", "Tired", "GoHomeAndSleepTilRested"},
	{"GoHomeAndEat", "NightTime", "GoHomeAndSleepTilRested"},
	{"GoHomeAndEat", "FullBarnAvavible", "EnterBarnAndMilkTheCows"},
	{"GoHomeAndEat", "FullFieldAvavible", "AtTheFieldsHarvesting"},
	{"GoHomeAndEat", "CartFull", "VisitMarketAndSell"},
	{"GoHomeAndEat", "FullHaveGoodsToSell", "VisitMarketAndSell"},
	{"GoHomeAndEat", "OutOfResourcesAndGold", "VisitMarketAndSell"},
	{"GoHomeAndEat", "OutOfResources", "VisitMarketAndBuy"},
	{"GoHomeAndEat", "OutOfResourcesAndGoldAndNoGoodsInCart->Milk", "EnterBarnAndMilkTheCows"},
	{"GoHomeAndEat", "OutOfResourcesAndGoldAndNoGoodsInCart->Crops", "AtTheFieldsHarvesting"},
	{"GoHomeAndEat", "Full", "AtThePubWithFriends"},
	{"GoHomeAndEat", "Stay", "GoHomeAndEat"},

	{"QuenchThirst", "Hungry", "GoHomeAndEat"},
	{"QuenchThirst", "Tired", "GoHomeAndSleepTilRested"},
	{"QuenchThirst", "NightTime", "GoHomeAndSleepTilRested"},
	{"QuenchThirst", "UnThirstyBarnAvavible", "EnterBarnAndMilkTheCows"},
	{"QuenchThirst", "UnThirstyFieldAvavible", "AtTheFieldsHarvesting"},
	{"QuenchThirst", "UnthirstyGoodsToSel", "VisitMarketAndSell"},
	{"QuenchThirst", "CartFull", "VisitMarketAndSell"},
	{"QuenchThirst", "Unthirsty", "AtThePubWithFriends"},
	{"QuenchThirst", "Stay", "QuenchThirst"},

	{"GoHomeAndSleepTilRested", "Morning", "EnterBarnAndMilkTheCows"},
	{"GoHomeAndSleepTilRested", "Rested", "EnterBarnAndMilkTheCows"},
	{"GoHomeAndSleepTilRested", "Hungry", "GoHomeAndEat"},
	{"GoHomeAndSleepTilRested", "Thirsty", "QuenchThirst"},
	{"GoHomeAndSleepTilRested", "CartFull", "VisitMarketAndSell"},
	{"GoHomeAndSleepTilRested", "TimeForFun", "AtThePubWithFriends"},
	{"GoHomeAndSleepTilRested", "Stay", "GoHomeAndSleepTilRested"},
	{"GoHomeAndSleepTilRested", "NightTime", "GoHomeAndSleepTilRested"},

	{"AtThePubWithFriends", "HungryAndRich", "BuyPie"},
	{"AtThePubWithFriends", "Hungry", "GoHomeAndEat"},
	{"AtThePubWithFriends", "ThirstyAndRich", "BuyAle"},
	{"AtThePubWithFriends", "Thirsty", "QuenchThirst"},
	{"AtThePubWithFriends", "Tired", "GoHomeAndSleepTilRested"},
	{"AtThePubWithFriends", "NightTime", "GoHomeAndSleepTilRested"},
	{"AtThePubWithFriends", "TimeForFun", "AtThePubWithFriends"},
	{"AtThePubWithFriends", "Die", "Dead"},

	{"BuyPie", "Full", "AtThePubWithFriends"},
	{"BuyPie", "OutOfGold", "GoHomeAndEat"},
	{"BuyPie", "Stay", "BuyPie"},
	{"BuyPie", "NightTime", "GoHomeAndSleepTilRested"},

	{"BuyAle", "Unthirsty", "AtThePubWithFriends"},
	{"BuyAle", "OutOfGold", "QuenchThirst"},
	{"BuyAle", "Stay", "BuyAle"},
	{"BuyAle", "NightTime", "GoHomeAndSleepTilRested"},
};

std::string Farmer::GetNameOfCurrentState() const
{
	if (m_pCurrentState == BuyAle::Instance()) 
	{
		return "BuyAle";
	}
	else if (m_pCurrentState == BuyPie::Instance()) 
	{
		return "BuyPie";
	}
	else if (m_pCurrentState == AtTheFieldsHarvesting::Instance()) 
	{
		return "AtTheFieldsHarvesting";
	}
	else if (m_pCurrentState == EnterBarnAndMilkTheCows::Instance()) 
	{
		return "EnterBarnAndMilkTheCows";
	}
	else if (m_pCurrentState == AtThePubWithFriends::Instance()) 
	{
		return "AtThePubWithFriends";
	}
	else if (m_pCurrentState == GoHomeAndSleepTilRested::Instance()) 
	{
		return "GoHomeAndSleepTilRested";
	}
	else if (m_pCurrentState == VisitMarketAndSell::Instance()) 
	{
		return "VisitMarketAndSell";
	}
	else if (m_pCurrentState == VisitMarketAndBuy::Instance()) 
	{
		return "VisitMarketAndBuy";
	}
	else if (m_pCurrentState == QuenchThirst::Instance()) 
	{
		return "QuenchThirst";
	}
	else if (m_pCurrentState == GoHomeAndEat::Instance()) 
	{
		return "GoHomeAndEat";
	}
	else if (m_pCurrentState == Dead::Instance()) 
	{
		return "Dead";
	}
	return "Unknown";
}

void Farmer::Update(GameTime gameTime)
{
	if (this->m_pCurrentState == Dead::Instance()) 
	{
		return; // Skip updates if the farmer is dead
	}

	std::string event = "";
	if (gameTime.GetHour() >= 22 || gameTime.GetHour() < 6)
	{
		event = "NightTime";
		Location* Current = this->GetLocation();
		this->ChangeLocation(&field);
		if (this->GetLocation()->GetResources() != 30)
		{
			int amount = this->GetLocation()->GetCropsMax();
			this->GetLocation()->ReplennishReshources(amount);
			this->GetLocation()->SetHasResources();
			this->SetFieldHasResource(true);
		}
		this->ChangeLocation(&barn);
		if (this->GetLocation()->GetResources() != 25)
		{
			int amount = this->GetLocation()->GetMilkMax();
			this->GetLocation()->ReplennishReshources(amount);
			this->GetLocation()->SetHasResources();
			this->SetBarnHasResource(true);
		}
		this->ChangeLocation(Current);
	}
	else 
	{
		event = this->m_pCurrentState->GetEvent(this);
	}
	

	// Get the next state based on the current state and event
	std::string nextState = getNextState(GetNameOfCurrentState(), event);


	//std::cout << "Update: CurrentState=" << GetNameOfCurrentState()
	//	<< ", Event=" << event
	//	<< ", NextState=" << nextState << std::endl;

	if (nextState != GetNameOfCurrentState()) 
	{
		auto newState = StateFactory::GetState(nextState);
		ChangeState(newState);
	}

	// Execute the current state's logic
	this->m_pCurrentState->Execute(this);

	if (this->m_pCurrentState->GetName() != "GoHomeAndSleepTilRested")
	{
		IncreaseThirst(0.5f);
		IncreaseHunger(0.5f);
		DecreaseEnergy(0.7f);
	}

}

void Farmer::ChangeState(State<Farmer>* pNewState)
{
	if (!pNewState) 
	{
		std::cerr << "Error: Trying to change to a null state!" << std::endl;
		return;
	}

	if (m_pCurrentState == pNewState) 
	{
		// Prevent transitioning to the same state
		std::cout << "Farmer is already in state " << GetNameOfCurrentState() << std::endl;
		return;
	}

	// Exit the current state
	if (m_pCurrentState) 
	{
		m_pCurrentState->Exit(this, pNewState->GetName());
	}

	// Update the current state to the new state
	m_pCurrentState = pNewState;

	// Enter the new state
	m_pCurrentState->Enter(this);

	//std::cout << "Changed state to " << GetNameOfCurrentState() << std::endl;
}

std::string Farmer::getNextState(const std::string& currentState, const std::string& event) 
{
	for (const auto& transition : m_stateTransitionTable)
	{
		// Check if the current state and event match the transition table entry
		if (transition.currentState == currentState && transition.event == event)
		{
			//std::cout << "Transition: CurrentState=" << currentState
			//	<< ", Event=" << event
			//	<< ", NextState=" << transition.nextState << std::endl;
			return transition.nextState;
		}
	}
	// If no transition is found, return the current state
	return currentState;
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