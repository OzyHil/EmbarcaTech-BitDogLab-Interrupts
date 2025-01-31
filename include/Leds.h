#ifndef LEDS_H
#define LEDS_H

#define NUM_PIXELS 25

#include <General.h>

uint32_t RGBMatrix(RGB color);
void Draw(double*, uint32_t, refs);
double* Drawing(int);
void BlinkRGBLed(int);

#endif