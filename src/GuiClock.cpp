#include <cstdint>

#include "GuiClock.hpp"

namespace gui
{
    GuiClock::GuiClock()
    {
        k_timer_init(&clockTimer, Callback, nullptr);
        k_timer_user_data_set(&clockTimer, this);
        k_timer_start(&clockTimer, K_SECONDS(1), K_SECONDS(1));
    }

    void GuiClock::SyncTime(uint32_t hours, uint32_t minutes, uint32_t seconds)
    {
        this->hours = hours;
        this->minutes = minutes;
        this->seconds = seconds;
    }

    void GuiClock::Callback(k_timer *timer)
    {
        GuiClock *instance = static_cast<GuiClock *>(k_timer_user_data_get(timer));

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
    }
} // namespace gui
