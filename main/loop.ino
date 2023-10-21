void loop(){
  dbug {
    if (loop_test == 0) msg ("Initializing the first loop");
    msg("We're on loop now");
    loop_test++;
    msg("This is the loop..:");
    msg(str(loop_test));
  }

  //--- Funções de botões
  if (TESTANDO) btn_liga_led();
  btn_muda_modo();
  btn_modo_brilho();


  //
  contador();

  //debug_solo(10); // teste do led solo
  dbug{ 
    msg(" ");
    msg(" ");
    msg(" ");
  }
}