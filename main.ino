//Codigo para um Arduino Uno. Se for mudar para mega ou nanos, cheque a configuração de portas.

#include <Wire.h> // Inclui a biblioteca para comunicação I2C
#include <Adafruit_PWMServoDriver.h> // Inclui a biblioteca para lidar com o PCA9685


//----------- DECLARE GLOBAIS AQUI ---------------

const bool TESTANDO = true; //Reduz globais de tempo para pequenos periodos.
const bool DEBUG = true; // Faz testes usando o led local do arduino e retorna msgs de log


    //--- Pinos para outras coisas

//#define solo_pwm <valor>  //O 33º PWM que é conectado com o arduino Uno

    //Solo led tests

    const int ledPin = 3; // Define the LED pin (port 1)

    //--- Conectores PCA9685

#define porta_extensor_A 0x40 //Pino analogico do arduino p/ conexão IC2
//#define saida_extensor_B = 0x41 // Pino analogico, eu acho que é o 41

#define max_frequency_PCA 1600

#define extensor_liga_max 4095 // 4095 é o valor de frequencia para deixar o mais aceso possível
#define extensor_desliga 4096 // 4096 é o valor do led desligado completo
                                // setPWM(pin, 0, 4096) = setPWM(pin, 0, extensor_desliga)
                                // https://learn.adafruit.com/16-channel-pwm-servo-driver/faq


Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(porta_extensor_A); // endereço do IC2
//Adafruit_PWMServoDriver pwm2 = Adafruit_PWMServoDriver(saida_extensor_B); // endereço do IC2

    // Variáveis de estado

bool TODOS_LIGADOS = false; // Marca true se todos os leds no catálogo estão acesos

//bool led_ligado[1][15] ={}; //false = desligado, true = ligado

void setup(){

    //--- Conectores PCA9685 

    Wire.begin(); // biblioteca do wire rodando.
    pwm1.begin();
    //pwm2.begin();
    pwm1.setPWMFreq(max_frequency_PCA); // Set the PWM frequency (e.g., 1000 = 1000Hz) 1000 seria 25% da potencia
    //pwm2.setPWMFreq(1000); // pode usar o max_frequency_PCA aqui.

    //--- Inicializando catalogo de leds

    if (DEBUG){
      pinMode(LED_BUILTIN, OUTPUT);
    }
}

void loop(){
    //delay(500);
    pwm1.setPWM(0, 0, max_frequency_PCA);
    delay(1000);
    //pwm1.setPWM(0, 0, 1000);
    pwm1.setPWM(0, 0, extensor_desliga);

    debug_blink(50);


    // Gradually increase the LED brightness
    for (int brightness = 0; brightness <= 255; brightness++) {
        analogWrite(ledPin, brightness);
        delay(10); // Delay for a smoother transition
    }

    // Gradually decrease the LED brightness
    for (int brightness = 255; brightness >= 0; brightness--) {
        analogWrite(ledPin, brightness);
        delay(10); // Delay for a smoother transition
    }
}

// -------------Declare funções aqui ----------------


void led_test(int channel){
    //pwm1.setPWM(channel, 0, 4095); // endereço, tempo do ciiclo pra ligar, ou algo assim, 
}

void debug_blink(int time){
  digitalWrite(LED_BUILTIN, HIGH);
  delay(time); // Wait for 1 second

  // Turn the LED off
  digitalWrite(LED_BUILTIN, LOW);
  delay(time); // Wait for 1 second
}