#include "Location.h"

Location cottage("Cottage", 0, 0, true, 20);
Location barn("Barn", 5, 5, true, 80);
Location market("Market", 15, 15, true, 1);
Location field("Field", 0, 10, true, 80);
Location well("Well", 2, 2, true, 1);
Location pub("Pub", 0, 0, true, 1);


Location::Location(const std::string& name, int x, int y, bool hasResources, int amountResouces) : 
    m_name(name), 
    m_x(x), 
    m_y(y), 
    m_hasResources(hasResources), 
    m_iResourcesLeft(amountResouces), 
    m_iCrops(80), 
    m_iMilk(80),
    m_iFood(20)  {}

std::string Location::GetName() const 
{
    return m_name;
}

int Location::GetX() const 
{
    return m_x;
}

int Location::GetY() const 
{
    return m_y;
}

int Location::GetResources() const
{
    return m_iResourcesLeft;
}

int Location::GetFoodMax() const
{
    return m_iFood;
}

int Location::GetCropsMax() const
{
    return m_iCrops;
}

int Location::GetMilkMax() const
{
    return m_iMilk;
}

bool Location::HasResources() const 
{
    return m_hasResources;
}

void Location::SetHasResources()
{
    if (m_iResourcesLeft > 0)
    {
        m_hasResources = true;
    }
    else
    {
        m_hasResources = false;
    }
}

void Location::DecreaseResources()
{
    m_iResourcesLeft -= 1;
}

void Location::IncreaseResources(int amount)
{
    m_iResourcesLeft += amount;
}

void Location::ReplennishReshources(int amount)
{
    m_iResourcesLeft = amount;
}

int Location::GetTravelTimeTo(const Location& other) const {
    return std::abs(m_x - other.GetX()) + std::abs(m_y - other.GetY());
}