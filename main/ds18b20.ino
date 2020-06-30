#include <OneWire.h>
#include <DallasTemperature.h>

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);
DallasTemperature sensors(&oneWire);

char ds18b20_json[100];
char ds18b20_json_complete[1000];

static int max_reset_loop = 12;
int reset_counter = 0;

uint8_t ds18b20_nb_devices = 0;

void ds18b20_setup() {

  // for printing ds18b20 addresses (debug)
  //getDeviceAddresses();

  sensors.setWaitForConversion(true);
  sensors.begin();

  // leave some time to init one wire bus
  delay(3000);

  // reset reset counter
  reset_counter=0;
  ds18b20_nb_devices = sensors.getDS18Count();
  ds18b20_nb_devices = sensors.getDS18Count();
}

char* ds18b20_getJson() {

  //Serial.print("NB DS18b20: ");
  //Serial.println(sensors.getDS18Count());

  // reinit oneWire bus if necessary
  if (ds18b20_nb_devices < sensors.getDS18Count() || reset_counter >= max_reset_loop) {
    ds18b20_setup();
  }
  // increment reset counter
  reset_counter++;
  
  ds18b20_json_complete[0]='{';
  ds18b20_json_complete[1]='\0';

  sensors.requestTemperatures();
  
  for(uint8_t index=0; index < sensors.getDS18Count(); index++) {

    DeviceAddress addr;  // typedef uint_8 DeviceAddress[8]
    
    //Serial.print("DS18b20 Temperature: ");
    //Serial.println(ds18b20_getTemperature(index));
    if ( strlen(ds18b20_json_complete) > 2 ) {
      strcat(ds18b20_json_complete, ", ");
    }
    sensors.getAddress(addr, index);
    sprintf(ds18b20_json, "\"%02hx%02hx-%02hx%02hx%02hx%02hx%02hx%02hx\": %.1f", addr[0], addr[1], addr[2], addr[3], addr[4], addr[5], addr[6], addr[7], sensors.getTempCByIndex(index));
    strcat(ds18b20_json_complete, ds18b20_json);
  }

  strcat(ds18b20_json_complete, "}");

  return &ds18b20_json_complete[0];
}

/**
 * Get DS18B20 temp by address (needs addresses as parameter)
 */
char* ds18b20_getJsonByAddress(uint8_t *addresses, int nb_sensors) {

  ds18b20_json_complete[0]='{';
  ds18b20_json_complete[1]='\0';
  uint8_t addr[8];

  sensors.requestTemperatures();

  for(int i=0; i < nb_sensors; i++) {
    uint8_t address[8];
    address = addresses[i][0];
    if ( strlen(ds18b20_json_complete) > 2 ) {
      strcat(ds18b20_json_complete, ", ");
    }
    sprintf(ds18b20_json, "\"%02hx%02hx-%02hx%02hx%02hx%02hx%02hx%02hx\": %.1f", address[0], address[1], address[2], address[3], address[4], address[5], address[6], address[7], 
    sensors.getTempC(address));
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
  
  ds18b20_json_complete[0]='{';
  ds18b20_json_complete[1]='\0';

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

  strcat(ds18b20_json_complete, "}");

  oneWire.reset_search();
  return;
}
