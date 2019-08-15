#include <SuperST7032.h>

// Create an instance of SuperST7032, with the I2C address
SuperST7032 lcd(0x3E);

void setup()
{
  lcd.begin();

  // Print some text
  lcd.print("Hi world");
}

void loop()
{
  // Cycle through various contrast settings
  // 25-35 is typically the best choice. Can be set to anything from 0 to 63

  for(int i = 0; i < 64; i++)
  {
    lcd.contrast(i);
    delay(75);
  }

  for(int i = 0; i < 64; i++)
  {
    lcd.contrast(63 - i);
    delay(75);
  }
}
