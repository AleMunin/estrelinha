void time_reset_all(short row, short col){ // Reseta todos os timers.
    led_Timer[row][col] = 0;      // reseta tempo total

    led_Timer_milis[row][col] = 0; // reseta tempo em mili
    led_Timer_M[row][col] = 0;    // reseta tempo em minutos
    led_Timer_H[row][col] = 0;    // reseta hora
    led_Timer_D[row][col] = 0;    // reseta dia
    led_Timer_S[row][col] = 0;    // reseta semana


    dbug msg("Timers resetados por time_reset_all");
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

void tempo_ligado(){ //Adiciona tempo proporcionalmente se o led estiver ligado
                    //Talvez não seja necessária, MAS estou deixando esse contador aqui caso seja.
  short row = 0;
  short col = 0;

  bool led_placa = false;

  for (row; row <= n_pca; row++){

    for (col; col < n_led; col++){

      if (row == (n_pca - 1) ){  // Se está na ultima fileira "placa" (ou seja, no led interno)

        if (col < 0) break; // não há mais leds. Apenas um na placa.

        if (solo_led){ //checagem pra solo led aqui baseado na const
          led_placa = true; //diz pra função final que se trata do led do arduino.
        }
      }

      if (!led_ligado[row][col]) continue; // pula os desligados

      led_Timer[row][col]++; // Adiciona milisegundos na contagem de quanto tempo total que tá ligado
      led_Timer_milis[row][col]++;  //Adiciona milisegundos pro contador de relógio

      if (led_Timer_milis[row][col] > UM_MINUTO){ //se o contador de milisegundos atingiu 1h
        led_Timer_M[row][col]++;
        led_Timer_milis[row][col] = 0;    // reseta milisegundo
      }

      if (led_Timer_M[row][col] > UMA_HORA){ //se o contador de minutos atingiu 60
        led_Timer_H[row][col]++;
        led_Timer_M[row][col] = 0;    // reseta milisegundo
      }

      if (led_Timer_H[row][col] > UM_DIA){ //se o contador de horas atingiu 1 dia
        led_Timer_D[row][col]++;
        led_Timer_H[row][col] = 0;    // reseta hora
      }

      if (led_Timer_D[row][col] > UMA_SEMANA){ //se o contador de horas atingiu 1 semana
        led_Timer_S[row][col]++;
        led_Timer_D[row][col] = 0;    // reseta dia
      }

      if (led_Timer_S[row][col] == UM_MES){ //se o contador de horas atingiu 1 mes
        led_Timer_S[row][col] = 0; // Reseta semana, enquanto n tiver usando o reset_all
        //time_reset_all(row,col);   // reseta tudo, talvez, ver os troços de tempo total depois voltar aqui
      }

      checa_tempo(row,col,led_placa);
    }
  }

}

void checa_tempo(short row, short col, bool solo_led){

  //Provavelmente compara tempo_permitido com o timer se for usar um switch gigante pro modo tempo
  //Se o tempo for maior, desliga_led(row, col, true).
  //Problema é que n da pra adicionar 2 meses, mas dane-se.
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
      if ( led_Timer_milis[row][col] > DEZ_SEGUNDOS_M){
                tempo_acabou = true;
      }
    break;

    case SEGUNDOS_30:
      if ( led_Timer_milis[row][col] > MEIO_MINUTO_M){
        tempo_acabou = true;
      }
    break;

    case MINUTOS_2:
      if ( led_Timer_milis[row][col] > DOIS_MINUTOS_M){
        tempo_acabou = true;
      }
    break;

    case MINUTOS_15:
      if ( led_Timer_milis[row][col] > QUINZE_MINUTOS){
        tempo_acabou = true;
      }
    break;

    case MINUTOS_30:
      if ( led_Timer_milis[row][col] > MEIA_HORA_M){
        tempo_acabou = true;
      }
    break;

    case HORAS_1:
      if ( led_Timer_milis[row][col] > UMA_HORA_M){
        tempo_acabou = true;
      }
    break;

    case HORAS_3:
      if ( led_Timer_milis[row][col] > TRES_HORAS_M){
        tempo_acabou = true;
      }
    break;

    case HORAS_6:
      if ( led_Timer_milis[row][col] > SEIS_HORAS_M){
        tempo_acabou = true;
      }
    break;

    case HORAS_12:
      if ( led_Timer_milis[row][col] > MEIO_DIA_M){
        tempo_acabou = true;
      }
    break;

    case DIA_1:
      if ( led_Timer_milis[row][col] > UM_DIA_M){
        tempo_acabou = true;
      }
    break;

    case DIA_2:
      if ( led_Timer_milis[row][col] > DOIS_DIAS_M){
        tempo_acabou = true;
      }
    break;

    case DIA_3:
      if ( led_Timer_milis[row][col] > TRES_DIAS_M){
        tempo_acabou = true;
      }
    break;

    case DIA_4:
      if ( led_Timer_milis[row][col] > QUATRO_DIAS_M){
        tempo_acabou = true;
      }
    break;

    case DIA_5:
      if ( led_Timer_milis[row][col] > CINCO_DIAS_M){
        tempo_acabou = true;
      }
    break;

    case DIA_6:
      if ( led_Timer_milis[row][col] > SEIS_DIAS_M){
        tempo_acabou = true;
      }
    break;


    case SEMANA_1:
      if ( led_Timer_milis[row][col] > UMA_SEMANA_M){
        tempo_acabou = true;
      }
    break;

    case SEMANA_2:
    if ( led_Timer_milis[row][col] > DUAS_SEMANAS_M){
        tempo_acabou = true;
      }
    break;

    case MES_1:
      if ( led_Timer_milis[row][col] > UM_MES_M){
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
