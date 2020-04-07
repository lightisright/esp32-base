
void touch_on(int pinId) {

  switch(pinId) {
    case 0:
      Serial.println("Touch 0 ON");
      break;
    default:
      break;
  }
}

void touch_off(int pinId) {

  switch(pinId) {
    case 0:
      //Serial.println("Touch 0 OFF");
      break;
    default:
      break;
  }
}
