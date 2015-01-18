/**
 * BoxOfWords firmware
 *
 * LCD-related functions
 *
 * Licence: MIT
 * Author: Ando Roots <david@sqroot.eu> 2014
 * Web: http://wp.me/p1OdID-114
 **/

// PWM pin for setting the LCD background LED brightness
//#define LCD_LED_PIN 10

/**
 * Display a word from a wordfile on the LCD
**/
void displayWord(String randomWord, byte selectedFile) {
  Serial.println(fileTitles[selectedFile]);
  Serial.println(randomWord);
}

/**
 * Adjust LCD LED backlight brightness (PWM pin)
**/
void setBrightness(byte level) {
  //analogWrite(LCD_LED_PIN, level);
}

/**
 * Show a simple loading message on the LCD
**/
void showLoadingMsg() {
  Serial.println("Hold on...");
}

/**
 * Scroll a longer-than-16 char word on the LCD
 *
 * Don't use Sleepy here - will cause the backlight to flicker (as the PWM pin will be powered down?)
 **/
void marquee( String text)
{
  /*int length = text.length();
  int pos;

  lcd.setCursor(0, 1);
  for( pos = 0; pos < displayLength; pos++) {
    lcd.print(text[pos]);
  }

    delay(1000);
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

    delay(settings.scrollSpeed);
    pos = pos + 1;
  }
  delay(900);*/
  Serial.println(text);
}


