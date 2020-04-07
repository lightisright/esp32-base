void mqtt_subscriptions() {
  client.subscribe("esp32swim");
  client.subscribe("esp32swim/heater");
  client.subscribe("esp32swim/pump");
}


/* for MQTT subscription if needed */
void mqtt_callback(char* topic, byte* message, unsigned int length) {
  
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  String notification;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  // Feel free to add more if statements to control more GPIOs with MQTT
  Serial.println(String(topic)+" : "+messageTemp);

  // esp32swim/pump
  if (String(topic) == "esp32swim/pump") {
    if(messageTemp == "on"){
      Serial.println("on");
      digitalWrite(pump_RelayPin, HIGH);
    }
    else if(messageTemp == "off"){
      Serial.println("off");
      digitalWrite(pump_RelayPin, LOW);
    }
    notification = "pump:"+messageTemp;
    mqtt_publish("esp32swim/notifications", (char*)notification.c_str());
  }
  // esp32swim/heater
  else if (String(topic) == "esp32swim/heater") {
    if(messageTemp == "on"){
      Serial.println("on");
      digitalWrite(heater_RelayPin, HIGH);
    }
    else if(messageTemp == "off"){
      Serial.println("off");
      digitalWrite(heater_RelayPin, LOW);
    }
    notification = "heater:"+messageTemp;
    mqtt_publish("esp32swim/notifications", (char*)notification.c_str());
  }
}
