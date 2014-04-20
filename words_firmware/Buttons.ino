void handleButtons() {
 uint8_t buttons[] = {A5, A4, A3, A2};
 
 
 for(int c = 0; c < 4; c++) {
  int buttonState = digitalRead(buttons[c]); 
  
  String msg ="";
  if (buttonState == LOW) {
  msg = (String)c+" LOW";
  } else {
   msg = (String)c+" HIGH"; 
  }
  
  lcd.clear();
 delay(40);
 lcd.print(msg);
delay(1000);
 
 }
}
