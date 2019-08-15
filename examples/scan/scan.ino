#include <SuperST7032.h>

// Create an instance of SuperST7032, with the I2C address
SuperST7032 lcd(0x3E);

void setup()
{
  lcd.begin();

  // Prints characters to the display.
  // Only the first 8 characters will be visible, until scan() scrolls through the registers
  lcd.print("Hello world! This LCD has 40x2 spaces!");
  delay(1000);
}

void loop()
{
  // Scroll through the display
  // Spend 200ms on a character before scrolling to the next
  // Wait 1000ms (1s) at the end and beginning
  // After scrolling to the end, scroll back to the beginning (true)
  lcd.scan(200, 1000, true);
}
