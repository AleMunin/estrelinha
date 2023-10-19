//Codigo para um Arduino Uno. Se for mudar para mega ou nanos, cheque a configuração de portas.

/*	buggy time
The time counter arrays are either causing something wrong that I have no idea why it is doing it, or my hardware that is alrerady showing
issues with set up and loop is way faultier than just a small transfer issue.

the debug_time function resets the loop() function after anything, even just a message, runs there.
all the array seems to be initialized properly.
If the if statements on the debug_time are commented out, even just regular messages, the loop cycle works normally.
*/


#include <Wire.h> // Inclui a biblioteca para comunicação I2C
#include <Adafruit_PWMServoDriver.h> // Inclui a biblioteca para lidar com o PCA9685

// ------------------------- PARÂMETROS DO PROJETO ------------------------- \\

const bool TESTANDO = true; //Reduz globais de tempo para pequenos periodos.
const bool DEBUG = true; // Faz testes usando o led local do arduino e retorna msgs de log
const bool BEEP = true; // caso tenha um buzzer instalado.

#define msg Serial.println //Pq cansa digitar isso
#define dbug if (DEBUG) //Deixa o código mais limpo
#define bip if (BEEP) // Mais fácil de rodar codigo
#define bip_me basic_buzz(250);
#define str String

int loop_test = 0;

#define num_placas  1 //Confirme o número de placas PCA
#define leds_por_placas 1 //Confirme o número de leds no pca. Minimo 1 led.
bool solo_led = true; // Se houver um led como estrela ele tem que ser confirmado a qui

#define buzzer_pin 4 // porta do buzzer.

// ------------------------- Conectores PCA9685 e o LED solo ------------------------- \\
 sempre são inicializados dois =/

#define porta_led 3 // está assumindo que o ledpin tá na porta 3
#define porta_extensor_A 0x40 //Pino analogico do arduino p/ conexão IC2
#define porta_extensor_B 0x41 // Pino analogico, eu acho que é o

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
const TEMPO_MAX modo_tempo = SEGUNDOS_30;
bool TODOS_LIGADOS = false; // Marca true se todos os leds no catálogo estão acesos

bool led_ligado[n_pca][n_led] = {}; // Catalogo de leds ligados false = desligado, true = ligado. 
unsigned long int led_Timer[n_pca][n_led] = {}; //milisegundos

unsigned short led_Timer_milis[n_pca][n_led] = {}; // 1 min = 60,000 milis. unsigned tem o valor maximo de 65,535
short led_Timer_M[n_pca][n_led] = {}; //minuto que o led tá ligado
short led_Timer_H[n_pca][n_led] = {}; //Horas logadas dele ligado (resetará ao chegar em 721)
short led_Timer_D[n_pca][n_led] = {}; // Dias logados (resetará ao chegar em 31)
short led_Timer_S[n_pca][n_led] = {}; // Semanas logadas (resetará ao chegar em 5)

unsigned long int tempo_permitido[n_pca][n_led] = {};


/*  Configuração das array:
*   Contanto que forem marcados ao construir, o algoritmo não liga se há 1, 2, ou 3 placas aonde diz respeito da array.
*   Ele sempre vai:
*    1. Assumir que o solo_led, se houver um, ficará no último endereço.
*    2. Assumir que há pelo menos um led conectado na placa registrada.
*   
*   Caso queira expandir para mais placas, se preocupe não com os contadores aqui mas com a declaração de Adafruit_PWMServoDriver,
*   onde a placa e a saida precisam ser declaradas.
*/

/* Tempo permitido
*  O seu valor máximo é baseado no enum TEMPO_MAX.
*  Se o modo SEGUNDOS_30 é ligado, cada led ligado ganha 30 segundos por moeda.
*  Logo seu valor é de 30000 milisegundos. E se mais uma moeda vier depois de todos estarem acesos, ele ganha mais 30mil milisegundos.
*  1 Dia seria apenas o valor de 1. E quando a comparação vem, é avaliada em 1 dia.
*/
