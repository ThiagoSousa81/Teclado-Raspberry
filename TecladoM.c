// Anibal Maldonado: Código principal  - https://github.com/PhD-Anibal
// Anibal Maldonado: LED Vermelho ao apertar 'A' - https://github.com/PhD-Anibal

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"


#define led_pin_red1 27        // porta do pino 27 LED RGB Vermelho
#define led_pin_green1 26        // porta do pino 26 LED RGB Verde
#define led_pin_blue1 22        // porta do pino 22 LED RGB Azul

#define led_pin_red2 21        // porta do pino 21 LED RGB Vermelho
#define led_pin_green2 20        // porta do pino 20 LED RGB Verde
#define led_pin_blue2 19        // porta do pino 19 LED RGB Azul

#define led_pin_red3 18        // porta do pino 18 LED RGB Vermelho
#define led_pin_green3 17        // porta do pino 17 LED RGB Verde
#define led_pin_blue3 16        // porta do pino 16 LED RGB Azul

#define BUZZER1 28              // define o pino 28 = Buzzer

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

void inicializaLedsRGB(){
    // Primeiro LED RGB
    gpio_init(led_pin_red1);
    gpio_init(led_pin_green1);
    gpio_init(led_pin_blue1);
    gpio_set_dir(led_pin_red1, GPIO_OUT);
    gpio_set_dir(led_pin_green1, GPIO_OUT);
    gpio_set_dir(led_pin_blue1, GPIO_OUT);

    // Segundo LED RGB
    gpio_init(led_pin_red2);
    gpio_init(led_pin_green2);
    gpio_init(led_pin_blue2);
    gpio_set_dir(led_pin_red2, GPIO_OUT);
    gpio_set_dir(led_pin_green2, GPIO_OUT);
    gpio_set_dir(led_pin_blue2, GPIO_OUT);

    // Terceiro LED RGB
    gpio_init(led_pin_red3);
    gpio_init(led_pin_green3);
    gpio_init(led_pin_blue3);
    gpio_set_dir(led_pin_red3, GPIO_OUT);
    gpio_set_dir(led_pin_green3, GPIO_OUT);
    gpio_set_dir(led_pin_blue3, GPIO_OUT);
}

void acendeLedRGB(int led, int red, int green, int blue){
    switch(led){
        case 1:
            gpio_put(led_pin_red1, red);
            gpio_put(led_pin_green1, green);
            gpio_put(led_pin_blue1, blue);
            break;
        case 2:
            gpio_put(led_pin_red2, red);
            gpio_put(led_pin_green2, green);
            gpio_put(led_pin_blue2, blue);
            break;
        case 3:
            gpio_put(led_pin_red3, red);
            gpio_put(led_pin_green3, green);
            gpio_put(led_pin_blue3, blue);
            break;
    }
}

void init_pwm(uint gpio) {
    gpio_set_function(gpio, GPIO_FUNC_PWM); // Configura o GPIO como PWM
    uint slice_num = pwm_gpio_to_slice_num(gpio);
    pwm_set_clkdiv(slice_num, 125.0f);     // Define o divisor do clock para 1 MHz
    pwm_set_wrap(slice_num, 1000);        // Define o TOP para frequência de 1 kHz
    pwm_set_chan_level(slice_num, pwm_gpio_to_channel(gpio), 0); // Razão cíclica inicial
    pwm_set_enabled(slice_num, true);     // Habilita o PWM
}

void set_buzzer_tone(uint gpio, uint freq) {
    uint slice_num = pwm_gpio_to_slice_num(gpio);
    uint top = 1000000 / freq;            // Calcula o TOP para a frequência desejada
    pwm_set_wrap(slice_num, top);
    pwm_set_chan_level(slice_num, pwm_gpio_to_channel(gpio), top / 2); // 50% duty cycle
}

void stop_buzzer(uint gpio) {
    uint slice_num = pwm_gpio_to_slice_num(gpio);
    pwm_set_chan_level(slice_num, pwm_gpio_to_channel(gpio), 0); // Desliga o PWM
}

