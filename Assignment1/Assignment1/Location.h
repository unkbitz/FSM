#pragma once
#include <string>
#include <cmath>

class Location 
{
private:
    std::string m_name;
    bool m_hasResources;
    int m_iResourcesLeft;
    int m_iFood;
    int m_iCrops;
    int m_iMilk;

public:
    // Constructor
    Location(const std::string& name, bool hasResources, int amountResouces);

    // Getters
    std::string GetName() const;
    int GetResources() const;
    bool HasResources() const;
    int GetFoodMax() const;
    int GetCropsMax() const;
    int GetMilkMax() const;

    // Setters
    void SetHasResources();
    void DecreaseResources();
    void IncreaseResources(int amount);
    void ReplennishReshources(int amount);
};

extern Location cottage;
extern Location barn;
extern Location market;
extern Location field;
extern Location well;
extern Location pub;
extern Location heaven;
