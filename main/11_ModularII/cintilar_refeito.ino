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
  /* Na lógica original, o loop rodava 1x pelos leds do (um for de 16)
    e rodava um loop aleatório de 16.
    Ele não considerava se os leds estavam ligados ou desligados.
    Na minha primeira adaptação, ele acidentalmente ligava os leds no catálogo, não faço a menor ideia do porquê.

    O maior problema aqui eram dois... o primeiro é que tanto na adaptação para o código aqui usando n_led sem o -1,
    ou no original, usando random(16), ele podia criar um out of bounds.

    O outro problema, que deixava o solo led ligado sempre, era que o solo_check checava apenas se é o último
    pca e se o solo led tá ativado, o que é suficiente para identificar em funções pequenas, como ligar led...
    mas não em loop.

    Mesmo que corrigido, ele ainda não iria checar correto pois o endereço do random não é guardado
    em rows em nenum dos casos.

    E isso foi 4 horas da minha vida.

    Nesse código, eu vou fazer o solo led brilhar raramente em comparação com os outros. Sem pular os 16 loops.

  */
  short led;
  for_row{
    
    for_col{
      //post_solo; //Esse não é necessário para esse código. Em teoria.
      short led = random((n_led - 1)); // seleciona um led aleatório, em cada um.
      
      if (led_ligado[row][led]){
      
        if ((row==(n_pca-1)) && (solo_led) &&(col==0)) {
          short reduzir = random(brilho_ino/3);
          short cintilar = random((brilho_ino * 0.75),brilho_ino);
          analogWrite(porta_led, cintilar);

          delay(50);

          analogWrite(porta_led, reduzir);

        }
        else{
          short brilho = brilho_pwm; //brilho_max; // brilho máximo do pwm
          short apagar = sem_brilho; // apaga o led
          short reduzir = random((brilho / 3), apagar); // aleatoriza nunmeros de 1365 até 4096
          short cintilar = random((brilho * 0.75), brilho);  // aleatoriza numeros de 3071.25 até 4095

          pwm[row].setPWM(led, 0, cintilar);
          delay(50);

          pwm[row].setPWM(led, 0, reduzir);
        }

      }// if ligado ends

    } //col ends
  }// row ends
  //delay(500);
}


// void cintilar_loop() { // Cintilar está funcionando nessa aqui mas está completamente bugado ligando ou o solo led ou todos os leds se é a única coisa rodando
//   for_col{
//       short col_cintila = random(n_led); // aleatoriza os leds
//       msg("Col = " + str(col_cintila));
//       short row = random(n_pca);

//       msg("Row = " + str(row));
//       if (led_ligado[row][col_cintila]) {
//         msg("Isso tá bugando por alguma razão");
//         continue;  //se o led tá apagado
//         msg("This went past continue");
//       }
//       //if ( (row == 2) && (col < 0)) col = 0;  //efeito colateral que faz o solo led ter 16x mais chance de piscar
//       if(((row==(n_pca-1))&&(col_cintila>0))&&(solo_led))continue;
//                         //Isso implica que há umachance dos 33 leds não rodarem essa função
      
//       solo_check{
//         // if (led_ligado[2][0]){
//         //   msg("Solo led It is turned on...");
//         //   delay(10000);
          
//         // }
//         short brilho = brilho_ino; //brilho_max; // brilho máximo do pwm
//         short apagar = 0; // apaga o led
//         short reduzir = random((apagar,brilho / 3)); // aleatoriza nunmeros de 0 até 255 / 3
//         short cintilar = random((brilho * 0.75), brilho);  // aleatoriza numeros de 3071.25 até 4095

//         analogWrite(porta_led, cintilar);

//         delay(50);

//         analogWrite(porta_led, reduzir);
//       }
//       else{  
//         short brilho = brilho_pwm; //brilho_max; // brilho máximo do pwm
//         short apagar = sem_brilho; // apaga o led
//         short reduzir = random((brilho / 3), apagar); // aleatoriza nunmeros de 1365 até 4096
//         short cintilar = random((brilho * 0.75), brilho);  // aleatoriza numeros de 3071.25 até 4095

//         pwm[row].setPWM(col_cintila, 0, cintilar);
//         delay(50);

//         pwm[row].setPWM(col_cintila, 0, reduzir);}
//   }
//   //delay(500);
// }

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
