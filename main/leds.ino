void liga_led(short row, short col, bool solo){
  if (solo){
    //digitalWrite(ledPin[row][col],HIGH); // liga o led
    dbug msg("O led solo do arduino deve ter ligado");
  }
  else{
    pwm[row].setPWM(col, 0, max_freq);
  }
  led_ligado[row][col] = true; // registra ele no catalogo
}


void desliga_led(short row, short col, bool solo){
  if (solo){
    //digitalWrite(ledPin[row][col],LOW); // desliga o led
    dbug msg("O led solo do arduino deve ter ligado");
  }
  else{
    pwm[row].setPWM(col, 0, sem_brilho);
  }
  led_ligado[row][col] = false; // registra ele no catalogo
}