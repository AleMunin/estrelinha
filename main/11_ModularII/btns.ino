/*  Botões:

  TEMPO
  BRILHO
  CONFIRMA

  BRILHO = Altera o modo brilho em um ciclo. No modo tempo.


  TEMPO = Adiciona o número de contagem no modo CONFIG

    - Varia baseado no estado, mas só adiciona contagem quando está nele

  TEMPO + BRILHO (por 5s) =   MODO = CONFIG

      - Se já está no modo config, reseta para o inicio do modo config

  NENHUM BOTÃO APERTADO POR 10s no MODO config = Reseta contagem.

      - Se mantem no modo de escolha de tempo atual

  CONFIRMA

    - Confirma a escolha de contagem atual, e roda ou pick_time_type ou modos_config

    - Se contagem == 0, som de alerta toca

  BRILHO + TEMPO + CONFIRMA = MODO TESTE de leds

*/

void config_request(){ //Pode ser usado em qualquer modo
  if ( (btn_BRILHO && btn_TEMPO) && (!btn_CONFIRMA )){
    MODO = CONFIG;
    first_config = true; // reseta rotina de setup do config, toda vez
    msg(F(""));
    msg(F("Modo Config pedido por botao"));
    msg(F(""));
  }
}

void time_request(){ //Pode ser usado em qualquer modo
  if (MODO != CONFIG) return;
  if ( (!btn_BRILHO) && (!btn_CONFIRMA) && (btn_TEMPO )){
    vezes_apertadas = cont;  // emenda os dois códigos bem direitinho (eu acho)
    msg("vezes apertadas: " + str(vezes_apertadas));
  }
}

void test_request(){
  if ( (btn_BRILHO) && (btn_TEMPO) && (btn_CONFIRMA )){
    MODO = TEST;
    modo_teste = CHECA_LED;
    ja_bootou = false;
    msg(F(""));
    msg(F("Modo teste pedido por botao"));
    msg(F(""));
  }
}

void confirm_request(){
  if (MODO != CONFIG) return;
  if (vezes_apertadas == 0) return;
  
  if ( (btn_CONFIRMA) && ((!btn_BRILHO) && (!btn_TEMPO))){ //Apenas rode se o input confirma foi tocado
    //confirma o input de contagem atual, chamandoas variaveis la

    if (TIME_TYPE == NENHUM_AINDA){
      dbug msg(F("Não existe TIME_TYPE ainda, será selecionado agora"));
      pick_time_type(); //Seleciona se quer o modo escolher minutos, horas, dias, quinzenas
    }
    else{
      msg(F("Um modo tempo foi selecionado"));
      modos_config(); //Seleciona o número de minutos, horas, dias, quinzenas.
      msg(F("Após a função confirm_request concluir, sairá do modo CONFIG"));
    }
    vezes_apertadas = 0; //redundancia
    cont = 0;
  }
}
