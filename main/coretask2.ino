void coreTaskTwo( void * pvParameters ){
  
    String taskMessage = "Task (DHT) running on core ";
    taskMessage = taskMessage + xPortGetCoreID();
    Serial.println(taskMessage);  //log para o serial monitor

    delay(3000);
    
    while(true){
    
      Serial.println(dht22_getJson(esp32_id, "dht0"));
      mqtt_publish("temphum/dht22", dht22_getJson(esp32_id, "dht0"));

      delay(1000);

      Serial.println(ds18b20_getJson(esp32_id));
      mqtt_publish("temp/ds18b20", ds18b20_getJson(esp32_id));
      
      delay(10000);
    } 
}