void canon(){
    set_buzzer_tone(BUZZER1, 395); 
        sleep_ms(500);
        stop_buzzer(BUZZER1);
        set_buzzer_tone(BUZZER1, 330); 
        sleep_ms(250);
        stop_buzzer(BUZZER1);
        set_buzzer_tone(BUZZER1, 352); 
        sleep_ms(250);
        stop_buzzer(BUZZER1);
        set_buzzer_tone(BUZZER1, 395); 
        sleep_ms(500);
        stop_buzzer(BUZZER1);
        set_buzzer_tone(BUZZER1, 330); 
        sleep_ms(250);
        stop_buzzer(BUZZER1);
        set_buzzer_tone(BUZZER1, 352); 
        sleep_ms(250);
        stop_buzzer(BUZZER1);
        set_buzzer_tone(BUZZER1, 395); 
        sleep_ms(500);
        stop_buzzer(BUZZER1);
        set_buzzer_tone(BUZZER1, 197); 
        sleep_ms(250);
        stop_buzzer(BUZZER1);
        set_buzzer_tone(BUZZER1, 223); 
        sleep_ms(250);
        stop_buzzer(BUZZER1);
        set_buzzer_tone(BUZZER1, 248); 
        sleep_ms(250);
        stop_buzzer(BUZZER1);
        set_buzzer_tone(BUZZER1, 265); 
        sleep_ms(250);
        stop_buzzer(BUZZER1);
        set_buzzer_tone(BUZZER1, 298); 
        sleep_ms(250);
        stop_buzzer(BUZZER1);
        set_buzzer_tone(BUZZER1, 330); 
        sleep_ms(250);
        stop_buzzer(BUZZER1);
        set_buzzer_tone(BUZZER1, 352); 
        sleep_ms(250);
        stop_buzzer(BUZZER1);
        set_buzzer_tone(BUZZER1, 330); 
        sleep_ms(500);
        stop_buzzer(BUZZER1);
        set_buzzer_tone(BUZZER1, 265); 
        sleep_ms(250);
        stop_buzzer(BUZZER1);
        set_buzzer_tone(BUZZER1, 298); 
        sleep_ms(250);
        stop_buzzer(BUZZER1);
        set_buzzer_tone(BUZZER1, 330); 
        sleep_ms(500);
        stop_buzzer(BUZZER1);
        set_buzzer_tone(BUZZER1, 167); 
        sleep_ms(250);
        stop_buzzer(BUZZER1);
        set_buzzer_tone(BUZZER1, 177); 
        sleep_ms(250);
        stop_buzzer(BUZZER1);
        set_buzzer_tone(BUZZER1, 197); 
        sleep_ms(250);
        stop_buzzer(BUZZER1);
        set_buzzer_tone(BUZZER1, 223); 
        sleep_ms(250);
        stop_buzzer(BUZZER1);
        set_buzzer_tone(BUZZER1, 197); 
        sleep_ms(250);
        stop_buzzer(BUZZER1);
        set_buzzer_tone(BUZZER1, 177); 
        sleep_ms(250);
        stop_buzzer(BUZZER1);
        set_buzzer_tone(BUZZER1, 197); 
        sleep_ms(250);
        stop_buzzer(BUZZER1);
        set_buzzer_tone(BUZZER1, 167); 
        sleep_ms(250);
        stop_buzzer(BUZZER1);
        set_buzzer_tone(BUZZER1, 177); 
        sleep_ms(250);
        stop_buzzer(BUZZER1);
        set_buzzer_tone(BUZZER1, 197); 
        sleep_ms(250);
        stop_buzzer(BUZZER1);
        set_buzzer_tone(BUZZER1, 177); 
        sleep_ms(500);
        stop_buzzer(BUZZER1);
        set_buzzer_tone(BUZZER1, 223); 
        sleep_ms(250);
        stop_buzzer(BUZZER1);
        set_buzzer_tone(BUZZER1, 197); 
        sleep_ms(250);
        stop_buzzer(BUZZER1);
        set_buzzer_tone(BUZZER1, 177); 
        sleep_ms(500);
        stop_buzzer(BUZZER1);
        set_buzzer_tone(BUZZER1, 167); 
        sleep_ms(250);
        stop_buzzer(BUZZER1);
        set_buzzer_tone(BUZZER1, 147); 
        sleep_ms(250);
        stop_buzzer(BUZZER1);
        set_buzzer_tone(BUZZER1, 167); 
        sleep_ms(250);
        stop_buzzer(BUZZER1);
        set_buzzer_tone(BUZZER1, 147); 
        sleep_ms(250);
        stop_buzzer(BUZZER1);
        set_buzzer_tone(BUZZER1, 132); 
        sleep_ms(250);
        stop_buzzer(BUZZER1);
        set_buzzer_tone(BUZZER1, 147); 
        sleep_ms(250);
        stop_buzzer(BUZZER1);
        set_buzzer_tone(BUZZER1, 167); 
        sleep_ms(250);
        stop_buzzer(BUZZER1);
        set_buzzer_tone(BUZZER1, 177); 
        sleep_ms(250);
        stop_buzzer(BUZZER1);
        set_buzzer_tone(BUZZER1, 197); 
        sleep_ms(250);
        stop_buzzer(BUZZER1);
        set_buzzer_tone(BUZZER1, 223); 
        sleep_ms(250);
        stop_buzzer(BUZZER1);
        set_buzzer_tone(BUZZER1, 177); 
        sleep_ms(500);
        stop_buzzer(BUZZER1);
        set_buzzer_tone(BUZZER1, 223); 
        sleep_ms(250);
        stop_buzzer(BUZZER1);
        set_buzzer_tone(BUZZER1, 197); 
        sleep_ms(250);
        stop_buzzer(BUZZER1);
        set_buzzer_tone(BUZZER1, 223); 
        sleep_ms(500);
        stop_buzzer(BUZZER1);
        set_buzzer_tone(BUZZER1, 247); 
        sleep_ms(250);
        stop_buzzer(BUZZER1);
        set_buzzer_tone(BUZZER1, 265); 
        sleep_ms(250);
        stop_buzzer(BUZZER1);
        set_buzzer_tone(BUZZER1, 247); 
        sleep_ms(250);
        stop_buzzer(BUZZER1);
        set_buzzer_tone(BUZZER1, 223); 
        sleep_ms(250);
        stop_buzzer(BUZZER1);
        set_buzzer_tone(BUZZER1, 197); 
        sleep_ms(250);
        stop_buzzer(BUZZER1);
        set_buzzer_tone(BUZZER1, 223); 
        sleep_ms(250);
        stop_buzzer(BUZZER1);
        set_buzzer_tone(BUZZER1, 247); 
        sleep_ms(250);
        stop_buzzer(BUZZER1);
        set_buzzer_tone(BUZZER1, 265); 
        sleep_ms(250);
        stop_buzzer(BUZZER1);
        set_buzzer_tone(BUZZER1, 297); 
        sleep_ms(250);
        stop_buzzer(BUZZER1);
        set_buzzer_tone(BUZZER1, 330); 
        sleep_ms(250);
        stop_buzzer(BUZZER1);
        set_buzzer_tone(BUZZER1, 265); 
        sleep_ms(750);
        stop_buzzer(BUZZER1);
}

