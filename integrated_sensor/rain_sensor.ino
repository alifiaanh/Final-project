void count(){
  inputRead = digitalRead(rainPin); // read input value
  if (inputRead == HIGH) { // check if the input is HIGH (button released)
    currentState = 0;
  }
  else {
    currentState = 1;
  }
  if (currentState != previousState) {
    if (currentState == 1) {
      counter = counter + 0.0704;
    }
  }
  
  delay(20);
}
