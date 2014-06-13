/**
 * BoxOfWords firmware
 *
 * Main menu related functions
 *
 * Licence: MIT
 * Author: Ando Roots <david@sqroot.eu> 2014
 * Web: http://wp.me/p1OdID-114
 **/
 
/**
 * Display the main menu - select which wordfile to open
**/
void showMenu() {

  // Refresh the menu?
  if (refreshMenuDisplay) {
    showFileName(menuIndex);
    refreshMenuDisplay = false;
    delay(50);
  }


  // Handle user input
  byte pressedBtn = getPressedBtn();

  switch (pressedBtn) {
  case btnEnter: // Select the current wordfile
    selectedFile = menuIndex;  
    break;
  case btnRight: // Display the next wordfile name
    refreshMenuDisplay = true;
    menuIndex++;
    if (menuIndex == numberOfFiles) {
      menuIndex = 0;    
    }
    break;
  case btnLeft: // Display the previous wordfile name
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

/**
 * Display the menu: str on the 1st row, wordfile name on the 2nd
**/
void showFileName(byte fileIndex) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Choose a list:");
  lcd.setCursor(0, 1);
  lcd.print(fileTitles[menuIndex]);
}

