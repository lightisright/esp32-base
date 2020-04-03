// https://microcontrollerslab.com/esp32-dht11-dht22-web-server/

#include <string.h>
#include "DHT.h"

#define DHTTYPE DHT22
uint8_t DHTPin = 27;

DHT dht(DHTPin, DHTTYPE); 
char dht_json[100];

void dht_setup() {

  pinMode(DHTPin, INPUT);
  dht.begin();
}

float dht22_getTemperature() {
  
  return dht.readTemperature(); 
}

float dht22_getHumidity() {
  
  return dht.readHumidity(); 
}

char* dht22_getJson(String id) {

  sprintf(dht_json, "{\"name\": \"%s\", \"id\": \"%s\", \"temp\": %f, \"hum\": %f}", esp32_id, id, dht22_getTemperature(), dht22_getHumidity());

  return &dht_json[0];
}
