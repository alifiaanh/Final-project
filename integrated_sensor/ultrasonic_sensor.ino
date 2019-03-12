void ultrasonic_sensor(){
  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin, LOW);

  durasi = pulseIn(echopin, HIGH);
  kedalaman = (durasi * 0.000343) / 2; 
}

