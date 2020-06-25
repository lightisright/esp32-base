// https://microcontrollerslab.com/esp32-dht11-dht22-web-server/

#include <string.h>
#include "DHT.h"

#define DHTTYPE DHT22

DHT dht(DHTPin, DHTTYPE); 
char dht_json[100];

void dht_setup() {

  pinMode(DHTPin, INPUT);
  dht.begin();

  // leave some time to init dht22
  delay(1000);

}

float dht22_getTemperature() {
  
  return dht.readTemperature(); 
}

float dht22_getHumidity() {
  
  return dht.readHumidity(); 
}

char* dht22_getJson(String id) {

  sprintf(dht_json, "{\"name\": \"%s\", \"id\": \"%s\", \"temp\": %.1f, \"hum\": %.0f}", esp32_id.c_str(), id, dht22_getTemperature(), dht22_getHumidity());

  return &dht_json[0];
}
