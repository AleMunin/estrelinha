bool wait_input(){  //conta quanto tempo está sem um input, antes de resetar o modo
  unsigned long millis_atual = millis();
  if ( millis_atual - millis_anterior > espera_para_apertar) return false;
  else return true;
}


void push_count(){ //conta quantas vezes o botão foi pressionado.

  if (MODO != CONFIG) return;
  
  if (!wait_input()){
    vezes_apertadas = 0;  //reseta contagem.
    //Faz um bip falando que resetou contagem
  }
  else if (btn_TEMPO) {
    millis_anterior = millis(); // registra nova contagem
    vezes_apertadas++;
  }
}

 

void modos_config(){  //Altera modo_tempo baseado em vezes apertadas e em qual TIME_TYPE está

  switch(TIME_TYPE){
    case NENHUM_AINDA: //precaução

    break;

    case SEGUNDOS:
      if (vezes_apertadas == 1){
        modo_tempo = SEGUNDOS_10;
      }
      else if (vezes_apertadas = 2){
        modo_tempo = SEGUNDOS_30;
      }

    break;

    case MINUTOS:
      if (vezes_apertadas == 1){
        modo_tempo = MINUTOS_2;
      }
      else if (vezes_apertadas = 2){
        modo_tempo = MINUTOS_15;
      }
      else if (vezes_apertadas = 3){
        modo_tempo = MINUTOS_30;
      }
    break;

    case HORAS:
      if (vezes_apertadas == 1){
        modo_tempo = HORAS_1;
      }
      else if (vezes_apertadas = 2){
        modo_tempo = HORAS_3;
      }
      else if (vezes_apertadas = 3){
        modo_tempo = HORAS_3;
      }
      else if (vezes_apertadas = 4){
        modo_tempo = HORAS_6;
      }
      else if (vezes_apertadas = 5){
        modo_tempo = HORAS_12;
      }
    break;

    case DIAS:

      switch(vezes_apertadas){ // de 1 a 7 dias
        case 0:
          //nada aqui
          dbug msg(F("seleção de zero dias, deu muito errado"));
        break;

        case 1:
          modo_tempo = DIA_1;
        break;

        case 2:
          modo_tempo = DIA_2;
        break;

        case 3:
          modo_tempo = DIA_3;
        break;

        case 4:
          modo_tempo = DIA_4;
        break;

        case 5:
          modo_tempo = DIA_5;
        break;

        case 6:
          modo_tempo = DIA_6;
        break;

        case 7:
          modo_tempo = SEMANA_1;
        break;
      }
    break;

    case QUINZENAS:

      if (vezes_apertadas == 1){
        modo_tempo = SEMANA_2;
      }
      else if (vezes_apertadas = 2){
        modo_tempo = MES_1;
      }

    break;

  }

  if (vezes_apertadas != 0) muda_tempo(); //altera tempo max, reseta leds, etc
  vezes_apertadas = 0;
  MODO = TIME; //muda estado do switch de loop
}

void pick_time_type(){  // seleciona TIME_TYPE (se quer escolher minutos, horas, dias, quinzenas)
  if ( (TIME_TYPE == NENHUM_AINDA) && (btn_CONFIRMA) ){ //esse if é redundancia de precaução

    dbug msg(F("pick_time_type vai selecionar um modo de escolha"));
    switch(vezes_apertadas){

      case 1:
        TIME_TYPE = SEGUNDOS;
      break;

      case 2:
        TIME_TYPE = MINUTOS;
      break;

      case 3:
        TIME_TYPE = HORAS;
      break;

      case 4:
        TIME_TYPE = DIAS;
      break;

      case 5:
        TIME_TYPE = QUINZENAS;
      break;
    }

    vezes_apertadas = 0;
  }
}

