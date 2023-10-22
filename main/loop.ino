void loop(){
  dbug {
    if (loop_test == 0) msg ("Initializing the first loop");
    else msg("We're on loop now");
    loop_test++;
    msg("This is the loop..:");
    msg(str(loop_test));
  }

  //--- Funções de botões
  //if (TESTANDO) btn_liga_led();
  //btn_muda_modo();
  //btn_modo_brilho();
  
  if ((digitalRead(porta_btn_liga) == HIGH) && (debounce_check (porta_btn_liga))){
    btn_clique_led = 1;
    btn_desclicado_led = 0;
  }else{
    btn_desclicado_led = 1;
  }
  keyup_btn_led ();
  //
  contador();
  catalogo_de_ligados(); // checa se todos os leds tão ligados

  //delay(1000);

  //debug_solo(10); // teste do led solo
  dbug{ 
    msg(" ");
    msg(" ");
    msg(" ");
  }
}