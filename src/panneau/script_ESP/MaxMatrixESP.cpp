#include <SPI.h>
#include "MaxMatrixESP.h"

/* PUBLIC */

MaxMatrixESP::MaxMatrixESP(byte sizeX, byte sizeY, byte CS, byte intensity) {
    matrixX = sizeX;
    matrixY = sizeY;
    matrixCS = CS;
    matrixIntensity = intensity;
    matrixNum = matrixX*matrixY;
    matrixBuffer = new byte[8*matrixNum];
}

void MaxMatrixESP::init(uint32_t clock) {
	pinMode(matrixCS, OUTPUT);
	SPI.begin();
	SPI.setDataMode(SPI_MODE0);
	SPI.setClockDivider(SPI_CLOCK_DIV2);

	sendByteAll(MAX7219_REG_DECODEMODE, 0);
	sendByteAll(MAX7219_REG_INTENSITY, matrixIntensity);
	sendByteAll(MAX7219_REG_SCANLIMIT, 7);
	sendByteAll(MAX7219_REG_SHUTDOWN, 1);
	sendByteAll(MAX7219_REG_DISPLAYTEST, 0);

	sendByteAll(MAX7219_REG_DIGIT0, 0);
	sendByteAll(MAX7219_REG_DIGIT1, 0);
	sendByteAll(MAX7219_REG_DIGIT2, 0);
	sendByteAll(MAX7219_REG_DIGIT3, 0);
	sendByteAll(MAX7219_REG_DIGIT4, 0);
	sendByteAll(MAX7219_REG_DIGIT5, 0);
	sendByteAll(MAX7219_REG_DIGIT6, 0);
	sendByteAll(MAX7219_REG_DIGIT7, 0);

	for (int row = 0; row < 8*matrixNum; row++) {
		matrixBuffer[row] = (byte)0;
	}

}

void MaxMatrixESP::sendByteAll(byte reg, byte data) {
	digitalWrite(matrixCS, LOW);
	for (byte device = 0; device < matrixNum; device++) {
		SPI.transfer(reg);
		SPI.transfer(data);
	}
	digitalWrite(matrixCS, HIGH);
}

void MaxMatrixESP::setPoint(int x, int y, bool value) {
  if ((x <=matrixX*8) && (x >0) && (y <=matrixY*8) && (y >0))
	  bitWrite(matrixBuffer[matrixX*(y-1)+((x-1)/8)], (x-1)%8, value);
}


void MaxMatrixESP::setRectangle(int x, int y, int sizeX, int sizeY, int value) {
  for (int posX = x; posX < x+sizeX; posX++) {
    for (int posY = y; posY < y+sizeY; posY++) {
      setPoint(posX, posY, value);
    }
  }
}


void MaxMatrixESP::setSquare(int x, int y, int size, int value) {
  setRectangle(x,y,size,size,value);
}


void MaxMatrixESP::setHorizontalLine(int x, int y, int size, int value) {
  setRectangle(x,y,size,1,value);
}


void MaxMatrixESP::setVerticalLine(int x, int y, int size, int value) {
  setRectangle(x,y,1,size,value);
}

void MaxMatrixESP::set1ByteDrawing(const byte d[8], int x, int y, bool value){
  for (int i=0;i<8;i++){
    for (int j=0;j< 8;j++){
      if (d[i] & (1<<j))
        setPoint(x+i, y+j, value);
    }
  }
}

void MaxMatrixESP::set2ByteDrawing(const int d[16], int x, int y, bool value){
  for (int i=0;i<16;i++){
    for (int j=0;j< 16;j++){
      if (d[i] & (1<<j))
        setPoint(x+i, y+j, value);
    }
  }
}


void MaxMatrixESP::set4ByteDrawing(const long int d[32], int x, int y, bool value){
  for (int i=0;i<32;i++){
    for (int j=0;j< 32;j++){
      if (d[i] & (1<<j))
        setPoint(x+i, y+j, value);
    }
  }
}



void MaxMatrixESP::setLetter(char c, int nbByte,int x,int y,bool value){
  switch (nbByte){
    case 1: 
      set1ByteDrawing(_1ByteLetter_[c-'a'],x,y,value);
    break;
    case 2:
      set2ByteDrawing(_2ByteLetter_[c-'a'],x,y,value);
    break;
    case 4:
      set4ByteDrawing(_4ByteLetter_[c-'a'],x,y,value);
    break;
    default :
      set1ByteDrawing(_1ByteLetter_[c-'a'],x,y,value);
    break; 
  }
}


void MaxMatrixESP::setString(String str, int nbByte,int x,int y,bool value){
   for (int i =0; i< str.length();i++){
      switch (nbByte){
        case 1: 
          setLetter(str[i],1,x+i*nbByte*8,y,value);
        break;
        case 2 :
          setLetter(str[i],2,x+i*nbByte*8,y,value);
        break; 
        case 4:
          setLetter(str[i],4,x+i*nbByte*8,y,value);
        break;
        default :
          setLetter(str[i],1,x+i*nbByte*8,y,value);
        break; 
      }
  }
}

void MaxMatrixESP::setWord(const char *mot, int len, int nbByte,int x,int y,bool value){
   for (int i =0; i< len;i++){
      switch (nbByte){
        case 1: 
          set1ByteDrawing(_1ByteLetter_[mot[i]-'a'],x+i*nbByte*8,y,value);
        break;
        default :
          set2ByteDrawing(_2ByteLetter_[mot[i]-'a'],x+i*nbByte*8,y,value);
        break; 
      }
  }
}

void MaxMatrixESP::render() {
	for (byte row = 1; row < 9; row++) {
		digitalWrite(matrixCS, LOW);
		for (byte device = matrixNum-1; (device >= 0 && device < matrixNum); device--) {
			SPI.transfer(9-row);
			SPI.transfer(matrixBuffer[(device%matrixX)+((device/matrixX)*8*matrixX)+((row-1)*matrixX)]);
		}
		digitalWrite(matrixCS, HIGH);
	}
}


/*byte MaxMatrixESP::getByte(int num) {
	return matrixBuffer[num];
}*/
