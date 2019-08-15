#include <SuperST7032.h>

// Create an instance of SuperST7032, with the I2C address
SuperST7032 lcd(0x3E);

void setup()
{
  lcd.begin();

  // Set cursor to the 3rd position in the top row, and print text
  lcd.setCursor(2, 0);
  lcd.print("Text");

  delay(1000);

  // Shift the text left by one space
  lcd.scrollDisplayLeft();

  delay(1000);

  // Shift the text right by one space
  lcd.scrollDisplayRight();

  delay(1000);

  // Shift the text right by 4 spaces
  lcd.scrollDisplayRight(4);

  delay(1000);

  // Shift the text left by 4 spaces
  lcd.scrollDisplayLeft(4);
}

void loop()
{
}
