
#pragma once

#include <lvgl.h>

namespace gui
{
    class GuiClock
    {
      public:
        GuiClock();

        void SyncTime(uint32_t hours, uint32_t minutes, uint32_t seconds);

      private:
        lv_obj_t *clockLabel = nullptr;
        lv_timer_t *clockTimer = nullptr;
        uint32_t seconds = 0;
        uint32_t minutes = 0;
        uint32_t hours = 0;

        static void Callback(lv_timer_t *timer);

        void UpdateLabel();
    };
} // namespace gui
