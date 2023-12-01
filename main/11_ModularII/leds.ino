void liga_led(short row, short col){
  solo_check{
    dbug (msg(F(" ")));
    dbug ledbug msg(F("ligando solo led"));
    lighton analogWrite(porta_led, brilho_ino);
  }
  else{
    lighton pwm[row].setPWM(col, 0, brilho_pwm);
    dbug ledbug msg("ligando pwm led " + str(col));
  }
}

void desliga_led(short row, short col){
  solo_check{
    dbug (msg(F(" ")));
    dbug ledbug msg(F("desligando solo led"));
    dbug (msg(F(" ")));
    analogWrite(porta_led, 0);
  }
  else{
    dbug ledbug msg("desligando pwm led [" + str(row) + "][" + str(col) + "]");
    pwm[row].setPWM(col, 0, sem_brilho);
  }
}



void liga_aleatorio(){
  //if (!btn_liga) return; //Se o sinal do botão n foi apertado
  
  dbug msg(F("liga aleatorio rodou"));
  dbug delay(1000);
  
  if (TODOS_LIGADOS){
    ledbug msg(F("liga_aleatorio: todos os leds já estão ligados"));
    mantem_ligado();
  }
  else{

    bool achou = false;
    short row_while, col_while, while_count;
    while_count = 0; // existe só para debugs
    ledbug msg (F("Um led será selecionado aleatóriamente"));  
    do{
      ledbug  delay(1500);
      if (TODOS_LIGADOS) break; //improvavel mas por precaução

      if (solo_led){
        row_while = random(n_pca-1);
      }
      else{
        row_while = random(n_pca);
      }

      if (row_while == 2) col_while = 0;
      else col_while = random(n_led-1);



      dbug{
        msg("");
        msg ("STOP EVERYTHING");
        delay (1000);
        msg ("ROW ON WHILE LOOP IS..." + str(row_while));
        msg ("COL ON WHILE LOOP IS..." + str(col_while));
        delay (2000);
        msg("");
      }
      
      msg("While loop = " + str(while_count + 0));
      while_count++;

      solo_skip_while; //previne os leds fantasmas se solo_led = true; N é logado em loops

      ledbug msg("dbug de led passou solo skip, [" + str(row_while) + "][" + str(col_while) +"]");
      
      if ( (!led_ligado[row_while][col_while]) || ((row_while==2)&&(col_while==0) && (!solo_ligado)) ) { //se o led tá desligado
        ledbug msg("O led [" + str(row_while) + "][" + str(col_while)  +"] foi selecionado aleatoriamente");
        time_start(row_while,col_while); //liga led e aciona timer
        xelor(row_while,col_while,true);
        achou = true; //encerra o loop
      }
      else {
        ledbug msg("O while rodará novamente pois o led já está ligado, ["+str(row_while)+"]["+str(col_while)+"]");
        
        if (while_count > 12){ // se levou muito tempo

          for_row{
            if (achou) break;
            for_col{
              if (achou) break;

              dbug bip bip_me;
              msg(F(""));
              msg(F(""));
              msg(F("Time out, o led será ligado por ordem crescente"));
              msg(F(""));
              msg(F(""));

              if ((!led_ligado[row][col]) || TST_SOLO_DESLIGADO ){ 
                    //prevenção pode ser um erro aqui. Mas por outro lado ele é o ultimo led mesmo.
                msg("Led ascendido = [" + str(row) + "][" + str(col) + "]");
                msg(F(""));
                msg(F(""));

                time_start(row,col); //liga led e aciona timer
                xelor(row,col,true);

                ledbug if (led_ligado[2][0] == true) msg("solo led ligado = true");
                dbug delay(2000);
                achou = true; //encerra o loop
                break;
              }
            }
          }
        }
        continue;
      }

      
    }
    while(!achou);
    ledbug if (led_ligado[2][0] == true) msg("solo led ligado = true");
    if (solo_ligado) msg("solo_ligado var = true");
    else msg("solo_ligado var = false");
    dbug delay(2000);

    //this was true until the loop on this function
    checa_todos_ligados(); // precisa ser checado imediatamente devido ao interrupt
  }
}

void checa_todos_ligados(){
  bool tudo_ligado = true;
  if (led_ligado[2][0] == true) msg("solo led ligado dentro do checa todos = true");
    if (solo_ligado) msg("solo_ligado dentro do checa todos = true");
    else msg("solo_ligado dentro do checa todos = false");


  dbug delay(2000);
  ledbug msg(F("checa_todos_ligados vai fazer o que deveria"));
  for_row{
    for_col{
      post_solo;
      if (led_ligado[row][col] == false){


        ifTESTE_SOLO {
          
          if (!solo_ligado){
            tudo_ligado = false;
            msg(F("led_ligado[2][0] foi avaliado como falso e solo_ligado confirmou"));
          }
          else{
            msg(F("led_ligado foi avaliado como falso, mas a prevenção corrigiu a função"));
            // é ridiculo que eu tenha que fazer isso
            dbug delay(2000);
          }
        }
        else{
          tudo_ligado = false;
        }
        
        ledbug msg("led desligado encontrado [" + printLed + "]"); //ignore o comentário do [2][0] enquanto prevenção é usada
      }
    }
    
  }
  ledbug {
    if (!tudo_ligado) msg(F("Há leds apagados"));
    else msg(F("Todos os leds estão ligados"));
  }
  TODOS_LIGADOS = tudo_ligado;
}

