void setup() {
  
  Serial.begin(9600);
  randomSeed(analogRead(0)); //stupid thing for random to be anything close to random.
  dbug msg("");
  bug();  //deixe sempre abaixo do serial pra testar coisas
  Wire.begin();
  pwm[0].begin();
  pwm[0].setPWMFreq(1000);

  MODO=CONFIG;

  pinMode(buzzer_pin, OUTPUT);
  bip bip_me;
  short col = 0;
  short row = 0;

  if (solo_led)n_pca++; //emula o solo led como uma placa para os loops

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
}