/*
 * 
 *  SuperST7032 - v1.0
 *  Code by Gavin Tryzbiak
 *  
 *  Arduino library built to communicate with any LCD using the ST7032 LCD controller (such as AQM0802A-RN-GBW, ERC1602FYG-4, and more.)
 *  Provides base functionality and added features not typically found in most LCD libraries.
 *  
 */

#include "SuperST7032.h"

#define DEFAULT_CONTRAST 25

// Constructors ///////////////////////////////////////////////////////////////////////
SuperST7032::SuperST7032() // No specified address (assume 0x3E)
{
  _slaveAdr = 0x3E;
}

SuperST7032::SuperST7032(uint8_t addressInput) // Specific address
{
  _slaveAdr = addressInput;
}

// Methods inherited from Print class /////////////////////////////////////////////////
size_t SuperST7032::write(uint8_t c)
{
  Wire.beginTransmission(_slaveAdr);
  Wire.write(0b01000000); // CO = 0, RS = 1
  Wire.write(c);
  Wire.endTransmission();
}

// Public Members /////////////////////////////////////////////////////////////////////
void SuperST7032::begin()
{
  Wire.begin();

  // Initialization sequence derived from Sitronix ST7032 datasheet page 33
  command(0b00111000); // "Function set"
  command(0b00111001); // "Function set"
  command(0b00000100); // "EntryMode set (not listed on datasheet)
  command(0b00010100); // "Internal OSC frequency"
  command(0b01110000 | (DEFAULT_CONTRAST & 0xF)); // "Contrast set"
  command(0b01011100 | ((DEFAULT_CONTRAST >> 4) & 0x3)); // "Power/ICON/Contrast control"
  command(0b01101100); // "Follower control"
  delay(200);
  command(0b00111000); // "Function set" Sets interface length, double line, normal font, instruction table 0
  command(0b00001100); // Display On
  command(0b00000001); // Clear Display
  delay(2);

  home();
  clear();
}

void SuperST7032::clear()
{
  command(0b00000001);
}

void SuperST7032::scan(uint16_t stepTime, uint16_t stopTime, bool rollBack)
{
  home();
  setCursor(0, 0);
  delay(stopTime-stepTime);
  for(int i = 0; i < 32; i++)
  {
    delay(stepTime);
    scrollDisplayLeft();
  }
  if(rollBack)
  {
    delay(stopTime-stepTime);
    for(int i = 0; i < 32; i++)
    {
      delay(stepTime);
      scrollDisplayRight();
    }
  }
}

void SuperST7032::scan()
{
  scan(250, 750, true);
}

void SuperST7032::home()
{
  command(0b00000010);
}

void SuperST7032::setCursor(uint8_t x, uint8_t y)
{
  command(0b10000000 | ((y%2) * 0b01000000 + x));
}

void SuperST7032::cursor(bool x)
{
  setState(0b00000010, x); // Sets bit 1 (cursor on/off) to x
  updateDisplaySettings();
}

void SuperST7032::cursor()
{
  cursor(true);
}

void SuperST7032::noCursor()
{
  cursor(false);
}

void SuperST7032::blink(bool x)
{
  setState(0b00000100, x); // Sets bit 2 (cursor blink on/off) to x
  updateDisplaySettings();
}

void SuperST7032::blink()
{
  blink(true);
}

void SuperST7032::noBlink()
{
  blink(false);
}

void SuperST7032::display(bool x)
{
  setState(0b00000001, x); // Sets bit 0 (display on/off) to x
  updateDisplaySettings();
}

void SuperST7032::display()
{
  display(true);
}

void SuperST7032::noDisplay()
{
  display(false);
}

void SuperST7032::scrollDisplayLeft()
{
  command(0b00011000);
}

void SuperST7032::scrollDisplayLeft(uint16_t count)
{
  for(uint16_t i = 0; i < count; i++)
    scrollDisplayLeft();
}

void SuperST7032::scrollDisplayRight()
{
  command(0b00011100);
}

void SuperST7032::scrollDisplayRight(uint16_t count)
{
  for(uint16_t i = 0; i < count; i++)
    scrollDisplayRight();
}

