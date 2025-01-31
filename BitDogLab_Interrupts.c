#include <stdio.h>
#include "pico/stdlib.h"
#include <stdlib.h>
#include <math.h>
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/adc.h"
#include "pico/bootrom.h"
#include "pio_matrix.pio.h"

#define RED_LED 13
#define BUTTON_A 5
#define NUM_PIXELS 25
#define LED_MATRIX 7

double drawing[25] = {0.0, 0.3, 0.3, 0.3, 0.0,
                      0.0, 0.3, 0.0, 0.3, 0.0,
                      0.0, 0.3, 0.3, 0.3, 0.0,
                      0.0, 0.3, 0.0, 0.3, 0.0,
                      0.0, 0.3, 0.3, 0.3, 0.0};

volatile bool buttonPressed = false;  // Variável global para indicar que o botão foi pressionado

uint32_t MatrixRGB(double b, double r, double g)
{
    unsigned char R, G, B;
    R = r * 255;
    G = g * 255;
    B = b * 255;
    return (G << 24) | (R << 16) | (B << 8);
}

void DrawPIO(double *drawing, uint32_t valor_led, PIO pio, uint sm, double r, double g, double b)
{
    for (int16_t i = 0; i < NUM_PIXELS; i++)
    {
        if (i % 2 == 0)
        {
            valor_led = MatrixRGB(drawing[24 - i], r = 0.0, g = 0.0);
            pio_sm_put_blocking(pio, sm, valor_led);
        }
        else
        {
            valor_led = MatrixRGB(b = 0.0, drawing[24 - i], g = 0.0);
            pio_sm_put_blocking(pio, sm, valor_led);
        }
    }
}


static void ButtonAInterrupt(uint gpio, uint32_t events)
{
    buttonPressed = true;
}

int main()
{
    PIO pio = pio0;
    uint32_t valor_led;
    double r = 0.0, b = 0.0, g = 0.0;

    set_sys_clock_khz(128000, false);

    stdio_init_all();

    uint offset = pio_add_program(pio, &pio_matrix_program);
    uint sm = pio_claim_unused_sm(pio, true);
    pio_matrix_program_init(pio, sm, offset, LED_MATRIX);

    gpio_init(RED_LED);
    gpio_set_dir(RED_LED, GPIO_OUT);

    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A);
    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, 1, &ButtonAInterrupt);

    while (true)
    {
        gpio_put(RED_LED, !gpio_get(RED_LED));  // Pisca o LED vermelho
        sleep_ms(100);

        if (buttonPressed)  // Se o botão foi pressionado
        {
            DrawPIO(drawing, valor_led, pio, sm, r, g, b); 
            buttonPressed = false; 
        }
    }
}