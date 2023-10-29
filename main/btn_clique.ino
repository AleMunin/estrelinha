#define btn 4

int btnNow; // vai receber o status atualizado do btn
int btnLast = LOW; // recebe o status anterior (começamos com LOW)

int cont = 0; // contador de numero de cliques

unsigned long mscLast = 0; // armazena o tempo do ultimo debounce
unsigned long mscChoice = 50; //tempo escolhido para se ter certeza que o botao realmente foi pressionado

void setup () {
  pinMode(btn, INPUT);
}

void loop () {

  debounce ();
  numClique ();  // funcao responsavel pelas acoes dependendo do numero de clique

}

void debounce () {
  int read = digitalRead(btn);

  if (read != btnLast ) { // se a leitura atual for diferente da anterior então,
    mscLast = millis (); // reseta o tempo
  }

  if ((millis () - mscLast) > mscChoice) { // se o resultado da expressao for maior que o tempo escolhido para debounce, então
    if (read != btnNow) { 
      btnNow = read;
      if (btnNow == HIGH) {
        cont ++;
      }
    }
  }
  btnLast = read;
}

void numClique () {
  if (cont == 1) {

  }
  if (cont == 2) {

  }
  if (cont == 3) {

  }
  // aqui fica os eventos que serao acionados conforme o numero de cliques
  // precisa criar uma condicao em que, se o numero de cliques nao for o que se espera, então 
  if (cont >= 4) {
    cont = 0;
    //reseta a contagem
  }

}