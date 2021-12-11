#include "Octopus.hpp"

uint64_t Octopus::m_totalFlashed = 0;

Octopus::Octopus(uint8_t startingLevel) : m_energyLevel(startingLevel), m_flashed(false)
{}

void Octopus::AddEnergyLevel()
{
    if(!m_flashed)
    {
        if(m_energyLevel < 9)
        {
            m_energyLevel++;
        }else
        {
            Flash();
        }
    }
}

void Octopus::ResetFlash()
{
    m_flashed = false;
}

void Octopus::Flash()
{
    m_flashed = true;
    m_totalFlashed++;
    m_energyLevel = 0;
}

uint8_t Octopus::GetEnergyLevel() const
{
    return m_energyLevel;
}

bool Octopus::GetFlashed() const
{
    return m_flashed;
}

std::ostream& operator<<(std::ostream& rOs, const Octopus& rOctopus)
{
    if(rOctopus.m_flashed)
    {
        rOs << '*'<<(int)rOctopus.GetEnergyLevel()<<'*';
    }
    else
    {
        rOs << ' '<<(int)rOctopus.GetEnergyLevel()<<' ';
    }
    return rOs;
}