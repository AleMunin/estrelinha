void debug_blink(int time_on, int time_off){ //Usa o led do arduino pra testar sinais.

  digitalWrite(LED_BUILTIN, HIGH);
  delay(time_on); // Liga o led

  // Desliga o led
  digitalWrite(LED_BUILTIN, LOW);
  delay(time_off);
}

void debug_solo(int espera){  //Gradualmente ascende o led solo da porta 3.

  Serial.println("Ligando led");
  for (int brightness = 0; brightness <= 255; brightness++) {
    analogWrite(porta_led, brightness);
    delay(espera); // Delay for a smoother transition
  }
  Serial.println("Desligando led");

  for (int brightness = 255; brightness >= 0; brightness--) {
    analogWrite(porta_led, brightness);
    delay(espera); // Delay for a smoother transition
  }
}

void boot(){ // Rotina quando está o set up.

}