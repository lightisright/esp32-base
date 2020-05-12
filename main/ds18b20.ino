#include <OneWire.h>
#include <DallasTemperature.h>

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);
DallasTemperature sensors(&oneWire);

char ds18b20_json[100];
char ds18b20_json_complete[1000];

void ds18b20_setup() {

  getDeviceAddresses();
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

    DeviceAddress addr;
    
    //Serial.print("DS18b20 Temperature: ");
    //Serial.println(ds18b20_getTemperature(index));
    if ( strlen(ds18b20_json_complete) > 2 ) {
      strcat(ds18b20_json_complete, ", ");
    }
    sensors.getAddress(addr, index);
    sprintf(ds18b20_json, "\"%s_ds18b20_%02hx%02hx-%02hx%02hx%02hx%02hx%02hx%02hx\": %.1f", esp32_id, addr[0], addr[1], addr[2], addr[3], addr[4], addr[5], addr[6], addr[7], ds18b20_getTemperature(index));
    strcat(ds18b20_json_complete, ds18b20_json);
  }

  strcat(ds18b20_json_complete, "}");

  return &ds18b20_json_complete[0];
}


// find out your DS18B20 addresses
// see also: https://github.com/PaulStoffregen/OneWire/blob/master/OneWire.h
void getDeviceAddresses(void) {
  byte i;
  byte addr[8];
  
  Serial.println("Getting the address...\n\r");
  /* initiate a search for the OneWire object we created and read its value into
  addr array we declared above*/
  
  while(oneWire.search(addr)) {
    Serial.print("The address is:\t");
    //read each byte in the address array
    for( i = 0; i < 8; i++) {
      Serial.print("0x");
      if (addr[i] < 16) {
        Serial.print('0');
      }
      // print each byte in the address array in hex format
      Serial.print(addr[i], HEX);
      if (i < 7) {
        Serial.print(", ");
      }
    }
    // a check to make sure that what we read is correct.
    if ( OneWire::crc8( addr, 7) != addr[7]) {
        Serial.print("CRC is not valid!\n");
        //return;
    }
  }
  oneWire.reset_search();
  return;
}
