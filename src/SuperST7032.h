/*
 * 
 *  SuperST7032 - v1.0
 *  Code by Gavin Tryzbiak
 *  https://github.com/GavinTryz
 *  
 *  Arduino library built to communicate with any LCD using the ST7032 LCD controller (such as AQM0802A-RN-GBW, ERC1602FYG-4, and more.)
 *  Includes standard LCD functionality in addition to extra features not typically found in most LCD libraries.
 *  
 */

#ifndef SuperST7032_h
#define SuperST7032_h

#include <Arduino.h>
#include <Wire.h>

class SuperST7032 : public Print
{
  public:
    // Constructors
    SuperST7032(); // No specified address (assume 0x3E) //............... Creates an instance of the class, defaulting to the I2C address of 0x3E
    SuperST7032(uint8_t addressInput); // Specific address //............. Creates an instance of the class with a specified I2C address

    // Methods inherited from Print class
    virtual size_t write(uint8_t c); //............................... Writes a single byte to the LCD. Required for printing custom characters

    // Members
    void begin(); //.................................................. Initializes the LCD
    void clear(); //.................................................. Clears the LCD
    void scan(uint16_t stepTime, uint16_t stopTime, bool rollBack); // Scans through the display memory. `stepTime` is the number of milliseconds it stays put before moving again. `stopTime` is how long it stays at the left and right edge. If `rollBack` is true, it will scan back to the start when finished.
    void scan(); //................................................... ^ Same as above, but only runs `scan(250, 750, true)`
    void home(); //................................................... Sets cursor to the top left display register
    void setCursor(uint8_t x, uint8_t y); //.......................... Sets cursor to a specified coordinate
    void cursor(bool x); //........................................... Turns cursor on or off
    void cursor(); //................................................. ^ Same as above
    void noCursor(); //............................................... ^ Same as above
    void blink(bool x); //............................................ Turns cursor blinking on or off
    void blink(); //.................................................. ^ Same as above
    void noBlink(); //................................................ ^ Same as above
    void display(bool x); //.......................................... Turns display on or off (but maintains data)
    void display(); //................................................ ^ Same as above
    void noDisplay(); //.............................................. ^ Same as above
    void scrollDisplayLeft(); //...................................... Moves all TEXT to the LEFT one space
    void scrollDisplayLeft(uint16_t count); //........................ Moves all TEXT to the LEFT a specified number of spaces
    void scrollDisplayRight(); //..................................... Moves all TEXT to the RIGHT one space
    void scrollDisplayRight(uint16_t count); //....................... Moves all TEXT to the RIGHT a specified number of spaces
    void autoscroll(bool x); //....................................... Turns autoscroll on or off (Keeps the cursor on the same spot of the display as it prints. Use setCursor() first)
    void autoscroll(); //............................................. ^ Same as above
    void noAutoscroll(); //........................................... ^ Same as above
    void leftToRight(); //............................................ Sets the print/write direction from left to right (default)
    void rightToLeft(); //............................................ Sets the print/write direction from right to left
    void createChar(uint8_t location, uint8_t charMap[]); //.......... Creates and saves a custom 5x8 character at the "location" 0-7. Use "write([location]);" to print. Sets cursor to 0, 0 afterwards
    void contrast(uint8_t x); //...................................... Sets contrast to a specified value from 0 to 63
    bool doubleLine(bool x); //....................................... Sets LCD to use double-line or single-line mode (default) (large font MUST be off to use double-line) (returns true if successful)
    bool doubleLine(); //............................................. ^ Same as above
    bool singleLine(); //............................................. ^ Same as above
    bool largeFont(bool x); //........................................ Sets LCD to use double-height or single-height (default) font (double-line MUST be off to use double-height font) (returns true if successful)
    bool largeFont(); //.............................................. ^ Same as above
    bool normalFont(); //............................................. (default) ^ Same as above

  private:
    void command(uint8_t cmd);
    void setState(uint8_t mask, bool x);
    void updateDisplaySettings();  //................................. Updates "Display ON/OFF" [0 0 0 0 1 D C B] (display, cursor, blink)
    void updateWriteSettings();  //................................... Updates "Entry Mode Set" [0 0 0 0 0 1 I/D S] (write direction, autoscroll)
    void updateFunctionSettings(); //..................................... Updates "Function Set" [0 0 1 DL N DH 0 IS] (interface length (always high), line count, font size)
    
    uint8_t _slaveAdr;

    // Default states (packed into one byte to save dynamic memory)
    uint8_t _states = 0b10101001;
    /* Bit 0: display on/off
     * Bit 1: cursor on/off
     * Bit 2: cursor blink on/off
     * Bit 3: write direction, 1 = left to right (default), 0 = right to left
     * Bit 4: autoscroll on/off
     * Bit 5: line count, 1 = double line (default), 0 = single line
     * Bit 6: font size, 1 = double height font, 0 = single/normal height font (default)
     * Bit 7: instruction table, 1 = table 1, 0 = table 0 (default)
     */
};

#endif 