void canon2() {
    set_buzzer_tone(BUZZER1, 523); // C
    sleep_ms(300);
    stop_buzzer(BUZZER1);
    set_buzzer_tone(BUZZER1, 523); // C
    sleep_ms(300);
    stop_buzzer(BUZZER1);
    set_buzzer_tone(BUZZER1, 587); // D
    sleep_ms(300);
    stop_buzzer(BUZZER1);
    set_buzzer_tone(BUZZER1, 523); // C
    sleep_ms(300);
    stop_buzzer(BUZZER1);
    set_buzzer_tone(BUZZER1, 698); // F
    sleep_ms(300);
    stop_buzzer(BUZZER1);
    set_buzzer_tone(BUZZER1, 659); // E
    sleep_ms(300);
    stop_buzzer(BUZZER1);
    set_buzzer_tone(BUZZER1, 523); // C
    sleep_ms(300);
    stop_buzzer(BUZZER1);
    set_buzzer_tone(BUZZER1, 523); // C
    sleep_ms(300);
    stop_buzzer(BUZZER1);
    set_buzzer_tone(BUZZER1, 587); // D
    sleep_ms(300);
    stop_buzzer(BUZZER1);
    set_buzzer_tone(BUZZER1, 523); // C
    sleep_ms(300);
    stop_buzzer(BUZZER1);
    set_buzzer_tone(BUZZER1, 698); // F
    sleep_ms(300);
    stop_buzzer(BUZZER1);
    set_buzzer_tone(BUZZER1, 659); // E
    sleep_ms(300);
    stop_buzzer(BUZZER1);
    set_buzzer_tone(BUZZER1, 523); // C
    sleep_ms(300);
    stop_buzzer(BUZZER1);
    set_buzzer_tone(BUZZER1, 523); // C
    sleep_ms(300);
    stop_buzzer(BUZZER1);
    set_buzzer_tone(BUZZER1, 698); // F
    sleep_ms(300);
    stop_buzzer(BUZZER1);
    set_buzzer_tone(BUZZER1, 659); // E
    sleep_ms(300);
    stop_buzzer(BUZZER1);
    set_buzzer_tone(BUZZER1, 784); // G
    sleep_ms(300);
    stop_buzzer(BUZZER1);
    set_buzzer_tone(BUZZER1, 523); // C
    sleep_ms(300);
    stop_buzzer(BUZZER1);
    set_buzzer_tone(BUZZER1, 523); // C
    sleep_ms(300);
    stop_buzzer(BUZZER1);
    set_buzzer_tone(BUZZER1, 587); // D
    sleep_ms(300);
    stop_buzzer(BUZZER1);
    set_buzzer_tone(BUZZER1, 523); // C
    sleep_ms(300);
    stop_buzzer(BUZZER1);
    set_buzzer_tone(BUZZER1, 698); // F
    sleep_ms(300);
    stop_buzzer(BUZZER1);
    set_buzzer_tone(BUZZER1, 659); // E
    sleep_ms(300);
    stop_buzzer(BUZZER1);
    set_buzzer_tone(BUZZER1, 523); // C
    sleep_ms(300);
    stop_buzzer(BUZZER1);
    set_buzzer_tone(BUZZER1, 523); // C
    sleep_ms(300);
    stop_buzzer(BUZZER1);
    set_buzzer_tone(BUZZER1, 698); // F
    sleep_ms(300);
    stop_buzzer(BUZZER1);
    set_buzzer_tone(BUZZER1, 659); // E
    sleep_ms(300);
    stop_buzzer(BUZZER1);
    set_buzzer_tone(BUZZER1, 784); // G
    sleep_ms(300);
    stop_buzzer(BUZZER1);
}


