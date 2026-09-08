#include <cstdint>
#include <format>

#include "GuiClock.hpp"

LV_FONT_DECLARE(lv_font_roboto_mono_30);

namespace gui
{
    GuiClock::GuiClock()
    {
        clockLabel = lv_label_create(lv_scr_act());

        lv_obj_set_style_text_color(clockLabel, lv_color_white(), LV_PART_MAIN);
        lv_obj_set_style_text_font(clockLabel, &lv_font_roboto_mono_30, LV_PART_MAIN);
        lv_obj_align(clockLabel, LV_ALIGN_BOTTOM_MID, 0, 0);

        UpdateLabel();

        clockTimer = lv_timer_create(Callback, 1000, this);
    }

    void GuiClock::SyncTime(uint32_t hours, uint32_t minutes, uint32_t seconds)
    {
        this->hours = hours;
        this->minutes = minutes;
        this->seconds = seconds;

        UpdateLabel();
    }

    void GuiClock::Callback(lv_timer_t *timer)
    {
        GuiClock *instance = static_cast<GuiClock *>(lv_timer_get_user_data(timer));

        instance->seconds++;

        if (instance->seconds >= 60)
        {
            instance->seconds = 0;
            instance->minutes++;
        }

        if (instance->minutes >= 60)
        {
            instance->minutes = 0;
            instance->hours++;
        }

        if (instance->hours >= 24)
        {
            instance->hours = 0;
        }

        instance->UpdateLabel();
    }

    void GuiClock::UpdateLabel()
    {
        auto time_str = std::format("{:02}:{:02}:{:02}", hours, minutes, seconds);
        lv_label_set_text(clockLabel, time_str.c_str());
    }
} // namespace gui
