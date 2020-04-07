# esp32-base


## Configuration

Edit `vars.h` file to set your own modules configuration

```
// ------------------------------------------------------------------
// WIFI module configuration
// ------------------------------------------------------------------
// Replace the next variables with your SSID/Password combination
const char* ssid = "YOUR_ACCESS_POINT_SSID";
const char* password = "YOUR_ACCESS_POINT_PASSWORD";

// ------------------------------------------------------------------
// ESP32 module ID
// - used for MQTT messages
// ------------------------------------------------------------------
const char* esp32_id = "MY_ESP32";

// WIFI status pin
const int wifi_LedPin = 25;         // Red LED

// MQTT Broker IP address
const char* mqtt_server = "192.168.0.1";
const int mqtt_port = 1883;
const int mqtt_max_connexion_attempts = 10;

// MQTT status pin
const int mqtt_StatusLedPin = 33;   // Yellow LED

// MQTT msg pin
const int mqtt_MsgLedPin = 32;      // Green LED

// Pump pin
const int pump_RelayPin = 16;

// Heater pin
const int heater_RelayPin = 17;

// Touch pins
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
#define touch_pin_numer T0
const int touch_led_pin_number = 32;

// GPIO where the DS18B20 is connected to
const int oneWireBus = 26;

// GPIO where the DHT22 is connected to
uint8_t DHTPin = 27;

```
