#include "rom_widget.h"

#include <fstream>
#include <stdexcept>

#include <imgui.h>

RomWidget::RomWidget(n_e_s::nes::Nes *nes) : nes_(nes) {}

void RomWidget::update() {
    ImGui::Begin("Load rom");
    ImGui::InputText("", rom_path_.data(), rom_path_.size());
    ImGui::SameLine();
    try {
        if (ImGui::Button("Load")) {
            std::ifstream rom(rom_path_.data(), std::ios::binary);
            nes_->load_rom(rom);
            if (load_action_) {
                load_action_();
            }
            info_text_ = "Rom loaded";
        }
    } catch (const std::invalid_argument &e) {
        info_text_ = e.what();
    }

    ImGui::Text("%s", info_text_.c_str());
    ImGui::End();
}

void RomWidget::add_load_action(const std::function<void(void)> &action) {
    load_action_ = action;
}
