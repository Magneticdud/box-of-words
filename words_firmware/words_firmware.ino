
#include <SD.h>
#include <LiquidCrystal.h>
#include <MenuBackend.h>
#include "WordFile.h"

LiquidCrystal lcd(9, 7, 5, 4, 3, 2);

char* fileList[] = {"WORDS_01.TXT","WORDS_02.TXT","WORDS_03.TXT","WORDS_04.TXT","WORDS_05.TXT","WORDS_06.TXT","WORDS_07.TXT", "WORDS_08.TXT"};
char* fileTitles[8] = {"Emotions1", "Places2", "Numbers", "Names", "Activities", "Letters", "Positions", "Games"};

#define SD_CS_PIN 8
#define NUMBER_OF_FILES 8

typedef struct Settings {
 byte brightness;
} Settings;

Settings settings = {.brightness = 255};


void setup()
{
  
  // make sure that the default chip select pin is set to
  // output, even if you don't use it:
  pinMode(10, OUTPUT);
  
  pinMode(A5, INPUT_PULLUP);
  pinMode(A4, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
 
  lcd.begin(16,2);
  lcd.noAutoscroll();
  lcd.print("Hold on, loading...");
    
  setBrightness(settings.brightness);
  
  delay(20);

  // See if the card is present and can be initialized
  while(!SD.begin(SD_CS_PIN)) {
    lcd.clear();
    lcd.print("Insert SD card.");
    delay(2000);
  }
  
  initSettings();
  
  lcd.clear();
}



void loop(void) {
   Serial.begin(9600);
  Serial.println("Starting navigation:\r\nUp: w   Down: s   Left: a   Right: d   Use: e");
  Serial.print("Brightness: ");
  Serial.println(settings.brightness);
  Serial.print("Title0: ");
  Serial.println(fileTitles[0]);
    
  buildMenu();
  
  while (true) {
    showMenu();
  }
  
  WordFile words = WordFile(fileList[0]);
  words.init();  
  lcd.print(fileList[0]);
  
  if (words.countLines() == 0) {
    lcd.setCursor(0,1);
    lcd.print("File is empty"); 
    lcd.setCursor(0,0);
  } else {
    String randomWord =  words.getRandomWord();
    displayWord(randomWord);
    
    ////////////*
    
    boolean goToNext = false;
    while(!goToNext) {
      if(digitalRead(A4) == LOW) {
       delay(20);
       if(digitalRead(A4) == LOW) {        
         goToNext = true;
       }
      } else {
       delay(100); 
      }
    }
    /////////////
    
  }

    lcd.clear();
  delay(3000);
}


