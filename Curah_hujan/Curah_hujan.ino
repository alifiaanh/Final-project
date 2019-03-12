int rainPin = 2; // Rain Meter Pin
int inputRead = 0; // variable for reading the pin status
float counter = 0;
int currentState = 0;
int previousState = 0;

void setup() {  
  pinMode(rainPin, INPUT); 
  Serial.begin(9600);
}

void loop() {
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
      Serial.println(counter,3);
    }
  }
  delay(20);
}
