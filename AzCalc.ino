//ESP32
//librerias pantalla
  #include <TFT_eSPI.h> // Hardware-specific library
  #include <SPI.h>
  #include "tinyexpr.h"
//fin librerias pantalla
  TFT_eSPI tft = TFT_eSPI();  //pantalla
//variables pins keypad
  int keypadOUT[4] = {13, 12, 14, 27};
  int kpMulxOUT[4] = {26, 25, 33, 32};
  int kpMulxDAT = 34;
//fin variables pins keypad
//pantalla variables
  int screenled = 5;
  const int freq = 5000;
  const int ledChannel = 0;
  const int resolution = 8;
//fin pantalla variables
//keymap matrix calcmode
  String keyMap1[4][14] = {
  //0       1       2         3       4        5       6        7         8          9       10         11         12        13
  {"0",    ".",  "<EXP>",  "<ANS>",  "=",     ""  ,    ""  ,  "<UP>",  "<DOWN>", "<LOG>" , "^(1/" ,  "<CALC>", "<SHIFT>",   ""     },//0
  {"1",    "2",    "3"  ,    "+"  ,  "-",   "<IN>", "<OUT>",     ",",    "^"   ,   "^2"  ,   "^3" , "<SOLVE>", "<ALPHA>",   ""     },//1
  {"4",    "5",    "6"  ,    "*"  ,  "/",   "(-)" ,   ";"  , "<HYP>",   "SIN(" , "COS("  , "TAN(" ,  "<STO>" ,  "<LEFT>",  "<AC>"  },//2
  {"7",    "8",    "9"  , "<DEL>" ,   "",  "<RCL>", "<ENG>",     "(",     ")"  , "<ab/c>", "<M+>" ,   "<LN>" ,  "<RIGH>", "<OMEGA>"} //3
  };
  String buffer ="";
  String key ="";
//


void setup() {
  Serial.begin(115200);
  setupScreen(); 
  setupPins(); //setup pins y pinled pantalla

  
}

void loop() {
  key = getKey();
  updateBuffer(key);
  tft.drawString( buffer,10,20);
  tft.drawString(String(te_interp(buffer.c_str(), 0)), 10, 35);
  delay(100);
}


void setupScreen(){
  tft.setRotation(3);
  tft.init();
  tft.fillScreen(TFT_BLACK);
  //tft.setTextColor(TFT_BLACK, TFT_WHITE); //usa mas energia *cambiar fill screen por white tambien.
 
}

void setupPins(){
  for(int i=0;i<4;i++){
    pinMode(keypadOUT[i], OUTPUT);
    pinMode(kpMulxOUT[i], OUTPUT);
  }
  pinMode(kpMulxDAT, INPUT);
  ledcSetup(ledChannel,freq,resolution);
  ledcAttachPin(screenled, ledChannel);
  ledcWrite(ledChannel,  100);
}

void setMuxChannel(byte channel){
  for(int i=0;i<4;i++){
    digitalWrite(kpMulxOUT[i], bitRead(channel, i));
  }
}

void updateBuffer(String mykey){
  if(mykey == "<DEL>"){
    buffer = buffer.substring(0, buffer.length() - 1);
    return ;
  }
  if (!key.isEmpty()) {
    buffer = buffer + mykey;
  }
  return ;
}

String getKey(){
  for(int j=0;j<4;j++){
    setALLOFF();
    digitalWrite(keypadOUT[j], HIGH);
    for(int i=0;i<14;i++){
      setMuxChannel(i); 
      if(((int) (analogRead(kpMulxDAT)))>500){
        tft.fillScreen(TFT_BLACK);
        return keyMap1[j][i];
      }
    }
  }
  return "";
}



int setALLON(){
  for(int i=0;i<4;i++){
    digitalWrite(keypadOUT[i], HIGH);
  }
}

int setALLOFF(){
  for(int i=0;i<4;i++){
    digitalWrite(keypadOUT[i], LOW);
  }
}