bool debounce_check (int pino){ // pino: o index do botão no arduino
    
  //Ele lê o estado atual do botão, cria um delay, e compara os dois.
  // Retorna falso se houve um debounce, retorna se não houve.
  dbug msg("função debounce ativada");
  bool estado = digitalRead(pino);
  delay(10);
  if (digitalRead(pino) == estado){
      dbug msg("debounce retornado como verdadeiro");
      return true;
  }
  else{
      dbug msg("debounce retornado como falso");
      return false;
    }
}