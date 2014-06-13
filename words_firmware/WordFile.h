/**
 * BoxOfWords firmware
 *
 * Wordfile library header
 *
 * Licence: MIT
 * Author: Ando Roots <david@sqroot.eu> 2014
 * Web: http://wp.me/p1OdID-114
 **/
#ifndef WordFile_h
#define WordFile_h

#include "Arduino.h"

// include the SD library:
#include <SD.h>

class WordFile {

public:
  WordFile(char* fileName);
  uint8_t init();
  String getRandomWord();
  unsigned int countLines();

private:
  char* _fileName;
  unsigned int _countLines();
  unsigned int numberOfLines = 0; 
  String _getLine(unsigned int lineNumber);
};

#endif

