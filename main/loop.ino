void loop(){
  dbug {
    if (loop_test == 0) msg ("Initializing the first loop");
    msg("We're on loop now");
    loop_test++;
    msg("This is the loop..:");
    msg(str(loop_test));
  }

  debug_blink(50, 50);
  debug_blink(200, 200);
  //pwm[0].setPWM(0, 0, max_freq);
  liga_led(0, 0, false);
  delay(1000);
  desliga_led(0, 0, false);
  delay(1000);

  debug_solo(10); // teste do led solo
  
  tempo_ligado();
}