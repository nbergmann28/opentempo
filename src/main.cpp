#include <zephyr/kernel.h>
#include <zephyr/drivers/display.h>
#include <zephyr/sys/printk.h>
#include <lvgl.h>

int main(void)
{
    printk("Main system initialized on Core %d\n", arch_curr_cpu()->id);
    
    const struct device *display_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));
    if (display_dev == NULL) {
        printk("Display device not found\n");
        return -1;
    }
    
    if (!device_is_ready(display_dev)) {
        printk("Display device not ready\n");
        return -1;
    }

    lv_obj_t *screen = lv_scr_act();
    lv_obj_set_style_bg_color(screen, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(screen, LV_OPA_COVER, LV_PART_MAIN);

    lv_obj_t *label = lv_label_create(screen);
    lv_label_set_text(label, "Hello, Zephyr!");

    lv_obj_set_style_text_color(label, lv_color_white(), LV_PART_MAIN);
    
    lv_obj_center(label);

    int ret = display_blanking_off(display_dev);
    if (ret != 0) {
        printk("Failed to turn display on: %d\n", ret);
        return ret;
    }

    printk("LVGL initialized and label created on Core %d\n", arch_curr_cpu()->id);
    
    /* Main continues on Core 0 handling background logic/BLE/Wi-Fi */
    while (1) {
        lv_timer_handler(); // Handle LVGL tasks
        k_msleep(5);
    }
    return 0;
}
