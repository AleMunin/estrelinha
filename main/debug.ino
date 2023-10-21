void debug_blink(int time_on, int time_off){ //Usa o led do arduino pra testar sinais. Usa delays

  digitalWrite(LED_BUILTIN, HIGH);
  delay(time_on); // Liga o led

  // Desliga o led
  digitalWrite(LED_BUILTIN, LOW);
  delay(time_off);
}

bool is_solo(short row, short col){ //detecta se é o led solitário
  if (!solo_led) return false;
  if ((row == n_pca) && (col == 0)) return true;
  else return false;
}


void debug_solo(int espera){  //Gradualmente ascende o led solo da porta 3. Does not catalog it

  Serial.println("Ligando led");
  for (int brightness = 0; brightness <= 255; brightness++) {
    analogWrite(porta_led, brightness);
    delay(espera); // Delay for a smoother transition
  }
  Serial.println("Desligando led");

  for (int brightness = 255; brightness >= 0; brightness--) {
    analogWrite(porta_led, brightness);
    delay(espera); // Delay for a smoother transition
  }
}

void debug_time(short row, short col){  // lista o tempo do catalogo.
  msg ("Função debug_time ativada");
  if (led_ligado[row][col]){
    //msg ("led_ligado can be evaluated");
    // msg ("Led [" + str(row) + "]["+ str(col) + "] vai está sob o tempo:");
    // msg ("Millis:");
    // //msg (led_Timer_milis[row][col]);
    // if (led_Timer_milis[row][col] > 0){
    //   msg("led_Timer_milis is bigger than 0");
    // }
    // else msg("led_timer_milis was evaluated less than 0");
    // msg ("Milis: " + str(led_Timer_milis[row][col]));
    // msg ("Minutos " + str(led_Timer_M[row][col]));
    // msg ("Horas " + str(led_Timer_H[row][col]));
    // msg ("Dias " + str(led_Timer_D[row][col]));
    // msg ("Semanas " + str(led_Timer_S[row][col]));
  }
  else{
    msg("it was false");
    // msg ("O led [" + str(row) + "]["+ str(col) + "] está desligado, verifique o código do chamado ou o hardware");
  }
}

void boot(){ // Rotina quando está o set up.

  debug_solo(10);

  
}