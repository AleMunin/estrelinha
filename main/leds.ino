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
  //dbug debug_time(row,col);
  led_ligado[row][col] = false; // registra ele no catalogo
  time_reset_all(row,col);
}


void liga_aleatorio(){
  if (!TODOS_LIGADOS){
    dbug msg("Sorteando led a ligar");
    short row, col;
    bool achou = false;

    do{
      row = random(n_pca);
      col = random(n_led);

        if ((row == n_pca) && (col > 0)) continue; // não há mais leds aqui

        if (!led_ligado[row][col]){ //se o led tá desligado
          
          liga_led(row,col,is_solo(row,col));
          achou = true; //encerra o loop
        }
        else continue;
    }
    while(!achou);
  }
  else{
    dbug msg("Todos os leds estão ligados. Adicionando mais tempo");
    adiciona_tempo(); // Vai pegar o que tá ligado a mais tempo e resetar a contagem
  }
}

void estrelinha () {
  
}

void modo_brilho(){

}