//Codigo para um Arduino Uno. Se for mudar para mega ou nanos, cheque a configuração de portas.

#include <Wire.h> // Inclui a biblioteca para comunicação I2C
#include <Adafruit_PWMServoDriver.h> // Inclui a biblioteca para lidar com o PCA9685

// ------------------------- PARÂMETROS DO PROJETO ------------------------- \\

const bool TESTANDO = true; //Reduz globais de tempo para pequenos periodos.
const bool DEBUG = true; // Faz testes usando o led local do arduino e retorna msgs de log
const bool BEEP = true; // caso tenha um buzzer instalado.

#define msg Serial.println //Pq cansa digitar isso
#define dbug if (DEBUG) //Deixa o código mais limpo

#define num_placas  1 //Confirme o número de placas PCA
#define leds_por_placas 1 //Confirme o número de leds no pca. SE NÃO HOUVER PLACAS MARQUE COMO ZERO.
bool solo_led = true; // Se houver um led como estrela ele tem que ser confirmado a qui

#define buzzer_pin 4 // porta do buzzer.

// ------------------------- Conectores PCA9685 e o LED solo ------------------------- \\
 sempre são inicializados dois =/

#define porta_led 3 // está assumindo que o ledpin tá na porta 3
#define porta_extensor_A 0x40 //Pino analogico do arduino p/ conexão IC2
#define porta_extensor_B 0x41 // Pino analogico, eu acho que é o

#define max_freq 1600 // frequência máxima do PCA

#define brilho_max 4095 // 4095 é o valor de frequencia para deixar o mais aceso possível
#define sem_brilho 4096 //4096 é o valor do led desligado completo por ser out of range.
/* PCA INFO:
  Ao contrário dos PWM do arduino que são valores 8-bit (255), o PCA usa 12-bit.
  Source: https://learn.adafruit.com/16-channel-pwm-servo-driver/faq
*/

Adafruit_PWMServoDriver pca_1 = Adafruit_PWMServoDriver(porta_extensor_A); // endereço do IC2


//------------------------- ESTADOS DA MAQUINA ------------------------- \\

enum TEMPO_MAX { //Estado da máquina que define o tempo máximo de brilho.
  SEGUNDOS_10,
  SEGUNDOS_30,
  MINUTOS_2,
  MINUTOS_30,
  HORAS_1,
  HORAS_3,
  HORAS_6,
  HORAS_12,
  DIA_1,
  SEMANA_1,
  SEMANA_2,
  MES_1
};

const TEMPO_MAX modo_tempo = SEGUNDOS_30;
bool TODOS_LIGADOS = false; // Marca true se todos os leds no catálogo estão acesos


