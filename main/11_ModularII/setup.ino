void setup() {
  MODO=CONFIG;

  Serial.begin(9600);
  randomSeed(analogRead(0)); //stupid thing for random to be anything close to random.
  dbug msg("");
  bug();  //deixe sempre abaixo do serial pra testar coisas
  Wire.begin();
  pwm[0].begin();
  pwm[0].setPWMFreq(1000);


  pwm[1].begin();
  pwm[1].setPWMFreq(1000);

  
  moedeira_setup();
  // attachInterrupt(digitalPinToInterrupt(moedeira), moedaInserida, RISING);


  pinMode(buzzer_pin, OUTPUT);
  bip bip_me;
  short col = 0;
  short row = 0;

  if (solo_led) n_pca++;

  setup_btn_clique ();
  
  muda_tempo();
  brilho_intensidade();

  dbug {
    msg("n_pca = " + str(n_pca));
    //pinMode(porta_led, OUTPUT); //deixaisso aqui, não tira carol
    delay(3000);
    msg (F("Saindo do setup"));
    msg("");
  }

  bip basic_buzz(1000);
  delay(1000);
}
