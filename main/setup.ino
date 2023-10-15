void setup(){

  Serial.begin(9600);

  Wire.begin(); // biblioteca do wire rodando para identificar os PCA
  //pca_1.begin();
  //pca_1.setPWMFreq(max_freq); // n precisa da frequencia maxima, mas

  pwm[0].begin();
  pwm[0].setPWMFreq(max_freq); // n precisa da frequencia maxima, mas

  

  if (BEEP){ //Se há um buzzer
    pinMode(buzzer_pin, OUTPUT);
    
    dbug basic_buzz(250);

    if(!TESTANDO) twinkle();
  }

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

}

