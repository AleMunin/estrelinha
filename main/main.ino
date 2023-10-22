//Codigo para um Arduino Uno. Se for mudar para mega ou nanos, cheque a configuração de portas.
#include <Wire.h> // Inclui a biblioteca para comunicação I2C
#include <Adafruit_PWMServoDriver.h> // Inclui a biblioteca para lidar com o PCA9685

// ------------------------- PARÂMETROS DO PROJETO ------------------------- \\

const bool TESTANDO = true; //Reduz globais de tempo para pequenos periodos.
const bool DEBUG = true; // Faz testes usando o led local do arduino e retorna msgs de log
const bool BEEP = true; // caso tenha um buzzer instalado.

#define msg Serial.println //Pq cansa digitar isso
#define dbug if (DEBUG) //Deixa o código mais limpo
#define bip if (BEEP) // Mais fácil de rodar codigo
#define bip_me basic_buzz(250)
#define str String

int loop_test = 0;

#define num_placas  1 //Confirme o número de placas PCA
#define leds_por_placas 3 //Confirme o número de leds no pca. Minimo 1 led.
bool solo_led = true; // Se houver um led conectado direto no arduino, marque true

#define buzzer_pin 4 // porta do buzzer no arduino.

// ------------------------- Conectores PCA9685 e o LED solo ------------------------- \\
 sempre são inicializados dois =/

#define porta_btn_liga 7 //botão para ligar o led, ao menos enquanto a moedeira n tá instalada
#define porta_btn_tempo 8 //botão pra mudar o modo tempo
#define porta_led 3 // está assumindo que o led solitário tá na porta 3 do arduino
#define porta_extensor_A 0x40 //Pino analogico do arduino p/ conexão IC2
#define porta_extensor_B 0x41 // Pino analogico, eu acho que é o

int btn_clique_led = 0;
int btn_desclicado_led = 0;

const int n_pca = num_placas;
const int n_led = leds_por_placas - 1; //

#define max_freq 1600 // frequência máxima do PCA

#define brilho_max 4095 // 4095 é o valor de frequencia para deixar o mais aceso possível
#define sem_brilho 4096 //4096 é o valor do led desligado completo por ser out of range.
/* PCA INFO:
  Ao contrário dos PWM do arduino que são valores 8-bit (255), o PCA usa 12-bit.
  Source: https://learn.adafruit.com/16-channel-pwm-servo-driver/faq
*/

//Adafruit_PWMServoDriver pca_1 = Adafruit_PWMServoDriver(); // endereço do IC2 não é necessário, ao contrário de alguns exemplos.
Adafruit_PWMServoDriver pwm[] = { Adafruit_PWMServoDriver(0x40) };

//------------------------- ESTADOS DA MAQUINA ------------------------- \\

enum TEMPO_MAX { //Estado da máquina que define o tempo máximo de brilho.
  SEGUNDOS_TESTE,
  SEGUNDOS_10,
  SEGUNDOS_30,
  MINUTOS_2,
  MINUTOS_15,
  MINUTOS_30,
  HORAS_1,
  HORAS_3,
  HORAS_6,
  HORAS_12,
  DIA_1,
  DIA_2,
  DIA_3,
  DIA_4,
  DIA_5,
  DIA_6,
  SEMANA_1,
  SEMANA_2,
  MES_1
};
TEMPO_MAX modo_tempo = SEGUNDOS_30;

short btn_count_time = 0; // conta quantas vezes o botão de modo tempo foi apertado
short btn_count_time_MAX = 3; // maximo que o contador de botões pode ir antes de resetar

bool TODOS_LIGADOS = false; // Marca true se todos os leds no catálogo estão acesos

bool led_ligado[1][1] = {}; // Catalogo de leds ligados false = desligado, true = ligado. 
unsigned long int led_Timer[1][1] = {}; //milisegundos

void time_reset_all(short row, short col){ // Reseta todos os timers
  //Costumava ter todos os leds
  led_Timer[row][col] = 0;      // reseta tempo total
}

