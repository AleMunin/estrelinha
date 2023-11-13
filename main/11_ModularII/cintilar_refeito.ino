// #include <Wire.h>
// #include <Adafruit_PWMServoDriver.h>

// Defina o endereço I2C das placas PCA9685
// Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

// void cintilar_setup() {
//   Serial.begin(9600);
//   Wire.begin();
//   pwm.begin();
//   randomSeed(analogRead(0)); // para que a função random realmente funcione
//   pwm.setPWMFreq(1000); // frequência recomendada para LEDs
// }

// void cintilar_loop() { //OG
//   for (int i = 0; i < 16; i++) {
//     int led = random(16); // aleatoriza os leds
//     int brilho = 4095; // brilho máximo do pwm
//     int apagar = 4096; // apaga o led
//     int reduzir = random((brilho / 3), apagar); // aleatoriza nunmeros de 1365 até 4096
//     int cintilar = random((brilho * 0.75), brilho);  // aleatoriza numeros de 3071.25 até 4095

//     pwm.setPWM(led, 0, cintilar);
//     delay(50);

//     pwm.setPWM(led, 0, reduzir);

//   }
//   delay(500);
// }


/*  teste 1
*  esse loop roda 16x
* pode haver problemas com a adaptação e com pular
* contanto que seja dificil de notar, tá tudo bem.

*/

void cintilar_loop() {
  for_col{
      short col_cintila = random(n_led); // aleatoriza os leds
      short row = random(n_pca);
      if (!led_ligado[row][col_cintila]) continue;  //se o led tá apagado
      //if ( (row == 2) && (col < 0)) col = 0;  //efeito colateral que faz o solo led ter 16x mais chance de piscar
      if(((row==(n_pca-1))&&(col_cintila>0))&&(solo_led))continue
                        //Isso implica que há umachance dos 33 leds não rodarem essa função
                       

      short brilho = brilho_max; // brilho máximo do pwm
      short apagar = sem_brilho; // apaga o led
      short reduzir = random((brilho / 3), apagar); // aleatoriza nunmeros de 1365 até 4096
      short cintilar = random((brilho * 0.75), brilho);  // aleatoriza numeros de 3071.25 até 4095

      pwm[row].setPWM(col_cintila, 0, cintilar);
      delay(50);

      pwm[row].setPWM(col_cintila, 0, reduzir);
  }
  //delay(500);
}

// void cintilar_loop() {
//   for_row{

//       //Nota: talez
//       short col = random(n_led); // aleatoriza os leds
//       if (!led_ligado[row][col]) continue;  //se o led tá apagado
//       //if ( (row == 2) && (col < 0)) col = 0;  //efeito colateral que faz o solo led ter 16x mais chance de piscar
//       solo_skip;  //basicamente um continue
//                         //Isso implica que há umachance dos 33 leds não rodarem essa função
                       

//       short brilho = brilho_max; // brilho máximo do pwm
//       short apagar = sem_brilho; // apaga o led
//       short reduzir = random((brilho / 3), apagar); // aleatoriza nunmeros de 1365 até 4096
//       short cintilar = random((brilho * 0.75), brilho);  // aleatoriza numeros de 3071.25 até 4095

//       pwm[row].setPWM(col, 0, cintilar);
//       delay(50);

//       pwm[row].setPWM(col, 0, reduzir);
//   }
//   //delay(500);
// }
