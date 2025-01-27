#pragma once
#include <string>
#include <cmath>

class Location 
{
private:
    std::string m_name;
    int m_x;
    int m_y;
    bool m_hasResources;
    int m_iResourcesLeft;

public:
    // Constructor
    Location(const std::string& name, int x, int y, bool hasResources, int amountResouces);

    // Getters
    std::string GetName() const;
    int GetX() const;
    int GetY() const;
    int GetResources() const;
    bool HasResources() const;

    // Setters
    void SetHasResources();
    void DecreaseResources();
    void ReplennishReshources(int amopunt);

    // Method to calculate distance between two locations
    double Distance(const Location& other) const;
};

extern Location cottage;
extern Location barn;
extern Location market;
extern Location field;
extern Location well;
extern Location pub;
