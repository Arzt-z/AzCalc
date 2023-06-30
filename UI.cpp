#include "UI.h"
#include <TFT_eSPI.h> 
#include <SPI.h>

  int bSize = 5;
  int bx =5;
  int by=5;
  int bheight =35;
  int radiusbox =6;

double x = 5;  // X position
double y = 40;  // Y position
double w = 320 - 10;  // Width
double h = 240 - 90;  // Height

//asdgfasdg
#define LTBLUE    0xB6DF
#define LTTEAL    0xBF5F
#define LTGREEN   0xBFF7
#define LTCYAN    0xC7FF
#define LTRED     0xFD34
#define LTMAGENTA 0xFD5F
#define LTYELLOW  0xFFF8
#define LTORANGE  0xFE73
#define LTPINK    0xFDDF
#define LTPURPLE  0xCCFF
#define LTGREY    0xE71C

#define BLUE      0x001F
#define TEAL      0x0438
#define GREEN     0x07E0
#define CYAN      0x07FF
#define RED       0xF800
#define MAGENTA   0xF81F
#define YELLOW    0xFFE0
#define ORANGE    0xFC00
#define PINK      0xF81F
#define PURPLE    0x8010
#define GREY      0xC618
#define WHITE     0xFFFF
#define BLACK     0x0000

#define DKBLUE    0x000D
#define DKTEAL    0x020C
#define DKGREEN   0x03E0
#define DKCYAN    0x03EF
#define DKRED     0x6000
#define DKMAGENTA 0x8008
#define DKYELLOW  0x8400
#define DKORANGE  0x8200
#define DKPINK    0x9009
#define DKPURPLE  0x4010
#define DKGREY    0x4A49


boolean display1 = true;
double ox , oy ;
//asd

//CGraph::myGraph(tft, 10, bheight+bx+bsize, _screenWidth-10, _screenHeight-(bheight+bx+bsize*2), float 0, float 10, float 2, float 0, float 10, float 2);

UI::UI(TFT_eSPI& tft, int screenWidth, int screenHeight) : _tft(tft), _screenWidth(screenWidth), _screenHeight(screenHeight) {
}


void UI::begin() {
  
  // Initialize the TFT display
  _tft.begin();
  _tft.setRotation(3);
  _tft.init();
  _tft.setSwapBytes(true);
  _tft.invertDisplay(1);
  _tft.fillScreen(TFT_BLACK);
  _tft.setTextColor(TFT_WHITE);

  drawBufferBox( 20,20,255);
  drawResultBox( 20,20,255);
  int mainboxmode=0;
  drawMainBox(bx, by, _screenWidth-10-(mainboxmode*((_screenWidth-10)*0.2)), bheight+(mainboxmode*bheight), 20,20,255);
  /*
  for (x = 0; x <= 6.3; x += .1) {
    y = sin(x);
    Graph( x, y, bx + 48, _screenHeight-(bheight+bSize+by+18), _screenWidth-(60+bx*2), _screenHeight-((bx+bheight+bSize)*2+20), 0, 6.5, 1, -1, 1, .25, "", "x", "sin(x)", DKBLUE, RED, GREEN, WHITE, BLACK, display1);
  }
  */
  //drawMainBox(bx, by, _screenWidth-10, bheight, 6, bSize, 20,20,255);


}

void UI::cleanBufferBox(){
  drawRoundBorderInside(bx, by, _screenWidth-10, bheight,  255,255,255);
}

void UI::drawBufferBox( int r, int g, int b) {
  drawRoundBorder(bx, by, _screenWidth-10, bheight, 20,20,255);
  drawRoundBorderInside(bx, by, _screenWidth-10, bheight,  255,255,255);
}

void UI::drawResultBox( int r, int g, int b) {
  drawRoundBorder(bx, _screenHeight-(by+bheight), _screenWidth-10, bheight, 20,20,255);
  drawRoundBorderInside(bx, _screenHeight-(by+bheight),_screenWidth-10, bheight,  10,10,10);
}

void UI::cleanResultBox(){
  drawRoundBorderInside(bx, _screenHeight-(by+bheight), _screenWidth-10, bheight, 10,10,10);
}

