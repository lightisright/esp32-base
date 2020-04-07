//essa função será responsável apenas por atualizar as informações no 
//display a cada 100ms
void core_mqtt( void * pvParameters ){

    String taskMessage = "Task (MQTT) running on core ";
    taskMessage = taskMessage + xPortGetCoreID();
    Serial.println(taskMessage);

    mqtt_setup();
    mqtt_setcallback(mqtt_callback);

    delay(1000);

    mqtt_manage();
}
