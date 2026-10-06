
#pragma once

#include <format>
#include <zephyr/kernel.h>
namespace gui
{
    class GuiClock
    {
      public:
        GuiClock();

        void SyncTime(uint32_t hours, uint32_t minutes, uint32_t seconds);

        std::string GetFormatetTime() const
        {
            return std::format("{:02}:{:02}:{:02}", hours, minutes, seconds);
        }

      private:
        k_timer clockTimer;
        uint32_t seconds = 0;
        uint32_t minutes = 0;
        uint32_t hours = 0;

        static void Callback(k_timer *timer);
    };
} // namespace gui
