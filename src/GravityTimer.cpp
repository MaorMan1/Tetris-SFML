#include "GravityTimer.hpp"

void GravityTimer::start(float seconds)
{
    m_delay = seconds;
    m_clock.restart();
}

bool GravityTimer::shouldFall(){
    return m_clock.getElapsedTime().asSeconds() >= m_delay;
}

void GravityTimer::reset(){
    m_clock.restart();
}

void GravityTimer::speedUp(float factor){ // Factor is 0.95 by default
    m_delay *= factor;
    if (m_delay < 0.1f)
        m_delay = 0.1f; // clamp to prevent going too fast
}

float GravityTimer::getDelay() const
{
    return m_delay;
}
