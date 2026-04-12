#include <Arduino.h>
#include <TFT_eSPI.h>
#include "face.h"

void desenharBoca(TFT_eSPI &tft,int cx, int cy, int r) {
  for (int ang = 0; ang <= 180; ang++) {
    float rad = ang * 3.1416 / 180.0;

    int x = cx + r * cos(rad);
    int y = cy + r * sin(rad);

    tft.drawPixel(x, y, TFT_GREEN);
  }
}

void desenharOlhos(TFT_eSPI &tft){
  tft.drawLine(60,10,60,50,TFT_GREEN);
  tft.drawLine(100,10,100,50,TFT_GREEN);
}

void desenharRostoAgradavel(TFT_eSPI &tft){
  desenharOlhos(tft);
  desenharBoca(tft,80,70,30);
  tft.setTextDatum(MC_DATUM);
  tft.setTextColor(TFT_GREEN);
  tft.setTextFont(2);
  tft.setTextSize(1);
  tft.drawString("Temperatura Agradavel", 80, 115);
};