void liga_led(short row, short col, bool solo){
  if (solo){
    //digitalWrite(ledPin[row][col],HIGH); // liga o led
    dbug msg("O led solo do arduino deve ter ligado");
  }
  else{
    pwm[row].setPWM(col, 0, max_freq);
  }
  led_ligado[row][col] = true; // registra ele no catalogo
  time_reset_all(row,col);
  //dbug debug_time(row,col);
}


void desliga_led(short row, short col, bool solo){
  if (solo){
    //digitalWrite(ledPin[row][col],LOW); // desliga o led
    dbug msg("O led solo do arduino deve ter desligado");
  }
  else{
    pwm[row].setPWM(col, 0, sem_brilho);
    dbug msg("O led PCA deve ter desligado");
  }
  dbug debug_time(row,col);
  led_ligado[row][col] = false; // registra ele no catalogo
  time_reset_all(row,col);
}


void estrelinha () {
  
}