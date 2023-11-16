
void loop() {

  loop_clique(); // talvez precise de uma array de delay
  
  config_request(); //Checa se quer o modo config
  test_request(TESTE_ATUAL); // Checa se quer o modo teste
  brilho_request(); //checa se quer alterar o modo brilho e altera direto, em qualquer outro modo, incluindo teste 

  
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
    debug_request(); //em modo debug, emula o chamado da moedeira para código abaixo.
    //codigo da moedeira aqui

    checa_todos_ligados(); 

    if ( (MOEDEIRA) || (btn_liga)){  //se foi recebido um sinal da moedeira ou botao de testes

      MOEDEIRA = false; // reseta estado.
      //btn_liga = false;

      liga_aleatorio(); //Liga um ou reseta tempo do led mais antigo.
    }

    //Codigo de cintilar aqui
    cintilar_loop();
    time_loop();
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
        if (!ja_bootou){  //Previne de bootar todo ciclo
          boot();
          ja_bootou = true;
        }
        cintilar_loop();  
        
      break; //------------------------------------------------

      dbug {
        loop_test++;
        //delay(1000);
      }

    } // switch modo teste

  } // if modo teste
  
  
  btn_reset(); // reseta estado dos botões
}