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

  drawBufferBox(bx, by, _screenWidth-10, bheight, 6, bSize, 20,20,255);
  drawResultBox(bx, _screenHeight-(by+bheight), _screenWidth-10, bheight, 6,bSize, 20,20,255);
}

void UI::cleanBufferBox(){
  drawRoundBorderInside(bx, by, _screenWidth-10, bheight, 6, bSize, 255,255,255);
}

void UI::drawBufferBox(int x, int y, int width, int height,int radius, int borderSize, int r, int g, int b) {
  drawRoundBorder(bx, by, _screenWidth-10, bheight, 6,bSize, 20,20,255);
  drawRoundBorderInside(bx, by, _screenWidth-10, bheight, 6,bSize, 255,255,255);
}

void UI::drawResultBox(int x, int y, int width, int height,int radius, int borderSize, int r, int g, int b) {
  drawRoundBorder(bx, _screenHeight-(by+bheight), _screenWidth-10, bheight, 6,bSize, 20,20,255);
  drawRoundBorderInside(bx, _screenHeight-(by+bheight), _screenWidth-10, bheight, 6,bSize, 10,10,10);
}

void UI::cleanResultBox(){
  drawRoundBorderInside(bx, _screenHeight-(by+bheight), _screenWidth-10, bheight, 6,bSize, 10,10,10);
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

void UI::printResult(String result){
  _tft.setTextColor(_tft.color565(230, 230, 255));
  _tft.setTextSize(3);
  drawRoundBorderInside(bx, _screenHeight-(by+bheight), _screenWidth-10, bheight, 6,bSize, 10,10,10);
  _tft.drawString(result, _screenWidth-(result.length()*18+20), _screenHeight-32);
  //ft.drawString(String(te_interp(buffer.c_str(), 0)), 50, 50);
  _tft.setTextColor(_tft.color565(0, 0, 0));
}



void UI::drawBox(int x, int y, int width, int height, const char* label) {
  // Draw a button on the display
  //_tft.drawRect(x, y, width, height, TFT_WHITE);
  _tft.fillRect(x, y, width, height, _tft.color565(0,0,255));
  _tft.setTextColor(_tft.color565(0,0,31));
  _tft.setTextSize(2);
  _tft.setCursor(x + 10, y + height / 2 - 10);
  _tft.println(label);
}

void UI::drawRoundBorder(int x, int y, int width, int height,int radius, int borderSize, int r, int g, int b) {
  _tft.fillRoundRect(x,y,width,height,radius,_tft.color565(r,g,b));
  _tft.fillRoundRect(x+(borderSize/2),y+(borderSize/2),width-borderSize,height-borderSize,radius,_tft.color565(r*0.7,g*0.7,b*0.7));
  _tft.fillRoundRect(x+(borderSize),y+(borderSize),width-borderSize*2,height-borderSize*2,radius,_tft.color565(255,255,255));
}

void UI::drawRoundBorderInside(int x, int y, int width, int height,int radius, int borderSize, int r, int g, int b) {
  _tft.fillRoundRect(x+(borderSize),y+(borderSize),width-borderSize*2,height-borderSize*2,radius,_tft.color565(r,g,b));
}

void UI::drawBorder(int x, int y, int width, int height, int borderSize, int r, int g, int b) {
  _tft.fillRect(x,y,width,height,_tft.color565(r,g,b));
  _tft.fillRect(x+(borderSize/2),y+(borderSize/2),width-borderSize,height-borderSize,_tft.color565(r*0.7,g*0.7,b*0.7));
  _tft.fillRect(x+(borderSize),y+(borderSize),width-borderSize*2,height-borderSize*2,_tft.color565(255,255,255));
}

