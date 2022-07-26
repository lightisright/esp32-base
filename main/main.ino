#include "vars.h"

static uint8_t taskCoreZero = 0;
static uint8_t taskCoreOne  = 1;

/* Multithreading method prototype */
/* https://techtutorialsx.com/2017/05/09/esp32-running-code-on-a-specific-core/
 *  
    xTaskCreatePinnedToCore(
                task,       //Function to implement the task 
                "taskname", //Name of the task
                6000,       //Stack size in words 
                NULL,       //Task input parameter 
                0,          //Priority of the task 
                NULL,       //Task handle.
                1);         //Core where the task should run 
*/

void setup() {

  Serial.begin(115200);

  #ifdef DEBUG
    Serial.println("*******************************************************");
    Serial.println("*                    WARNING                          *");
    Serial.println("*             DEBUG mode ACTIVATED !!!!               *");
    Serial.println("*******************************************************");
  #endif
  
  // WIFI Thread
  //delay(5000);
  //xTaskCreatePinnedToCore(core_wifi, "core_wifi", 10000, NULL, 0, NULL, taskCoreOne);
  
  // MQTT Thread (lower priority
  //delay(5000);
  //xTaskCreatePinnedToCore(core_mqtt, "core_mqtt", 10000, NULL, 1, NULL, taskCoreOne);
  
  // Temperature / humidity sensors thread
  //delay(5000);
  //xTaskCreatePinnedToCore(core_temp, "core_temp", 10000, NULL, 3, NULL, taskCoreOne);
  //xTaskCreatePinnedToCore(core_serre, "core_serre", 10000, NULL, 50, NULL, taskCoreOne);
  
  // Touch buttons thread
  //delay(5000);
  //xTaskCreatePinnedToCore(core_touch, "core_touch", 10000, NULL, 4, NULL, taskCoreOne);
}

void loop() {
  // put your main code here, to run repeatedly:
  // no need with threads
  #ifdef ESP32SERRE
    arrosage_serre();
  #endif
}
