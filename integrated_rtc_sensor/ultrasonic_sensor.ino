void ultrasonic_sensor(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  durasi = pulseIn(echoPin, HIGH);
  kedalaman = (durasi * 0.000343) / 2; 
}
