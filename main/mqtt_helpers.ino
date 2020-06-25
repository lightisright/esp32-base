
// Format topic to xxxx/yyyyy
// - overload topic root with esp32 id if no root present
String mqtt_format_topic(String topic) {
  
  String mqtt_topic = topic;
  if ( topic.indexOf("/")==-1 ) {
    mqtt_topic = esp32_id+"/"+topic;
  }

  return(mqtt_topic);
}

bool mqtt_match_topic(String topic, String topic_to_match) {
 topic = mqtt_format_topic(topic);
 topic_to_match = mqtt_format_topic(topic_to_match);
 return(topic == topic_to_match);
}

bool mqtt_match_msg(String topic, String topic_to_match, String msg, String msg_to_match) {
  return(mqtt_match_topic(topic, topic_to_match) && msg==msg_to_match);
}

/**
 * MQTT Pub Helpers
 */

void mqtt_pub(String topic, String msg) {
  mqtt_publish(topic, "{\"msg\":\""+msg+"\"}");
}

void mqtt_pub(String topic, String msg, String payload) {
  mqtt_publish(topic, "{\"msg\":\""+msg+"\", \"payload\":{"+payload+"}}");
}

void mqtt_pub_notify(String msg) {
  mqtt_pub("notify", msg);
}

void mqtt_pub_notify(String msg, String payload) {
  mqtt_pub("notify", msg, payload);
}

void mqtt_pub_warning(String msg) {
  mqtt_pub_notify(msg);
  mqtt_publish("warning", msg);
}

void mqtt_pub_warning(String msg, String payload) {
  mqtt_pub_notify(msg, payload);
  mqtt_pub("warning", msg, payload);
}

void mqtt_pub_error(String msg) {
  mqtt_pub_warning(msg);
  mqtt_publish("error", msg);
}

void mqtt_pub_error(String msg, String payload) {
  mqtt_pub_warning(msg, payload);
  mqtt_pub("error", msg, payload);
}
