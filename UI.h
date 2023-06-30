#ifndef UI_H
#define UI_H
//#include "TFT_eSPI_Controls.h"
#include <TFT_eSPI.h> 
#include <SPI.h>

class UI {
public:
  UI(TFT_eSPI& tft, int screenWidth, int screenHeight);
  void begin();
  void drawBox(int x, int y, int width, int height, const char* label);
  void drawBorder(int x, int y, int width, int height, int r, int g, int b);
  void drawRoundBorder(int x, int y, int width, int height, int r, int g, int b);
  void drawBufferBox( int r, int g, int b);
  void drawResultBox( int r, int g, int b);
  void drawRoundBorderInside(int x, int y, int width, int height, int r, int g, int b);
  String updateBuffer(String buffer, String mykey);
  void cleanBufferBox();
  void cleanResultBox();
  void printResult(String buffer);
  void drawMainBox(int x, int y, int width, int height, int r, int g, int b);
  //void Graph(Adafruit_HX8357 &d, double x, double y, double gx, double gy, double w, double h, double xlo, double xhi, double xinc, double ylo, double yhi, double yinc, String title, String xlabel, String ylabel, unsigned int gcolor, unsigned int acolor, unsigned int pcolor, unsigned int tcolor, unsigned int bcolor, boolean &redraw);
  void Graph( double x, double y, double gx, double gy, double w, double h, double xlo, double xhi, double xinc, double ylo, double yhi, double yinc, String title, String xlabel, String ylabel, unsigned int gcolor, unsigned int acolor, unsigned int pcolor, unsigned int tcolor, unsigned int bcolor, boolean &redraw);
  void SIN(double num1,double num2);

private:
  TFT_eSPI& _tft;
  int _screenWidth;
  int _screenHeight;
};

#endif