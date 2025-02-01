#include "General.h"
#include "Leds.h"

refs pio;
uint32_t valorLed;
RGB color;
double *drawing;
volatile uint8_t count = 0;
static volatile uint32_t lastTimeA = 0;
static volatile uint32_t lastTimeB = 0;

void SetInterruption(int pin);
void HandleInterruption(uint gpio, uint32_t events);
void UpdateDrawing(uint gpio, volatile uint32_t *lastTime, int step);
bool BlinkLedCallback(struct repeating_timer *t);

int main()
{
    pio = InitPIO();

    SetInput(BUTTON_A);
    SetInterruption(BUTTON_A);

    SetInput(BUTTON_B);
    SetInterruption(BUTTON_B);

    SetOutput(RED_LED);

    color.red = 2;
    color.green = 4;
    color.blue = 8;

    double *drawing = Drawing(0);
    Draw(drawing, valorLed, pio, color);

    struct repeating_timer timer;
    add_repeating_timer_ms(100, BlinkLedCallback, NULL, &timer);

    while (true){
        sleep_ms(1);
    }
}

void SetInterruption(int pin)
{
    gpio_set_irq_enabled_with_callback(pin, GPIO_IRQ_EDGE_FALL, 1, &HandleInterruption);
}

void HandleInterruption(uint gpio, uint32_t events)
{
    // Botão pressionado foi o A
    if (gpio == 5)
    {
        UpdateDrawing(gpio, &lastTimeA, 1); // Incrementa count
    }
    // Botão pressionado foi o B
    else if (gpio == 6)
    {
        UpdateDrawing(gpio, &lastTimeB, -1); // Decrementa count
    }
}

void UpdateDrawing(uint gpio, volatile uint32_t *lastTime, int step)
{
    uint32_t currentTime = to_us_since_boot(get_absolute_time());

    if (currentTime - *lastTime > 250000)
    {
        *lastTime = currentTime;

        if ((step == 1 && count < 9) || (step == -1 && count > 0))
        {
            count += step;

            drawing = Drawing(count);
            Draw(drawing, valorLed, pio, color);
        }
    }
}

bool BlinkLedCallback(struct repeating_timer *t)
{
    gpio_put(RED_LED, !gpio_get(RED_LED));
    return true;
}