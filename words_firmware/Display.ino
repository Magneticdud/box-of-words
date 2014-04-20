#define LCD_LED_PIN 10

void displayWord(String randomWord) {
 
  lcd.setCursor(0,1);
  lcd.print(randomWord);
  lcd.setCursor(0,0);
  Serial.println(randomWord);
}

void setBrightness(byte level) {
 analogWrite(LCD_LED_PIN, level);
}

