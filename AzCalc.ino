//ESP32
  #include <TFT_eSPI.h> // Hardware-specific library
  #include <SPI.h>
  #include "tinyexpr.h"
  #include "UI.h"

  TFT_eSPI tft = TFT_eSPI();  //pantalla
  int displayWidth = 320;
  int displayHeight = 240;
  UI ui(tft, displayWidth , displayHeight);
//vars pins keypad
  int keypadOUT[4] = {13, 12, 14, 27};
  int kpMulxOUT[4] = {26, 25, 33, 32};
  int keymapmode = 1;
  int kpMulxDAT = 34;
//end vars pins keypad
  int timmer=0;
  int timmer2=0;
  String result="";
  int xgraph = 0;
  bool redraw = false;
//display vars
  int screenled = 5;
  const int freq = 5000;
  const int ledChannel = 0;
  const int resolution = 8;

//end display vars
//keymap matrix calcmode
  String keyMap1[4][14] = {
  //0       1       2         3       4        5       6        7         8          9       10         11         12        13
  {"0",    ".",  "<EXP>",  "<ANS>",  "=",     ""  ,    ""  ,  "<UP>",  "<DOWN>", "<LOG>" , "^(1/" ,  "<CALC>", "<SHIFT>",   ""     },//0
  {"1",    "2",    "3"  ,    "+"  ,  "-",   "<IN>", "<OUT>",     ",",    "^"   ,   "^2"  ,   "^3" , "<SOLVE>", "<ALPHA>",   ""     },//1
  {"4",    "5",    "6"  ,    "*"  ,  "/",   "(-)" ,   ";"  , "<HYP>",   "sin(" , "COS("  , "TAN(" ,  "<STO>" ,  "<LEFT>",  "<AC>"  },//2
  {"7",    "8",    "9"  , "<DEL>" ,   "",  "<RCL>", "<ENG>",     "(",     ")"  , "<ab/c>", "<M+>" ,   "<LN>" ,  "<RIGH>", "<OMEGA>"} //3
  };
  String keyMap2[4][14] = {
  //0       1       2         3       4        5       6        7         8          9       10         11         12        13
  {"0",    ".",    "x"  ,    "y"  ,  "=",     ""  ,    ""  ,  "<UP>",  "<DOWN>",    "e"  ,   "f"  ,    "a"   , "<SHIFT>",   ""     },//0
  {"1",    "2",    "3"  ,    "+"  ,  "-",   "<IN>", "<OUT>",     ",",    "^"   ,   "^2"  ,   "^3" ,    "b"   , "<ALPHA>",   ""     },//1
  {"4",    "5",    "6"  ,    "*"  ,  "/",   "(-)" ,   ";"  , "<HYP>",   "sin(" , "COS("  , "TAN(" ,    "c"   ,  "<LEFT>",  "<AC>"  },//2
  {"7",    "8",    "9"  , "<DEL>" ,   "",  "<RCL>", "<ENG>",     "(",     ")"  , "<ab/c>", "<M+>" ,    "d"   ,  "<RIGH>", "<OMEGA>"} //3
  };
  String buffer ="";
  String key ="";
  String oldkey ="";
//


void setup() {
  Serial.begin(115200);
  ui.begin(); 
  setupPins(); //setup pins y pinled display
  ui.Graph2(0,0, true);
}
  

void loop() {
  //ui.drawBorder(5, 5, dpWidth-10, 40, 5, 5,10,15);

  if (timmer>1000){
    key = getKey();
    timmer=0;

    if (!key.isEmpty() && key!=oldkey) {
      
      buffer = ui.updateBuffer(buffer,key);
      ui.cleanResultBox();
      result = (ui.printResult(String(te_interp(buffer.c_str(), 0))));
      redraw = true;
      ui.cleanMainBox();
      xgraph=0;
      oldkey=key;
    }else{
      oldkey="muahaha";//is just to allow the key to be pressed again after the timer ends
      timmer=-100000;//is to avoid getting 2 times the key with 1 press, probably should change the number base on the processor speed.
    }
    
  }

  timmer++;

  
  if(xgraph>10){
    xgraph=0;
  }

  redraw=false;
  xgraph=xgraph+0.01;
  timmer2++;
}

void setupScreen(){

  //tft.setTextColor(TFT_BLACK, TFT_WHITE); //invierte los colores fondo y texto *cambiar fill screen por white tambien.
}

void setupPins(){
  for(int i=0;i<4;i++){
    pinMode(keypadOUT[i], OUTPUT);
    pinMode(kpMulxOUT[i], OUTPUT);
  }
  pinMode(kpMulxDAT, INPUT);
  ledcSetup(ledChannel,freq,resolution);
  ledcAttachPin(screenled, ledChannel);
  ledcWrite(ledChannel,  200);
}

void setMuxChannel(byte channel){
  for(int i=0;i<4;i++){
    digitalWrite(kpMulxOUT[i], bitRead(channel, i));
  }
}

void updateBuffer(String mykey){
  tft.setTextSize(3);
  if(mykey == "<DEL>"){
    buffer = buffer.substring(0, buffer.length() - 1);
    tft.drawString( buffer,10,10);
    tft.setTextSize(2);
    return ;
  }
  if (!key.isEmpty()) {
    buffer = buffer + mykey;
    tft.drawString( buffer,10,10);
  }
  tft.setTextSize(2);
  return ;
}

String getKey(){
  for(int j=0;j<4;j++){
    //setALLOFF();
    for (int k = 0; k < 4; k++) {
      digitalWrite(keypadOUT[k], (k == j) ? HIGH : LOW);
    }
    for(int i=0;i<14;i++){
      setMuxChannel(i); 
      if(((int) (analogRead(kpMulxDAT)))>500){
        //tft.fillScreen(TFT_BLACK);
        if(keyMap1[j][i]=="<ALPHA>"){
          keymapmode = keymapmode*(-1);
          ui.drawBufferBox( 135-115*keymapmode,20,255);
          ui.drawbufferless16(buffer);
          return "";
        }
        if(keymapmode == 1){
          return keyMap1[j][i];
        }
        if(keymapmode == (-1)){
          return keyMap2[j][i];
        }
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

String analyzeAndReplaceString(String inputString, double variableValue) {
  String outputString = inputString;

  int index = outputString.indexOf('x');

  
  while (index >= 0) {
    outputString.replace("x", String(variableValue)); 
    index = outputString.indexOf('x', index + 1); 
  }

  return outputString;
}