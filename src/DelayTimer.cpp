#include "DelayTimer.hpp"

void DelayTimer::start(float seconds)
{
    m_duration = sf::seconds(seconds);
    m_clock.restart();
    m_active = true;   
}

bool DelayTimer::isDone() const
{
    return m_active && m_clock.getElapsedTime() >= m_duration;
}

bool DelayTimer::isActive() const
{
    return m_active;
}

void DelayTimer::reset()
{
    m_active = false;
}

sf::Time DelayTimer::getElapsed() const
{
    return m_clock.getElapsedTime();
}

sf::Time DelayTimer::getDuration() const
{
    return m_duration;
}
