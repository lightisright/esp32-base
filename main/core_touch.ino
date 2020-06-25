void core_touch( void * pvParameters ) {
  
    String taskMessage = "Task (DHT) running on core ";
    taskMessage = taskMessage + xPortGetCoreID();
    Serial.println(taskMessage);

    touch_setup();
    
    delay(1000);

    touch_manage(touch_on,touch_off);
}
