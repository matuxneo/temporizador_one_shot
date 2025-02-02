#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"
#include <stdio.h>

// Definição dos pinos
#define LED_BLUE_PIN 11    // GPIO11 - LED Azul
#define LED_RED_PIN 12     // GPIO12 - LED Vermelho
#define LED_GREEN_PIN 13   // GPIO13 - LED Verde
#define BUTTON_PIN 5       // GPIO5 - Botão

// Estados e controle
volatile bool leds_on = false;          // Indica se os LEDs estão ligados
volatile bool sequence_running = false; // Indica se a sequência está em execução
volatile uint32_t last_button_time = 0;
const uint32_t debounce_time = 50;      // Debounce de 50ms

// Estrutura para armazenar o estado da sequência
typedef struct {
    uint8_t led_state; // Estado atual da sequência (3: Todos, 2: Vermelho+Verde, 1: Verde)
} sequence_data_t;

// Função de callback para sequência de desligamento
int64_t turn_off_callback(alarm_id_t id, void *user_data) {
    sequence_data_t *data = (sequence_data_t *)user_data; // Recupera os dados do usuário
    printf("Sequência de desligamento: %d\n", data->led_state);  // Log de debug

    switch (data->led_state) {
        case 3:
            gpio_put(LED_BLUE_PIN, 0);  // Desliga Azul (2 LEDs restantes)
            break;
        case 2:
            gpio_put(LED_RED_PIN, 0);   // Desliga Vermelho (1 LED restante)
            break;
        case 1:
            gpio_put(LED_GREEN_PIN, 0); // Desliga Verde (todos desligados)
            leds_on = false;            // Permite nova ativação com o botão
            sequence_running = false;   // Finaliza a sequência
            break;
    }

    data->led_state--; // Próximo estágio

    // Agenda próximo estágio se necessário
    if (data->led_state > 0) {
        return 3000000; // 3 segundos em microssegundos
    }
    return 0; // Finaliza a sequência
}

// Verificação do botão com debounce
bool is_button_pressed() {
    uint32_t now = to_ms_since_boot(get_absolute_time()); // Tempo atual em ms desde o boot do sistema 
    if ((now - last_button_time) > debounce_time) {
        last_button_time = now;     // Atualiza o tempo do último pressionamento do botão 
        return !gpio_get(BUTTON_PIN); // Lógica ativa em LOW
    }
    return false; // Botão não pressionado ou ainda em debounce 
}

int main() {
    // Inicialização de hardware
    stdio_init_all(); // Inicializa UART para debug via USB CDC 
    printf("Sistema de Temporização One-Shot\n"); // Log de inicialização 

    // Configuração dos LEDs
    gpio_init(LED_BLUE_PIN); // Inicializa pino do LED Azul 
    gpio_set_dir(LED_BLUE_PIN, GPIO_OUT); // Define pino como saída 
    gpio_init(LED_RED_PIN);   // Inicializa pino do LED Vermelho   
    gpio_set_dir(LED_RED_PIN, GPIO_OUT); // Define pino como saída 
    gpio_init(LED_GREEN_PIN); // Inicializa pino do LED Verde
    gpio_set_dir(LED_GREEN_PIN, GPIO_OUT); // Define pino como saída

    // Configuração do botão
    gpio_init(BUTTON_PIN); // Inicializa pino do botão
    gpio_set_dir(BUTTON_PIN, GPIO_IN); // Define pino como entrada
    gpio_pull_up(BUTTON_PIN); // Habilita resistor de pull-up interno

    // Dados da sequência
    sequence_data_t sequence_data;

    while (true) {
        // Verifica se o botão foi pressionado e se nenhuma sequência está em execução
        if (is_button_pressed() && !sequence_running) {
            printf("Botão pressionado: Iniciando sequência\n");  // Log de debug

            // Liga todos os LEDs
            gpio_put(LED_BLUE_PIN, 1); // Liga Azul
            gpio_put(LED_RED_PIN, 1); // Liga Vermelho
            gpio_put(LED_GREEN_PIN, 1); // Liga Verde
            leds_on = true; // Marca que os LEDs estão ligados

            // Reinicia o estado da sequência
            sequence_data.led_state = 3;

            // Marca que a sequência está em execução 
            sequence_running = true;

            // Agenda desligamento em 3 segundos, passando os dados da sequência
            add_alarm_in_ms(3000, turn_off_callback, &sequence_data, false);
        }

        sleep_ms(10); // Reduz consumo de CPU
    }

    return 0; // Nunca chega aqui
}