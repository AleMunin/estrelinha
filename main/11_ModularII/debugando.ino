void bug(){

  if(!DEBUG){
    DEBUG_LED = false;
    DEBUG_TIME = false;
    DEBUG_ROW = false;
    DEBUG_COL = false;
    DEBUG_EYEBLESS = false;
    NO_DELAY = true;
  }
  else{
    dbug msg (F("DEBUG = TRUE"));
    ledbug msg (F("DEBUG_LED = TRUE"));
    tbug msg (F("DEBUG_TIME = TRUE"));
    rowbug msg (F("DEBUG-ROW = TRUE"));
    colbug msg (F("DEBUG-COL = TRUE"));
    lighton msg(F("Os leds estão ligados"));
    lightoff msg (F("Leds estão desligados para saúde visual"));
    nd msg (F("NO_DELAY = TRUE"));
  }
}


void brilho_log(){
  msg("brilho_pwm, brilho_ino: [" + str(brilho_pwm) + "], " + str(brilho_ino));
  msg("min_pwm, min_ino: [" + str(brilho_min_pwm) + "], " + str(brilho_min_ino));
}

void brilho_debug(){
  brilho_log();
  modo_brilho = UM_QUARTO;
  brilho_intensidade();
  brilho_log();
  modo_brilho = DOIS_QUARTOS;
  brilho_intensidade();
  brilho_log();
  modo_brilho = TRES_QUARTOS;
  brilho_intensidade();
  brilho_log();
  modo_brilho = QUATRO_QUARTOS;
  brilho_intensidade();
}

void debug_count(){
  dbug{


  msg("");
  msg("loop: " +str(loop_test));
  loop_test++;
  }
}


//Botoes Emulados

void fake_button_turnon(){  //Finge apertar o botão de ligar, ou o sinal da moedeira
  dbug {  
    if (!FAKE_BTN){
      msg(F("Botao falso foi chamado, mas o modo está desativado"));

      btn_liga = false;
    }
    dbug (F("Botao falso para foi ativado"));
    btn_liga = true;
  }
}

bool debug_request(){ //basicamente um debouce igual ao loop_clique() exclusivo pro botão de debug
  dbug{
    int read = digitalRead(porta_tst);
    if (read != btn_liga_last){
      btn_liga_last = millis();
    }
    if ((millis () - btn_liga_last) > mscChoice){
      btn_liga_now = read;
        if (btn_liga_now == HIGH){
          dbug (F("Btn de teste para foi ativado, simulando a moedeira"));
          btn_liga = true;
        }
        else{
          btn_liga = false;
        }
    }
    btn_liga_last = read;
  }
}

void fake_liga_chance(){  //Aperta o botão falso aleatóriamente
  dbug {
    if ( ( (!TODOS_LIGADOS)&& (random(5) > 3)) || ((TODOS_LIGADOS)&& (random(10) > 1)) ) {
      ledbug msg("");
      ledbug msg(F("o botão vai ser apertado"));
      ledbug msg("");
      fake_button_turnon();
    }
    else{
      ledbug msg(F("O botão não foi apertado dessa vez"));
      btn_liga = false;
    }
  }
}

//---------------------- ROTINAS ------------------------------\\

// Liga todos

void boot(){ //Desliga e liga todos os leds, deixa todos ligados no final para testar.
  msg(F("Boot, all leds"));
  liga_todos();
  delay(2000);
  msg (F("Desligando os leds"));
  desliga_todos();
  delay(2000);
  msg (F("Ligando os leds novamente"));
  liga_todos();
}
// Liga todos...