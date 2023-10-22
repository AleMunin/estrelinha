void liga_led(short row, short col, bool solo = false){
  if (solo){
    digitalWrite(porta_led, HIGH);
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
    digitalWrite(porta_led, LOW);
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


void catalogo_de_ligados(){
  bool tudo_ligado = true;
  short row =0;
  short col = 0;
  for (row; row <= n_pca; row++){
    for (col; col <= n_led; col++){
      //precisa previnir de achar a ultima array de solo leds ou sempre vai marcar false
      if ( (row == n_pca) && (col > 0) ) break;
      dbug msg("Não estão ligados!");
      if(!led_ligado[row][col]) tudo_ligado = false;
    }
  }

  TODOS_LIGADOS = tudo_ligado;
  dbug if (TODOS_LIGADOS) msg("TODOS OS LEDS FORAM LIGADOS");
}
void estrelinha () {
  
}

void modo_brilho(){

}