void setup(){

    //--- Conectores PCA9685 

    Wire.begin(); // biblioteca do wire rodando.
    pca_1.begin();
    //pca_2.begin();
    pca_1.setPWMFreq(max_freq); // Set the PWM frequency (e.g., 1000 = 1000Hz) 1000 seria 25% da potencia
    //pca_2.setPWMFreq(1000); // pode usar o max_freq aqui.

    //--- Inicializando catalogo de leds

    if (DEBUG){
      pinMode(LED_BUILTIN, OUTPUT);
    }
}