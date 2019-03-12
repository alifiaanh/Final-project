#include <Wire.h>
//RTC Initializion
#include <DS3231.h>
//SD Card Initializion
#include <SPI.h>
#include <SD.h>
//Ultrasonic Initializion
#define trigPin 6
#define echoPin 7
//DHT Initializion
#include <DHT.h>
#define DHTPIN 8  //menggunakan pin 8 untuk pemasangan sensornya
#define DHTTYPE DHT22 //memilih tipe DHT22, bisa diubah menjadi DHT11, DHT21
DHT dht(DHTPIN, DHTTYPE);  //setting pin yang dipilih dan tipe DHT


DS3231 rtc(SDA, SCL); //Reading Procedur 
File myFile;
double durasi, kedalaman;
float suhu;
float kelembaban;

void setup()
{
//Set baudrate at 115200
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  dht.begin(); //Komunikasi DHT dengan Arduino
 
//RTC DS3231 reading procedure
  rtc.begin();
  rtc.setDOW(TUESDAY);
  rtc.setDate(12,03,2019);
  rtc.setTime(15,23,00); 

 Serial.println("Read MicoSd Card");
 delay(1000);
 
 if (!SD.begin(4)) 
 {
 Serial.println("Failed read microsd card on module!");
 return;
 }

 if(!SD.exists("testdata.txt")){
  Serial.println("file testdata.txt not found");
  Serial.println("create testdata.txt ......");
  myFile = SD.open("testdata.txt", FILE_WRITE);
  myFile.close();
  Serial.println("create file succes!!");
 }else{
  Serial.println("file testdata.txt is available");
 }
 delay(1000);
}   
 
void loop()
{ 
  ultrasonic_sensor();
  dht_sensor();
  myFile = SD.open("testdata.txt", FILE_WRITE);
  if (myFile) // jika file tersedia tulis data
  {
  Serial.print(rtc.getDOWStr());
  Serial.print(",");
  myFile.print(rtc.getDOWStr());
  myFile.print(",");
  
  Serial.print(rtc.getDateStr());
  Serial.print(" -- ");
  myFile.print(rtc.getDateStr());
  myFile.print(" -- ");

  Serial.println(rtc.getTimeStr());
  myFile.println(rtc.getTimeStr());
  myFile.close();
  
  if (kedalaman <= 0.02 || kedalaman >= 4) {
  Serial.println("diluar jangkauan");
  }else{
  Serial.print("Kekosongan:");  
  Serial.print(kedalaman);
  Serial.println(" meter");
  myFile.print("Kekosongan:");  
  myFile.print(kedalaman);
  myFile.println(" meter");
  }
  
  Serial.print("Suhu:");  
  Serial.print(suhu);
  Serial.println("' Celcius");
  
  Serial.print("Kelembaban:");  
  Serial.print(kelembaban);
  Serial.println(" %");
  Serial.println(" ");
  
  myFile.print("Suhu:");  
  myFile.print(suhu);
  myFile.println("'Celcius");
  
  myFile.print("Kelembaban:");  
  myFile.print(kelembaban);
  myFile.println(" %");
  myFile.println(" ");
  myFile.close();  
 }
 else 
 {
 Serial.println("Failed open testdata.txt"); // jika gagal print error
 }
 delay(2000); //total jeda yaitu 5 detik karena proses penulisan data kurang lebih 3 detik
} 
