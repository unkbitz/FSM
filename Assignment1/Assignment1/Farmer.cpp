#include "StateFactory.h"
#include <cassert>

Farmer::Farmer(int ID, std::string name, int startCondition) :
	m_icart(0),
	m_name(name),
	m_imilkLeft(10),
	m_icropsLeft(10),
	m_lastLocation(&cottage),
	m_location(&barn),
	m_iGoldCoins(15),
	m_fThirst(2 * startCondition),
	m_fHunger(1 * startCondition),
	m_fEnergy(10 * startCondition),
	m_fieldHasResource(true),
	m_barnHasResource(true),
	m_invitationAccepted(false),
	m_hasBeenGreeted(false),
	BaseEntity(ID),
	m_pCurrentState(EnterBarnAndMilkTheCows::Instance()),
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
	{"EnterBarnAndMilkTheCows", "CartFull", "VisitMarketAndSell"},
	{"EnterBarnAndMilkTheCows", "Hungry", "GoHomeAndEat"},
	{"EnterBarnAndMilkTheCows", "Thirsty", "QuenchThirst"},
	{"EnterBarnAndMilkTheCows", "Tired", "GoHomeAndSleepTilRested"},
	{"EnterBarnAndMilkTheCows", "NightTime", "GoHomeAndSleepTilRested"},  
	{"EnterBarnAndMilkTheCows", "OutOfResources", "VisitMarketAndSell"},  
	{"EnterBarnAndMilkTheCows", "OutOfResourcesFieldAvailable", "AtTheFieldsHarvesting"},
	{"EnterBarnAndMilkTheCows", "TimeForFun", "AtThePubWithFriends"},
	{"EnterBarnAndMilkTheCows", "TimeToRest", "GoHomeAndChill"},
	{"EnterBarnAndMilkTheCows", "Stay", "EnterBarnAndMilkTheCows"},

	{"AtTheFieldsHarvesting", "CartFull", "VisitMarketAndSell"},
	{"AtTheFieldsHarvesting", "Hungry", "GoHomeAndEat"},
	{"AtTheFieldsHarvesting", "Thirsty", "QuenchThirst"},
	{"AtTheFieldsHarvesting", "Tired", "GoHomeAndSleepTilRested"},
	{"AtTheFieldsHarvesting", "NightTime", "GoHomeAndSleepTilRested"},
	{"AtTheFieldsHarvesting", "OutOfResources", "VisitMarketAndSell"},
	{"AtTheFieldsHarvesting", "TimeForFun", "AtThePubWithFriends"},
	{"AtTheFieldsHarvesting", "TimeToRest", "GoHomeAndChill"},
	{"AtTheFieldsHarvesting", "OutOfResourcesBarnAvailable", "EnterBarnAndMilkTheCows"},
	{"AtTheFieldsHarvesting", "Stay", "AtTheFieldsHarvesting"},

	{"VisitMarketAndSell", "Hungry", "GoHomeAndEat"},
	{"VisitMarketAndSell", "Thirsty", "QuenchThirst"},
	{"VisitMarketAndSell", "Tired", "GoHomeAndSleepTilRested"},
	{"VisitMarketAndSell", "NightTime", "GoHomeAndSleepTilRested"},
	{"VisitMarketAndSell", "TimeForFun", "AtThePubWithFriends"},
	{"VisitMarketAndSell", "SoldAll->Milk", "EnterBarnAndMilkTheCows"},
	{"VisitMarketAndSell", "SoldAll->Crops", "AtTheFieldsHarvesting"},
	{"VisitMarketAndSell", "TimeToRest", "GoHomeAndChill"},
	{"VisitMarketAndSell", "Stay", "VisitMarketAndSell"},

	{"VisitMarketAndBuy", "Hungry", "GoHomeAndEat"},
	{"VisitMarketAndBuy", "Thirsty", "QuenchThirst"},
	{"VisitMarketAndBuy", "Tired", "GoHomeAndSleepTilRested"},
	{"VisitMarketAndBuy", "NightTime", "GoHomeAndSleepTilRested"},
	{"VisitMarketAndBuy", "CartFull", "VisitMarketAndSell"},
	{"VisitMarketAndBuy", "DoneShoping->Milk", "EnterBarnAndMilkTheCows"},
	{"VisitMarketAndBuy", "DoneShoping->Crops", "AtTheFieldsHarvesting"},
	{"VisitMarketAndBuy", "TimeForFun", "AtThePubWithFriends"},
	{"VisitMarketAndBuy", "TimeToRest", "GoHomeAndChill"},
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
	{"GoHomeAndEat", "TimeForFun", "AtThePubWithFriends"},
	{"VisitMarketAndSell", "TimeToRest", "GoHomeAndChill"},
	{"GoHomeAndEat", "Stay", "GoHomeAndEat"},

	{"QuenchThirst", "Hungry", "GoHomeAndEat"},
	{"QuenchThirst", "Tired", "GoHomeAndSleepTilRested"},
	{"QuenchThirst", "NightTime", "GoHomeAndSleepTilRested"},
	{"QuenchThirst", "UnThirstyBarnAvavible", "EnterBarnAndMilkTheCows"},
	{"QuenchThirst", "UnThirstyFieldAvavible", "AtTheFieldsHarvesting"},
	{"QuenchThirst", "UnthirstyGoodsToSel", "VisitMarketAndSell"},
	{"QuenchThirst", "CartFull", "VisitMarketAndSell"},
	{"QuenchThirst", "TimeForFun", "AtThePubWithFriends"},
	{"VisitMarketAndSell", "TimeToRest", "GoHomeAndChill"},
	{"QuenchThirst", "Stay", "QuenchThirst"},

	{"GoHomeAndSleepTilRested", "Rested", "EnterBarnAndMilkTheCows"},
	{"GoHomeAndSleepTilRested", "Hungry", "GoHomeAndEat"},
	{"GoHomeAndSleepTilRested", "Thirsty", "QuenchThirst"},
	{"GoHomeAndSleepTilRested", "CartFull", "VisitMarketAndSell"},
	{"GoHomeAndSleepTilRested", "Stay", "GoHomeAndSleepTilRested"},
	{"GoHomeAndSleepTilRested", "NightTime", "GoHomeAndSleepTilRested"},

	{"GoHomeAndChill", "Hungry", "GoHomeAndEat"},
	{"GoHomeAndChill", "Thirsty", "QuenchThirst"},
	{"GoHomeAndChill", "Tired", "GoHomeAndSleepTilRested"},
	{"GoHomeAndChill", "Stay", "GoHomeAndChill"},
	{"GoHomeAndChill", "NightTime", "GoHomeAndSleepTilRested"},

	{"AtThePubWithFriends", "HungryAndRich", "BuyPie"},
	{"AtThePubWithFriends", "Hungry", "GoHomeAndEat"},
	{"AtThePubWithFriends", "ThirstyAndRich", "BuyAle"},
	{"AtThePubWithFriends", "Thirsty", "QuenchThirst"},
	{"AtThePubWithFriends", "Tired", "GoHomeAndSleepTilRested"},
	{"AtThePubWithFriends", "NightTime", "GoHomeAndSleepTilRested"},
	{"AtThePubWithFriends", "TimeForFun", "AtThePubWithFriends"},

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
	else if (m_pCurrentState == GoHomeAndChill::Instance())
	{
		return "GoHomeAndChill";
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

	if (this->GetHunger() > 38 || this->GetThirst() > 28)
	{
		this->ChangeState(Dead::Instance());
	}
	else if (gameTime.GetHour() == 20 && gameTime.GetMinute() == 0 && this->m_invitationAccepted == true)
	{
		event = "TimeForFun";
	}
	else if (gameTime.GetHour() >= 22 || gameTime.GetHour() < 6)
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

}

