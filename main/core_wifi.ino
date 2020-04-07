//essa função ficará mudando o estado do led a cada 1 segundo
//e a cada piscada (ciclo acender e apagar) incrementará nossa variável blinked
void core_wifi( void * pvParameters ){
  
    String taskMessage = "Task (WIFI) running on core ";
    taskMessage = taskMessage + xPortGetCoreID();

    wifi_setup();

    delay(1000);

    Serial.println(taskMessage);  //log para o serial monitor

    wifi_manage(60*1000);
}
