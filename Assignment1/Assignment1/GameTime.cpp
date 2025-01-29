#include "GameTime.h"
#include <string>

void GameTime::Update() {
    m_iMinute += 15;
    if (m_iMinute >= 60) {
        m_iMinute = 0;
        m_iHour++;
        if (m_iHour >= 24)
        {
            m_iHour = 0;
            m_iDay++;
        }
    }
}

std::string GameTime::GetTimeString() const 
{
    std::string timeString = (m_iHour < 10 ? "0" : "") + std::to_string(m_iHour) + ":" +
        (m_iMinute < 10 ? "0" : "") + std::to_string(m_iMinute) + " Day: " + std::to_string(m_iDay);
    return timeString;
}

int GameTime::GetHour() const
{
    return m_iHour;
}

int GameTime::GetMinute() const
{
    return m_iMinute;
}
