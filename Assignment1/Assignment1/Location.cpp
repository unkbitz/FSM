#include "Location.h"

Location cottage("Cottage", 0, 0, true, 20);
Location barn("Barn", 5, 5, true, 35);
Location market("Market", 15, 15, true, 1);
Location field("Field", 0, 10, true, 45);
Location well("Well", 2, 2, true, 1);
Location pub("Pub", 0, 0, true, 1);


Location::Location(const std::string& name, int x, int y, bool hasResources, int amountResouces)
    : m_name(name), m_x(x), m_y(y), m_hasResources(hasResources), m_iResourcesLeft(amountResouces) {}

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

void Location::ReplennishReshources(int amount)
{
    m_iResourcesLeft = amount;
}

// Calculate distance between two locations
double Location::Distance(const Location& other) const 
{
    return std::sqrt((m_x - other.m_x) * (m_x - other.m_x) +
        (m_y - other.m_y) * (m_y - other.m_y));
}
