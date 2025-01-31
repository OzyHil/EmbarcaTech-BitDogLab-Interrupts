#include <stdio.h>
#include "pico/stdlib.h"
#include <stdlib.h>
#include <math.h>
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/adc.h"
#include "pico/bootrom.h"
#include "pio_matrix.pio.h"

#include "General.h"
#include "Leds.h"

refs pio;
uint32_t valorLed;
uint8_t count = 0;
double *drawing;

void HandleInterruption(uint gpio, uint32_t events)
{
    if (gpio == 5)
    {
        if (count < 9)
        {
            count++;
            drawing = Drawing(count);
            Draw(drawing, valorLed, pio);
        }
    }
}

void SetInterruption(int pin)
{
    gpio_set_irq_enabled_with_callback(pin, GPIO_IRQ_EDGE_FALL, 1, &HandleInterruption);
}

int main()
{
    pio = InitPIO();

    uint16_t time = 100;

    SetInput(BUTTON_A);
    SetInterruption(BUTTON_A);

    SetOutput(RED_LED);

    double *drawing = Drawing(0);
    Draw(drawing, valorLed, pio);

    while (true)
    {
        BlinkRGBLed(RED_LED, time);
    }
}
