
#include <SD.h>
#include <PortsLCD.h>
#include "WordFile.h"
#include <JeeLib.h> 
#include <MemoryFree.h>

#define SD_CS_PIN 8
#define NUMBER_OF_FILES 8


// Pin definitions for buttons
// A5 - 19; A4 - 18; A3 - 17; A2 - 16;
const byte btnEnter = A5;
const byte btnBack = A4;
const byte btnLeft = A3;
const byte btnRight = A2;

// Max analogRead value for a button to be considered LOW / active
const byte btnLowMaxThreshold = 100;

// Setup watchdog
ISR(WDT_vect) { Sleepy::watchdogEvent(); }


typedef struct Settings {
 byte brightness;
} Settings;

Settings settings = {
  .brightness = 255
};

LiquidCrystal lcd(9, 7, 5, 4, 3, 2);

char* fileList[] = {"WORDS_00.TXT","WORDS_01.TXT","WORDS_02.TXT","WORDS_03.TXT","WORDS_04.TXT","WORDS_05.TXT","WORDS_06.TXT", "WORDS_07.TXT"};
String fileTitles[8] = {"WORDS_00.TXT","WORDS_01.TXT","WORDS_02.TXT","WORDS_03.TXT","WORDS_04.TXT","WORDS_05.TXT","WORDS_06.TXT", "WORDS_07.TXT"};

int selectedFile = -1;
boolean wait = true;

void setup()
{
  
  // Make sure that the default chip select pin is set to
  // output, even if you don't use it
  pinMode(10, OUTPUT);
  
  // Set button pins as inputs with internal Atmega 20k pullup resistors enabled
  pinMode(btnEnter, INPUT_PULLUP);
  pinMode(btnBack, INPUT_PULLUP);
  pinMode(btnLeft, INPUT_PULLUP);
  pinMode(btnRight, INPUT_PULLUP);
  
  
  Serial.begin(9600);
    
  lcd.begin(16,2);
  
  lcd.noAutoscroll();
  lcd.print("   BoxOfWords   ");
  lcd.setCursor(0,1);
  lcd.print("A. Roots 2014-04");
    
  setBrightness(settings.brightness);
  
  delay(2000);

  // See if the card is present and can be initialized
  while(!SD.begin(SD_CS_PIN)) {
    lcd.clear();
    lcd.print("Insert SD card.");
    Sleepy::loseSomeTime(2000);
  }
  
  initSettings();

  lcd.clear();

  lcd.print(fileTitles[0]);
}



void loop(void) {
  
/*  while (selectedFile == -1) {
    showMenu();
  }
  */
  selectedFile = 0;
  
  WordFile words = WordFile(fileList[selectedFile]);
  words.init();  
  
  lcd.clear();
  lcd.print(fileTitles[selectedFile]);
  
  if (words.countLines() == 0) {
    lcd.setCursor(0,1);
    lcd.print("File is empty"); 
    lcd.setCursor(0,0);
  } else {
    
    while (selectedFile != -1) {
      String randomWord =  words.getRandomWord();
      lcd.clear();
      displayWord(randomWord);
      wait = true;
      
      while (wait) {
        
        
        if (getPressedBtn() == btnRight) {
          wait = false;
          delay(50);
        }
   
        if (Serial.available()) {
	  byte read = Serial.read();
	  switch (read) {
	    case 'd': wait = false; break;
	    case 'w': selectedFile = -1; wait = false; break;
	  }
	}
      }
    }
  }

    lcd.clear();
    Sleepy::loseSomeTime(3000);
}


