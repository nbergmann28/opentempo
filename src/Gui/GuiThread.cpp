
#include <zephyr/drivers/display.h>
#include <zephyr/drivers/pwm.h>
#include <zephyr/kernel.h>

#include "GuiThread.hpp"

namespace gui
{
    void GuiThread::SetBacklightBrightness(const struct pwm_dt_spec *backlight_dev,
                                           uint32_t brightness)
    {
        if (!pwm_is_ready_dt(backlight_dev))
        {
            printk("Backlight device not ready\n");
            return;
        }

        // Ensure brightness is within 0-100% range
        brightness = std::min<uint32_t>(brightness, 100);

        // Convert brightness percentage to pulse width in nanoseconds
        uint32_t period_ns = backlight_dev->period; // Assuming period is set in the pwm_dt_spec
        uint32_t pulse_ns = (period_ns * brightness) / 100;

        int ret = pwm_set_pulse_dt(backlight_dev, pulse_ns);
        if (ret != 0)
        {
            printk("Failed to set backlight brightness: %d\n", ret);
        }
    }

    void GuiThread::GuiThreadEntry()
    {
        const struct device *display_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));
        const struct pwm_dt_spec backlight_dev = PWM_DT_SPEC_GET(DT_ALIAS(backlight_pwm));

        clock.SyncTime(12, 34, 56);

        if (!device_is_ready(display_dev))
        {
            printk("Display device not ready\n");
            return;
        }

        if (!pwm_is_ready_dt(&backlight_dev))
        {
            printk("Backlight device not ready\n");
            return;
        }

        SetBacklightBrightness(&backlight_dev, 0);

        lv_obj_t *screen = lv_scr_act();
        lv_obj_set_style_bg_color(screen, lv_color_black(), LV_PART_MAIN);
        lv_obj_set_style_bg_opa(screen, LV_OPA_COVER, LV_PART_MAIN);

        lv_obj_t *label = lv_label_create(screen);
        lv_label_set_text(label, "Hello, Bergmann's!");

        lv_obj_set_style_text_color(label, lv_color_white(), LV_PART_MAIN);
        lv_obj_set_style_text_font(label, &lv_font_montserrat_24, LV_PART_MAIN);

        lv_obj_center(label);

        lv_obj_t *clockLabel = lv_label_create(screen);
        lv_label_set_text(clockLabel, "00:00:00");
        lv_obj_set_style_text_color(clockLabel, lv_color_white(), LV_PART_MAIN);
        lv_obj_set_style_text_font(clockLabel, &lv_font_roboto_mono_30, LV_PART_MAIN);
        lv_obj_align(clockLabel, LV_ALIGN_BOTTOM_MID, 0, 0);

        int ret = display_blanking_off(display_dev);
        if (ret != 0)
        {
            printk("Failed to turn display on: %d\n", ret);
            return;
        }

        printk("LVGL initialized and label created on Core %d\n", arch_curr_cpu()->id);
        k_msleep(5);
        SetBacklightBrightness(&backlight_dev, 100);

        while (true)
        {
            lv_label_set_text(clockLabel, clock.GetFormatetTime().c_str());
            lv_timer_handler(); // Handle LVGL tasks
            k_sleep(K_MSEC(100));
        }
    }
} // namespace gui
