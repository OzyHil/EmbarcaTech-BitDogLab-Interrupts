#ifndef GENERAL_H
#define GENERAL_H

#include <stdio.h>
#include "pico/stdlib.h"
#include <stdlib.h>
#include <math.h>
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/adc.h"
#include "pico/bootrom.h"
#include "pio_matrix.pio.h"

#define BUTTON_A 5
#define RED_LED 13
#define LED_MATRIX 7

typedef struct PIORefs {
    PIO ref;
    uint offset;
    uint stateMachine;
} refs;

typedef struct RGB {
    double red;
    double green;
    double blue;
} RGB;

refs InitConf();
refs InitPIO();
void SetInput(int);
void SetOutput(int);

#endif