#include "General.h"
#include "Leds.h"

// Variáveis globais

refs pio;                               // Referência do PIO
uint32_t valorLed;                      // Valor do LED a ser enviado
RGB color;                              // Cor do LED (RGB)
double *drawing;                        // Desenho (sequência de LEDs acesos)
volatile uint8_t count = 0;             // Contador do número mostrado
static volatile uint32_t lastTimeA = 0; // Tempo de última interrupção do botão A
static volatile uint32_t lastTimeB = 0; // Tempo de última interrupção do botão B

void SetInterruption(int pin);                                        // Configura a interrupção para o botão
void HandleInterruption(uint gpio, uint32_t events);                  // Função que lida com a interrupção dos botões
void UpdateDrawing(uint gpio, volatile uint32_t *lastTime, int step); // Atualiza o desenho com base no botão pressionado
bool BlinkLedCallback(struct repeating_timer *t);                     // Função de callback para fazer o LED piscar

int main()
{
    // Inicializa o PIO
    pio = InitPIO();

    // Configura botões A e B e atribui interrupções
    SetInput(BUTTON_A);
    SetInterruption(BUTTON_A);
    SetInput(BUTTON_B);
    SetInterruption(BUTTON_B);

    // Configura o LED vermelho
    SetOutput(RED_LED);

    // Define a cor dos LEDs da matriz
    color.red = 2;
    color.green = 4;
    color.blue = 8;

    // Inicializa o desenho com o número 0 e exibe na matriz
    double *drawing = Drawing(0);
    Draw(drawing, valorLed, pio, color);

    // Configura o timer para alternar o estado do LED a cada 100 ms
    struct repeating_timer timer;
    add_repeating_timer_ms(100, BlinkLedCallback, NULL, &timer);

    // Loop principal que mantém o sistema funcionando
    while (true)
    {
        sleep_ms(1); // Coloca o processador em modo de baixo consumo
    }
}

// Função para configurar a interrupção no pino do botão
void SetInterruption(int pin)
{
    gpio_set_irq_enabled_with_callback(pin, GPIO_IRQ_EDGE_FALL, 1, &HandleInterruption);
}

// Função que é chamada quando ocorre uma interrupção de botão
void HandleInterruption(uint gpio, uint32_t events)
{
    // Verifica se o botão A foi pressionado
    if (gpio == 5)
    {
        UpdateDrawing(gpio, &lastTimeA, 1); // Incrementa o contador e atualiza o desenho
    }
    // Verifica se o botão B foi pressionado
    else if (gpio == 6)
    {
        UpdateDrawing(gpio, &lastTimeB, -1); // Decrementa o contador e atualiza o desenho
    }
}

// Função que atualiza o desenho com base no botão pressionado
void UpdateDrawing(uint gpio, volatile uint32_t *lastTime, int step)
{
    uint32_t currentTime = to_us_since_boot(get_absolute_time());

    // Verifica se o tempo de debouncing passou (250ms)
    if (currentTime - *lastTime > 250000)
    {
        *lastTime = currentTime;

        // Verifica se o contador pode ser incrementado ou decrementado
        if ((step == 1 && count < 9) || (step == -1 && count > 0))
        {
            count += step;

            // Atualiza o desenho de acordo com o novo valor do contador
            drawing = Drawing(count);
            Draw(drawing, valorLed, pio, color);
        }
    }
}

// Função de callback que faz o LED piscar
bool BlinkLedCallback(struct repeating_timer *t)
{
    // Inverte o estado do LED vermelho
    gpio_put(RED_LED, !gpio_get(RED_LED));

    return true; // Retorna true para continuar o timer
}
