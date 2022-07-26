#include <Preferences.h>

int tempo_vanne = 30;   // tempo attente ouverture vanne (secondes)

void arrosage_serre() {

  Preferences preferences;
  int delay_minutes = 0;      // starting delay in minutes (also used internally between 2 arrosages)
  int duration_minutes = 10;   // duration in minutes

  #ifdef DEBUG
    Serial.println("DEBUG Mode: force duration to 1 minute)");
    duration_minutes = 1;
  #endif

  // get delay & duration from memory
  preferences.begin(esp32_id.c_str(), false);
  unsigned int read_delay_minutes = preferences.getUInt("arrosage_serre_delay", delay_minutes);
  unsigned int read_duration_minutes = preferences.getUInt("arrosage_serre_duration", duration_minutes);
  preferences.end();

  // configure GPIO pins
  pinMode(pump_RelayPin, OUTPUT);
  pinMode(heater_RelayPin, OUTPUT);

  while (true) {

    // wait configured duration
    Serial.println("arrosage_serre: Waiting for arrosage start.");
    int delaytime = read_delay_minutes*60 - (tempo_vanne+read_duration_minutes*60);  // retrait de la durée d'arrosage pour avoir toujours le bon délai d'arrosage
    if ( delaytime < 0 ) {
      delaytime=0;
    }
    Serial.print("Delay before next arrosage: ");
    Serial.print(delaytime);
    Serial.print(" secondes (");
    Serial.print(delaytime/60);
    Serial.println(" minutes)");
    delay(delaytime*1000); 

    _do_arrosage_serre(read_duration_minutes);

    // Load new duration (if set) from memory
    preferences.begin(esp32_id.c_str(), false);
    unsigned int read_duration_minutes = preferences.getUInt("arrosage_serre_duration", duration_minutes);
    preferences.end();
    
    // set next arrosage in 24 hours
    read_delay_minutes = 60*24;       // for real condition
    #ifdef DEBUG
      Serial.println("DEBUG Mode: force delay to 15 minutes)");
      read_delay_minutes = 15*1;       // for testing purpose
    #endif
  }
}

void _do_arrosage_serre(unsigned int duration_minutes) {

    // start arrosage
    Serial.println("arrosage_serre: Arrosage starting....");
  
    Serial.println("arrosage_serre: Electrovanne: ON....");
    digitalWrite(heater_RelayPin, HIGH);
  
    delay(tempo_vanne*1000); // attente ouverture vanne
  
    Serial.println("arrosage_serre: Pompe: ON....");
    digitalWrite(pump_RelayPin, HIGH);
  
    Serial.println("arrosage_serre: Arrosage in progress....");
    delay(duration_minutes*60*1000);
  
    Serial.println("arrosage_serre: Pompe: OFF....");
    digitalWrite(pump_RelayPin, LOW);
  
    Serial.println("arrosage_serre: Electrovanne: OFF....");
    digitalWrite(heater_RelayPin, LOW);

    // start arrosage
    Serial.println("arrosage_serre: Arrosage stopped.");
}
