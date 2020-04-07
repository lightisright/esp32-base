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


void mqtt_manage() {

  while(true) {
    if ( !__mqtt_up() ) {
      Serial.println("MQTT: Service down... Attempting new connexion...");
      if ( !__mqtt_connect() ) {
        Serial.println("MQTT: CONNEXION FAILED - wait 2 minutes before new connexion attempt...");
      }
      else {
        Serial.println("MQTT: Subscribing to topics & start loop...");
        client.subscribe("esp32swim");
        client.subscribe("esp32swim/heater");
        client.subscribe("esp32swim/pump");
        //delay(1000);
        while(client.loop()) { delay(1000); }
      }
    }
    // wait 2 minutes between 2 connexion checks / attempts
    delay(2*60*1000);
  }
}

void mqtt_loop() {
  client.loop();
}

bool __mqtt_up() {
  bool status = ( wifi_status() && client.connected() );
  if ( !status ) {
    digitalWrite(mqtt_StatusLedPin, HIGH);
  }
  return status;
}

bool __mqtt_connect() {

  int connexionCounter = 0;
  
  // Loop until we're reconnected
  while (!__mqtt_up() && connexionCounter < mqtt_max_connexion_attempts) {
    
    Serial.println("MQTT: Attempting MQTT connection...");

    // Attempt to connect
    if (client.connect(esp32_id)) {
      digitalWrite(mqtt_StatusLedPin, LOW);
      Serial.println("MQTT: connected to server");
      return true;
    }
    
    // Attempt to connexion failed
    else {
      Serial.print("MQTT: connexion to server failed, rc=");
      Serial.println(client.state());
      Serial.println("MQTT: try again in 60 seconds...");
      
      // Wait 5 seconds before retrying & increase counter
      int waitloopcounter=0;
      while(waitloopcounter < 60) {
        digitalWrite(mqtt_StatusLedPin, LOW);
        delay(500);
        digitalWrite(mqtt_StatusLedPin, HIGH);
        delay(500);
        waitloopcounter++;
      }
      connexionCounter++;
    }
  }

  /* FALLBACK MSG */
  Serial.println("MQTT: max connexion attempts reached, abort MQTT server connexion...");
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
