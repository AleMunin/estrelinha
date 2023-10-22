bool debounce_check (int pino){ // pino: o index do botão no arduino
    
  //Ele lê o estado atual do botão, cria um delay, e compara os dois.
  // Retorna falso se houve um debounce, retorna se não houve.
  dbug msg("função debounce ativada");
  bool estado = digitalRead(pino);
  delay(10);
  if (digitalRead(pino) == estado){
      dbug msg("debounce retornado como verdadeiro");
      return true;
  }
  else{
      dbug msg("debounce retornado como falso");
      return false;
    }
}

void btn_liga_led(){
  if (debounce_check(porta_btn_liga)){
    liga_aleatorio();
  }
}

void btn_muda_modo(){
  if (debounce_check(porta_btn_tempo)){
    btn_count_time++;
  }
}

void btn_modo_brilho(){
  
}
 

void novo_modo(){ // adiciona novo modo

  //Permitir detectar o modo de segundos e 30 minutos apenas em (TESTANDO);
}

void btn_on_off_led () {
  if (digitalRead(porta_led)==HIGH) {
    digitalWrite(porta_led, LOW);
  }else{
    digitalWrite(porta_led, HIGH);
  }
}

void keyup_btn_led (){
  if ((btn_clique_led==1) and (btn_desclicado_led==1)) {
    btn_clique_led = 0;
    btn_desclicado_led = 0;
    //btn_on_off_led (); //debug direto pra ligar leds
    liga_aleatorio();
  } 
}


