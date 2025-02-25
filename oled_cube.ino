#include <Arduino.h>
#include <U8g2lib.h>
#include "vector.h"

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif


vector vectors[8]; // 8 3D co-ordinates

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
//U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R2, /* reset=*/U8X8_PIN_NONE);

vector vectorA = setVector(18, 18, 0, 0);
vector vectorB = setVector(-18, 18, 0, 0);
vector vectorC = setVector(-18, -18, 0, 0);
vector vectorD = setVector(18, -18, 0, 0);

vector vectorE = setVector(18, 18, 0, 0);
vector vectorF = setVector(-18, 18, 0, 0);
vector vectorG = setVector(-18, -18, 0, 0);
vector vectorH = setVector(18, -18, 0, 0);

#define offset 5

// Screen centre as X, Y coords
#define CX 64
#define CY 32

#define W 128
#define H 64

void setup()
{
  vectors[0]=setVector(2, 3, 0, 0);

  u8g2.begin();
}

void loop()
{
  u8g2.clearBuffer();

  // Redraw grid-lines

  //u8g2.drawLine(0, CY, W, CY);
  //u8g2.drawLine(CX, 0, CX, H);
  
  
  u8g2.drawLine(CX + vectorA.x, CY + vectorA.y, CX + vectorB.x, CY + vectorB.y);
  u8g2.drawLine(CX + vectorB.x, CY + vectorB.y, CX + vectorC.x, CY + vectorC.y);
  u8g2.drawLine(CX + vectorC.x, CY + vectorC.y, CX + vectorD.x, CY + vectorD.y);
  u8g2.drawLine(CX + vectorD.x, CY + vectorD.y, CX + vectorA.x, CY + vectorA.y);

  u8g2.drawLine(CX + vectorE.x+offset, CY + vectorE.y-offset, CX + vectorF.x+offset, CY + vectorF.y-offset);
  u8g2.drawLine(CX + vectorF.x+offset, CY + vectorF.y-offset, CX + vectorG.x+offset, CY + vectorG.y-offset);
  u8g2.drawLine(CX + vectorG.x+offset, CY + vectorG.y-offset, CX + vectorH.x+offset, CY + vectorH.y-offset);
  u8g2.drawLine(CX + vectorH.x+offset, CY + vectorH.y-offset, CX + vectorE.x+offset, CY + vectorE.y-offset);

  u8g2.drawLine(CX + vectorE.x+offset, CY + vectorE.y-offset, CX + vectorA.x, CY + vectorA.y);
  u8g2.drawLine(CX + vectorF.x+offset, CY + vectorF.y-offset, CX + vectorB.x, CY + vectorB.y);
  u8g2.drawLine(CX + vectorG.x+offset, CY + vectorG.y-offset, CX + vectorC.x, CY + vectorC.y);
  u8g2.drawLine(CX + vectorH.x+offset, CY + vectorH.y-offset, CX + vectorD.x, CY + vectorD.y);


  
  rotateVector(&vectorA, 0.3333);
  rotateVector(&vectorB, 0.3333);
  rotateVector(&vectorC, 0.3333);
  rotateVector(&vectorD, 0.3333);
  rotateVector(&vectorE, 0.3333);
  rotateVector(&vectorF, 0.3333);
  rotateVector(&vectorG, 0.3333);
  rotateVector(&vectorH, 0.3333);
   

  u8g2.sendBuffer();
  
  delay(50);
}