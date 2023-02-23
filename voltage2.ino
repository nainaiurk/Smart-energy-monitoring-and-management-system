int voltage_measure(){
  int Vout = (analogRead(voltage1)*240/4096);
  delay(1000);
  // if (Vout < 150)  Vout = 150;
  // else if (Vout > 240)  Vout = 240;
  // // else if (!v0Pin) Vout = 0;
  Serial.print("V: ");
  Serial.println(String(Vout));
  return Vout;
}
