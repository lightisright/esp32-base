#include "vars.h"

static uint8_t taskCoreZero = 0;
static uint8_t taskCoreOne  = 1;

/* Multithreading method prototype */
/*
xTaskCreatePinnedToCore(coreTaskZero,   // função que implementa a tarefa
                    "coreTaskZero",     // nome da tarefa
                    10000,              // número de palavras a serem alocadas para uso com a pilha da tarefa
                    NULL,               // parâmetro de entrada para a tarefa (pode ser NULL)
                    1,                  // prioridade da tarefa (0 a N)
                    NULL,               // referência para a tarefa (pode ser NULL)
                    taskCoreOne);       // Núcleo que executará a tarefa
*/

void setup() {

  Serial.begin(115200);

  // WIFI Thread
  delay(5000);
  xTaskCreatePinnedToCore(core_wifi, "core_wifi", 10000, NULL, 1, NULL, taskCoreOne);
  
  // MQTT Thread
  delay(5000);
  xTaskCreatePinnedToCore(core_mqtt, "core_mqtt", 10000, NULL, 2, NULL, taskCoreOne);
  
  // Temperature / humidity sensors thread
  delay(5000);
  //xTaskCreatePinnedToCore(core_temp, "core_temp", 10000, NULL, 3, NULL, taskCoreOne);
  xTaskCreatePinnedToCore(core_serre, "core_serre", 10000, NULL, 3, NULL, taskCoreOne);
  
  // Touch buttons thread
  delay(5000);
  xTaskCreatePinnedToCore(core_touch, "core_touch", 10000, NULL, 4, NULL, taskCoreOne);
}

void loop() {
  // put your main code here, to run repeatedly:
  // no need with threads
}
