/*
 * gpio_drv2.h
 *
 *  Created on: Apr 9, 2025
 *      Author: Ulysses Andulte
 */

#ifndef INCLUDE_GPIO_DRV_H_
#define INCLUDE_GPIO_DRV_H_
#include <stdint.h>


typedef enum
{
    D10_LED = 31,
    D9_LED = 34,
}LED_t;

void gpio_init(uint32_t gpio, uint32_t addr);
#endif /* INCLUDE_GPIO_DRV2_H_ */
