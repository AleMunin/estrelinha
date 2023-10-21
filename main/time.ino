
void time_setup(){
  dbug msg("Dando valor 0 a todos leds");
  short row =0;
  short col = 0;
  for (row=0; row < n_pca; row++){

    for (col=0; col < n_led; col++){
      //Até as faixas não existentes precisam ser inicializadas para evitar erros
      led_ligado[row][col] = false; // registra ele no catalogo
      time_reset_all(row,col); // Nesse contexto inicializa todos os timers.
    }
  }
}


#define UM_MINUTO 60000
#define UMA_HORA 60 //milisegundos, talvez mudar
#define UM_DIA 24 // 24h
#define UMA_SEMANA 7 // 7 dias
#define UM_MES 4 //4 semanas


#define UM_SEGUNDO_M 1000 // 1 segundo em milisegundo
#define DEZ_SEGUNDOS_M 1000 // 1 segundo em milisegundo
#define MEIO_MINUTO_M 30000 // 30 segundos em mili
#define DOIS_MINUTOS_M 120000 // 2 min em mili
#define QUINZE_MINUTOS 900000
#define MEIA_HORA_M 1800000

#define UMA_HORA_M 3600000 
#define TRES_HORAS_M 10800000
#define SEIS_HORAS_M 21600000
#define MEIO_DIA_M 43200000

#define UM_DIA_M 86400000
#define DOIS_DIAS_M 172800000
#define TRES_DIAS_M 259200000
#define QUATRO_DIAS_M 345600000
#define CINCO_DIAS_M 432000000
#define SEIS_DIAS_M 518400000

#define UMA_SEMANA_M 604800000
#define DUAS_SEMANAS_M 1209600000
#define UM_MES_M 2419200000 //dois meses passa da range de long int
  
//O tempo adicionado é baseado num switch usando o timer, todos os switches chamam outra função, passando parametros diferentes
//os parametros são basicamente esses defines.


void checa_tempo(short row, short col, bool solo_led){

  bool tempo_acabou = false;
  
  switch (modo_tempo) {
    /*    Eu do futuro, tenho certeza que você está se perguntando porque não fazer um switch onde o define
          é posto para definir uma variável local com o seu valor de milisegundos.
          A resposta é que eu pensei nisso só quando terminei de formatar ela.
          E deixei ela assim porque não sabia se ia precisar adicionar mais coisas ali.
    */
    case SEGUNDOS_TESTE:
      // Levae this for when you want to test stuff.
    break;

    case SEGUNDOS_10:
      if ( led_Timer[row][col] > DEZ_SEGUNDOS_M){
        tempo_acabou = true;
      }
    break;

    case SEGUNDOS_30:
      if ( led_Timer[row][col] > MEIO_MINUTO_M){
        tempo_acabou = true;
      }
    break;

    case MINUTOS_2:
      if ( led_Timer[row][col] > DOIS_MINUTOS_M){
        tempo_acabou = true;
      }
    break;

    case MINUTOS_15:
      if ( led_Timer[row][col] > QUINZE_MINUTOS){
        tempo_acabou = true;
      }
    break;

    case MINUTOS_30:
      if ( led_Timer[row][col] > MEIA_HORA_M){
        tempo_acabou = true;
      }
    break;

    case HORAS_1:
      if ( led_Timer[row][col] > UMA_HORA_M){
        tempo_acabou = true;
      }
    break;

    case HORAS_3:
      if ( led_Timer[row][col] > TRES_HORAS_M){
        tempo_acabou = true;
      }
    break;

    case HORAS_6:
      if ( led_Timer[row][col] > SEIS_HORAS_M){
        tempo_acabou = true;
      }
    break;

    case HORAS_12:
      if ( led_Timer[row][col] > MEIO_DIA_M){
        tempo_acabou = true;
      }
    break;

    case DIA_1:
      if ( led_Timer[row][col] > UM_DIA_M){
        tempo_acabou = true;
      }
    break;

    case DIA_2:
      if ( led_Timer[row][col] > DOIS_DIAS_M){
        tempo_acabou = true;
      }
    break;

    case DIA_3:
      if ( led_Timer[row][col] > TRES_DIAS_M){
        tempo_acabou = true;
      }
    break;

    case DIA_4:
      if ( led_Timer[row][col] > QUATRO_DIAS_M){
        tempo_acabou = true;
      }
    break;

    case DIA_5:
      if ( led_Timer[row][col] > CINCO_DIAS_M){
        tempo_acabou = true;
      }
    break;

    case DIA_6:
      if ( led_Timer[row][col] > SEIS_DIAS_M){
        tempo_acabou = true;
      }
    break;


    case SEMANA_1:
      if ( led_Timer[row][col] > UMA_SEMANA_M){
        tempo_acabou = true;
      }
    break;

    case SEMANA_2:
    if ( led_Timer[row][col] > DUAS_SEMANAS_M){
        tempo_acabou = true;
      }
    break;

    case MES_1:
      if ( led_Timer[row][col] > UM_MES_M){
        tempo_acabou = true;
      }
    break;
  }

  if (tempo_acabou) {
    dbug msg ("checa_tempo() comparou o led [" + str(row) + "]["+ str(col) + "] e seu tempo acabou.");
    dbug msg ("Led [" + str(row) + "]["+ str(col) + "] vai desligar.");

    desliga_led(row,col,solo_led);
  }
}


void contador(){ // Adiciona milisegundos estimados para apagar.
                //É mais preciso sem com !DEBUG, onde há menos delays
  short row =0;
  short col = 0;
  for (row; row <= n_pca; row++){

    for (col; col < n_led; col++){

      if (led_ligado[row][col]){
        led_Timer[row][col]++;

        checa_tempo(row,col,is_solo(row,col)); // checa se já não é hora de desligar
      }
    }
  }
}

void adiciona_tempo(){ //Descobre o led ligado a mais tempo e reseta ele

  if (!TODOS_LIGADOS){
     msg("Função adiciona_tempo não devia ter sido chamada");
     return;
  }
  unsigned long int maior_tempo_ligado = 0;
  short row = 0;
  short col = 0;

  bool achou_nenhum = true;
  short biggest_row = 0;
  short biggest_col = 0;

  // Loop para achar o maior valor
  for (row; row <= n_pca; row++){
    for (col; col < n_led; col++){
      if (!led_ligado[row][col]) continue; // ignore leds desligados para salvar tempo

      if ( led_Timer[row][col] < maior_tempo_ligado){
          maior_tempo_ligado = led_Timer[row][col];
          biggest_row = row;
          biggest_col = col;
          achou_nenhum = false;
      }
    }
  }

  time_reset_all(row,col);

}


