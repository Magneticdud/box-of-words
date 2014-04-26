
void showMenu() {

          Serial.print("Current: "); Serial.println(menuIndex);
          
  if (refreshMenuDisplay) {
    Serial.println("Refreshing display");
    showFileName(menuIndex);
    refreshMenuDisplay = false;
    delay(50);
  }
  
  byte pressedBtn = getPressedBtn();
  
  switch (pressedBtn) {
    case btnEnter:
        selectedFile = menuIndex;  
    break;
    case btnRight:
      refreshMenuDisplay = true;
      menuIndex++;
      if (menuIndex == numberOfFiles) {
        menuIndex = 0;    
      }
    break;
    case btnLeft:
      refreshMenuDisplay = true;
      if(menuIndex == 0) {
        menuIndex = numberOfFiles - 1;    
      } else {
        menuIndex--;
      }
    break;
  }
  
  if (pressedBtn != 0) {
    delay(100);
    return;
  }
  
  
  
  if (Serial.available()) {
   byte input = Serial.read();
  switch (input) {
   case 'a': menuIndex--; if(menuIndex <= 0) menuIndex = numberOfFiles; break;
   case 'd': menuIndex++; if (menuIndex >= numberOfFiles) menuIndex = 0;break;
   case 's': selectedFile = menuIndex; break;
  }
 
 Serial.println(fileTitles[menuIndex]);
  
  }
    delay(100);
  
}

void showFileName(byte fileIndex) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Choose a list:");
  lcd.setCursor(0, 1);
  lcd.print(fileTitles[menuIndex]);
}
