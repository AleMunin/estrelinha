void setup(){


  Serial.begin(9600);
  msg("Comunicação estabelecida");
  Wire.begin(); // biblioteca do wire rodando para identificar os PCA
  msg("Protocolo I2C Iniciado");

  
  pwm[0].begin();
  pwm[0].setPWMFreq(max_freq); // n precisa da frequencia maxima, mas
  msg("Placa PCA inicializada");

  msg("Still on setup");
  if (BEEP){ //Se há um buzzer
    pinMode(buzzer_pin, OUTPUT);

    dbug bip_me;

    if(!TESTANDO) twinkle();
  }
  else msg("Global Beeper offline");

  
  msg("Exiting setup...");
}

