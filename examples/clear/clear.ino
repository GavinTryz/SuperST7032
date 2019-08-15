#include <SuperST7032.h>

// Create an instance of SuperST7032, with the I2C address
SuperST7032 lcd(0x3E);

void setup()
{
  lcd.begin();

  // Print characters to the display
  lcd.print("Hi");

  delay(1000);

  // Clear display
  lcd.clear();

  delay(1000);

  // Print characters to the display
  // Text is placed at the top left, because clearing the display also sets the cursor to home
  lcd.print("Hello");
}

void loop()
{
}
