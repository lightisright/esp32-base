void mqtt_subscriptions() {

  String topic;

  mqtt_gpio_setup();
  
  topic = esp32_id+"/heater";
  client.subscribe(topic.c_str());
  topic = esp32_id+"/pump";
  client.subscribe(topic.c_str());
  topic = esp32_id+"/restart";
  client.subscribe(topic.c_str());
}

void mqtt_gpio_setup() {
  
  pinMode(pump_RelayPin, OUTPUT);
  pinMode(heater_RelayPin, OUTPUT);
}

void mqtt_notify_error(String topic_str, String messageTemp) {
  
  mqtt_pub_error("UNKNOWN message", "\"topic\":\""+topic_str+"\",\"message\":\""+messageTemp+"\"");
}

/* for MQTT subscription if needed */
void mqtt_callback(char* topic, byte* message, unsigned int length) {
  
  String messageTemp;
  String topic_str = String(topic);

  for (int i = 0; i < length; i++) {
    messageTemp += (char)message[i];
  }

  // TRACE
  //Serial.print("Message arrived on topic: "+topic_str+". Message: "+messageTemp);
  //mqtt_pub_notify(topic_str, messageTemp);
  
  // esp32swim/pump
  if (mqtt_match_topic(topic_str, "pump")) {
    if(messageTemp == "on"){
      digitalWrite(pump_RelayPin, HIGH);
    }
    else if(messageTemp == "off"){
      digitalWrite(pump_RelayPin, LOW);
    }
    else {
      mqtt_notify_error(topic_str, messageTemp);
    }
    mqtt_pub_notify("Pump "+messageTemp+" triggered on "+topic_str, "\"pump\":\""+messageTemp+"\"");
  }
  
  // esp32swim/heater
  else if (mqtt_match_topic(topic_str, "heater")) {
    if(messageTemp == "on"){
      digitalWrite(heater_RelayPin, HIGH);
    }
    else if(messageTemp == "off"){
      digitalWrite(heater_RelayPin, LOW);
    }
    else {
      mqtt_notify_error(topic_str, messageTemp);
    }
    mqtt_pub_notify("Heater "+messageTemp+" triggered on "+topic_str, "\"heater\":\""+messageTemp+"\"");
  }

  // esp32swim/restart
  else if (mqtt_match_topic(topic_str, "restart")) {
    mqtt_pub_notify("ESP Restart triggered");
    ESP.restart();
  }

  // UNKNOWN MESSAGE
  else {
    mqtt_notify_error(topic_str, messageTemp);
  }
}
