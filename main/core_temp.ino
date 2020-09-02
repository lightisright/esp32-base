void core_temp( void * pvParameters ) {
  
    String taskMessage = "Task (DHT) running on core ";
    taskMessage = taskMessage + xPortGetCoreID();
    Serial.println(taskMessage);

    dht_setup();
    ds18b20_setup();

    while(true){
    
      mqtt_publish("dht22", dht22_getJson("dht0"));

      delay(1000);

      mqtt_publish("ds18b20", ds18b20_getJson());

      mqtt_publish("ds18b20", ds18b20_getJsonByAddress(/*dallas_addresses, 2*/));
      
      delay(1000*60*5);   // wait 5mn between 2 messages
    } 
}
