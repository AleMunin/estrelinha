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

void cintilar_loop() {
  for (int i = 0; i < 16; i++) {
    int led = random(16); // aleatoriza os leds
    int brilho = 4095; // brilho máximo do pwm
    int apagar = 4096; // apaga o led
    int reduzir = random((brilho / 3), apagar); // aleatoriza nunmeros de 1365 até 4096
    int cintilar = random((brilho * 0.75), brilho);  // aleatoriza numeros de 3071.25 até 4095

    pwm.setPWM(led, 0, cintilar);
    delay(50);

    pwm.setPWM(led, 0, reduzir);

  }
  delay(500);
}
