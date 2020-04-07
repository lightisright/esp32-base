/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com
*********/

#include <WiFi.h>

void wifi_setup() {

  pinMode(wifi_LedPin, OUTPUT);
  digitalWrite(wifi_LedPin, HIGH);
}

/* INFINITE LOOP to manage WIFI connexion / reconnexion every "checkDelay" seconds */
void wifi_manage(int checkDelay) {

  while (true) {

    if ( WiFi.status() != WL_CONNECTED ) {

      if ( !__wifi_connect() ) {
        Serial.print("WiFi connexion retry in ");
        Serial.print(checkDelay/1000);
        Serial.println("s....");
      }

      delay(checkDelay);
    }
  }
}

// returns wifi status: true if up, false if down
bool wifi_status() {

  return ( WiFi.status() == WL_CONNECTED );
}

/* Internal method to connect to WIFI */
bool __wifi_connect() {

  // We start by connecting to a WiFi network
  Serial.println("Connecting to ");
  Serial.println(ssid);
  Serial.println("WiFi blinking LED means connexion is in progress... waiting...");

  int counter = 0;
  while (WiFi.status() != WL_CONNECTED && counter < 60) {
    // Try connexion every 5 seconds
    if ( counter % 5 == 0 ) {
      WiFi.begin(ssid, password);
    }
    digitalWrite(wifi_LedPin, HIGH);
    delay(500);
    digitalWrite(wifi_LedPin, LOW);
    delay(500);
    counter++;
  }

  if ( WiFi.status() == WL_CONNECTED ) {
    digitalWrite(wifi_LedPin, LOW);
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    return true;
  }

  digitalWrite(wifi_LedPin, HIGH);
  Serial.println("WiFi connexion failed !");
  return false;
}
