#include <MenuBackend.h>



MenuBackend menu = MenuBackend(menuUseEvent, menuChangeEvent);


void buildMenu() {
  
  char charBuf0[fileTitleStrings[0].length()+1];
  fileTitleStrings[0].toCharArray(charBuf0, fileTitleStrings[0].length()+1);  
  MenuItem miFile0 = MenuItem(charBuf0, '0');

  char charBuf1[fileTitleStrings[1].length()+1];
  fileTitleStrings[1].toCharArray(charBuf1, fileTitleStrings[1].length()+1);  
  MenuItem miFile1 = MenuItem(charBuf1, '1');    

  char charBuf2[fileTitleStrings[2].length()+1];
  fileTitleStrings[2].toCharArray(charBuf2, fileTitleStrings[2].length()+1);  
  MenuItem miFile2 = MenuItem(charBuf2, '2');    


  char charBuf3[fileTitleStrings[3].length()+1];
  fileTitleStrings[3].toCharArray(charBuf3, fileTitleStrings[3].length()+1);  
  MenuItem miFile3 = MenuItem(charBuf3, '3');    

Serial.println(miFile3.getName());

  menu.getRoot().add(miFile0);
  miFile0.addRight(miFile1);
  miFile1.addRight(miFile2);
  miFile2.addRight(miFile3);
  miFile3.addRight(miFile0);
  
  menu.moveDown();
}

void showMenu() {

if (Serial.available()) {
		byte read = Serial.read();
		switch (read) {
			case 'w': menu.moveUp(); break;
			case 's': menu.moveDown(); break;
			case 'd': menu.moveRight(); break;
			case 'a': menu.moveLeft(); break;
			case 'e': menu.use(); break;
		}
	} else {
          delay(100);
        }
  
}


void menuUseEvent(MenuUseEvent used)
{
	Serial.print("Menu use ");
	Serial.println(used.item.getName());
	
        for (byte i = 0; i < NUMBER_OF_FILES; i++) {
          char dig = (char)(((int)'0')+i);

         if (used.item.getShortkey() == dig) {

          selectedFile = i;
          return;
         } 
        }
        Serial.println("Could not find the file");
}


void menuChangeEvent(MenuChangeEvent changed)
{
	
	Serial.println(changed.to.getName());
    //Serial.print("freeMemory()=");
//    Serial.println(freeMemory());

}
