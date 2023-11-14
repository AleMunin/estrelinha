#include <Wire.h> // biblioteca para comunicação I2C - A4 (SDA) e A5 (SCL)
// um resistor pull-up é necessário ao conectar os pinos SDA/SCL - não precisa por causa do PCA que já vem embutido um resistor
#include <Adafruit_PWMServoDriver.h> // Inclui a biblioteca para lidar com o PCA9685

Adafruit_PWMServoDriver pwm[] = { Adafruit_PWMServoDriver(0x40) };

short n_led = 8;
short n_pca = 1;  //digite o numero de PCAs
const short btn_num = 3;

bool solo_led = false; //se true, setup dirá para emular ele como uma pca

#define brilho_max 4095
#define sem_brilho 4096

#define porta_led 3
#define porta_tst 4 //btn de teste

int btn_liga_luz = LOW;
int btn_liga_last = LOW;
int btn_liga_now;


const bool DEBUG = true; // Se falso, todos os outros debugs são falsos
bool DEBUG_LED = true; // debug para funções de led
bool DEBUG_TIME = true;
bool DEBUG_ROW = false;
bool DEBUG_COL = false;
bool DEBUG_EYEBLESS = false;
bool BEEP = true;

bool FAKE_BTN = true;

// NÃO MEXE - Elas já tão prontas

short col=0; //C++ implicou com escopo por razão nenhuma nos defines.
short row=0;
short bti=0;

int loop_test = 0;

// Contadores
bool TODOS_LIGADOS = false;
bool led_ligado[2][15] = {{false}}; //a range da array nunca é alterada em nenhum teste
unsigned long led_timer[2][15] = {{0}}; // elas são estáticas e os loops cortam antes de dar problema
unsigned long start_time[2][15] = {{0}}; // Evita um problema de comparação 

// Estados

bool btn_liga = false;

bool btn_CONFIRMA = false;
bool btn_BRILHO = false;
bool btn_TEMPO = false;

bool first_config = true;
bool first_time = true;

short vezes_apertadas = 0; // 0 = nenhum apertado, valores importantes são sempre maior que 0

unsigned long millis_anterior = 0;  // registra o tempo que levou para ser apertado
#define espera_para_apertar 15000 //Espera para apertar

// Convenience defines


#define dbug if(DEBUG)
#define bip if (BEEP)
#define ledbug if(DEBUG_LED)
#define tbug if(DEBUG_TIME)
#define rowbug if(DEBUG_ROW) // use em combinação com os outros, tbug rowbug para loops de tempo etc
#define colbug if (DEBUG_COL)
#define lighton if(!DEBUG_EYEBLESS)
#define lightoff if(DEBUG_EYEBLESS)

#define msg Serial.println
#define str String
#define bip_me basic_buzz(250)

//loops

#define for_row for(row=0;row<n_pca;row++)
#define for_col for(col=0;col<n_led;col++)
#define for_btn for(bti=0;bti<btn_num;bti++)

#define printLed str(row)+"]["+str(col) 

#define post_solo if(((row==(n_pca-1))&&(col>0))&&(solo_led))break //i tested, this seems to work
#define solo_skip if(((row==(n_pca-1))&&(col>0))&&(solo_led))continue
#define solo_skip_while if(((row_while==(n_pca-1))&&(col_while>0))&&(solo_led))continue

#define solo_check if((row==(n_pca-1))&&(solo_led))


//--------------------- DEFINES DE TEMPO

// Defines de tempo

#define UM_SEGUNDO_M 1000 // 1 segundo em milisegundo
#define DEZ_SEGUNDOS_M 10000 // 1 segundo em milisegundo
#define MEIO_MINUTO_M 30000 // 30 segundos em mili
#define DOIS_MINUTOS_M 120000 // 2 min em mili
#define QUINZE_MINUTOS 900000
#define MEIA_HORA_M 1800000

#define UMA_HORA_M 3600000 
#define TRES_HORAS_M 10800000
#define SEIS_HORAS_M 21600000
#define MEIO_DIA_M 43200000

#define UM_DIA_M 86400000
#define DOIS_DIAS_M 172800000
#define TRES_DIAS_M 259200000
#define QUATRO_DIAS_M 345600000
#define CINCO_DIAS_M 432000000
#define SEIS_DIAS_M 518400000

#define UMA_SEMANA_M 604800000
#define DUAS_SEMANAS_M 1209600000
#define UM_MES_M 2419200000 //dois meses passa da range de long int

// -------------- ENUMS

enum BRILHO {
  DESLIGADO,
  UM_QUARTO,
  DOIS_QUARTOS,
  TRES_QUARTOS,
  QUATRO_QUARTOS
};

BRILHO modo_brilho = TRES_QUARTOS;

short switch_BRILHO = 4;
short brilho_pwm = brilho_max;
short brilho_min_pwm = brilho_max*0.75; //o valor maximo que o brilho pode abaixar
short brilho_ino = 255;
short brilho_min_ino = 255*0.75;  //o valor maximo que o brilho pode abaixar


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
TEMPO_MAX modo_tempo = SEGUNDOS_10;

unsigned long tempo_max = MEIO_MINUTO_M;

enum SELECT_TIME {  //Modo de seleção do TEMPO_MAX
  TESTE,    // Para qualquer coisa
  NENHUM_AINDA,
  SEGUNDOS, // Para testes mais padronizados
  MINUTOS,
  HORAS,
  DIAS,
  QUINZENAS
};

SELECT_TIME TIME_TYPE = SEGUNDOS;

enum GLOBAL_MODE {
  CONFIG, //Espera configuração de botões
  TIME,   //Roda a rotina normal de tempo, com a moedeira
  TEST    //Roda as rotinas de testes
};

GLOBAL_MODE MODO = TEST;

enum TESTS {
  CHECA_LED, //Deixa o boot em modo de espera.
  TESTE_ATUAL // Modo onde você roda o teste que você quiser durante desenvolvimento
};

TESTS modo_teste = TESTE_ATUAL;

bool ja_bootou = false; //lock que evita bootar de novo

bool MOEDEIRA = false; 