std::string Farmer::getNextState(const std::string& currentState, const std::string& event)
{
	for (const auto& transition : m_stateTransitionTable)
	{
		// Check if the current state and event match the transition table entry
		if (transition.currentState == currentState && transition.event == event)
		{
			return transition.nextState;
		}
	}
	// If no transition is found, return the current state
	return currentState;
}

void Farmer::ChangeLocation(Location* newLocation)
{
	m_hasBeenGreeted = false;
	m_lastLocation = m_location;
	m_location = newLocation;
}

void Farmer::SendMessage(Farmer& recipient, const std::string& message) const
{
	recipient.ReceiveMessage(m_name + ": " + message);
}

void Farmer::ReceiveMessage(const std::string& message)
{
	m_messages.push(message);
}

void Farmer::ProcessMessages(std::vector<std::unique_ptr<Farmer>>& farmers)
{
	const std::string green = "\033[32m";
	const std::string resetColor = "\033[0m";
	while (!m_messages.empty())
	{
		std::string message = m_messages.front();
		m_messages.pop();
		std::cout << green << m_name << " reviced a message: " << message << resetColor << std::endl;

		if (message.find("Hi! You wanna join me at the pub by 20:00?") != std::string::npos)
		{
			if (m_fEnergy > 55)
			{
				std::string responce = "Sure, I'll join you!";

				this->SetInvitationAccepted(true);
				std::string inviterName = message.substr(0, message.find(':'));
				for (auto& farmer : farmers)
				{
					if (farmer->GetName() == inviterName)
					{
						SendMessage(*farmer, responce);
						farmer->SetInvitationAccepted(true);
						std::cout << green << this->GetName() << " answered " << farmer->GetName() << resetColor << std::endl;
						break;
					}
				}
			}
			else
			{
				this->SetInvitationAccepted(false);
				std::string responce = "Sorry, I can't make it.";

				std::string inviterName = message.substr(0, message.find(':'));
				for (auto& farmer : farmers)
				{
					if (farmer->GetName() == inviterName)
					{
						SendMessage(*farmer, responce);
						std::cout << green << this->GetName() << " answered " << farmer->GetName() << resetColor << std::endl;
						break;
					}
				}
			}
		}

		if (message.find("Sorry, but I am exhasted, I'll stay at home.") != std::string::npos ||
			message.find("Sorry, but I can't afford to come tonight.") != std::string::npos)
		{
			if (m_fEnergy < 5)
			{
				std::string responce = "That's okey! I was to tierd to go anyway!";

				this->SetInvitationAccepted(false);
				std::string inviterName = message.substr(0, message.find(':'));
				for (auto& farmer : farmers)
				{
					if (farmer->GetName() == inviterName)
					{
						SendMessage(*farmer, responce);
						farmer->SetInvitationAccepted(false);
						std::cout << green << this->GetName() << " answered " << farmer->GetName() << resetColor << std::endl;
						break;
					}
				}
			}
			else if (m_iGoldCoins < 10)
			{
				std::string responce = "That's okey! I can't go either!";

				this->SetInvitationAccepted(false);
				std::string inviterName = message.substr(0, message.find(':'));
				for (auto& farmer : farmers)
				{
					if (farmer->GetName() == inviterName)
					{
						SendMessage(*farmer, responce);
						farmer->SetInvitationAccepted(false);
						std::cout << green << this->GetName() << " answered " << farmer->GetName() << resetColor << std::endl;
						break;
					}
				}
			}
			else if (Only1Going(farmers) == true)
			{
				std::string responce = "That's okey! I'll stay at home as well, otherwise I'd be going alone.";

				this->SetInvitationAccepted(false);
				std::string inviterName = message.substr(0, message.find(':'));
				for (auto& farmer : farmers)
				{
					if (farmer->GetName() == inviterName)
					{
						SendMessage(*farmer, responce);
						farmer->SetInvitationAccepted(false);

						std::cout << green << this->GetName() << " answered " << farmer->GetName() << resetColor << std::endl;
						break;
					}
				}
			}
			else
			{
				this->SetInvitationAccepted(true);
				std::string responce = "Okey, hope you can come some other time!";

				std::string inviterName = message.substr(0, message.find(':'));
				for (auto& farmer : farmers)
				{
					if (farmer->GetName() == inviterName)
					{
						SendMessage(*farmer, responce);
						farmer->SetInvitationAccepted(false);
						std::cout << green << this->GetName() << " answered " << farmer->GetName() << resetColor << std::endl;
						break;
					}
				}
			}
		}
	}
}

