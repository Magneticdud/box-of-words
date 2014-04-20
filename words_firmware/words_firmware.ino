
#include <SD.h>
#include <PortsLCD.h>
#include "WordFile.h"
#include <Bounce2.h>
#include <JeeLib.h> 
#include <MemoryFree.h>

#define SD_CS_PIN 8
#define NUMBER_OF_FILES 8


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

Bounce buttonLeft = Bounce();
Bounce buttonRight = Bounce();
Bounce buttonEnter = Bounce();
Bounce buttonBack = Bounce();

int selectedFile = -1;
boolean wait = true;

void setup()
{
  
  // make sure that the default chip select pin is set to
  // output, even if you don't use it:
  pinMode(10, OUTPUT);
  
  pinMode(A5, INPUT_PULLUP);
  pinMode(A4, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  pinMode(A0, INPUT_PULLUP);
 
  buttonLeft.attach(A5);
  buttonRight.attach(A4);
  buttonEnter.attach(A3);
  buttonBack.attach(A2);
  
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
        buttonEnter.update();
        buttonRight.update();
        buttonBack.update();
        
        if (buttonEnter.read() == LOW) {
          wait = false;
          delay(50);
        }
        
/*        if (buttonBack.read() == LOW) {
          selectedFile = -1;
          wait = false;
        }
  */      
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


