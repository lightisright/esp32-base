static uint8_t taskCoreZero = 0;
static uint8_t taskCoreOne  = 1;

void setup() {

  Serial.begin(115200);

  
  wifi_setup();
 
  //cria uma tarefa que será executada na função coreTaskZero, com prioridade 1 e execução no núcleo 0
  //coreTaskZero: piscar LED e contar quantas vezes
  xTaskCreatePinnedToCore(
                    coreTaskZero,   /* função que implementa a tarefa */
                    "coreTaskZero", /* nome da tarefa */
                    10000,      /* número de palavras a serem alocadas para uso com a pilha da tarefa */
                    NULL,       /* parâmetro de entrada para a tarefa (pode ser NULL) */
                    1,          /* prioridade da tarefa (0 a N) */
                    NULL,       /* referência para a tarefa (pode ser NULL) */
                    taskCoreOne);         /* Núcleo que executará a tarefa */

  delay(500);

  mqtt_setup();
  xTaskCreatePinnedToCore(
                    coreTaskOne,
                    "coreTaskOne",
                    10000,
                    NULL,
                    2,
                    NULL,
                    taskCoreOne);
 
   delay(500);

   dht_setup();
   ds18b20_setup();
   xTaskCreatePinnedToCore(
                    coreTaskTwo,
                    "coreTaskTwo",
                    10000,
                    NULL,
                    3,
                    NULL,
                    taskCoreOne);

   delay(500);

   touch_setup();
   xTaskCreatePinnedToCore(
                    coreTaskThree,
                    "coreTaskThree",
                    10000,
                    NULL,
                    4,
                    NULL,
                    taskCoreOne);

}

void loop() {
  // put your main code here, to run repeatedly:

}
