void loop(){
  debug_blink(50, 50);
  
  Serial.println("This is running from concatenated files");
  debug_blink(200, 200);
  Serial.println("This is some bull bullshit");

  Serial.println("I'm tired and horny");
  //pca_1.setPWM(0, 0, max_freq);
  //pwm[0].setPWM(0, 0, max_freq);

  liga_led(0, 0, false);

 
  delay(1000);
  //pca_1.setPWM(0, 0, 1000);
  //pwm[0].setPWM(0, 0, sem_brilho);
  desliga_led(0, 0, false);

  debug_solo(10); // teste do led solo

  dbug {
    msg("THis is a loop define test");
  }
}