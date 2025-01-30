#include <stdio.h>
#include "pico/stdlib.h"

#define RED_LED 13

int main()
{
    stdio_init_all();

    gpio_init(RED_LED);
    gpio_set_dir(RED_LED, GPIO_OUT);

    while (true) {
        gpio_put(RED_LED, !gpio_get(RED_LED));
        sleep_ms(100);
    }
}
