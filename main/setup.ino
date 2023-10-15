void setup(){

  Serial.begin(9600);

  Wire.begin(); // biblioteca do wire rodando para identificar os PCA
  pca_1.begin();
  pca_1.setPWMFreq(max_freq);

  short n_pca = num_placas;
  short n_led = leds_por_placas;

  dbug msg("THis is a define test");
/*  Configuração das array:
*   Contanto que forem marcados ao construir, o algoritmo não liga se há 1, 2, ou 3 placas aonde diz respeito da array.
*   Ele sempre vai:
*    1. Assumir que o solo_led, se houver um, ficará no último endereço.
*    2. Assumir que há pelo menos um led conectado na placa registrada.
*   
*   Caso queira expandir para mais placas, se preocupe não com os contadores aqui mas com a declaração de Adafruit_PWMServoDriver,
*   onde a placa e a saida precisam ser declaradas.
*/

  bool led_ligado[n_pca][n_led]; // Catalogo de leds ligados false = desligado, true = ligado. 
  unsigned long int led_Timer[n_pca][n_led] = {}; //milisegundos
  int led_Timer_H[n_pca][n_led] = {}; //Horas logadas dele ligado (resetará ao chegar em 721)
  int16_t led_Timer_D[n_pca][n_led] = {}; // Dias logados (resetará ao chegar em 31)
  int16_t led_Timer_S[n_pca][n_led] = {}; // Semanas logadas (resetará ao chegar em 5)



}

