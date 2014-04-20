#include <MenuBackend.h>



MenuBackend menu = MenuBackend(menuUseEvent, menuChangeEvent);

MenuItem fileItems[NUMBER_OF_FILES] = {
  MenuItem(fileTitles[0], '0'),
  MenuItem(fileTitles[1], '1'),
  MenuItem(fileTitles[2], '2'),
  MenuItem(fileTitles[3], '3'),
  MenuItem(fileTitles[4], '4'),
  MenuItem(fileTitles[5], '5'),
  MenuItem(fileTitles[6], '6'),
  MenuItem(fileTitles[7], '7'),
};

void buildMenu() {
  


  menu.getRoot().add(fileItems[0]);
  fileItems[0].addRight(fileItems[1]);
  fileItems[1].addRight(fileItems[2]);
  fileItems[2].addRight(fileItems[3]);
  fileItems[3].addRight(fileItems[0]);
  
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
