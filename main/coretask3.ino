void coreTaskThree( void * pvParameters ){
  
    String taskMessage = "Task (DHT) running on core ";
    taskMessage = taskMessage + xPortGetCoreID();
    Serial.println(taskMessage);  //log para o serial monitor

    touch_manage(touch_on,touch_off);
}

void touch_on(int pinId) {

  switch(pinId) {
    case 0:
      Serial.println("Touch 0 ON");
      break;
    default:
      break;
  }
}

void touch_off(int pinId) {

  switch(pinId) {
    case 0:
      Serial.println("Touch 0 OFF");
      break;
    default:
      break;
  }
}
