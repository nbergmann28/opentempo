#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

int main(void)
{
    printk("Main system initialized on Core %d\n", arch_curr_cpu()->id);

    while (true)
    {
        k_msleep(1000);
    }
    return 0;
}
