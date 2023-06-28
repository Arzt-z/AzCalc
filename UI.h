#ifndef UI_H
#define UI_H
#include <TFT_eSPI.h> 
#include <SPI.h>

class UI {
public:
  UI(TFT_eSPI& tft, int screenWidth, int screenHeight);
  void begin();
  void drawBox(int x, int y, int width, int height, const char* label);
  void drawBox(int x, int y, int width, int height, int r, int g, int b);
  void drawBorder(int x, int y, int width, int height, int borderSize, int r, int g, int b);
  String updateBuffer(String buffer, String mykey);
  void cleanBufferBox();
private:
  TFT_eSPI& _tft;
  int _screenWidth;
  int _screenHeight;
};

#endif