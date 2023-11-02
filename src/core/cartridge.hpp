#pragma once

#include "types.hpp"
#include <string>
#include <vector>

class Cartridge
{
public:
    enum MirrorMode
    {
        MIRROR_HORIZONTAL,
        MIRROR_VERTICAL
    };

    struct Info
    {
        uint8_t mapper = 0;
        uint8_t prg_banks = 0;
        uint8_t chr_banks = 0;
        uint32_t prg_size = 0;
        uint32_t chr_size = 0;
        MirrorMode mirror_mode = MIRROR_HORIZONTAL;
        bool baterry = false;
        bool trainer = false;
        bool four_screen_mode = false;
        bool vs_unisystem = false;
        bool playchoice_10 = false;
        bool is_nes2_format = false;
    };

public:
    Cartridge() = default;
    ~Cartridge();

    const Info& info() const;
    bool load_from_file(const std::string& path);

private:
    Info m_info;

    void parse_rom_header(const uint8_t* header);
    std::string mirror_mode_to_string(MirrorMode mode);
};
