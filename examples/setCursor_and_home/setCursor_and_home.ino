#include <SuperST7032.h>

// Create an instance of SuperST7032, with the I2C address
SuperST7032 lcd(0x3E);

void setup()
{
  lcd.begin();

  // Turn on cursor and cursor blink
  lcd.cursor();
  lcd.blink();

  delay(1000);

  // Print "1" to the bottom right of the display
  lcd.setCursor(7, 1);
  delay(1000);
  lcd.print(1);

  delay(1000);

  // Go home (top left of the display) and print "2"
  lcd.home();
  delay(1000);
  lcd.print(2);
}

void loop()
{
}
