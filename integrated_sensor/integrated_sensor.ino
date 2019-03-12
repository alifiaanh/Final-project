//LCD Initialization
#include <LiquidCrystal.h>
LiquidCrystal lcd(10, 9, 7, 6, 5, 4);

//DHT Initialization
#include <DHT.h>
#define DHTPIN 8  //menggunakan pin 8 untuk pemasangan sensornya
#define DHTTYPE DHT22 //memilih tipe DHT22, bisa diubah menjadi DHT11, DHT21
DHT dht(DHTPIN, DHTTYPE);  //setting pin yang dipilih dan tipe DHT

//Ultrasonic Initialization
#define trigPin 2
#define echoPin 3

//Tipping Bucket Initialization
int rainPin = 9;
int inputRead = 0;
int currentState = 0;
int previousState = 0;

//define variable
double durasi, kedalaman;
float counter = 0;
float suhu;
float kelembaban;

void setup () {
  Serial.begin(115200);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  lcd.begin(16, 2); //Komunikasi lcd dengan Arduino
  dht.begin(); //Komunikasi DHT dengan Arduino
}
void loop() {
  count();
  if (kedalaman <= 0.02 || kedalaman >= 4) {
  Serial.println("diluar jangkauan");
  } else {
  ultrasonic_sensor();
  dht_sensor();
  lcd_print();
  delay(25);
  }
}
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

