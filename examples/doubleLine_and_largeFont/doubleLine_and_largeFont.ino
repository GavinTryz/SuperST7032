#include <SuperST7032.h>

// Create an instance of SuperST7032, with the I2C address
SuperST7032 lcd(0x3E);

void setup()
{
  lcd.begin();
}

void loop()
{
  // Large font & single line
  lcd.singleLine(); // Single Line must be set before using Large Font
  lcd.largeFont();
  lcd.clear();
  lcd.home();
  lcd.print("BIG TEXT");

  delay(2000);

  // Normal font & double line
  lcd.normalFont(); // Normal Font must be set before using Double Line
  lcd.doubleLine();
  lcd.clear();
  lcd.home();
  lcd.print("Normal");
  lcd.setCursor(4, 1);
  lcd.print("Font");

  delay(2000);
}