void SuperST7032::autoscroll(bool x)
{
  setState(0b00010000, x); // Sets bit 4 (autoscroll on/off) to x
  updateWriteSettings();
}

void SuperST7032::autoscroll()
{
  autoscroll(true);
}

void SuperST7032::noAutoscroll()
{
  autoscroll(false);
}

void SuperST7032::leftToRight()
{
  _states = _states | 0b00001000; // Sets bit 3 (write direction) to 1 (left to right)
  updateWriteSettings();
}

void SuperST7032::rightToLeft()
{
  _states = _states & 0b11110111; // Sets bit 3 (write direction) to 0 (right to left)
  updateWriteSettings();
}

void SuperST7032::createChar(uint8_t charAddress, uint8_t charMap[])
{
  if(charAddress > 7) // Verifies you only write to character addresses 0 - 7
    return;
  command(0b01000000 | (charAddress << 3));
  for (byte i = 0; i < 8; i++)
    write(charMap[i]);
  home();
}

void SuperST7032::contrast(uint8_t x)
{
  setState(0b10000000, 1); // Use instruction table 1
  updateFunctionSettings();
  command(0b01110000 | (x & 0xF)); // "Contrast set"
  command(0b01011100 | ((x >> 4) & 0x3)); // "Power/ICON/Contrast control"
  setState(0b10000000, 0); // Back to instruction table 0
  updateFunctionSettings();
}

bool SuperST7032::doubleLine(bool x)
{
  if(x)
    return doubleLine();
  return singleLine();
}

bool SuperST7032::doubleLine()
{
  if(_states >> 6 & 0b00000001) // Verify the font isn't currently large
    return false;
  _states = _states | 0b00100000; // Set bit 5 (line count) to 1 (double)
  updateFunctionSettings();
  return true;
}

bool SuperST7032::singleLine()
{
  _states = _states & 0b11011111;// Set bit 5 (line count) to 0 (single)
  updateFunctionSettings();
  return true;
}

bool SuperST7032::largeFont(bool x)
{
  if(x)
    return largeFont();
  return normalFont();
}

bool SuperST7032::largeFont()
{
  if(_states >> 5 & 0b00000001) // Verify the display isn't currently set to 2-line mode
    return false;
  _states = _states | 0b01000000; // Set bit 6 (font size) to 1 (double height)
  updateFunctionSettings();
  return true;
}

bool SuperST7032::normalFont()
{
  _states = _states & 0b10111111; // Set bit 6 (font size) to 1 (single/normal height)
  updateFunctionSettings();
  return true;
}

// Private Members ////////////////////////////////////////////////////////////////////
void SuperST7032::command(uint8_t cmd)
{
  Wire.beginTransmission(_slaveAdr);
  Wire.write(0b00000000); // CO = 0, RS = 0, Declare that a command is about to be sent
  Wire.write(cmd);
  Wire.endTransmission();
  delay(2); // The slowest instructions can take up to just over 1ms to execute
}

void SuperST7032::setState(uint8_t mask, bool x)
{
  if(x)
    _states = _states | mask;
  else
    _states = _states & ~mask;
}

void SuperST7032::updateDisplaySettings() // Updates "Display ON/OFF" [0 0 0 0 1 D C B] (display, cursor, blink)
{
  command(0b00001000 | (0b00000100 & _states << 2) | (0b00000010 & _states) | (0b00000001 & _states >> 2));
}

void SuperST7032::updateWriteSettings() // Updates "Entry Mode Set" [0 0 0 0 0 1 I/D S] (write direction, autoscroll)
{
  command(0b00000100 | (0b00000010 & _states >> 2) | (0b00000001 & _states >> 4));
}

void SuperST7032::updateFunctionSettings() // Updates "Function Set" [0 0 1 DL N DH 0 IS] (interface length (always high), line count, font size, instruction table set)
{
  command(0b00110000 | (0b00001000 & _states >> 2) | (0b00000100 & _states >> 4) | (0b00000001 & _states >> 7));
}
