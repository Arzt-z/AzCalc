#include "UI.h"
  int bSize = 5;
  int bx =5;
  int by=5;
  int bheight =35;
UI::UI(TFT_eSPI& tft, int screenWidth, int screenHeight) : _tft(tft), _screenWidth(screenWidth), _screenHeight(screenHeight) {
}

void UI::begin() {
  // Initialize the TFT display
  _tft.begin();
  _tft.setRotation(3);
  _tft.init();
  _tft.invertDisplay(1);
  _tft.fillScreen(TFT_BLACK);
  _tft.setTextColor(TFT_WHITE);

  drawBorder(bx, by, _screenWidth-10, bheight, bSize, 10,15,20);
}

String UI::updateBuffer(String buffer, String mykey) {
  if (!mykey.isEmpty()) {
    _tft.setTextColor(_tft.color565(0, 0, 0));
    _tft.setTextSize(3);
    if (mykey == "<DEL>") {
      buffer = buffer.substring(0, buffer.length() - 1);
      cleanBufferBox();
    } else if (mykey == "<AC>") {
      buffer = "";
      cleanBufferBox();
    }else{
      buffer = buffer + mykey;
    }
    if (buffer.length() >= 16) {
      _tft.drawString(buffer.substring(0, 16), 12, 12);
    } else {
      _tft.drawString(buffer, 12, 12);
    }
  }
  return buffer;
}

void UI::cleanBufferBox(){
  drawBox(bx+(bSize),by+(bSize),(_screenWidth-10)-bSize*2,bheight-bSize*2,255,255,255);
}

void UI::drawBox(int x, int y, int width, int height, const char* label) {
  // Draw a button on the display
  //_tft.drawRect(x, y, width, height, TFT_WHITE);
  _tft.fillRect(x, y, width, height, _tft.color565(0,0,31));
  _tft.setTextColor(_tft.color565(0,0,31));
  _tft.setTextSize(2);
  _tft.setCursor(x + 10, y + height / 2 - 10);
  _tft.println(label);
}

void UI::drawBox(int x, int y, int width, int height, int r, int g, int b) {
  // Draw a box on the display
  //_tft.drawRect(x, y, width, height, TFT_WHITE);
  _tft.fillRect(x, y, width, height, _tft.color565(r,g,b));
}


void UI::drawBorder(int x, int y, int width, int height, int borderSize, int r, int g, int b) {
  drawBox(x,y,width,height,r,g,b);
  drawBox(x+(borderSize/2),y+(borderSize/2),width-borderSize,height-borderSize,r*0.7,g*0.7,b*0.7);
  drawBox(x+(borderSize),y+(borderSize),width-borderSize*2,height-borderSize*2,255,255,255);
}

