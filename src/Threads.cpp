
#include <zephyr/kernel.h>

#include "Gui/GuiThread.hpp"

#define GUI_THREAD_STACK_SIZE 4096
#define CLOCK_THREAD_STACK_SIZE 4096

void GuiThreadEntry(void * /*unused*/, void * /*unused*/, void * /*unused*/)
{
    static gui::GuiThread guiThread;
    guiThread.GuiThreadEntry();
}

K_THREAD_DEFINE(GuiThread, GUI_THREAD_STACK_SIZE, GuiThreadEntry, NULL, NULL, NULL, 0, 0, 0);