void UI::drawMainBox(int x, int y, int width, int height, int r, int g, int b) {
  drawRoundBorder(bx, by + bheight, _screenWidth-10, _screenHeight - (bheight*2+by+bSize), 20,20,255);
  drawRoundBorderInside(bx, by + bheight, _screenWidth-10, _screenHeight - (bheight*2+by+bSize),  0,0,0);
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
  drawRoundBorderInside(bx, _screenHeight-(by+bheight), _screenWidth-10, bheight, 10,10,10);
      if (result.length() >= 16) {
        _tft.drawString(result.substring(0, 16), _screenWidth-(16*18+20), _screenHeight-32);
    } else {
      _tft.drawString(result, _screenWidth-(result.length()*18+20), _screenHeight-32);
    }
  
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

void UI::drawRoundBorder(int x, int y, int width, int height, int r, int g, int b) {
  _tft.fillRoundRect(x,y,width,height,radiusbox,_tft.color565(r,g,b));
  _tft.fillRoundRect(x+(bSize /2),y+(bSize /2),width-bSize ,height-bSize ,radiusbox,_tft.color565(r*0.7,g*0.7,b*0.7));
  _tft.fillRoundRect(x+(bSize ),y+(bSize ),width-bSize *2,height-bSize *2,radiusbox,_tft.color565(255,255,255));
}

void UI::drawRoundBorderInside(int x, int y, int width, int height, int r, int g, int b) {
  _tft.fillRoundRect(x+(bSize ),y+(bSize ),width-bSize *2,height-bSize *2,radiusbox,_tft.color565(r,g,b));
}

void UI::drawBorder(int x, int y, int width, int height, int r, int g, int b) {
  _tft.fillRect(x,y,width,height,_tft.color565(r,g,b));
  _tft.fillRect(x+(bSize /2),y+(bSize /2),width-bSize ,height-bSize ,_tft.color565(r*0.7,g*0.7,b*0.7));
  _tft.fillRect(x+(bSize ),y+(bSize ),width-bSize *2,height-bSize *2,_tft.color565(255,255,255));
}


void UI::Graph( double x, double y, double gx, double gy, double w, double h, double xlo, double xhi, double xinc, double ylo, double yhi, double yinc, String title, String xlabel, String ylabel, unsigned int gcolor, unsigned int acolor, unsigned int pcolor, unsigned int tcolor, unsigned int bcolor, boolean &redraw) {

  double ydiv, xdiv;
  // initialize old x and old y in order to draw the first point of the graph
  // but save the transformed value
  // note my transform funcition is the same as the map function, except the map uses long and we need doubles
  //static double ox = (x - xlo) * ( w) / (xhi - xlo) + gx;
  //static double oy = (y - ylo) * (gy - h - gy) / (yhi - ylo) + gy;
  double i;
  double temp;
  int rot, newrot;

  if (redraw == true) {

    redraw = false;
    ox = (x - xlo) * ( w) / (xhi - xlo) + gx;
    oy = (y - ylo) * (gy - h - gy) / (yhi - ylo) + gy;
    // draw y scale
    for ( i = ylo; i <= yhi; i += yinc) {
      // compute the transform
      temp =  (i - ylo) * (gy - h - gy) / (yhi - ylo) + gy;

      if (i == 0) {
        _tft.drawLine(gx, temp, gx + w, temp, acolor);
      }
      else {
        _tft.drawLine(gx, temp, gx + w, temp, gcolor);
      }

      _tft.setTextSize(1);
      _tft.setTextColor(tcolor, bcolor);
      _tft.setCursor(gx - 40, temp);
      // precision is default Arduino--this could really use some format control
      _tft.println(i);
    }
    // draw x scale
    for (i = xlo; i <= xhi; i += xinc) {

      // compute the transform

      temp =  (i - xlo) * ( w) / (xhi - xlo) + gx;
      if (i == 0) {
        _tft.drawLine(temp, gy, temp, gy - h, acolor);
      }
      else {
        _tft.drawLine(temp, gy, temp, gy - h, gcolor);
      }

      _tft.setTextSize(1);
      _tft.setTextColor(tcolor, bcolor);
      _tft.setCursor(temp, gy + 10);
      // precision is default Arduino--this could really use some format control
      _tft.println(i);
    }

    //now draw the labels
    _tft.setTextSize(2);
    _tft.setTextColor(tcolor, bcolor);
    _tft.setCursor(gx , gy - h - 30);
    _tft.println(title);

    _tft.setTextSize(1);
    _tft.setTextColor(acolor, bcolor);
    _tft.setCursor(gx , gy + 20);
    _tft.println(xlabel);

    _tft.setTextSize(1);
    _tft.setTextColor(acolor, bcolor);
    _tft.setCursor(gx - 30, gy - h - 10);
    _tft.println(ylabel);


  }

  //graph drawn now plot the data
  // the entire plotting code are these few lines...
  // recall that ox and oy are initialized as static above
  x =  (x - xlo) * ( w) / (xhi - xlo) + gx;
  y =  (y - ylo) * (gy - h - gy) / (yhi - ylo) + gy;
  _tft.drawLine(ox, oy, x, y, pcolor);
  _tft.drawLine(ox, oy + 1, x, y + 1, pcolor);
  _tft.drawLine(ox, oy - 1, x, y - 1, pcolor);
  ox = x;
  oy = y;

}


void UI::SIN(double num1,double num2){
  for (x = 0; x <= 6.5; x += .1) {
    y = sin(num1*x);
    Graph( x, y, bx + 48, _screenHeight-(bheight+bSize+by+18), _screenWidth-(60+bx*2), _screenHeight-((bx+bheight+bSize)*2+20), 0, 6.5, 1, -1, 1, .25, "", "x", "sin(x)", DKBLUE, RED, GREEN, WHITE, BLACK, display1);
  }
}

/*
  End of graphing functioin
*/



