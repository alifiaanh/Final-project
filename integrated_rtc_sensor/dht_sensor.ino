void dht_sensor(){
  kelembaban = dht.readHumidity(); //menyimpan nilai Humidity pada variabel kelembaban
  suhu = dht.readTemperature(); //menyimpan nilai Temperature pada variabel suhu
}

