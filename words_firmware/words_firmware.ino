/**
 * BoxOfWords firmware
 *
 * Arduino based suggestion generator for improvisers.
 * 
 * Licence: MIT
 * Author: Ando Roots <david@sqroot.eu> 2014
 * Web: http://wp.me/p1OdID-114
**/

#include <SD.h>
#include <PortsLCD.h> // From JeeLib, overrides LiquidCrystal
#include "WordFile.h" // SD card wordfile reader
#include <JeeLib.h>  // Power saving functions

const byte SD_CS_Pin = 8; // SD chip select
const byte numberOfFiles = 8; // Number of wordfiles
const byte displayLength = 16; // LCD character columns (16x2)

// Pin definitions for buttons
// A5 - 19; A4 - 18; A3 - 17; A2 - 16;
const byte btnEnter = A5;
const byte btnBack = A2;
const byte btnLeft = A3;
const byte btnRight = A4;

// Max analogRead value for a button to be considered LOW / active
const byte btnLowMaxThreshold = 100;

// Setup watchdog
ISR(WDT_vect) { 
  Sleepy::watchdogEvent(); 
}


typedef struct Settings {
  byte brightness;
  int scrollSpeed;
} 
Settings;

Settings settings = {
  .brightness = 255,
  .scrollSpeed = 180
};

LiquidCrystal lcd(9, 7, 5, 4, 3, 2);

char* fileList[] = {
  "WORDS_00.TXT","WORDS_01.TXT","WORDS_02.TXT","WORDS_03.TXT","WORDS_04.TXT","WORDS_05.TXT","WORDS_06.TXT", "WORDS_07.TXT"};
String fileTitles[8] = {
  "WORDS_00.TXT","WORDS_01.TXT","WORDS_02.TXT","WORDS_03.TXT","WORDS_04.TXT","WORDS_05.TXT","WORDS_06.TXT", "WORDS_07.TXT"};

int selectedFile = -1;
byte menuIndex = 0;
boolean wait = true;

boolean refreshMenuDisplay = true;

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

  lcd.begin(displayLength, 2);

  lcd.print("   BoxOfWords   ");
  lcd.setCursor(0,1);
  lcd.print("for improvisers");

  setBrightness(settings.brightness);

  Sleepy::loseSomeTime(2000);

  // See if the card is present and can be initialized
  while(!SD.begin(SD_CS_Pin)) {
    lcd.clear();
    lcd.print("Insert SD card.");
    Sleepy::loseSomeTime(2000);
  }

  initSettings();
  setBrightness(settings.brightness);
}



void loop(void) {

  while (selectedFile == -1) {
    showMenu();
    delay(10);
  }

  WordFile words = WordFile(fileList[selectedFile]);
  words.init();  

  lcd.clear();
  lcd.print(fileTitles[selectedFile]);

  if (words.countLines() == 0) {
    lcd.setCursor(0,1);
    lcd.print("File is empty"); 
    lcd.setCursor(0,0);
  } 
  else {

    while (selectedFile != -1) {
      String randomWord =  words.getRandomWord();
      displayWord(randomWord, selectedFile);
      wait = true;

      while (wait) {

        byte pressedBtn = getPressedBtn();

        switch (pressedBtn) {
        case btnRight:
          wait = false;
          delay(50);
          break;
        case btnBack:
          selectedFile = -1;
          wait = false;
          refreshMenuDisplay = true;
          showLoadingMsg();
          return;
          break;
        default:
          if (randomWord.length() > displayLength) {
            lcd.clear();
            marquee(randomWord); 
          }
          break;
        }


      }
    }
  }

  lcd.clear();
  Sleepy::loseSomeTime(3000);
}



