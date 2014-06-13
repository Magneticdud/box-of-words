/**
 * BoxOfWords firmware
 *
 * Settings file related functions
 *
 * Licence: MIT
 * Author: Ando Roots <david@sqroot.eu> 2014
 * Web: http://wp.me/p1OdID-114
 **/

char* settingsFileName = "SETTINGS.TXT";

/**
 * Load the contents of the settings file or create a new settings file if it doesn't exist
**/
void initSettings() {

  if (SD.exists(settingsFileName)) {
    readSettingsFile();
  } 
  else {
    createSettingsFile(); 
  }
}

/**
 * Create a new settings file
**/
void createSettingsFile() {
  File settingsFile = SD.open(settingsFileName, FILE_WRITE);
  
  if (settingsFile) {
    
    char* lines[] = {
    "brightness=200",
    "scrollSpeed=180",
    "title0=WORDS_00.TXT",
    "title1=WORDS_01.TXT",
    "title2=WORDS_02.TXT",
    "title3=WORDS_03.TXT",
    "title4=WORDS_04.TXT",
    "title5=WORDS_05.TXT",
    "title6=WORDS_06.TXT",
    "title7=WORDS_07.TXT"
    };
  
    for (byte i = 0; i < sizeof(lines); i++) {
      settingsFile.println(lines[i]);
    }
    
    settingsFile.close();  
  }
}

/**
 * Return True if the current line has more characters to read and the file is available
**/
boolean lineHasMoreChars(char currentChar, File file) {
  return currentChar != '\n' && file.available();
}

/**
 * Read the contents of the settings file and set program variables accordingly.
 * Ugly, but works.
 * Original code from http://jurgen.gaeremyn.be/index.php/arduino/reading-configuration-file-from-an-sd-card.html
**/
void readSettingsFile() {

  File settingsFile = SD.open(settingsFileName);

  char character;
  String description = "";
  String value = "";

  // read from the file until there's nothing else in it:
  while (settingsFile.available()) {
    character = settingsFile.read();

    if(character == '#')         {
      // Comment - ignore this line
      while(lineHasMoreChars(character, settingsFile)){
        character = settingsFile.read();
      };
    } 
    else if(isalnum(character))      {  // Add a character to the description
      description.concat(character);
    } 
    else if(character =='=')         {  // start checking the value for possible results
      // First going to trim out all trailing white spaces
      do {
        character = settingsFile.read();
      } 
      while(character == ' ');


      if(description == "brightness") {
        value = "";
        while(lineHasMoreChars(character, settingsFile)) {
          if(isdigit(character)) {
            value.concat(character);
          } 
          
          character = settingsFile.read();            
        };
          // Convert string to array of chars
          char charBuf[value.length()+1];
          value.toCharArray(charBuf,value.length()+1);
          // Convert chars to integer
          settings.brightness = atoi(charBuf);

      }
      if(description == "scrollSpeed") {
        value = "";
        while(lineHasMoreChars(character, settingsFile)) {
          if(isdigit(character)) {
            value.concat(character);
          } 
          
          character = settingsFile.read();            
        };

          // Convert string to array of chars
          char charBuf[value.length()+1];
          value.toCharArray(charBuf,value.length()+1);
          // Convert chars to integer
          settings.scrollSpeed = atoi(charBuf);
      } 
      else if(description == "title0") {

        value = "";
        do {
          value.concat(character);
          character = settingsFile.read();
        } 
        while(lineHasMoreChars(character, settingsFile));

        fileTitles[0] = value;


      } 
      else if(description == "title1") {
        value = "";
        do {
          value.concat(character);
          character = settingsFile.read();
        } 
        while(lineHasMoreChars(character, settingsFile));
        fileTitles[1] = value;
      }
      else if(description == "title2") {
        value = "";
        do {
          value.concat(character);
          character = settingsFile.read();
        } 
        while(lineHasMoreChars(character, settingsFile));
        fileTitles[2] = value;

      }
      else if(description == "title3") {
        value = "";
        do {
          value.concat(character);
          character = settingsFile.read();
        } 
        while(lineHasMoreChars(character, settingsFile));
        fileTitles[3] = value;

      }
      else if(description == "title4") {
        value = "";
        do {
          value.concat(character);
          character = settingsFile.read();
        } 
        while(lineHasMoreChars(character, settingsFile));
        fileTitles[4] = value;


      }
      else if(description == "title5") {
        value = "";
        do {
          value.concat(character);
          character = settingsFile.read();
        } 
        while(lineHasMoreChars(character, settingsFile));
        fileTitles[5] = value;

      }
      else if(description == "title6") {
        value = "";
        do {
          value.concat(character);
          character = settingsFile.read();
        } 
        while(lineHasMoreChars(character, settingsFile));
        fileTitles[6] = value;  
      }

      else if(description == "title7") {
        value = "";
        do {
          value.concat(character);
          character = settingsFile.read();
        } 
        while(lineHasMoreChars(character, settingsFile));
        fileTitles[7] = value;

      }

      else { // unknown parameter
        while(lineHasMoreChars(character, settingsFile))
          character = settingsFile.read();
      }
      description = "";
    } 
    else {
      // Ignore this character (could be space, tab, newline, carriage return or something else)
    }

  }
  
  // close the file:
  settingsFile.close();
}

