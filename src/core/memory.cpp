#include "memory.hpp"

Memory::Memory()
{
}

Memory::~Memory()
{
}

uint8_t Memory::read(uint16_t address)
{
    if (address < 0x2000)
        return m_internal_ram[address & 0x7FF];

    // TODO: PPU, APU, Controller, Cartridge
    return 0;
}

void Memory::write(uint16_t address, uint8_t data)
{
    if (address < 0x2000)
        m_internal_ram[address & 0x7FF] = data;

    // TODO: PPU, APU, Controller, Cartridge
}
