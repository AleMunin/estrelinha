void setup(){

 
  Serial.begin(9600);
  msg("Comunicação estabelecida");
  Wire.begin(); // biblioteca do wire rodando para identificar os PCA
  msg("Protocolo I2C Iniciado");

  for (short i = 0; i < n_pca; i++){
    pwm[i].begin();
    pwm[i].setPWMFreq(max_freq); // n precisa da frequencia maxima, mas
  }
  msg("Placa PCA inicializada");

  if (BEEP){ //Se há um buzzer
    pinMode(buzzer_pin, OUTPUT);
    dbug bip_me;
    if(!TESTANDO) twinkle();
  }
  else msg("Global Beeper offline");

  time_setup(); //Inicializa as arrays timers propriamente

  boot();
  
  msg("Exiting setup...");
}