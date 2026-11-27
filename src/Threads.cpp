
#include <zephyr/device.h>
#include <zephyr/input/input.h>
#include <zephyr/kernel.h>

#include "Gui/GuiThread.hpp"

#define GUI_THREAD_STACK_SIZE 4096
#define CLOCK_THREAD_STACK_SIZE 4096

void GuiThreadEntry(void * /*unused*/, void * /*unused*/, void * /*unused*/)
{
    static gui::GuiThread guiThread;
    INPUT_CALLBACK_DEFINE_NAMED(DEVICE_DT_GET(DT_NODELABEL(xpt2046)),
                                gui::GuiThread::TouchEventCallback, &guiThread, touch_event);
    guiThread.GuiThreadEntry();
}

K_THREAD_DEFINE(GuiThread, GUI_THREAD_STACK_SIZE, GuiThreadEntry, NULL, NULL, NULL, 0, 0, 0);
