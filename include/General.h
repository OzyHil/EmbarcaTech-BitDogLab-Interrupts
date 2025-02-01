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

#define BUTTON_A 5 // Pino do Botão A
#define BUTTON_B 6 // Pino do Botão B
#define RED_LED 13 // Pino do LED vermelho
#define LED_MATRIX 7

typedef struct PIORefs {
    PIO ref;
    uint offset;
    uint stateMachine;
} refs;

typedef struct RGB {
    int8_t red;
    int8_t green;
    int8_t blue;
} RGB;

refs InitConf();
refs InitPIO();
void SetInput(int);
void SetOutput(int);

#endif