#include <SuperST7032.h>

// Create an instance of SuperST7032, with the I2C address
SuperST7032 lcd(0x3E);

void setup()
{
  lcd.begin();

  // Turn on cursor and cursor blink
  lcd.cursor();
  lcd.blink();

  // Set cursor to the 4th position in the top row
  lcd.setCursor(4, 0);

  delay(1000);

  // Print characters from right to left
  lcd.rightToLeft();
  lcd.print("Hey!");

  // Set cursor to the 4th position in the bottom row
  lcd.setCursor(3, 1);

  delay(1000);

  // Print characters from left to right
  lcd.leftToRight();
  lcd.print("Hey!");

}

void loop()
{
}
