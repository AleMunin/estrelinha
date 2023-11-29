#define buzzer_pin 6 //originalmente 2

void basic_buzz(short tempo){ //Buzz basico
  if (!BEEP) return;
  dbug msg("Tocando o buzzer");
  tone(buzzer_pin,261,tempo);
  delay(tempo);
  noTone(buzzer_pin);
}

void tempo_bip(){ //toca baseado no número de vezes apertadas
  if (!BEEP) return;
  short i;
  for (i = 0; i < vezes_apertadas; i++){
    basic_buzz(150);
  }
}