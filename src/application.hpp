#pragma once

#include "global.hpp"
#include "emulator.hpp"
#include "input_manager.hpp"
#include "version.hpp"
#include <string>
#include <memory>
#include <SDL.h>

class Application
{
public:
    Application():
        m_nes(std::make_unique<Emulator>(m_input_manager))
    {}

    ~Application();

    int run(int argc, char* argv[]);
    void set_window_title(const std::string& title);
    SDL_Window* window() const { return m_window; }

private:
    InputManager m_input_manager;
    std::unique_ptr<Emulator> m_nes;
    SDL_Window* m_window = nullptr;
    SDL_Renderer* m_renderer = nullptr;
    SDL_Texture* m_frame_texture = nullptr;

    std::string m_window_title = EMU_VERSION_NAME;
    int m_window_width = PPU::ScreenWidth;
    int m_window_height = PPU::ScreenHeigh;
    int m_screen_scale = 2;
    bool m_running = false;
    bool m_exit = false;
    bool m_show_popup = false;
    bool m_show_about = false;

    bool init();
    void process_events();
    void on_keyboard_event(const SDL_KeyboardEvent& event);
    void on_window_event(const SDL_Event& event);
    void render();
    void render_menubar();
    void render_exit_dialog();
    void render_about_dialog();

    void reset_window_size();
    void open_nes_file();
    void set_dark_theme();
};
