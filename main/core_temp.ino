void core_temp( void * pvParameters ){
  
    String taskMessage = "Task (DHT) running on core ";
    taskMessage = taskMessage + xPortGetCoreID();
    Serial.println(taskMessage);

    dht_setup();
    ds18b20_setup();

    // leave some time to init one wire bus
    delay(5000);
    
    while(true){
    
      Serial.println(dht22_getJson("dht0"));
      mqtt_publish("esp32swim/dht22", dht22_getJson("dht0"));

      delay(1000);

      Serial.println(ds18b20_getJson());
      mqtt_publish("esp32swim/ds18b20", ds18b20_getJson());
      
      delay(10000);
    } 
}
