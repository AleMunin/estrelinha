void setup() {
  
  Serial.begin(9600);
  dbug msg("");
  bug();  //deixe sempre abaixo do serial pra testar coisas
  Wire.begin();
  pwm[0].begin();
  pwm[0].setPWMFreq(1600);

  short col = 0;
  short row = 0;
  
  muda_tempo();
  brilho_intensidade();

  if (solo_led)n_pca++;
  dbug msg("n_pca = " + str(n_pca));
  //pinMode(porta_led, OUTPUT); //deixaisso aqui, não tira carol
  delay(3000);
  dbug msg (F("Saindo do setup"));
  dbug msg("");
}