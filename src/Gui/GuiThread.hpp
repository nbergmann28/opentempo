
#pragma once

#include "../GuiClock.hpp"
#include <cstdint>
#include <lvgl.h>

LV_FONT_DECLARE(lv_font_roboto_mono_30);

namespace gui
{
    class GuiThread
    {
      public:
        GuiThread() = default;

        void GuiThreadEntry();

      private:
        gui::GuiClock clock;

        static void SetBacklightBrightness(const struct pwm_dt_spec *backlight_dev,
                                           uint32_t brightness);
    };
} // namespace gui
