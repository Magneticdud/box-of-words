
void showMenu() {

  if (refreshMenuDisplay) {
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
    } 
    else {
      menuIndex--;
    }
    break;
  }

  if (pressedBtn != 0) {
    delay(100);
    return;
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

