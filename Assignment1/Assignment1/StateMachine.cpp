#include <cassert>
#include "State.h"

template <class entity_type>
class StateMachine
{
private:
	//a pointer to the agent that owns this instance
	entity_type* m_pOwner;
	State<entity_type>* m_pCurrentState;

public:
	StateMachine(entity_type* owner) :m_pOwner(owner),
		m_pCurrentState(NULL)
	{}

	void SetCurrentState(State<entity_type>* s) { m_pCurrentState = s; }

	void Update()const
	{
		//same for the current state
		if (m_pCurrentState) this->m_pCurrentState->Execute(m_pOwner);
	}
	void ChangeState(State<entity_type>* pNewState)
	{
		if (!pNewState || pNewState == m_pCurrentState) return;

		if (m_pCurrentState) {
			m_pCurrentState->Exit(m_pOwner);
		}

		m_pCurrentState = pNewState;

		if (m_pCurrentState) {
			m_pCurrentState->Enter(m_pOwner);
		}
	}

	State<entity_type>* CurrentState() const { return this->m_pCurrentState; }
};