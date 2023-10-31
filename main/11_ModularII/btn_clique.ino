#define btn_tempo 4
#define btn_brilho 7
#define btn_confirma 8

int btnNow[3]; // vai receber o status atualizado do btn
int btnLast[3] = {LOW,LOW,LOW}; // recebe o status anterior (começamos com LOW)

int btns[3] = {btn_tempo, btn_brilho, btn_confirma};
int n;
// btn confirma 7, btn brilho 4, btn tempo 8


int cont = 0; // contador de numero de cliques
  //Vezes apertadas já faz isso, mas vou deixar aqui caso precise para uma array

unsigned long mscLast[3]; // armazena o tempo do ultimo debounce
const unsigned long mscChoice = 50; //tempo escolhido para se ter certeza que o botao realmente foi pressionado

void setup_btn_clique () {

  for (n = 0; n < 3; n++) {
    pinMode(btns[n], INPUT);
  }
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
        else{
          btn_para_global(n, false);
        }
      }else{
        //colocar a variável como falso aqui
        
      }
    }
    btnLast[n] = read;  
  }  
}

void btn_para_global(int n, bool stat){
  switch(n){
    case 0: //tempo
      btn_TEMPO = stat;
      dbug if (stat) msg(F("Botão TEMPO apertado"));
    break;

    case 1: //brilho
      btn_BRILHO = stat;
      dbug if (stat) msg(F("Botão BRILHO apertado"));
    break;

    case 2: //confirma
      btn_CONFIRMA = stat;
      dbug if (stat) msg(F("Botão CONFIRMA apertado"));
    break;

    default:
      dbug msg(F("Something very wrong in button indexing"));
    break;
  }
  //delay(500);
}