void Farmer::Meet(std::unique_ptr<Farmer>& otherFarmer)
{
	otherFarmer->m_hasBeenGreeted = true;
	const std::string brightBlue = "\033[94m";
	const std::string resetColor = "\033[0m";

	if (this->GetLocation()->GetName() == "Cottage")
	{
		std::cout << brightBlue << this->GetName() << ": 'Hey " << otherFarmer->GetName() << "!'" << resetColor << std::endl;
		std::cout << brightBlue << otherFarmer->GetName() << ": 'Hey " << this->GetName() << "!'" << resetColor << std::endl;
	}
	else if (this->GetLocation()->GetName() == "Barn")
	{
		std::cout << brightBlue << this->GetName() << ": 'Hey " << otherFarmer->GetName() << "! Hard work today!'" << resetColor << std::endl;
		std::cout << brightBlue << otherFarmer->GetName() << ": 'Every day, " << this->GetName() << "!'" << resetColor << std::endl;
	}
	else if (this->GetLocation()->GetName() == "Market")
	{
		std::cout << brightBlue << this->GetName() << ": 'Hey " << otherFarmer->GetName() << "! What a coincidence to run into you at the market!?'" << resetColor << std::endl;
		if (otherFarmer->GetNameOfCurrentState() == "VisitMarketAndSell")
		{
			std::cout << brightBlue << otherFarmer->GetName() << ": 'Yes, I am here to sell goods, what brought you here, " << this->GetName() << "?'" << resetColor << std::endl;
			if (this->GetNameOfCurrentState() == "VisitMarketAndSell")
			{
				std::cout << brightBlue << this->GetName() << ": 'Same as you, my friend!'" << resetColor << std::endl;
			}
			else
			{
				std::cout << brightBlue << this->GetName() << ": 'I am doing some food shopping.'" << resetColor << std::endl;
			}
		}
		if (otherFarmer->GetNameOfCurrentState() == "VisitMarketAndBuy")
		{
			std::cout << brightBlue << otherFarmer->GetName() << ": 'Yes, I am here to buy more food, what brought you here, " << this->GetName() << "?'" << resetColor << std::endl;
			if (this->GetNameOfCurrentState() == "VisitMarketAndBuy")
			{
				std::cout << brightBlue << this->GetName() << ": 'Same as you, my friend!'" << resetColor << std::endl;
			}
			else
			{
				std::cout << brightBlue << this->GetName() << ": 'I am selling some goods.'" << resetColor << std::endl;
			}
		}
	}
	else if (this->GetLocation()->GetName() == "Field")
	{
		std::cout << brightBlue << this->GetName() << ": 'Hey " << otherFarmer->GetName() << "! The sun is hot today!'" << resetColor << std::endl;
		std::cout << brightBlue << otherFarmer->GetName() << ": 'Yes it is, but rather that than rain! Don't you think, " << this->GetName() << "?'" << resetColor << std::endl;
		std::cout << brightBlue << this->GetName() << ": 'True!'" << resetColor << std::endl;
	}
	else if (this->GetLocation()->GetName() == "Well")
	{
		std::cout << brightBlue << this->GetName() << ": 'Hey " << otherFarmer->GetName() << "! Don't we have the best water one can imagine?'" << resetColor << std::endl;
		std::cout << brightBlue << otherFarmer->GetName() << ": 'Most certainly, " << this->GetName() << "!'" << resetColor << std::endl;
	}
	else if (this->GetLocation()->GetName() == "Pub")
	{
		std::cout << brightBlue << this->GetName() << ": 'Hey " << otherFarmer->GetName() << "! How glad I am to see you here tonight!'" << resetColor << std::endl;
		std::cout << brightBlue << otherFarmer->GetName() << ": 'Yeah, we both deserve this! Right, " << this->GetName() << "?'" << resetColor << std::endl;
		std::cout << brightBlue << this->GetName() << ": 'Indeed, my friend!'" << resetColor << std::endl;
	}

	this->changeLastLocation(this->GetLocation());
	otherFarmer->changeLastLocation(otherFarmer->GetLocation());
}



bool Farmer::CartIsFull() const
{
	if (m_icart > 11)
	{
		return true;
	}
	return false;
}

bool Farmer::Only1Going(std::vector<std::unique_ptr<Farmer>>& farmers)
{
	bool Only1Going = false;
	int peopleGoing = 0;
	for (auto& farmer : farmers)
	{
		if (farmer->InvitationAccepted())
		{
			peopleGoing++;
		}
	}
	if (peopleGoing > 1)
	{
		Only1Going = false;
	}
	else
	{
		Only1Going = true;
		this->SetInvitationAccepted(false);
	}
	return Only1Going;
}