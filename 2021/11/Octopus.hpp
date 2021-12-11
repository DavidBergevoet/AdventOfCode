#ifndef OCTOPUS_HPP_
#define OCTOPUS_HPP_

#include <iostream>
#include <ostream>

class Octopus 
{
public:
    Octopus(uint8_t startingValue = 0);

    void AddEnergyLevel();
    void ResetFlash();

    static uint64_t GetTotalFlashed(){return m_totalFlashed;};
    uint8_t GetEnergyLevel() const;
    bool GetFlashed() const;
    friend std::ostream& operator<<(std::ostream& rOs, const Octopus& rOctopus);
private:
    static uint64_t m_totalFlashed;
    uint8_t m_energyLevel;
    bool m_flashed;

    void Flash();
};

#endif // OCTOPUS_HPP_