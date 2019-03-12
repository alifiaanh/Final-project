void save_file(){
 myFile = SD.open("testdata.txt", FILE_WRITE);
 if (myFile){
  myFile.print(rtc.getDowStr);
  myFile.print(suhu);
  myFile.print(kelembaban);
  myFile.print(counter);
  myFile.print(kedalaman);
 }
}

