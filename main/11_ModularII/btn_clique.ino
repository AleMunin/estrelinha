#define btn_tempo 5
#define btn_brilho 6
#define btn_confirma 7

#define ledVermelho 9
#define ledBranco 10
#define ledVerde 11

int btnNow[3]; // vai receber o status atualizado do btn
int btnLast[3] = {LOW,LOW,LOW}; // recebe o status anterior (começamos com LOW)

int btns[3] = {btn_tempo, btn_brilho, btn_confirma};
int n;
// btn confirma 7, btn brilho 4, btn tempo 8


int cont = 0; // contador de numero de cliques
  //Vezes apertadas já faz isso, mas vou deixar aqui caso precise para uma array

unsigned long mscLast[3]; // armazena o tempo do ultimo debounce
const unsigned long mscChoice = 100; //tempo escolhido para se ter certeza que o botao realmente foi pressionado

void setup_btn_clique () {

  for (n = 0; n < 3; n++) {
    pinMode(btns[n], INPUT);
  }

  pinMode(ledVermelho, OUTPUT);
  pinMode(ledBranco, OUTPUT);
  pinMode(ledVerde, OUTPUT);
}

void vermelho () {
  digitalWrite(ledVermelho, HIGH);
  digitalWrite(ledBranco, LOW);
  digitalWrite(ledVerde, LOW);
}

void branco () {
  digitalWrite(ledVermelho, LOW);
  digitalWrite(ledBranco, HIGH);
  digitalWrite(ledVerde, LOW);
}

void verde () {
  digitalWrite(ledVermelho, LOW);
  digitalWrite(ledBranco, LOW);
  digitalWrite(ledVerde, HIGH);
}

void loop_clique () {
  for (n = 0; n < 3; n++) {
    int read = digitalRead(btns[n]);

    if (read != btnLast[n] ) { // se a leitura atual for diferente da anterior então,
      mscLast[n] = millis (); // reseta o tempo
    }

    if ((millis () - mscLast[n]) > mscChoice) { // se o resultado da expressao for maior que o tempo escolhido para debounce, então
      if (read != btnNow[n]) {
        btnNow[n] = read;
        if (btnNow[n] == HIGH) {
          
          bip bip_me;
          if (n == 0) { //Apenas se modo tempo
             //msg(F("tempo apertado"));
            cont ++;
          }
          //colocar a variável como verdadeiro aqui
          btn_para_global(n, true);
        }
      }else{
        btn_para_global(n, false); //reseta botão para falso
      }
    }
    btnLast[n] = read;  
  }  
}

void btn_para_global(int n, bool stat){
  switch(n){
    case 0: //tempo
      if (stat) vermelho();
      btn_TEMPO = stat;
      dbug if (stat) msg(F("Botão TEMPO apertado"));
    break;

    case 1: //brilho
      if (stat) branco();
      btn_BRILHO = stat;
      dbug if (stat) msg(F("Botão BRILHO apertado"));
    break;

    case 2: //confirma
      if (stat) verde();
      btn_CONFIRMA = stat;
      dbug if (stat) msg(F("Botão CONFIRMA apertado"));
    break;

    default:
      dbug msg(F("Something very wrong in button indexing"));
    break;
  }
  //delay(500);
}
