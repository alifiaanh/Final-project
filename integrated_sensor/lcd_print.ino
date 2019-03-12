void lcd_print(){
  lcd.setCursor(0,0);
  lcd.print("T:");
  lcd.print(suhu,1);
  lcd.print("C");
  
  lcd.setCursor(0,1);
  lcd.print("H:");
  lcd.print(kelembaban,1);
  lcd.print("%");

  lcd.setCursor(8,0);
  lcd.print("R:");
  lcd.print(counter,2);
  lcd.print("mm");

  lcd.setCursor(8,1);
  lcd.print("h:");
  lcd.print(kedalaman,1);  
  lcd.print("m");
  
}