void apagarTodosLeds(){
    acendeLedRGB(1, 0, 0, 0);
    acendeLedRGB(2, 0, 0, 0);
    acendeLedRGB(3, 0, 0, 0);
}

int main() {
    stdio_init_all(); // Inicializa a comunicação serial
    init_keypad();    // Configura o teclado
    inicializaLedsRGB(); // Inicializa os LEDs RGB
    
    gpio_init(BUZZER1);
    gpio_set_dir(BUZZER1, GPIO_OUT);
    init_pwm(BUZZER1);

while (true) {
    char key = get_key(); // Lê a tecla pressionada
    if (key) {
        apagarTodosLeds(); // Apaga todos os LEDs antes de acender um novo
        switch (key) {
             case 'A': 
                acendeLedRGB(1, 1, 0, 0); // LED 1 vermelho
                set_buzzer_tone(BUZZER1, 440); // Frequência 440 Hz (Nota Lá)
                sleep_ms(500);
                stop_buzzer(BUZZER1);
                break;
            case 'B': 
                acendeLedRGB(2, 0, 1, 0); // LED 2 verde
                set_buzzer_tone(BUZZER1, 494); // Frequência 494 Hz (Nota Si)
                sleep_ms(500);
                stop_buzzer(BUZZER1);
                break;
            case 'C':
                acendeLedRGB(3, 0, 0, 1); // LED 3 azul
                set_buzzer_tone(BUZZER1, 523); // Frequência 523 Hz (Nota Dó)
                sleep_ms(500);
                stop_buzzer(BUZZER1);
                break;
            case 'D':
                acendeLedRGB(1, 1, 1, 0);
                acendeLedRGB(2, 0, 1, 0);
                acendeLedRGB(3, 0, 0, 1);
                set_buzzer_tone(BUZZER1, 587); // Frequência 587 Hz (Nota Ré)
                sleep_ms(500);
                stop_buzzer(BUZZER1);
                break;
            case '*':
                canon(); // Função específica
                set_buzzer_tone(BUZZER1, 659); // Frequência 659 Hz (Nota Mi)
                sleep_ms(500);
                stop_buzzer(BUZZER1);
                break;
            case '#':
                canon2(); // Função específica
                set_buzzer_tone(BUZZER1, 698); // Frequência 698 Hz (Nota Fá)
                sleep_ms(500);
                stop_buzzer(BUZZER1);
                break;
            case '0':
                acendeLedRGB(1, 1, 0, 0); // LED 1 vermelho
                set_buzzer_tone(BUZZER1, 698); // Frequência 698 Hz (Nota Fá)
                sleep_ms(500);
                stop_buzzer(BUZZER1);
                break;
            case '1':
                acendeLedRGB(1, 0, 1, 0); // LED 1 verde
                set_buzzer_tone(BUZZER1, 293); // Nota Ré (D4) - 293 Hz
                sleep_ms(500);
                stop_buzzer(BUZZER1);
                break;
            case '2':
                acendeLedRGB(1, 0, 0, 1); // LED 1 azul
                set_buzzer_tone(BUZZER1, 329); // Nota Mi (E4) - 329 Hz
                sleep_ms(500);
                stop_buzzer(BUZZER1);
                break;
            case '3':
                acendeLedRGB(2, 1, 0, 0); // LED 2 vermelho
                set_buzzer_tone(BUZZER1, 349); // Nota Fá (F4) - 349 Hz
                sleep_ms(500);
                stop_buzzer(BUZZER1);
                break;
            case '4':
                acendeLedRGB(2, 0, 1, 0); // LED 2 verde
                set_buzzer_tone(BUZZER1, 392); // Nota Sol (G4) - 392 Hz
                sleep_ms(500);
                stop_buzzer(BUZZER1);
                break;
            case '5':
                acendeLedRGB(2, 0, 0, 1); // LED 2 azul
                set_buzzer_tone(BUZZER1, 440); // Nota Lá (A4) - 440 Hz
                sleep_ms(500);
                stop_buzzer(BUZZER1);
                break;
            case '6':
                acendeLedRGB(3, 1, 0, 0); // LED 3 vermelho
                set_buzzer_tone(BUZZER1, 493); // Nota Si (B4) - 493 Hz
                sleep_ms(500);
                stop_buzzer(BUZZER1);
                break;
            case '7':
                acendeLedRGB(3, 0, 1, 0); // LED 3 verde
                set_buzzer_tone(BUZZER1, 523); // Nota Dó (C5) - 523 Hz
                sleep_ms(500);
                stop_buzzer(BUZZER1);
                break;
            case '8':
                acendeLedRGB(3, 0, 0, 1); // LED 3 azul
                set_buzzer_tone(BUZZER1, 587); // Nota Ré (D5) - 587 Hz
                sleep_ms(500);
                stop_buzzer(BUZZER1);
                break;
            case '9':
                acendeLedRGB(1, 1, 1, 1); // LED 1 branco
                set_buzzer_tone(BUZZER1, 659); // Nota Mi (E5) - 659 Hz
                sleep_ms(500);
                stop_buzzer(BUZZER1);
                break;
            default:
                printf("Tecla não associada: %c\n", key);
                break;
        }
        stop_buzzer(BUZZER1); 
        printf("Tecla pressionada: %c\n", key);
    }
    sleep_ms(50); // Pequeno atraso para evitar leituras duplicadas
}

} 