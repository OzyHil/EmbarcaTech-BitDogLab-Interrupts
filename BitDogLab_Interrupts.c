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
static volatile uint32_t lastTimeA = 0;
static volatile uint32_t lastTimeB = 0;
static volatile uint32_t lastTimeRGB = 0;

void UpdateDrawing(uint gpio, volatile uint32_t *lastTime, int step)
{
    uint32_t currentTime = to_us_since_boot(get_absolute_time());

    if (currentTime - *lastTime > 200000)
    {
        *lastTime = currentTime;

        if ((step == 1 && count < 9) || (step == -1 && count > 0))
        {
            count += step;
            drawing = Drawing(count);
            Draw(drawing, valorLed, pio);
            printf("%d", count);
        }
    }
}

void HandleInterruption(uint gpio, uint32_t events)
{
    if (gpio == 5)
    {
        UpdateDrawing(gpio, &lastTimeA, 1); // Incrementa count
    }
    else if (gpio == 6)
    {
        UpdateDrawing(gpio, &lastTimeB, -1); // Decrementa count
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
    uint32_t currentTime = to_us_since_boot(get_absolute_time());

    SetInput(BUTTON_A);
    SetInterruption(BUTTON_A);

    SetInput(BUTTON_B);
    SetInterruption(BUTTON_B);

    SetOutput(RED_LED);

    double *drawing = Drawing(0);
    Draw(drawing, valorLed, pio);

    while (true)
    {
        currentTime = to_us_since_boot(get_absolute_time());
        if (currentTime - lastTimeRGB > 100000)
        {
            lastTimeRGB = currentTime;
            BlinkRGBLed(RED_LED);
        }
    }
}