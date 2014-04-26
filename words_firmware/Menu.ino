byte menuIndex = 0;
byte oldMenuIndex = 0;

void showMenu() {

  if (menuIndex != oldMenuIndex) {
    lcd.setCursor(0,1);
    lcd.print(fileTitles[menuIndex]);
  }
  
  byte pressedBtn = getPressedBtn();
  
  if (pressedBtn == btnEnter) {
    selectedFile = menuIndex;
    return;
  }
  
  if (pressedBtn == btnRight) {
    menuIndex--; if(menuIndex <= 0) menuIndex = NUMBER_OF_FILES;
    return;
  }
  
  if (pressedBtn == btnLeft) {
    menuIndex++; if (menuIndex >= NUMBER_OF_FILES) menuIndex = 0;
    return;
  }
  
  if (Serial.available()) {
   byte input = Serial.read();
  switch (input) {
   case 'a': menuIndex--; if(menuIndex <= 0) menuIndex = NUMBER_OF_FILES; break;
   case 'd': menuIndex++; if (menuIndex >= NUMBER_OF_FILES) menuIndex = 0;break;
   case 's': selectedFile = menuIndex; break;
  }
 
 Serial.println(fileTitles[menuIndex]);
  
  } else {
    delay(100);
  }
}
