#include <DHT.h>
#define DHTPIN 8  //menggunakan pin 5 untuk pemasangan sensornya
#define DHTTYPE DHT22 //memilih tipe DHT22, bisa diubah menjadi DHT11, DHT21
DHT dht(DHTPIN, DHTTYPE);  //setting pin yang dipilih dan tipe DHT

#define trigpin 6
#define echopin 7

//define variable
double durasi, kedalaman;

void setup () {
  Serial.begin(115200);
  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);
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
 
  //pengukuran

  durasi = pulseIn(echopin, HIGH);
  kedalaman = (durasi / 2) * 0.000343;

  if (kedalaman <= 0.02 || kedalaman >= 4) {
    Serial.println("diluar jangkauan");
    } else {

    Serial.print("Ketinggian air:");
    Serial.print(kedalaman);
    Serial.println(" m");
    Serial.print("Kelembaban:");
    Serial.println(kelembaban);
    Serial.print("Suhu:");
    Serial.print(suhu);
    Serial.println(" C");
    delay(2000);
    }
  }
