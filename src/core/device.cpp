#include "device.hpp"
#include "cpu.hpp"
#include "apu.hpp"
#include "ppu.hpp"
#include "cartridge.hpp"
#include "controller.hpp"
#include "memory.hpp"

Device::Device()
{
    m_cartridge = new Cartridge();
    m_ppu = new PPU(m_cartridge);
    m_apu = new APU();
    m_controller = new Controller();
    m_memory = new Memory(m_apu, m_ppu, m_cartridge, m_controller);
    m_cpu = new CPU(m_memory);
}

Device::~Device()
{
    delete m_ppu;
    delete m_cartridge;
    delete m_controller;
    delete m_memory;
    delete m_apu;
    delete m_cpu;
}

void Device::reset()
{
    m_apu->reset();
    m_ppu->reset();
    m_cpu->reset();
}

void Device::run()
{
    if (!m_cartridge->is_loaded())
        return;

    m_ppu->frame_start();
    while (!m_ppu->frame_rendered())
    {
        if (m_cpu->cycles() == 0 && m_ppu->nmi())
        {
            m_cpu->nmi();
            m_ppu->nmi_clear();
        }

        m_cpu->tick();

        // PPU is 3 times faster
        m_ppu->tick();
        m_ppu->tick();
        m_ppu->tick();
    }
}

bool Device::load_rom_file(const std::string& file_path)
{
    if (!m_cartridge->load_from_file(file_path))
        return false;

    reset();
    return true;
}

uint32_t* Device::screen()
{
    return m_ppu->frame_buffer();
}
