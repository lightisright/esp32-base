void coreTaskTwo( void * pvParameters ){
  
    String taskMessage = "Task (DHT) running on core ";
    taskMessage = taskMessage + xPortGetCoreID();
    Serial.println(taskMessage);  //log para o serial monitor

    delay(3000);
    
    while(true){
    
      Serial.println(dht22_getJson("dht0"));
      mqtt_publish("temphum/dht22", dht22_getJson("dht0"));

      delay(1000);

      Serial.println(ds18b20_getJson());
      mqtt_publish("temp/ds18b20", ds18b20_getJson());
      
      delay(10000);
    } 
}
