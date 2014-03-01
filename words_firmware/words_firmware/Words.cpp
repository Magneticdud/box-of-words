/*
  Words.cpp
*/

#include "Arduino.h"
#include "Words.h"

// include the SD library:
#include <SPI.h>
#include <SD.h>
#include <SdFat.h>
#include <SdFatUtil.h>

// set up variables using the SD utility library functions:
Sd2Card _card;
SdVolume _volume;
SdFile _root;
SdFo;e _file;

Words::Words(int CSPin)
{
  _CSPin = CSPin;
}

uint8_t Words::init()
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }


  // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
  // Note that even if it's not used as the CS pin, the hardware SS pin 
  // (10 on most Arduino boards, 53 on the Mega) must be left as an output 
  // or the SD library functions will not work. 
  pinMode(SS, OUTPUT);


  // we'll use the initialization code from the utility libraries
  // since we're just testing if the card is working!
  if (!_card.init(SPI_HALF_SPEED, _CSPin)) {
    return SD_ERROR_CARD_INIT;
  } 
  

  switch(_card.type()) {
    case SD_CARD_TYPE_SD1:
    case SD_CARD_TYPE_SD2:
    case SD_CARD_TYPE_SDHC:
      break;
    default:
      return SD_ERROR_UNKNOWN_TYPE;
  }

  // Now we will try to open the 'volume'/'partition' - it should be FAT16 or FAT32
  if (!_volume.init(_card)) {
    return SD_ERROR_PARTITION;
  }

  _root.openRoot(_volume);
  
  // list all files in the card with date and size
  _root.ls(LS_R | LS_DATE | LS_SIZE);
  
  return SD_INIT_SUCCESS;
}

 void Words::getFilesList(char **files, int array_size) {
   
   
   
 for (int i = 0; i < array_size; i++) {
  files[i] = "This is file "; 
 }
 
 


 
 
}
