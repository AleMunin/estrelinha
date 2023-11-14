#define buzzer_pin 2

void basic_buzz(short tempo){ //Buzz basico
  if (!BEEP) return;
  dbug msg("Tocando o buzzer");
  tone(buzzer_pin,261,tempo);
  delay(tempo);
  noTone(buzzer_pin);
}