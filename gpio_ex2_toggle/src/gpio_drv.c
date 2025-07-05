#include "gpio_drv.h"
#include "board.h"



void gpio_init(uint32_t gpio, uint32_t addr)
{
    GPIO_setPinConfig(addr);
    GPIO_setPadConfig(gpio, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(gpio, GPIO_QUAL_SYNC);
    GPIO_setDirectionMode(gpio, GPIO_DIR_MODE_OUT);
    GPIO_setControllerCore(gpio, GPIO_CORE_CPU1);
}
