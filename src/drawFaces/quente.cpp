#include <Arduino.h>
#include <TFT_eSPI.h>
#include <face.h>


void desenharRostoQuente(TFT_eSPI &tft){
  tft.drawLine(40, 20, 70, 60, TFT_RED);
  tft.drawLine(120, 20, 90, 60, TFT_RED);
  tft.drawLine(50, 90, 110, 90, TFT_RED);
  tft.setTextDatum(MC_DATUM);
  tft.setTextColor(TFT_RED);
  tft.setTextFont(2);
  tft.setTextSize(1);
  tft.drawString("Ta muito quente", 80, 110);
}