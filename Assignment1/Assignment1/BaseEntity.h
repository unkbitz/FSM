#pragma once
#include "GameTime.h"
class BaseEntity
{
private:
	int m_ID;
	static int m_iNextValidID;
	void SetID(int val);

public:
	BaseEntity(int id)
	{
		SetID(id);
	}
	virtual ~BaseEntity() {}
	virtual void Update(GameTime gameTime) = 0;
	int ID()const { return m_ID; }
 };