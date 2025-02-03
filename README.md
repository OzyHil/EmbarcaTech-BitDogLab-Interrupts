# Projeto de Interrupções com RP2040 - BitDogLab

## Vídeo de Demonstração

O vídeo de demonstração pode ser encontrado https://youtu.be/kJ67gHHnHos.

## Descrição

Este projeto foi desenvolvido por mim, **Hilquias Rodrigues de Oliveira**, com o objetivo de demonstrar o uso de interrupções e controle de LEDs em um microcontrolador **RP2040**, utilizando a placa de desenvolvimento **BitDogLab**. O projeto envolve a manipulação de uma matriz 5x5 de LEDs endereçáveis **WS2812**, controle de um **LED RGB**, e o uso de **botões** para interagir com os LEDs. O sistema lida com interrupções para responder ao acionamento dos botões e implementa o tratamento de *bouncing* (debouncing) via software.

## Funcionalidades

1. **Piscar LED Vermelho**: O LED vermelho do LED RGB pisca continuamente 5 vezes por segundo.
2. **Incrementar e Decrementar Número**: Os botões A e B permitem incrementar ou decrementar um número exibido na matriz 5x5 de LEDs.
3. **Debouncing**: O tratamento de *bouncing* dos botões foi implementado via software para garantir que as interrupções sejam gerenciadas corretamente.

## Componentes Utilizados

- **Matriz 5x5 de LEDs WS2812** (GPIO 7)
- **LED RGB na cor vermelha** (GPIO 13)
- **Botão A** (GPIO 5)
- **Botão B** (GPIO 6)

## Aspectos do Projeto

- Implementação de interrupções para os botões.
- Debouncing via software.
- Controle de LEDs comuns e LEDs endereçáveis WS2812.
- Código bem estruturado e comentado.

## Como Executar

1. Conecte a placa **BitDogLab** via USB, e coloque-a em **modo BOOTSEL**.
2. Compile o código e envie para a placa **BitDogLab**.
3. Interaja com o sistema pressionando os botões A e B para alterar o número exibido na matriz de LEDs.
4. O LED RGB piscará continuamente a cada 0.2 segundos (5Hz).
