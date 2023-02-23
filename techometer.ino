void techometer() {
  int sensorValue = digitalRead(ir);

  prevVal = currentVal;
  currentVal = sensorValue;

  if (prevVal > currentVal) pulses++;

  if (millis() - lastSampleTime > 3000) {
    rpm = pulses * 4 * 50;
    // rpm = constrain(rpm, minRPM, maxRPM);
    if(rpm>0 && rpm < 10000) Serial.println("rpm :" + String(rpm));
    pulses = 0;
    lastSampleTime = millis();
  }
}