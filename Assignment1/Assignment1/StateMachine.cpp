#include <cassert>
#include "State.h"

template <class entity_type>
class StateMachine
{
private:
	//a pointer to the agent that owns this instance
	entity_type* m_pOwner;
	State<entity_type>* m_pCurrentState;
	//a record of the last state the agent was in
	State<entity_type>* m_pPreviousState;
	//this state logic is called every time the FSM is updated
	State<entity_type>* m_pGlobalState;
public:
	StateMachine(entity_type* owner) :m_pOwner(owner),
		m_pCurrentState(NULL),
		m_pPreviousState(NULL),
		m_pGlobalState(NULL)
	{}
	//use these methods to initialize the FSM
	void SetCurrentState(State<entity_type>* s) { m_pCurrentState = s; }
	void SetGlobalState(State<entity_type>* s) { m_pGlobalState = s; }
	void SetPreviousState(State<entity_type>* s) { m_pPreviousState = s; }


	//call this to update the FSM
	void Update()const
	{
		//same for the current state
		if (m_pCurrentState) this->m_pCurrentState->Execute(m_pOwner);
	}
	//change to a new state
	void ChangeState(State<entity_type>* pNewState)
	{
		if (!pNewState || pNewState == m_pCurrentState) return; // Prevent null or redundant transitions

		if (m_pCurrentState) {
			m_pCurrentState->Exit(m_pOwner); // Call exit logic of the current state
		}

		m_pCurrentState = pNewState;

		if (m_pCurrentState) {
			m_pCurrentState->Enter(m_pOwner); // Call entry logic of the new state
		}
	}
	//change state back to the previous state
	void RevertToPreviousState()
	{
		ChangeState(m_pPreviousState);
	}
	//accessors
	State<entity_type>* CurrentState() const { return this->m_pCurrentState; }
	State<entity_type>* GlobalState() const { return this->m_pGlobalState; }
	State<entity_type>* PreviousState() const { return this->m_pPreviousState; }
	//returns true if the current state’s type is equal to the type of the
	//class passed as a parameter.
	bool isInState(const State<entity_type>& st)const;
};