# esp32-base


## Configuration

Edit `vars.ino` file to set your own modules configuration

```
// ------------------------------------------------------------------
// WIFI module configuration
// ------------------------------------------------------------------
// Replace the next variables with your SSID/Password combination
const char* ssid = "YOUR_ACCESS_POINT_SSID";
const char* password = "YOUR_ACCESS_POINT_PASSWORD";

// ------------------------------------------------------------------
// ESP32 module ID for MQTT messages
// ------------------------------------------------------------------
String esp32_id = "MY_ESP32";

```
