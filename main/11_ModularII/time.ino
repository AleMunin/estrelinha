void xelor(short row, short col, bool stat ){ // stat = true liga, false desliga
  if(stat){
    led_ligado[row][col] = true;
    start_time[row][col] = millis();  //Previne problemas com comparação
  }
  else{
    led_ligado[row][col] = false;
    start_time[row][col] = 0;
  }
  led_timer[row][col] = 0;  //previne comparação no primeiro ciclo, de desligar o led, por usar millis();
}

void time_start(short row, short col){  //Liga e cataloga o led como ligado
  if (col < n_led) {
    post_solo_return;
    lighton liga_led(row, col); //se os leds tão ativados, use isso
    led_ligado[row][col] = true;
  }
}

void time_end(short row, short col){
  //if (col < n_led) { //segurança desnecessária
  post_solo_return;
  desliga_led(row,col);
  xelor(row,col,false);
   
  //}
  //led_ligado[row][col] = false; //xelor does that
  
}


void tempo_acabou(short row, short col, bool new_mode = false){
  unsigned long int time_limit = tempo_max;
  //Isso era usando o contador geral
  if ((led_timer[row][col] > time_limit) || (new_mode)){ // Esse é usando milisegundos
    tbug msg (F("O tempo do led acabou"));
    lighton time_end(row, col);
  }
}


void mantem_ligado(){
  if (!TODOS_LIGADOS) return;

  unsigned long int maior_tempo_ligado = 0;
  short biggest_row = 0;
  short biggest_col = 0;
  

  for_row{
    for_col{
      post_solo;
      if(!led_ligado[row][col]) continue; //se led tá desligado ignore
      
      if ( led_timer[row][col] > maior_tempo_ligado){
          maior_tempo_ligado = led_timer[row][col];
          biggest_row = row;
          biggest_col = col;
      }
    }
  }
  

  ledbug msg("zerando [" +str(biggest_row)+"]["+str(biggest_col)  +"]");
  xelor(biggest_row,biggest_col,true);// Reseta o tempo
  
}


void contagem(short row, short col){


  // if (led_ligado[row][col]){
  //   led_timer[row][col]++;
  //   tbug msg ( "O led ["  + printLed +"] foi considerado ligado, time++ em " + str(led_timer[row][col]) );
  // }
  if (led_ligado[row][col]){

    unsigned long tempo_atual = millis();    
    led_timer[row][col] = millis() - start_time[row][col];  //start_time foi iniciado em xelor
    msg (tempo_atual);
    msg("menos...");
    msg (start_time[row][col]);
    msg("da....");
    msg (led_timer[row][col]);
    tbug msg ( "O led ["  + printLed +"] foi considerado ligado, millis: " + str(led_timer[row][col]) + " de " + str(tempo_max));
  
    dbug delay(1000);
  }

}

void time_loop(){
  tbug msg (F("Time loop começou"));
  for_row{
      for_col{
      post_solo;
      contagem(row,col);  //por enquanto row n é adicionado
      tempo_acabou(row,col);
    }
  }
  tbug msg (F("Time loop terminou"));
}


void muda_tempo(){
  tbug msg("tempo_max:" +str(tempo_max));

  switch (modo_tempo) {
    
    case SEGUNDOS_TESTE:
      // Levae this for when you want to test stuff.
    break;

    case SEGUNDOS_10:
      tempo_max = DEZ_SEGUNDOS_M;
    break;

    case SEGUNDOS_30:
      tempo_max = MEIO_MINUTO_M;
    break;

    case MINUTOS_2:
      dbug tempo_max = 20000;
      else tempo_max = DOIS_MINUTOS_M;
    break;

    case MINUTOS_15:
      //dbug tempo_max = 30000;
      tempo_max = QUINZE_MINUTOS;
    break;

    case MINUTOS_30:
      //dbug tempo_max = 40000;
      tempo_max = MEIA_HORA_M;
    break;

    case HORAS_1:
      //dbug tempo_max = 50000;
      tempo_max = UMA_HORA_M;
    break;

    case HORAS_3:
      //dbug tempo_max = 70000;
      tempo_max = TRES_HORAS_M;
    break;

    case HORAS_6:
      tempo_max = SEIS_HORAS_M;
    break;

    case HORAS_12:
      tempo_max = MEIO_DIA_M;
    break;

    case DIA_1:
      tempo_max = UM_DIA_M;
    break;

    case DIA_2:
      tempo_max = DOIS_DIAS_M;
    break;

    case DIA_3:
      tempo_max = TRES_DIAS_M;
    break;

    case DIA_4:
      tempo_max = QUATRO_DIAS_M;
    break;

    case DIA_5:
      tempo_max = CINCO_DIAS_M;
    break;

    case DIA_6:
      tempo_max = SEIS_DIAS_M;
    break;


    case SEMANA_1:
      tempo_max = UMA_SEMANA_M;
    break;

    case SEMANA_2:
      tempo_max = DUAS_SEMANAS_M;
    break;

    case MES_1:
      tempo_max = UM_MES_M;
    break;  
  }
  tbug msg("tempo_max:" +str(tempo_max));
  tbug msg("");
  tbug msg(F("O novo modo resetará todos os leds"));
  tbug msg("");

  for_row{
    for_col{
      //post_solo;

      tempo_acabou(row,col,true); // will reset and turn off all the leds.
    }
  }
  //chama função de resetar tudo
}

