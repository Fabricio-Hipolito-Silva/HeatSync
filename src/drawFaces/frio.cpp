#include <Arduino.h>
#include <TFT_eSPI.h>
#include "face.h"

int cx = 80;
int cy = 54;

void desenharBoca(TFT_eSPI &tft, int cx, int cy, int r) {
  for (int ang = 0; ang <= 180; ang++) {
    float rad = ang * 3.1416 / 180.0;

    int x = cx + r * cos(rad);
    int y = cy - r * sin(rad);

    tft.drawPixel(x, y, TFT_BLUE);
  }
}

void desenharOlhos(TFT_eSPI &tft){
//Vo mentir não, pedi pro chatgpt fazer essa parte porque tava com preguica de fazer o W.
  //olho esquerdo
  tft.drawLine(cx - 50, cy - 20, cx - 40, cy, TFT_BLUE);      
  tft.drawLine(cx - 40, cy,      cx - 30, cy - 20, TFT_BLUE);  
  tft.drawLine(cx - 30, cy - 20, cx - 20, cy, TFT_BLUE);      
  tft.drawLine(cx - 20, cy,      cx - 10, cy - 20, TFT_BLUE); 

  //olho direito
  tft.drawLine(cx + 10, cy - 20, cx + 20, cy, TFT_BLUE);       
  tft.drawLine(cx + 20, cy,      cx + 30, cy - 20, TFT_BLUE);  
  tft.drawLine(cx + 30, cy - 20, cx + 40, cy, TFT_BLUE);       
  tft.drawLine(cx + 40, cy,      cx + 50, cy - 20, TFT_BLUE);  

};

void desenharRostoFrio(TFT_eSPI &tft){
desenharBoca(tft, cx, cy +40, 30);
  tft.setTextDatum(MC_DATUM);
  tft.setTextColor(TFT_BLUE);
  tft.setTextFont(2);
  tft.setTextSize(1);
  tft.drawString("Ta muito frio", 80, 110);
}