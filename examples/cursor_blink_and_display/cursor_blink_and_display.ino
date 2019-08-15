#include <SuperST7032.h>

// Create an instance of SuperST7032, with the I2C address
SuperST7032 lcd(0x3E);

void setup()
{
  // Print "A"
  lcd.begin();
  lcd.print('A');

  // Turn on cursor, then print "B"
  lcd.cursor();
  delay(1000);
  lcd.print('B');

  // Turn on cursor blink, then print "C"
  lcd.blink();
  delay(1000);
  lcd.print('C');

  // Turn off cursor blink, then print "D"
  lcd.noBlink();
  delay(1000);
  lcd.print('D');

  // Turn off cursor, then print "E"
  lcd.noCursor();
  delay(1000);
  lcd.print('E');
}

void loop()
{
  // Flash display on and off
  
  // Turn off display
  delay(500);
  lcd.noDisplay();

  // Turn on display
  delay(500);
  lcd.display();
}
