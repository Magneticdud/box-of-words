/**
 * BoxOfWords firmware
 *
 * Arduino based suggestion generator for improvisers.
 * Selects random words from wordlist files on an SD card and displays them on a 16x2 LCD.
 * Built as a present to Trent Pancy, the organizer of the Finland International Improv Festival 2014.
 * 
 * Licence: MIT
 * Author: Ando Roots <david@sqroot.eu> 2014
 * Web: http://wp.me/p1OdID-114
 **/
 
#include <SPI.h>
#include <SD.h>
#include "WordFile.h" // SD card wordfile reader
#include <JeeLib.h>  // Power saving functions

const byte SD_CS_Pin = 10; // SD chip select
const byte numberOfFiles = 8; // Number of wordfiles
const byte displayLength = 16; // LCD character columns (16x2)

// Pin definitions for buttons
const byte btnEnter = A0;
const byte btnBack = A1;
const byte btnLeft = A2;
const byte btnRight = A3;

// Max analogRead value for a button to be considered LOW / active (hack)
const byte btnLowMaxThreshold = 100;

// Setup watchdog
ISR(WDT_vect) { 
  Sleepy::watchdogEvent(); 
}

// Datastructure for holding operational settings
typedef struct Settings {
  byte brightness;
  int scrollSpeed;
} 
Settings;

Settings settings = {
  .brightness = 255,
  .scrollSpeed = 180
};

// Filenames of all wordfiles
char* fileList[] = {
  "WORDS_00.TXT","WORDS_01.TXT","WORDS_02.TXT","WORDS_03.TXT","WORDS_04.TXT","WORDS_05.TXT","WORDS_06.TXT", "WORDS_07.TXT"};

// Human-readable, meaningful titles for the wordfiles. Order matches with fileLists[]. Default values will be replaced from the SD card.
String fileTitles[8] = {
  "WORDS_00.TXT","WORDS_01.TXT","WORDS_02.TXT","WORDS_03.TXT","WORDS_04.TXT","WORDS_05.TXT","WORDS_06.TXT", "WORDS_07.TXT"};

int selectedFile = -1; // The index of the currently open file from fileList[]
byte menuIndex = 0; // Index of the currently displaying file title (when navigating the list of fileTitles[])
boolean wait = true; // True when a word is displaying and we wait for input from the user

boolean refreshMenuDisplay = true; // Set to False to avoid flickering the LCD screen with unneeded updates (when in the Select File menu)

void setup()
{

  // Make sure that the default chip select pin is set to
  // output, even if you don't use it
  pinMode(10, OUTPUT);

  // Set button pins as inputs with internal Atmega 20k pullup resistors enabled (important, no hardware resistors!)
  pinMode(btnEnter, INPUT_PULLUP);
  pinMode(btnBack, INPUT_PULLUP);
  pinMode(btnLeft, INPUT_PULLUP);
  pinMode(btnRight, INPUT_PULLUP);

  Serial.begin(9600);
  Serial.println("Serial start");

  // See if the SD card is present and can be initialized. Wait until card is inserted.
  while(!SD.begin(SD_CS_Pin)) {
    Serial.println("Insert SD card.");
    Sleepy::loseSomeTime(2000);
  }

  // Read and parse the settings file (or create if needed)
  initSettings();
  
  // Create all missing wordfiles as blank files
  createMissingWordFiles();
}



void loop(void) {

  // State #1: in the main menu until a wordfile is selected
  while (selectedFile == -1) {
    showMenu();
    delay(10);
  }

  // The user has selected a wordfile, move to state #2: showing random words from that file
  
  // Open the file
  WordFile words = WordFile(fileList[selectedFile]);
  words.init();  

  // Print the title of the file in the first row of the LCD
  Serial.println(fileTitles[selectedFile]);

  // If the file is empty (0 lines), show an error message and move back to the main menu
  if (words.countLines() == 0) {
    Serial.println("File is empty"); 
    delay(3000);
    selectedFile = -1;
    wait = false;
    refreshMenuDisplay = true;
    showLoadingMsg();
    return;
  }

  while (selectedFile != -1) { // Until the user presses the back button
  
    // Fetch a new random line from the wordfile, display it and wait
    String randomWord =  words.getRandomWord();
    displayWord(randomWord, selectedFile);
    wait = true;

    while (wait) { // Waiting for user input

      // Handle button presses
      
      byte pressedBtn = getPressedBtn();

      switch (pressedBtn) {
      case btnRight: // Get the next word
        wait = false;
        delay(50);
        break;
      case btnBack: // Move to state #1, the main menu
        selectedFile = -1;
        wait = false;
        refreshMenuDisplay = true;
        showLoadingMsg();
        return;
        break;
      default: // Just display the word
        if (randomWord.length() > displayLength) {
          marquee(randomWord); 
        }
        break;
      }
    }
  }


  Sleepy::loseSomeTime(2000);
}



/**
 * Create all missing wordfiles as blank files to avoid the program blowing up when a blank/malformed card is inserted.
**/
void createMissingWordFiles() {
  for (byte i = 0; i < numberOfFiles; i++) {
    if (!SD.exists(fileList[i])) {
      File wordFile = SD.open(fileList[i], FILE_WRITE);

      if (wordFile) {
        wordFile.print("");
        wordFile.close();  
      }
    }
  }
  delay(50);
}



