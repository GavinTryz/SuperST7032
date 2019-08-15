#include <SuperST7032.h>

// Create an instance of SuperST7032, with the I2C address
SuperST7032 lcd(0x3E);

void setup()
{
  lcd.begin();

  // Turn on cursor and cursor blink
  lcd.cursor();
  lcd.blink();

  // Set cursor to the 6th position in the top row
  lcd.setCursor(5, 0);

  // Turn on autoscroll
  lcd.autoscroll();

  // Print letters one by one to the display
  for(char c = 'A'; c <= 'Z'; c++)
  {
    lcd.print(c);
    delay(250);
  }

  delay(1000);
  
  // Scan through the entirety of the display memory
  lcd.scan();
}

void loop()
{
}
