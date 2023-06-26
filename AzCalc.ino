//ESP32
//librerias pantalla
  #include <TFT_eSPI.h> // Hardware-specific library
  #include <SPI.h>
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



void setup() {
  Serial.begin(115200);
  setupScreen(); 
  setupPins(); //setup pins y pinled pantalla

  
}

void loop() {
  //digitalWrite(kpMulxDAT, HIGH);
  ledcWrite(ledChannel,  200);
  for(int j=0;j<4;j++){
    setALLOFF();
    digitalWrite(keypadOUT[j], HIGH);
    //setMuxChannel(i);
    for(int i=0;i<14;i++){
      setMuxChannel(i); 
      //Serial.println("read: " + digitalRead(kpMulxDAT));
      //Serial.println(analogRead(kpMulxDAT));
      if(((int) (analogRead(kpMulxDAT)))>500){
        tft.drawString( String(j)+ " : " + String(i),10,10);
        Serial.print(j);
        Serial.print(":");
        Serial.println(i);
        delay(100);
      }
      delay(1);
      //setMuxChannel(0);
      

    }
  }

  delay(1);
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
}

int setMuxChannel(byte channel){
  for(int i=0;i<4;i++){
    digitalWrite(kpMulxOUT[i], bitRead(channel, i));
  }
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
//?
void printPadLines(){
  Serial.println("///pad//");
    for(int i=0;i<4;i++){
      Serial.print(digitalRead(keypadOUT[i]));
  }
  Serial.println();
  Serial.println("/////");
}

void printchannels(){
  Serial.println("/////");
    for(int i=0;i<4;i++){
     Serial.println(kpMulxOUT[i]);
  }
  Serial.println("/////");
}
///??