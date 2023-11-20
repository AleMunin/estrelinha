#define moedeira 2 // para interrupção no arduino uno
#define ledConfirmar 4 // para confirmar o recebimento do sinal da moedeira para o arduíno
#define valorAlmejado 100 // qual valor deseja cobrar?
#define ledAcionar 6 // led apenas para demostrar o evento que vai ser acionado ao atingir o valorAlmejado

volatile bool novaMoeda = false;                  
volatile int pulso;     //contagem de pulso
volatile int timeOut = 0;   //tempo limite após a última moeda inserida
String tipoMoeda; // identificar qual é o valor da moeda que está utilizando (no meu caso, de 1 real e de 50 centavos)
int qualTipoMoeda; // pulso que foi cadastrado na moedeira

int moeda; // valor que irá receber para atingir o valorAlmejado
int totalMoeda; // para calcular o que falta de valor para atingir o valorAlmejado
int creditos = 0; 


void setup() {
  Serial.begin(9600);                 
  attachInterrupt(digitalPinToInterrupt(moedeira), moedaInserida, RISING);

  pinMode(ledConfirmar, OUTPUT);
  pinMode(ledAcionar, OUTPUT);
}

// evento acionado automaticamente antes do loop
void moedaInserida(){
  novaMoeda = true; 
  pulso++;
  digitalWrite(ledConfirmar, HIGH);
  timeOut = 0;
}

void loop() { 
  if (novaMoeda == true){
    // Serial.println(timeOut);
    // Serial.println(" --------- x ---------");
    if(pulso == 2 || timeOut>25){          
      identificaMoeda();

      // Serial.println(moeda);

      if (moeda >= valorAlmejado || totalMoeda >= valorAlmejado) {
        creditos = creditos + 1;
        moeda = moeda - valorAlmejado;  
      }else if (moeda < valorAlmejado) { 
        totalMoeda = totalMoeda + moeda; // salva o valor na memória
        creditos = 0;
      } else { // caso nenhuma das alternativas, não faça nada! }
    
      // Serial.println(totalMoeda);
      // Serial.println(" ~~~~~~~~~~~~~~ ");
      // as vezes o valor fica negativo, mas não tem problema!!

      Serial.println(moeda);
      Serial.println(" centavos restantes para acender os leds, e ");
      Serial.println(creditos);  
      Serial.println(" créditos atuais.");

      // led indicando recebimento do pulso
      digitalWrite(ledConfirmar, LOW);

      // evento a ser acionado se existir créditos
      if (creditos > 0) { 
        digitalWrite(ledAcionar, HIGH);
        delay(1000);
        digitalWrite(ledAcionar, LOW);

        totalMoeda = 0;
        creditos = 0;
      }		
      delay(100);
    }
    timeOut++;
    delay(5);
  }  
}

void identificaMoeda(){
  switch (pulso) { 
    case 1:
      tipoMoeda = "Moeda de 1 real ";
      Serial.println("Tipo: " + tipoMoeda);
      qualTipoMoeda = 1;
      moeda = 100;
      Serial.println(qualTipoMoeda,DEC);  
      Serial.println(" ------- ") ;         
      pulso = 0;
      novaMoeda = false;
      break;
    case 2:
      tipoMoeda = "Moeda de 50 centavos";
      Serial.println("Tipo: " + tipoMoeda);
      qualTipoMoeda = 2;
      moeda = 50;
      Serial.println(qualTipoMoeda,DEC);   
      Serial.println(" ------- ") ;    

      if (totalMoeda == moeda) {
        novaMoeda = true;
      }else {
        pulso = 0;
        novaMoeda = false;
      }
      break;
  }
}
