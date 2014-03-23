#define LCD_LED_PIN 10
#define LCD_CONTRAST_PIN 6

void displayWord(String randomWord) {
 
  lcd.setCursor(0,1);
  lcd.print(randomWord);
  lcd.setCursor(0,0);
}

void setBrightness(byte level) {
 analogWrite(LCD_LED_PIN, level);
}

void setContrast(byte level) {
 analogWrite(LCD_CONTRAST_PIN, level);
}
