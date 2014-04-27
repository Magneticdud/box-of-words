#define LCD_LED_PIN 10

void displayWord(String randomWord, byte selectedFile) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(fileTitles[selectedFile]);
  lcd.setCursor(0,1);

  lcd.print(randomWord);

  lcd.setCursor(0,0);
}

void setBrightness(byte level) {
  analogWrite(LCD_LED_PIN, level);
}

void showLoadingMsg() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Hold on...");
}


void marquee( String text)
{
  int length = text.length();
  int pos;

  lcd.setCursor(0, 1);
  for( pos = 0; pos < displayLength; pos++) {
    lcd.print(text[pos]);
  }

    Sleepy::loseSomeTime(1000);
  pos = 1;


  while(pos <= length - displayLength)
  {
    lcd.setCursor(0,1);
    for( int i=0; i < displayLength; i++) {
      lcd.print(text[pos+i]);
      if (getPressedBtn()) {
        return;
      }
    }

    delay(settings.scrollSpeed); // Don't pass `byte scrollSpeed` to Sleepy
    pos = pos + 1;
  }
  Sleepy::loseSomeTime(300);
}


