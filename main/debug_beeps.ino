void basic_buzz(short tempo){ //Buzz basico
  if (!BEEP) return void();
  dbug msg("Tocando o buzzer");
  tone(buzzer_pin,261,tempo);
  delay(tempo);
  noTone(buzzer_pin);
}

void twinkle(){ // Thanks to AbhishekGhosh / Arduino-Buzzer-Tone-Codes  https://github.com/AbhishekGhosh/Arduino-Buzzer-Tone-Codes
  if (!BEEP) return void();
  int speakerPin = buzzer_pin;
  int length = 15; // the number of notes

  //twinkle twinkle little star
  char notes[] = "ccggaag ffeeddc ggffeed ggffeed ccggaag ffeeddc "; // a space represents a rest
  int beats[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 };
  int tempo = 300;


  for (int i = 0; i < length; i++) {
    if (notes[i] == ' ') {
      delay(beats[i] * tempo); // rest
    } else {
      playNote(notes[i], beats[i] * tempo);
    }
    
    // pause between notes
    delay(tempo / 2); 
  }
}

void playTone(int tone, int duration) {
  int speakerPin = buzzer_pin;

  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone);
  }
}

void playNote(char note, int duration) {
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };
  
  // play the tone corresponding to the note name
  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}