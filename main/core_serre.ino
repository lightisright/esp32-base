//essa função ficará mudando o estado do led a cada 1 segundo
//e a cada piscada (ciclo acender e apagar) incrementará nossa variável blinked
void core_serre( void * pvParameters ) {
  
    String taskMessage = "Core SERRE activated...";
    Serial.println(taskMessage);

    hardcoded_arrosage();
}
