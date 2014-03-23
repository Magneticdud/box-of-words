
#include <SD.h>
#include <LiquidCrystal.h>

#include "WordFile.h"

LiquidCrystal lcd(9, 7, 5, 4, 3, 2);

char* fileList[] = {"WORDS_01.TXT","WORDS_02.TXT","WORDS_03.TXT","WORDS_04.TXT","WORDS_05.TXT","WORDS_06.TXT","WORDS_07.TXT", "WORDS_08.TXT"};

#define SD_CS_PIN 8
#define NUMBER_OF_FILES 8
#define SETTINGS_FILE "SETTINGS.TXT"

typedef struct Settings {
 byte brightness; 
} Settings;

Settings settings = {.brightness = 255};

void setup()
{
  // For debugging only  
  Serial.begin(9600);
  
  lcd.begin(16,2);
  lcd.noAutoscroll();
  lcd.clear();
    
  setBrightness(settings.brightness);
  setContrast(40);
  
  // See if the card is present and can be initialized
  while(!SD.begin(SD_CS_PIN)) {
    lcd.clear();
    lcd.print("Insert SD card.");
    delay(2000);
  }
  
  if (SD.exists(SETTINGS_FILE)) {
    readSettingsFile();
  } else {
   createSettingsFile(); 
  }
}




void loop(void) {

  for (int j = 0; j < NUMBER_OF_FILES; j++) {

  for (int o = 0; o < 8; o++) {
    WordFile words = WordFile(fileList[j]);
  words.init();  
  lcd.print(fileList[j]);
  
if (words.countLines() == 0) {
  lcd.setCursor(0,1);
 lcd.print("File is empty"); 
   lcd.setCursor(0,0);
} else {


  String randomWord =  words.getRandomWord();
  displayWord(randomWord);
}

  delay(1000);
    lcd.clear();
  }
  
  }
  
}


void createSettingsFile() {
  File settingsFile = SD.open(SETTINGS_FILE, FILE_WRITE);
  
  if (settingsFile) {
    settingsFile.print("brightness:200");
    settingsFile.close();  
  }
}

void readSettingsFile() {

}
