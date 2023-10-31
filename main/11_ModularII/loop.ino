void loop() {

  loop_clique(); // talvez precise de uma array de delay
  
  config_request(); //Checa se quer o modo config
  test_request(); // Checa se quer o modo teste

  if (MODO == CONFIG){
    // Ordem dos botões
    if (first_config){  //Garante que não vai haver problema com as condicionais.
      desliga_todos();
      first_config = false;
      TIME_TYPE = NENHUM_AINDA; // proibe o submenu de agir.
      cont = 0;
      vezes_apertadas = 0;
      dbug msg(F("O modo config foi rodado pela primeira vez"));
    }
    
    //---- FIX: ------: push_count(); // Checa se precisa resetar o estado de contagem, ou adicionar nela

    confirm_request(); // checa se deseja confirmar o input colocado
    time_request(); //Checa se no modo config, apertou o botão tempo, adiciona ao contador

    if (MODO != CONFIG){
      dbug{
        msg("");
        msg(F("Saíndo do modo CONFIG"));
        msg("");
      }
    }
  }
  else if (MODO == TIME){

    if (first_time){  //seja gentil
      dbug msg (F("modo TIME"));
      first_time = false;
    } 
    
    //Se botão de tempo e brilho são apertados ao mesmo tempo por 5 segundos
    //entra em modo teste?


  }
  else if (MODO == TEST){

    switch(modo_teste){

      case CHECA_LED:
        if (!ja_bootou){  //Previne de bootar todo ciclo
          boot();
          ja_bootou = true;
        }

      break;  //------------------------------------------------

      case TESTE_ATUAL: // atualmente testando o que a rotina do modo tempo vai ser
        if (!TODOS_LIGADOS) fake_liga_chance(); //por enquanto não vamos adicionar mais tempo 
        checa_todos_ligados(); 
        dbug {
          if (TODOS_LIGADOS){
            msg ("");
            msg(F("TODOS OS LEDS FORAM LIGADOS"));
            msg ("");
          }
        }
        if (!TODOS_LIGADOS) liga_aleatorio();
        time_loop();

        //estrelinha();
      break; //------------------------------------------------

      dbug {
        loop_test++;
        //delay(1000);
      }

    } // switch modo teste

  } // if modo teste
  
}