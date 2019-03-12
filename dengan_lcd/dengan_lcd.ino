//Inisialisasi LCD
#include <LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 5, 4, 3, 2);

//Inisialisasi DHT
#include <DHT.h>
#define DHTPIN 8  //menggunakan pin 8 untuk pemasangan sensornya
#define DHTTYPE DHT22 //memilih tipe DHT22, bisa diubah menjadi DHT11, DHT21
DHT dht(DHTPIN, DHTTYPE);  //setting pin yang dipilih dan tipe DHT

//Inisialisasi Ultrasonic
#define trigpin 6
#define echopin 7

//Inisialisasi Tipping Bucket
int rainPin = 9;
int inputRead = 0;
int currentState = 0;
int previousState = 0;


//define variable
double durasi, kedalaman;
float counter = 0;

void setup () {
  Serial.begin(115200);
  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);
  lcd.begin(16, 2); //Komunikasi lcd dengan Arduino
  dht.begin(); //Komunikasi DHT dengan Arduino
}

void loop() {
  float kelembaban = dht.readHumidity(); //menyimpan nilai Humidity pada variabel kelembaban
  float suhu = dht.readTemperature(); //menyimpan nilai Temperature pada variabel suhu
  
  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin, LOW);

  inputRead = digitalRead(rainPin); // read input value
  if (inputRead == HIGH){ // check if the input is HIGH
  currentState = 0;
  }
  else {
   currentState = 1;  
  }
  
  //pengukuran
  
  durasi = pulseIn(echopin, HIGH);
  kedalaman = (durasi / 2) * 0.000343;
  if (currentState != previousState){
      counter = counter + 0.0704;
    }
  
  if (kedalaman <= 0.02 || kedalaman >= 4) {
    Serial.println("diluar jangkauan");
    } else {

    lcd.setCursor(0, 0);
    lcd.print ("Tinggi:");
    lcd.print (kedalaman);  
    lcd.print (" M");

    lcd.setCursor(0, 1);
    lcd.print("Kelembapan:");
    lcd.print(kelembaban);
    lcd.print(" %");
    delay(1000);
    lcd.clear();
    
    lcd.setCursor(0, 0);
    lcd.print("Suhu:");
    lcd.print(suhu);
    lcd.print(" C");
    delay(1000);
    lcd.clear();

    lcd.setCursor(0, 1);
    lcd.print("Hujan:");
    lcd.print(counter,3);
    lcd.print(" mm/hari");
    delay(1000);
    lcd.clear();
    
    Serial.println(kedalaman);
    Serial.println(kelembaban);
    Serial.println(suhu);
    Serial.println(counter,3);
    }
}
