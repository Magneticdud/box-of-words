/*
  Words.cpp
*/

#include "Arduino.h"
#include "Words.h"

// include the SD library:
#include <SPI.h>
#include <SdFat.h>
#include <SdFatUtil.h>

// set up variables using the SD utility library functions:
Sd2Card _card;
SdVolume _volume;
SdFile _root;
SdFile _file;


  
  // store error strings in flash to save RAM
#define error(s) error_P(PSTR(s))
  
  
Words::Words(int CSPin)
{
  _CSPin = CSPin;
}

void _error_P(const char* str) {
  PgmPrint("error: ");
  SerialPrintln_P(str);
  if (_card.errorCode()) {
    PgmPrint("SD error: ");
    Serial.print(_card.errorCode(), HEX);
    Serial.print(',');
    Serial.println(_card.errorData(), HEX);
  }
  while(1);
}

uint8_t Words::init()
{
  
  
  // Open serial communications and wait for port to open:

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

  if (!_root.openRoot(_volume)) {
   return SD_ERROR_ROOT_FAIL; 
  }
  
  // list all files in the card with date and size
  _root.ls(LS_R | LS_DATE | LS_SIZE);
  
  return SD_INIT_SUCCESS;
}


 void Words::getFilesList(char **files, int array_size) {
   
   
   
 for (int i = 0; i < array_size; i++) {
  files[i] = "This is file "; 
 }
 /*
 
// This code is just copied from SdFile.cpp in the SDFat library
  // and tweaked to print to the client output in html!
  dir_t p;
  
  _root.rewind();
String name;
int cnt = 0;

  while (_root.readDir(p) > 0) {
    // done if past last used entry
    if (p.name[0] == DIR_NAME_FREE) break;

    // skip deleted entry and entries for . and  ..
    if (p.name[0] == DIR_NAME_DELETED || p.name[0] == '.') continue;

    // only list subdirectories and files
    if (!DIR_IS_FILE_OR_SUBDIR(&p)) continue;

 
    
    // print file name with possible blank fill
    for (uint8_t i = 0; i < 11; i++) {
      if (p.name[i] == ' ') continue;
      
      if (i == 8) {
        name = name + '.';
      }
      
      name = name + (char)p.name[i];
    }
    
    cnt++;
    files[cnt] = "name";
    if (cnt >= array_size) {
      break;
    }

  }

 */
 
}
