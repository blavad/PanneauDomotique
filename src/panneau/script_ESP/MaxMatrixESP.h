#include <Arduino.h>
#include "drawing.h"

// MAX7219 registers..
#define MAX7219_REG_DIGIT0       0x1
#define MAX7219_REG_DIGIT1       0x2
#define MAX7219_REG_DIGIT2       0x3
#define MAX7219_REG_DIGIT3       0x4
#define MAX7219_REG_DIGIT4       0x5
#define MAX7219_REG_DIGIT5       0x6
#define MAX7219_REG_DIGIT6       0x7
#define MAX7219_REG_DIGIT7       0x8

#define MAX7219_REG_NOOP         0x0
#define MAX7219_REG_DECODEMODE   0x9
#define MAX7219_REG_INTENSITY    0xA
#define MAX7219_REG_SCANLIMIT    0xB
#define MAX7219_REG_SHUTDOWN     0xC
#define MAX7219_REG_DISPLAYTEST  0xF

class MaxMatrixESP {
    
public:

    /**
     * Constructor.
     * sizeX: X size of the array
     * sizeY: Y size of the array
     * CS: CS pin connected to your ESP8266
     */
    MaxMatrixESP(byte sizeX, byte sizeY, byte CS, byte intensity);

    /**
     * Initialize the SPI interface.
     * clock: clock speed in Hz
     */
    void init(uint32_t clock);

    /**
     * Send the same byte to all the devices.
     * reg: MAX7219 register
     * data: Byte to be sent
     */
    void sendByteAll(byte reg, byte data);

    /**
     * Set the value (0 or 1) at the specified coordinates
     * x: X coordinate
     * y: Y coordinate
     * value: The value for this point
     */
    void setPoint(int x, int y, bool value);

    
    /**
     * Set a rectangle at the specified coordinates
     * x: X coordinate 
     * y: Y coordinate
     * sizeX : The X size of the rectangle
     * sizeY : The Y size of the rectangle
     * value: The value for this rectangle
     */
    void setRectangle(int x, int y, int sizeX, int sizeY, int value);

  
    /**
     * Set a square at the specified coordinates
     * x: X coordinate
     * y: Y coordinate
     * size: The size of the square
     * value: The value for this square
     */
    void setSquare(int x, int y, int size, int value);


    /**
     * Set a horizontal line at the specified coordinates
     * x: X coordinate
     * y: Y coordinate
     * size: The size of the line
     * value: The value for this line
     */
    void setHorizontalLine(int x, int y, int size, int value);

    /**
     * Set a vertical line at the specified coordinates
     * x: X coordinate
     * y: Y coordinate
     * size: The size of the line
     * value: The value for this line
     */
    void setVerticalLine(int x, int y, int size, int value);


    /**
     * Set a one byte drawing at the specified coordinates
     * d: the drawing (8x8 pixels)
     * x: X coordinate
     * y: Y coordinate
     * value: The value for this drawing
     */
    void set1ByteDrawing(const byte d[8], int x, int y, bool value);


      /**
     * Set a two byte drawing at the specified coordinates
     * d: the drawing (16x16 pixels)
     * x: X coordinate
     * y: Y coordinate
     * value: The value for this drawing
     */
    void set2ByteDrawing(const int d[16], int x, int y, bool value);
  
  
    /**
     * Set a four byte drawing at the specified coordinates
     * d: the drawing (32x32 pixels)
     * x: X coordinate
     * y: Y coordinate
     * value: The value for this drawing
     */
    void set4ByteDrawing(const long int d[32], int x, int y, bool value);


    /**
     * Set letter at the specified coordinates
     * c: The letter
     * nbByte: The size of the letter; 1,2 or 4 Byte(s)
     * x: X coordinate
     * y: Y coordinate
     * value: The value for this letter
     */
    void setLetter(char c, int nbByte,int x,int y,bool value);


    /**
     * Set string at the specified coordinates
     * str: The string
     * nbByte: The size of the string ; 1,2 or 4 Byte(s)
     * x: X coordinate
     * y: Y coordinate
     * value: The value for this letter
     */
    void setString(String str, int nbByte,int x,int y,bool value);
 

    /**
     * Draw the buffer on the matrix array
     */
    void render();
    
private:
    byte* matrixBuffer;
    byte matrixNum = 1;
    byte matrixCS = 0;
    byte matrixX = 1;
    byte matrixY = 1;
    byte matrixIntensity = 1;
};
