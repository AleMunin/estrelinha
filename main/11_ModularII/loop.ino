
void loop() {

  msg(F(" "));
  msg(F("------------------ "));
  msg(F(" "));

  loop_clique(); // talvez precise de uma array de delay
  
  config_request(); //Checa se quer o modo config
  test_request(TESTE_ATUAL); // Checa se quer o modo teste
  brilho_request(); //checa se quer alterar o modo brilho e altera direto, em qualquer outro modo, incluindo teste 

  moedeira_loop(); //Funciona uma vez, em qualquer modo.

  if (creditos > 0) { 
    dbug delay(5000);
    //liga_aleatorio();
    if (MODO == TIME) {
      MOEDEIRA_OK = true;
    }
    novaMoeda = false;
    creditos = 0;
  }		

  
  if (MODO == CONFIG){
    // Ordem dos botões
    if (first_config){  //Garante que não vai haver problema com as condicionais.

      desliga_todos();
      msg(F("O modo config foi rodado pela primeira vez"));
      bip mode_buzz(200);
      dbug delay(300);
      first_config = false;
      TIME_TYPE = NENHUM_AINDA; // proibe o submenu de agir.
      cont = 0;
      vezes_apertadas = 0;
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
      delay(500);
      bip basic_buzz(1000);
    }
  }
  else if (MODO == TIME){

    if (first_time){  //seja gentil
      delay(300);
      mode_buzz(100);
      delay(60);
      mode_buzz(200);
      delay(60);
      mode_buzz(300);


      msg (F("modo TIME"));
      delay(200);
      first_time = false;
    }
    // debug_request(); //em modo debug, emula o chamado da moedeira para código abaixo.

    checa_todos_ligados(); 

    if ( (MOEDEIRA_OK) || (btn_liga)){  //se foi recebido um sinal da moedeira ou botao de testes

      MOEDEIRA_OK = false; // reseta estado.
      btn_liga = false;

      liga_aleatorio(); //Liga um ou reseta tempo do led mais antigo.
    }
    time_loop();
    ledbug delay(400);
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
      //cintilar_loop();  
        
      break; //------------------------------------------------

      dbug {
        loop_test++;
        delay(1000);
      }

    } // switch modo teste

  } // if modo teste
  
  
  btn_reset(); // reseta estado dos botões
}