#include "Location.h"

Location cottage("Cottage", true, 20);
Location barn("Barn", true, 80);
Location market("Market", true, 1);
Location field("Field", true, 80);
Location well("Well", true, 1);
Location pub("Pub", true, 1);
Location heaven("Heaven", true, 1);


Location::Location(const std::string& name, bool hasResources, int amountResouces) : 
    m_name(name), 
    m_hasResources(hasResources), 
    m_iResourcesLeft(amountResouces), 
    m_iCrops(80), 
    m_iMilk(80),
    m_iFood(20)  {}

std::string Location::GetName() const 
{
    return m_name;
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
