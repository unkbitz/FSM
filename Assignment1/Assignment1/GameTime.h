#pragma once
#include <iostream>

class GameTime {
private:
    int m_iHour;
    int m_iMinute;
    int m_iDay;
public:
    GameTime(int hour, int minute) : m_iHour(hour), m_iMinute(minute), m_iDay(1) {}
    void Update();
    std::string GetTimeString() const;
    int GetHour() const;
    int GetMinute() const;
};