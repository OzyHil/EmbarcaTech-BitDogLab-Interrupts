#include <General.h>
#include <Leds.h>


refs InitConf()
{
    refs pio;
    pio.ref = pio0;
    stdio_init_all();
    if (set_sys_clock_khz(128000, false))
        printf("Clock configurado para %ld\n", clock_get_hz(clk_sys));
    pio.offset = pio_add_program(pio.ref, &pio_matrix_program);
    pio.stateMachine = pio_claim_unused_sm(pio.ref, true);
    return pio;
}

refs InitPIO()
{
    refs pio = InitConf();
    pio_matrix_program_init(pio.ref, pio.stateMachine, pio.offset, LED_MATRIX);
    return pio;
}

void SetInput(int pin)
{
    gpio_init(pin);
    gpio_set_dir(pin, false);
    gpio_pull_up(pin);
}

void SetOutput(int pin)
{
    gpio_init(pin);
    gpio_set_dir(pin, true);
    gpio_put(pin, 0);
}