#include <Leds.h>

uint32_t RGBMatrix(RGB color)
{
    unsigned char R, G, B;
    R = color.red * 255;
    G = color.green * 255;
    B = color.blue * 255;
    return (G << 24) | (R << 16) | (B << 8);
}

void Draw(double *drawing, uint32_t valorLed, refs pio)
{
    RGB finalColor;

    for (int16_t i = (NUM_PIXELS)-1; i >= 0; i--)
    {

        if (drawing[i])
        {
            finalColor.red = 0.1;
            finalColor.green = 0.2;
            finalColor.blue = 0.3;
        }
        else
        {
            finalColor.red = 0.0;
            finalColor.green = 0.0;
            finalColor.blue = 0.0;
        }
        valorLed = RGBMatrix(finalColor);
        pio_sm_put_blocking(pio.ref, pio.stateMachine, valorLed);
    }
}

double *Drawing(int drawing)
{
    // Desenho X
    static double drawing0[] = {
        0.0, 1.0, 1.0, 1.0, 0.0,
        0.0, 1.0, 0.0, 1.0, 0.0,
        0.0, 1.0, 0.0, 1.0, 0.0,
        0.0, 1.0, 0.0, 1.0, 0.0,
        0.0, 1.0, 1.0, 1.0, 0.0};

    static double drawing1[] = {
        0.0, 0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 1.0, 0.0,
        0.0, 0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, .0, 0.0};

    static double drawing2[] = {
        0.0, 1.0, 1.0, 1.0, 0.0,
        0.0, 1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 1.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0, 0.0,
        0.0, 1.0, 1.0, 1.0, 0.0};

    static double drawing3[] = {
        0.0, 1.0, 1.0, 1.0, 0.0,
        0.0, 1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 1.0, 1.0, 0.0,
        0.0, 1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 1.0, 1.0, 0.0};

    static double drawing4[] = {
        0.0, 1.0, 0.0, 1.0, 0.0,
        0.0, 1.0, 0.0, 1.0, 0.0,
        0.0, 1.0, 1.0, 1.0, 0.0,
        0.0, 1.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 1.0, 0.0};

    static double drawing5[] = {
        0.0, 1.0, 1.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0, 0.0,
        0.0, 1.0, 1.0, 1.0, 0.0,
        0.0, 1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 1.0, 1.0, 0.0};

    static double drawing6[] = {
        0.0, 1.0, 1.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0, 0.0,
        0.0, 1.0, 1.0, 1.0, 0.0,
        0.0, 1.0, 0.0, 1.0, 0.0,
        0.0, 1.0, 1.0, 1.0, 0.0};

    static double drawing7[] = {
        0.0, 1.0, 1.0, 1.0, 0.0,
        0.0, 1.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 1.0, 0.0,
        0.0, 1.0, 0.0, 0.0, 0.0};

    static double drawing8[] = {
        0.0, 1.0, 1.0, 1.0, 0.0,
        0.0, 1.0, 0.0, 1.0, 0.0,
        0.0, 1.0, 1.0, 1.0, 0.0,
        0.0, 1.0, 0.0, 1.0, 0.0,
        0.0, 1.0, 1.0, 1.0, 0.0};

    static double drawing9[] = {
        0.0, 1.0, 1.0, 1.0, 0.0,
        0.0, 1.0, 0.0, 1.0, 0.0,
        0.0, 1.0, 1.0, 1.0, 0.0,
        0.0, 1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 1.0, 1.0, 0.0};

    switch (drawing)
    {
    case 1:
        return drawing1;
        break;
    case 2:
        return drawing2;
        break;
    case 3:
        return drawing3;
        break;
    case 4:
        return drawing4;
        break;
    case 5:
        return drawing5;
        break;
    case 6:
        return drawing6;
        break;
    case 7:
        return drawing7;
        break;
    case 8:
        return drawing8;
        break;
    case 9:
        return drawing9;
        break;
    default:
        return drawing0;
    }
}

void BlinkRGBLed(int pin, int time)
{
    gpio_put(pin, !gpio_get(pin));
    sleep_ms(time);
}