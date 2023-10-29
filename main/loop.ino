void loop() {

  config_request(); //Checa se quer o modo config
  test_request(); // Checa se quer o modo teste
  

  if (MODO == CONFIG){
    // Ordem dos botões
    if (first_config){  //Garante que não vai haver problema com ascondicionais.
      first_config = false;
      TIME_TYPE = NENHUM_AINDA; // proibe o submenu de agir.
      vezes_apertadas = 0;
      dbug msg(F("O modo config foi rodado pela primeira vez"));
    }

    push_count(); // Checa se precisa resetar o estado de contagem, ou adicionar nela
    confirm_request(); // checa se deseja confirmar o input colocado
    
  }
  else if (MODO == TIME){

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

      break;

      case TESTE_ATUAL: // atualmente testando o que a rotina do modo tempo vai ser
        fake_liga_chance();
        checa_todos_ligados();
        dbug {
          if (TODOS_LIGADOS){
            msg ("");
            msg(F("TODOS OS LEDS FORAM LIGADOS"));
            msg ("");
          }
        }
        liga_aleatorio();
        time_loop();

        estrelinha();
      break;

      dbug {
        loop_test++;
        delay(1000);
      }

    } // switch modo teste

  } // if modo teste
  
}