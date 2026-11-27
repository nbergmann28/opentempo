
#pragma once

#include "../GuiClock.hpp"
#include <cstdint>
#include <lvgl.h>
#include <zephyr/input/input.h>

LV_FONT_DECLARE(lv_font_roboto_mono_30);

namespace gui
{
    class GuiThread
    {
      public:
        GuiThread() = default;

        void GuiThreadEntry();
        static void TouchEventCallback(struct input_event *event, void *user_data);

      private:
        gui::GuiClock clock;

        void HandleTouchEvent(struct input_event *event);
        static void SetBacklightBrightness(const struct pwm_dt_spec *backlight_dev,
                                           uint32_t brightness);
    };
} // namespace gui
