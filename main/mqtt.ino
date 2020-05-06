#include <PubSubClient.h>
#include <WiFi.h>

WiFiClient espClient;
PubSubClient client(espClient);

long lastMsg = 0;
char msg[50];

void mqtt_setup() {
  
  client.setServer(mqtt_server, mqtt_port);

  // configure status LED
  pinMode(mqtt_StatusLedPin, OUTPUT);
  digitalWrite(mqtt_StatusLedPin, HIGH);

  // configure msg LED
  pinMode(mqtt_MsgLedPin, OUTPUT);
  digitalWrite(mqtt_MsgLedPin, LOW);
}

void mqtt_setcallback(void (&callback_func)(char* topic, byte* message, unsigned int length)) {
  client.setCallback(callback_func);
}


void mqtt_manage(void (&mqtt_subscription_func)()) {

  while(true) {
    if ( !__mqtt_up() ) {
      Serial.println("MQTT: Service down... Attempting new connexion...");
      if ( !__mqtt_connect() ) {
        Serial.println("MQTT: CONNEXION FAILED - wait 2 minutes before new connexion attempt...");
      }
      else {
        Serial.println("MQTT: Subscribing to topics & start loop...");
        mqtt_subscription_func();
        //delay(1000);
        while(client.loop()) { delay(1000); }
      }
    }
    // wait 2 minutes between 2 connexion checks / attempts
    delay(2*60*1000);
  }
}

bool __mqtt_up() {
  bool status = ( wifi_status() && client.connected() );
  if ( !status ) {
    digitalWrite(mqtt_StatusLedPin, HIGH);
  }
  return status;
}

bool __mqtt_connect() {

  Serial.println("MQTT: Attempting MQTT connection...");
  Serial.println("MQTT blinking LED means connexion is in progress... waiting 60s for connexion...");

  int waitloopcounter=0;
  while(!__mqtt_up() && waitloopcounter < 60) {
    // try reconnexion every 5 seconds
    if ( waitloopcounter % 5 ==0 ) {
      client.connect(esp32_id);
    }
    digitalWrite(mqtt_StatusLedPin, LOW);
    delay(500);
    digitalWrite(mqtt_StatusLedPin, HIGH);
    delay(500);
    waitloopcounter++;
  }

  if (__mqtt_up()) {
    digitalWrite(mqtt_StatusLedPin, LOW);
    Serial.println("MQTT: connected to server");
    return true;
  }

  /* FALLBACK MSG */
  digitalWrite(mqtt_StatusLedPin, HIGH);
  Serial.print("MQTT: connexion to server failed, rc=");
  Serial.println(client.state());
  return false;
}

void mqtt_publish(char* subject, char* msg) {

  if ( ! __mqtt_up() ) {
    if ( !__mqtt_connect() ) {
      Serial.print("MQTT down: can't publish message");
      Serial.print(subject);
      Serial.print(" : ");
      Serial.println(msg);
    }
  }
  
  client.publish(subject, msg);
  digitalWrite(mqtt_MsgLedPin, LOW);
  delay(200);
  digitalWrite(mqtt_MsgLedPin, HIGH);
}



/* for subscription (later) */
void callback_func_sample(char* topic, byte* message, unsigned int length) {
  
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  // Feel free to add more if statements to control more GPIOs with MQTT

  // If a message is received on the topic esp32/output, you check if the message is either "on" or "off". 
  // Changes the output state according to the message
  if (String(topic) == "esp32/output") {
    Serial.print("Changing output to ");
    if(messageTemp == "on"){
      Serial.println("on");
      digitalWrite(mqtt_MsgLedPin, LOW);
    }
    else if(messageTemp == "off"){
      Serial.println("off");
      digitalWrite(mqtt_MsgLedPin, HIGH);
    }
  }
}
