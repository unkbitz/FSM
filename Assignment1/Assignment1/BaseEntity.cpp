#include <iostream>
#include "BaseEntity.h"

int BaseEntity::m_iNextValidID = 0;

void BaseEntity::SetID(int value)
{
	if (value >=  m_iNextValidID)
	{
		m_ID = value;
		m_iNextValidID = value + 1;
	}
	else
	{
		throw std::invalid_argument("ID not valid");
	}
}