/*
  Words.h
*/
#ifndef Words_h
#define Words_h

#include "Arduino.h"

// include the SD library:
#include <SPI.h>
#include <SD.h>

uint8_t const SD_INIT_SUCCESS = 0;
uint8_t const SD_ERROR_CARD_INIT = 1;
uint8_t const SD_ERROR_UNKNOWN_TYPE = 2;
uint8_t const SD_ERROR_PARTITION = 3;


class Words {
 public:
 Words(int CSPin);
 uint8_t init();
 void getFilesList(char **files, int array_size);

 private:
  int _CSPin; 
  Sd2Card _card;
  SdVolume _volume;
  SdFile _root;
  SdFile _file;
};

#endif
