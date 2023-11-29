#define moedeira 2 // para interrupção no arduino uno (copiado para o inicio do arquivo)
#define valorAlmejado 100 // qual valor deseja cobrar?

const bool moedeira_individual = false; //teste antigo da moedeira com os leds
#define moed_solo if(moedeira_individual)

bool novaMoeda = false;

volatile int moeda = 0; // valor que irá receber para atingir o valorAlmejado
int creditos = 0; 


void moedeira_setup() {

  attachInterrupt(digitalPinToInterrupt(moedeira), moedaInserida, FALLING);

}

// evento acionado automaticamente antes do loop
void moedaInserida(){
  moeda = 100;
  basic_buzz(250);
  novaMoeda = true; 
}

void moedeira_loop() { 
  if (novaMoeda == true){
    if (moeda >= valorAlmejado) {
      creditos = creditos + 1;
      moeda = moeda - valorAlmejado;

    }else { 
      // caso nenhuma das alternativas, não faça nada!
    }

    Serial.println(moeda);
    Serial.println(F(" centavos restantes para acender os leds, e "));
    Serial.println(creditos);  
    Serial.println(F(" créditos atuais."));

  }  
} 