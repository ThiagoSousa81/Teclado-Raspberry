// Anibal Maldonado: Código principal  - https://github.com/PhD-Anibal
// Anibal Maldonado: LED Vermelho ao apertar 'A' - https://github.com/PhD-Anibal

#include <stdio.h>
#include "pico/stdlib.h"


#define led_pin_red 22        // porta do pino 27 LED RGB Vermelho
#define led_pin_green 21        // porta do pino 27 LED RGB Vermelho
#define led_pin_blue 20        // porta do pino 27 LED RGB Vermelho

// Define os pinos do teclado
uint columns[4] = {4, 3, 2, 1}; // Colunas conectadas aos GPIOs
uint rows[4] = {8, 7, 6, 5};    // Linhas conectadas aos GPIOs

// Mapa de teclas
char KEY_MAP[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

// Inicializa os pinos do teclado
void init_keypad() {
    for (int i = 0; i < 4; i++) {
        gpio_init(columns[i]);         // Inicializa os pinos das colunas
        gpio_set_dir(columns[i], GPIO_IN); // Configura as colunas como entrada com pull-up
        gpio_pull_up(columns[i]);

        gpio_init(rows[i]);            // Inicializa os pinos das linhas
        gpio_set_dir(rows[i], GPIO_OUT);   // Configura as linhas como saída
        gpio_put(rows[i], 1);          // Define as linhas como HIGH
    }
}

// Verifica qual tecla foi pressionada
char get_key() {
    for (int r = 0; r < 4; r++) {
        gpio_put(rows[r], 0); // Ativa a linha atual
        for (int c = 0; c < 4; c++) {
            if (gpio_get(columns[c]) == 0) { // Verifica se a coluna está LOW
                gpio_put(rows[r], 1); // Restaura a linha
                return KEY_MAP[r][c]; // Retorna a tecla pressionada
            }
        }
        gpio_put(rows[r], 1); // Restaura a linha
    }
    return 0; // Nenhuma tecla pressionada
}

int main() {
    stdio_init_all(); // Inicializa a comunicação serial
    init_keypad();    // Configura o teclado
    gpio_init(led_pin_red);
    gpio_set_dir(led_pin_red, GPIO_OUT);
    gpio_init(led_pin_green);
    gpio_set_dir(led_pin_green, GPIO_OUT);
    gpio_init(led_pin_blue);
    gpio_set_dir(led_pin_blue, GPIO_OUT);        

    while (true) {
        char key = get_key(); // Lê a tecla pressionada
        if (key) {
            switch (key) {
                case 'A': 
                gpio_put(led_pin_red, 1);
                gpio_put(led_pin_green, 0);
                gpio_put(led_pin_blue, 0);
                // por código para desligar outros LEDS
                break;
                case 'B': 
                gpio_put(led_pin_red, 0);
                gpio_put(led_pin_green, 1);
                gpio_put(led_pin_blue, 0);                // por código para desligar outros LEDS
                break;
                case 'C':
                gpio_put(led_pin_red, 0);
                gpio_put(led_pin_green, 0);
                gpio_put(led_pin_blue, 1);                
                // por código para desligar outros LEDS
                break;                                
            }          
            printf("Tecla pressionada: %c\n", key);
        }
        sleep_ms(200); // Pequeno atraso para evitar leituras duplicadas
    }
}
