#include <SuperST7032.h>

// Create an instance of SuperST7032, with the I2C address
SuperST7032 lcd(0x3E);

// Create a first custom 5x8 character map
byte myFirstChar[8] = {
  0b00000,
  0b00100,
  0b01010,
  0b10001,
  0b01010,
  0b00100,
  0b00000,
  0b00000
};

// The first custom character should look like this diamond
/*
 * ░░░░░
 * ░░█░░
 * ░█░█░
 * █░░░█
 * ░█░█░
 * ░░█░░
 * ░░░░░
 * ░░░░░
 */

// Create a second custom 5x8 character map
byte mySecondChar[8] = {
  0b00000,
  0b11111,
  0b10001,
  0b10001,
  0b10001,
  0b11111,
  0b00000,
  0b00000
};

// The second custom character should look like this square
/*
 * ░░░░░
 * █████
 * █░░░█
 * █░░░█
 * █░░░█
 * █████
 * ░░░░░
 * ░░░░░
 */

void setup()
{
  lcd.begin();

  // Assign the first custom character map a number 0-7
  lcd.createChar(0, myFirstChar);

  // Assign the second custom character map a number 0-7
  lcd.createChar(1, mySecondChar);

  // Print the first custom character (diamond) (you must use write() not print() )
  lcd.write(0);

  // Print the second custom character (square) (you must use write() not print() )
  lcd.write(1);
}

void loop()
{
}
