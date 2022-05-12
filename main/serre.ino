#include <EEPROM.h>
#define EEPROM_SIZE 1

void hardcoded_arrosage() {

  EEPROM.begin(EEPROM_SIZE);

  pinMode(pump_RelayPin, OUTPUT);
  pinMode(heater_RelayPin, OUTPUT);

  mqtt_pub_notify("Hardcoded arrosage activated.... waiting 10s....");

  mqtt_pub_notify("hardcoded_arrosage: Electrovanne: ON....");
  digitalWrite(heater_RelayPin, HIGH);

  delay(20000); // attente ouverture vanne

  mqtt_pub_notify("hardcoded_arrosage: Pompe: ON....");
  digitalWrite(pump_RelayPin, HIGH);

  mqtt_pub_notify("hardcoded_arrosage: Arrosage in progress 60s....");
  delay(60000);

  mqtt_pub_notify("hardcoded_arrosage: Pompe: OFF....");
  digitalWrite(pump_RelayPin, LOW);

  delay(50);

  mqtt_pub_notify("hardcoded_arrosage: Electrovanne: OFF....");
  digitalWrite(heater_RelayPin, LOW);

  while (true) {
    mqtt_pub_notify("hardcoded_arrosage: Waiting 1h for ESP shutdown or restart.");
    delay(3600000);
  }
}
