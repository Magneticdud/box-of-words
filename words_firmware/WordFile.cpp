/**
 * BoxOfWords firmware
 *
 * Wordfile library
 *
 * Licence: MIT
 * Author: Ando Roots <david@sqroot.eu> 2014
 * Web: http://wp.me/p1OdID-114
 **/

#include "Arduino.h"
#include "WordFile.h"

// include the SD library:
#include <SD.h>

const char wordDelimiter = '\n';

WordFile::WordFile(char* fileName)
{
  _fileName = fileName;
  randomSeed(analogRead(A0));

}

uint8_t WordFile::init()
{

  numberOfLines = _countLines(); 

  return 0;
}

/**
 * Count the lines in the wordfile (one word pre line)
**/
unsigned int WordFile::_countLines() {

  File dataFile = SD.open(_fileName);

  char character;
  unsigned int lines = 0;
  if (dataFile) {
    while (dataFile.available()) {

      character = dataFile.read();

      if (character == wordDelimiter) {
        lines++;
      }
    }

    dataFile.close(); 
  }

  return lines;
}

/**
 * Get the specified line from the wordfile
**/
String WordFile::_getLine(unsigned int lineNumber) {

  String returnValue = "";
  File dataFile = SD.open(_fileName);

  String currentLine = "";
  char character;
  unsigned int currentLineNumber = 0;

  if (dataFile) {

    while (dataFile.available()) {

      character = dataFile.read();

      if (character == '\n') {

        if (currentLineNumber == lineNumber) {
          returnValue = currentLine;
          break;
        }

        currentLineNumber++;
        currentLine = "";
      } 
      else {
        currentLine.concat(character);
      }
    }

    dataFile.close();
  }

  return returnValue;

}

/**
 * Return a random word from the wordfile
**/
String WordFile::getRandomWord() {

  return WordFile::_getLine(random(numberOfLines));
}

/**
 * Return the number of lines in the wordfile
**/
unsigned int WordFile::countLines(){
  return numberOfLines;
}


