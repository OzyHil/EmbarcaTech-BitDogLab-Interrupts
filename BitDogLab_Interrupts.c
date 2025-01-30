#include <stdio.h>
#include "pico/stdlib.h"

#define RED_LED 13
#define BUTTON_A 5

static void ButtonAInterrupt(uint gpio, uint32_t events){
    printf("A\n");
}

int main()
{
    stdio_init_all();

    gpio_init(RED_LED);
    gpio_set_dir(RED_LED, GPIO_OUT);

    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A);
    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, 1, & ButtonAInterrupt);

    while (true) {
        gpio_put(RED_LED, !gpio_get(RED_LED));
        sleep_ms(100);

    }
}
