#define LCD_LED_PIN 10

void displayWord(String randomWord, byte selectedFile) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(fileTitles[selectedFile]);
  lcd.setCursor(0,1);
  lcd.print(randomWord);
  lcd.setCursor(0,0);
  Serial.println(randomWord);
}

void setBrightness(byte level) {
 analogWrite(LCD_LED_PIN, level);
}

void showLoadingMsg() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Hold on...");
}

