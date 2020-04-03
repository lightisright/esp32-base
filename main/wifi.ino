/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com
*********/

#include <WiFi.h>

// LED Pin
const int wifi_LedPin = 25;   // Red LED

void wifi_setup() {

  pinMode(wifi_LedPin, OUTPUT);

  digitalWrite(wifi_LedPin, LOW);
  delay(1000);
  digitalWrite(wifi_LedPin, HIGH);
}

/* INFINITE LOOP to manage WIFI connexion / reconnexion every "checkDelay" seconds */
void wifi_manage(int checkDelay) {

  while (true) {

    if ( WiFi.status() != WL_CONNECTED ) {

      digitalWrite(wifi_LedPin, HIGH);

      __wifi_connect();

      delay(checkDelay);
    }
  }
}

// returns wifi status: true if up, false if down
bool wifi_status() {

  return ( WiFi.status() == WL_CONNECTED );
}

/* Internal method to connect to WIFI */
void __wifi_connect() {

  delay(10);

  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(wifi_LedPin, HIGH);
    delay(300);
    Serial.print(".");
    digitalWrite(wifi_LedPin, LOW);
    delay(200);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
