void liga_led(short row, short col){
  solo_check{
    dbug (msg(F(" ")));
    dbug ledbug msg(F("ligando solo led"));
    lighton analogWrite(porta_led, brilho_ino);
  }
  else{
    lighton pwm[row].setPWM(col, 0, brilho_pwm);
    dbug ledbug msg("ligando pwm led " + str(col));
  }
}

void desliga_led(short row, short col){
  solo_check{
    dbug (msg(F(" ")));
    dbug ledbug msg(F("desligando solo led"));
    dbug (msg(F(" ")));
    analogWrite(porta_led, 0);
  }
  else{
    dbug ledbug msg("desligando pwm led [" + str(row) + "][" + str(col) + "]");
    pwm[row].setPWM(col, 0, sem_brilho);
  }
}



void liga_aleatorio(){
  if (!btn_liga) return; //Se o sinal do botão n foi apertado
  if (TODOS_LIGADOS){
    ledbug msg(F("liga_aleatorio: todos os leds já estão ligados"));
    mantem_ligado();
  }
  else{

    bool achou = false;
    short row_while, col_while, while_count;
    while_count = 0; // existe só para debugs
    ledbug msg (F("Um led será selecionado aleatóriamente"));  
    do{
      ledbug  delay(2000);
      if (TODOS_LIGADOS) break; //improvavel mas por precaução

      row_while = random(n_pca);
      col_while = random(n_led);
      dbug{
        msg("");
        msg ("STOP EVERYTHING");
        delay (1000);
        msg ("ROW ON WHILE LOOP IS..." + str(row_while));
        msg ("COL ON WHILE LOOP IS..." + str(col_while));
        delay (4000);
        msg("");
      }
      ledbug {
        msg("While loop = " + str(while_count + 0));
        while_count++;
      }
      solo_skip_while; //previne os leds fantasmas se solo_led = true; N é logado em loops

      ledbug msg("dbug de led passou solo skip, [" + printLed +"]");
      
      if (!led_ligado[row_while][col_while]){ //se o led tá desligado
        ledbug msg("O led [" + printLed +"] foi selecionado aleatoriamente");
        time_start(row_while,col_while); //liga led e aciona timer
        xelor(row_while,col_while,true);
        achou = true; //encerra o loop
      }
      else {
        ledbug msg("O while rodará novamente pois o led já está ligado, ["+str(row_while)+"]["+str(col_while)+"]");
        continue;
      }
    }
    while(!achou);
  }
}

void checa_todos_ligados(){
  bool tudo_ligado = true;
  ledbug msg(F("checa_todos_ligados vai fazer o que deveria"));
  for_row{
    for_col{
      post_solo;
      if (!led_ligado[row][col]){
        tudo_ligado = false;
        ledbug msg("led desligado encontrado [" + printLed + "]");
      }
    }
    
  }
  ledbug {
    if (!tudo_ligado) msg(F("Há leds apagados"));
    else msg(F("Todos os leds estão ligados"));
  }
  TODOS_LIGADOS = tudo_ligado;
}

void muda_modo_brilho(){
  msg(F("Muda brilho vai alterar o brilho"));
  msg ("Brilho = " + str(modo_brilho));
  msg ("switch_BRILHO = " + str(switch_BRILHO));
  switch_BRILHO++;
  

  if (switch_BRILHO > 4){
    switch_BRILHO = 1; // O ciclo nunca vai pra zero, mas coloquei no switch caso precise mudar no futuro
  } 
  switch(switch_BRILHO){
  
    case 0:
      modo_brilho = DESLIGADO;
    break;

    case 1:
      modo_brilho = UM_QUARTO;
      msg(F("Modo Brilho se tornou Um 1/4"));
    break;

    case 2:
      modo_brilho = DOIS_QUARTOS;
      msg(F("Modo Brilho se tornou Um 2/4"));
    break;
    
    case 3:
      modo_brilho = TRES_QUARTOS;
      msg(F("Modo Brilho se tornou Um 3/4"));
    break;
    
    case 4:
      modo_brilho = QUATRO_QUARTOS;
      msg(F("Modo Brilho se tornou Um 4/4"));
    break;
    }

  msg ("Brilho = " + str(modo_brilho));
  msg ("switch_BRILHO = " + str(switch_BRILHO));
}

void religa_em_modo_brilho(){ 
  for_row{
    for_col{
      if ((row == 2) && (col == 0)){
        if(led_ligado[row][col]) msg(F("solo led está ligado em rebrilho"));
        else msg(F("Solo led está desligado em rebrilho"));
        delay(500);
      }
      post_solo;
      if(led_ligado[row][col]) liga_led(row,col);
    }
  }
}

void brilho_intensidade(){

  dbug msg("Brilho max era " + str(brilho_pwm) + " e " + str (brilho_ino));
  msg ("Brilho = " + str(modo_brilho));

  switch(modo_brilho){
    case(UM_QUARTO):
      brilho_pwm = (brilho_max*0.25);
      brilho_ino = (255*0.25);
      
      brilho_min_pwm = brilho_max*0.15;
      brilho_min_ino = 255*0.15;
    break;

    case(DOIS_QUARTOS):
      brilho_pwm = (brilho_max*0.5);
      brilho_ino = (255*0.5);

      brilho_min_pwm = brilho_max*0.25;
      brilho_min_ino = 255*0.25;
    break;

    case(TRES_QUARTOS):
      brilho_pwm = (brilho_max*0.75);
      brilho_ino = (255*0.75);

      brilho_min_pwm = brilho_max*0.5;
      brilho_min_ino = 255*0.55;
    break;

    case(QUATRO_QUARTOS):
      brilho_pwm = brilho_max;
      brilho_ino = 255;

      brilho_min_pwm = brilho_max * 0.75;
      brilho_min_ino = 255*0.75;
    break;

  }

  dbug msg("Brilho max agora é " + str(brilho_pwm) + " e " + str (brilho_ino));
  msg ("Brilho = " + str(modo_brilho));

  dbug delay(5000);

}

// n tá sendo mais usado
void estrelinha(){ // Da um loop nos leds ligados. Faz o brilho deles alterar.
  for_row{
    for_col{
      post_solo;
      
      if (!led_ligado[row][col]) continue;
      if (random(10>7)){
        ledbug msg("o cintilar ["+printLed+"] foi pulado");
        continue;
      }

      short brilhinho;
      
      solo_check{
        brilhinho = random(brilho_min_ino, brilho_ino);
        lighton analogWrite(porta_led, brilhinho);
      }
      else{
        brilhinho = random(brilho_min_pwm, brilho_pwm);
        lighton pwm[row].setPWM(col, 0, brilhinho);
      }

      ledbug brilho_log();
      ledbug msg("brilinho:" + str(brilhinho));
    }

  }
}

void liga_todos(){
  for_row{
    for_col{
      post_solo;
      time_start(row,col);
      delay(300);
    }
  }
}

void desliga_todos(){
  for_row{
    for_col{
      post_solo;
      time_end(row,col);
      //time_start(row,col);
      delay(300);
    }
  }
}
