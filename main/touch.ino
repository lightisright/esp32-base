const int VALUE_THRESHOLD = 15;

int TOUCH_SENSOR_VALUE;

/*
  Touch0 >> GPIO4
  Touch1 >>  Not available on Devkit 30 pin version but available on Devkit 36 pin version 
  Touch2 >> GPIO2
  Touch3 >> GPIO15
  Touch4 >> GPIO13
  Touch5 >> GPIO12
  Touch6 >> GPIO14
  Touch7 >> GPIO27
  Touch8 >> GPIO33
  Touch9 >> GPIO32
*/

void touch_setup()
{
  delay(1000); 
  pinMode (touch_led_pin_number, OUTPUT);
}

void touch_manage(void (&func_on)(int), void (&func_off)(int)) {

  while(true) {
    
    TOUCH_SENSOR_VALUE = touchRead(touch_pin_numer);
    
    if(TOUCH_SENSOR_VALUE < VALUE_THRESHOLD)
    {
      Serial.print("Touch sensor activated.");
      digitalWrite(touch_led_pin_number, HIGH);
      func_on(0);
    }
    else{
      digitalWrite(touch_led_pin_number, LOW);
      func_off(0);
    }

    delay(200);
  }
}
