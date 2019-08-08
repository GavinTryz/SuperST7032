# SuperST7032
Arduino library built to communicate with any LCD using the ST7032 LCD controller (such as AQM0802A-RN-GBW, ERC1602FYG-4, and more.) Includes standard LCD functionality in addition to extra features not typically found in most LCD libraries.
Code by Gavin Tryzbiak

## Methods
`SuperST7032` and `SuperST7032(uint8_t addressInput)` - Constructors. Either specify a particular I2C address, or have it default to 0x3E

`begin()` - Initializes the LCD
`clear()` - Clears the LCD
`print(char c)`, `print(String str)`, and more - Prints data to the LCD. Inherited from the print Class. Supports things such as printing in BIN/HEX, character arrays, and other features from the Print class
`write(byte x)` - Writes a single byte to the LCD. Required for printing custom characters
`scan(unint16_t stepTime, uint16_t stopTime, bool rollBack)` and `scan()` - Scans through the display memory. `stepTime` is the number of milliseconds it stays put before moving again. `stopTime` is how long it stays at the left and right edge. If `rollBack` is true, it will scan back to the start when finished. `scan()` simply runs `scan(250, 750, true)`
`home()` - Sets cursor to top left display register and brings top left display register into view
`setCursor(uint8_t x, uint8_t y)` - Sets cursor to the top left display register
`cursor(bool x)`, `cursor()`, and `noCursor()` - Turns cursor on or off
`blink(bool x)`, `blink()`, and `noBlink()` - Turns cursor blinking on or off
`display(bool x)`, `display()`, and `noDisplay()` - Turns display on or off (but maintains data)
`scrollDisplayLeft()` and `scrollDisplayLeft(uint16_t count)` - Moves all TEXT to the LEFT once or a specified number of spaces
`scrollDisplayRight()` and `scrollDisplayRight(uint16_t count)` - Moves all TEXT to the RIGHT once or a specified number of spaces
`autoscroll(bool x)`, `autoscroll()`, and `noAutoscroll()` - Turns autoscroll on or off (Keeps the cursor on the same spot of the display as it prints. Use setCursor() first)
`leftToRight()` - Sets the print/write direction from left to right (default)
`rightToLeft()` - Sets the print/write direction from right to left
`createChar(uint8_t location, uint8_t charMap[])` - Creates and saves a custom 5x8 character at the "location" 0-7. Use "write([location]);" to print. Sets cursor to 0, 0 afterwards
`contrast(uint8_t x)` - Sets contrast to a specified value from 0 to 63
`doubleLine(bool x)`, `doubleLine()`, and `singleLine()` - Sets LCD to use double-line (default) or single-line mode (large font MUST be off to use double-line) (returns true if successful)
`largeFont(bool x)`, `largeFont()`, and `normalFont()` - Sets LCD to use double-height or single-height (default) font (double-line MUST be off to use double-height font) (returns true if successful)
