//Wire Initialization
#include <Wire.h>

//RTC Initialization
#include <DS3231.h>
DS3231 rtc(SDA, SCL); //RTC Reading Procedure

//SD Card Initialization
#include <SPI.h>
#include <SD.h>
File myFile;

//LCD Initialization
//#include <LiquidCrystal.h>
//LiquidCrystal lcd(10, 9, 7, 6, 5, 4);

//DHT Initialization
#include <DHT.h>
#define DHTPIN 8  //menggunakan pin 8 untuk pemasangan sensornya
#define DHTTYPE DHT22 //memilih tipe DHT22, bisa diubah menjadi DHT11, DHT21
DHT dht(DHTPIN, DHTTYPE);  //setting pin yang dipilih dan tipe DHT

//Ultrasonic Initialization
#define TrigPin 2
#define EchoPin 3

//Inisialisasi Tipping Bucket
//int rainPin = 9;
//int inputRead = 0;
//int currentState = 0;
//int previousState = 0;

//define variable
double durasi, kedalaman;
float counter = 0;
float suhu;
float kelembaban;



void setup () {
  Serial.begin(115200);
  
  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);
  
  rtc.begin();
  rtc.setDOW(TUESDAY);
  rtc.setDate(12,03,2019);
  rtc.setTime(17,41,00); 
  
  lcd.begin(16, 2); //Komunikasi lcd dengan Arduino
  
  dht.begin(); //Komunikasi DHT dengan Arduino

  Serial.println("Read MicoSd Card");
  delay(1000);
 
  if (!SD.begin(4)) 
 {
 Serial.println("Failed read microsd card on module!");
 return;
 }

 if(!SD.exists("SensorData.txt")){
  Serial.println("File SensorData.txt not found");
  Serial.println("Create SensorData.txt ......");
  myFile = SD.open("SensorData.txt", FILE_WRITE);
  myFile.close();
  Serial.println("Create File Success!!");
 }else{
  Serial.println("File SensorData.txt is Available");
 }
 delay(1000);
}

void loop() {
  count();
  if (kedalaman <= 0.02 || kedalaman >= 4) {
  Serial.println("diluar jangkauan");
  } else {
  ultrasonic_sensor();
  dht_sensor();
  lcd_print();
//  delay(25);
}

