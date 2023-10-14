void debug_blink(int time_on, int time_off){ //Usa o led do arduino pra testar sinais.

  digitalWrite(LED_BUILTIN, HIGH);
  delay(time_on); // Liga o led

  // Desliga o led
  digitalWrite(LED_BUILTIN, LOW);
  delay(time_off);
}