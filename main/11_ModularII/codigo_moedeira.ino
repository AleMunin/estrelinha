//#define moedeira 2 // para interrupção no arduino uno (copiado para o inicio do arquivo)
#define ledConfirmar 4 // para confirmar o recebimento do sinal da moedeira para o arduíno
#define valorAlmejado 100 // qual valor deseja cobrar?
#define ledAcionar 6 // led apenas para demostrar o evento que vai ser acionado ao atingir o valorAlmejado

const bool moedeira_individual = false; //teste antigo da moedeira com os leds
#define moed_solo if(moedeira_individual)

volatile bool novaMoeda = false;                  
volatile int pulso;     //contagem de pulso
volatile int timeOut = 0;   //tempo limite após a última moeda inserida
String tipoMoeda; // identificar qual é o valor da moeda que está utilizando (no meu caso, de 1 real e de 50 centavos)
int qualTipoMoeda; // pulso que foi cadastrado na moedeira

int moeda; // valor que irá receber para atingir o valorAlmejado
int creditos = 0; 


void moedeira_setup() {
  //Serial.begin(9600);                 
  attachInterrupt(digitalPinToInterrupt(moedeira), moedaInserida, RISING);

  moed_solo{
    pinMode(ledConfirmar, OUTPUT);
    pinMode(ledAcionar, OUTPUT);
  }

}

// evento acionado automaticamente antes do loop
void moedaInserida(){
  novaMoeda = true; 
  pulso++;

  moed_solo digitalWrite(ledConfirmar, HIGH);

  timeOut = 0;
}

void identificaMoeda(){
  switch (pulso) { 
    case 1:
      tipoMoeda = "Moeda valor único ";
      Serial.println("Tipo: " + tipoMoeda);
      qualTipoMoeda = 1;
      moeda = 100;
      Serial.println(qualTipoMoeda,DEC);  
      Serial.println(" ------- ") ;         
      pulso = 0;
      novaMoeda = false;
      break;
  }
}


void moedeira_loop() { 
  if (novaMoeda == true){

    if(pulso == 1 || timeOut>25){          
      identificaMoeda();

      // Serial.println(moeda);

      if (moeda >= valorAlmejado || totalMoeda >= valorAlmejado) {
        creditos = creditos + 1;
        moeda = moeda - valorAlmejado;

        //Essa é a única parte que interage com o resto do código

        MOEDEIRA_OK = true;
      }
      
      else { // caso nenhuma das alternativas, não faça nada!
      }

      Serial.println(moeda);
      Serial.println(F(" centavos restantes para acender os leds, é "));
      Serial.println(creditos);  
      Serial.println(F(" créditos atuais."));

      // led indicando recebimento do pulso
      moed_solo digitalWrite(ledConfirmar, LOW);

      // evento a ser acionado se existir créditos
      if (creditos > 0) { 
        moed_solo digitalWrite(ledAcionar, HIGH);
        delay(1000);
        moed_solo digitalWrite(ledAcionar, LOW);

        creditos = 0;
      }		
      delay(100);
    }
    timeOut++;
    delay(5);
  }  
}
