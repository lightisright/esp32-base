#include <OneWire.h>
#include <DallasTemperature.h>

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);
DallasTemperature sensors(&oneWire);

char ds18b20_json[100];
char ds18b20_json_complete[1000];

void ds18b20_setup() {

  sensors.begin();
}

float ds18b20_getTemperature(uint8_t index) {
  
  sensors.requestTemperatures(); 

  return sensors.getTempCByIndex(index);
}

char* ds18b20_getJson() {

  //Serial.print("NB DS18b20: ");
  //Serial.println(sensors.getDS18Count());
  
  ds18b20_json_complete[0]='{';
  ds18b20_json_complete[1]='\0';

  for(uint8_t index=0; index < sensors.getDS18Count(); index++) {
    //Serial.print("DS18b20 Temperature: ");
    //Serial.println(ds18b20_getTemperature(index));
    if ( strlen(ds18b20_json_complete) > 2 ) {
      strcat(ds18b20_json_complete, ", ");
    }
    sprintf(ds18b20_json, "\"%s-ds18b20-%02d\": %f", esp32_id, index, ds18b20_getTemperature(index));
    strcat(ds18b20_json_complete, ds18b20_json);
  }

  strcat(ds18b20_json_complete, "}");

  return &ds18b20_json_complete[0];
}