void auditoria_de_leds(){ // não funciona com prevenção solo_led, evite usar


  /* há alguns leds que simplesmente falharam a contagem e se desligaram.
    eles ficam ligados eternamente mesmo com o catálogo desligado.
    Isso força um reset periódicamente
  */


  if (audit < DOIS_MINUTOS_M){ //impreciso, mas irrelevante
    audit++;
    dbug msg("audit " + str(audit) + " / " + str(DOIS_MINUTOS_M));
  }
  else{
    msg(F("||||||||||||||||||||"));
    msg(F("Auditoria de leds começou"));
    msg(F("||||||||||||||||||||"));
    dbug delay(3000);

    for_row{
      for_col{
        if((!led_ligado[row][col]) || TST_SOLO_DESLIGADO ){
          time_end(row,col);
        }
      }
    }
    audit = 0;
  }
}

void muda_modo_brilho(){
  msg(F("Muda brilho vai alterar o brilho"));
  msg ("Brilho = " + str(modo_brilho));
  msg ("switch_BRILHO = " + str(switch_BRILHO));
  switch_BRILHO++;
  

  if (switch_BRILHO > 4){
    switch_BRILHO = 1; // O ciclo nunca vai pra zero, mas coloquei no switch caso precise mudar no futuro
  } 
  switch(switch_BRILHO){
  
    case 0:
      modo_brilho = DESLIGADO;
    break;

    case 1:
      modo_brilho = UM_QUARTO;
      msg(F("Modo Brilho se tornou Um 1/4"));
    break;

    case 2:
      modo_brilho = DOIS_QUARTOS;
      msg(F("Modo Brilho se tornou Um 2/4"));
    break;
    
    case 3:
      modo_brilho = TRES_QUARTOS;
      msg(F("Modo Brilho se tornou Um 3/4"));
    break;
    
    case 4:
      modo_brilho = QUATRO_QUARTOS;
      msg(F("Modo Brilho se tornou Um 4/4"));
    break;
    }

  msg ("Brilho = " + str(modo_brilho));
  msg ("switch_BRILHO = " + str(switch_BRILHO));
}

void religa_em_modo_brilho(){ 
  for_row{
    for_col{
      if ((row == 2) && (col == 0)){
        if(led_ligado[row][col]) msg(F("solo led está ligado em rebrilho"));
        else msg(F("Solo led está desligado em rebrilho"));
        dbug delay(500);
      }
      post_solo;
      if( (led_ligado[row][col]) || TST_SOLO_LIGADO) liga_led(row,col);
    }
  }
}

void brilho_intensidade(){

  dbug msg("Brilho max era " + str(brilho_pwm) + " e " + str (brilho_ino));
  msg ("Brilho = " + str(modo_brilho));

  switch(modo_brilho){
    case(UM_QUARTO):
      brilho_pwm = (brilho_max*0.25);
      brilho_ino = (255*0.25);
      
      brilho_min_pwm = brilho_max*0.15;
      brilho_min_ino = 255*0.15;
    break;

    case(DOIS_QUARTOS):
      brilho_pwm = (brilho_max*0.5);
      brilho_ino = (255*0.5);

      brilho_min_pwm = brilho_max*0.25;
      brilho_min_ino = 255*0.25;
    break;

    case(TRES_QUARTOS):
      brilho_pwm = (brilho_max*0.75);
      brilho_ino = (255*0.75);

      brilho_min_pwm = brilho_max*0.5;
      brilho_min_ino = 255*0.55;
    break;

    case(QUATRO_QUARTOS):
      brilho_pwm = brilho_max;
      brilho_ino = 255;

      brilho_min_pwm = brilho_max * 0.75;
      brilho_min_ino = 255*0.75;
    break;

  }

  dbug msg("Brilho max agora é " + str(brilho_pwm) + " e " + str (brilho_ino));
  msg ("Brilho = " + str(modo_brilho));

  dbug delay(500);

}

// n tá sendo mais usado
void estrelinha(){ // Da um loop nos leds ligados. Faz o brilho deles alterar.
  for_row{
    for_col{
      post_solo;
      
      if (!led_ligado[row][col]) continue;
      if (random(10>7)){
        ledbug msg("o cintilar ["+printLed+"] foi pulado");
        continue;
      }

      short brilhinho;
      
      solo_check{
        brilhinho = random(brilho_min_ino, brilho_ino);
        lighton analogWrite(porta_led, brilhinho);
      }
      else{
        brilhinho = random(brilho_min_pwm, brilho_pwm);
        lighton pwm[row].setPWM(col, 0, brilhinho);
      }

      ledbug brilho_log();
      ledbug msg("brilinho:" + str(brilhinho));
    }

  }
}

void liga_todos(){
  for_row{
    for_col{
      post_solo;
      time_start(row,col);
      nd delay(300);
      else delay(150);
    }
  }
}

void desliga_todos(){
  for_row{
    for_col{
      post_solo;
      time_end(row,col);
      //time_start(row,col);
      nd delay(300);
      else delay(150);
    }
  }
}
