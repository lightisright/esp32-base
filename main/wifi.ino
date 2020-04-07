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
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  delay(2000);

  int counter = 0;
  while (WiFi.status() != WL_CONNECTED && counter < 30) {
    Serial.println("WiFi not connected... waiting...");
    digitalWrite(wifi_LedPin, HIGH);
    delay(300);
    digitalWrite(wifi_LedPin, LOW);
    delay(200);
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
