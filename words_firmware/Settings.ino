
char* settingsFileName = "SETTINGS.TXT";

void initSettings() {
  
  if (SD.exists(settingsFileName)) {
    readSettingsFile();
  } else {
   createSettingsFile(); 
  }
  
}

void createSettingsFile() {
  Serial.println("Creating a new settings file");
  File settingsFile = SD.open(settingsFileName, FILE_WRITE);
  
  if (settingsFile) {
    settingsFile.print("brightness:200");
    settingsFile.close();  
  }
}

// http://jurgen.gaeremyn.be/index.php/arduino/reading-configuration-file-from-an-sd-card.html
void readSettingsFile() {

  File settingsFile = SD.open(settingsFileName);
  
  char character;
  String description = "";
  String value = "";
  boolean valid = true;
  
    // read from the file until there's nothing else in it:
    while (settingsFile.available()) {
      character = settingsFile.read();
             if(character == '#')         {
               // Comment - ignore this line
               while(character != '\n'){
                 character = settingsFile.read();
               };
      } else if(isalnum(character))      {  // Add a character to the description
        description.concat(character);
      } else if(character =='=')         {  // start checking the value for possible results
      // First going to trim out all trailing white spaces
      do {
        character = settingsFile.read();
      } while(character == ' ');
      
      
        if(description == "brightness") {
          value = "";
          while(character != '\n') {
            if(isdigit(character)) {
              value.concat(character);
            } else if(character != '\n') {
              // Use of invalid values
              valid = false;
            }
            character = settingsFile.read();            
          };
          if (valid) { 
            // Convert string to array of chars
            char charBuf[value.length()+1];
            value.toCharArray(charBuf,value.length()+1);
            // Convert chars to integer
            settings.brightness = atoi(charBuf);
          } else {
            // revert to default value for invalid entry in settings
            settings.brightness = 200;
          }
          
          
        } else if(description == "title0") {
          
           value = "";
           do {
             value.concat(character);
             character = settingsFile.read();
           } while(character != '\n');
           
fileTitles[0] = value;

        
        } 
        else if(description == "title1") {
           value = "";
           do {
             value.concat(character);
             character = settingsFile.read();
           } while(character != '\n');
           fileTitles[1] = value;
        }
        else if(description == "title2") {
           value = "";
           do {
             value.concat(character);
             character = settingsFile.read();
           } while(character != '\n');
                     fileTitles[2] = value;

        }
        else if(description == "title3") {
           value = "";
           do {
             value.concat(character);
             character = settingsFile.read();
           } while(character != '\n');
           fileTitles[3] = value;
        
        }
        else if(description == "title4") {
           value = "";
           do {
             value.concat(character);
             character = settingsFile.read();
           } while(character != '\n');
            fileTitles[4] = value;
           
        
        }
        else if(description == "title5") {
           value = "";
           do {
             value.concat(character);
             character = settingsFile.read();
           } while(character != '\n');
                         fileTitles[5] = value;
        
        }
        else if(description == "title6") {
           value = "";
           do {
             value.concat(character);
             character = settingsFile.read();
           } while(character != '\n');
                         fileTitles[6] = value;  
        }
        
        else if(description == "title7") {
           value = "";
           do {
             value.concat(character);
             character = settingsFile.read();
           } while(character != '\n');
                        fileTitles[7] = value;
           
        
        }
        
        
        
        else { // unknown parameter
          while(character != '\n')
          character = settingsFile.read();
        }
        description = "";
      } else {
        // Ignore this character (could be space, tab, newline, carriage return or something else)
      }
    
    }
    // close the file:
    settingsFile.close();
}
