#include <Wire.h>
#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>

SoftwareSerial BT (11,10);// RX, TX

#define pinMatrizLED 7

Adafruit_NeoPixel strip = Adafruit_NeoPixel(4, pinMatrizLED, NEO_GBR + NEO_KHZ800);

int mode = 0;   

char texto;

void setup() {
  
  BT.begin(9600);

  strip.begin();
  strip.show();        
  strip.setBrightness(50);
}

void loop() {


if (BT.available()) {
  
    texto = BT.read();

      if(texto=='a'){     
         if(++mode > 5) mode = 0; 
            switch(mode) {          
        case 0:
          colorWipe(strip.Color(  0,   0,   0), 50);   // Desligado
          break;
        case 1:
          colorWipe(strip.Color(255,   0,   0), 50);    // Vermelho
          break;
        case 2:
          colorWipe(strip.Color(0, 255,   0), 50);    // Verde
          break;
        case 3:
          colorWipe(strip.Color(0,   0, 255), 50);    // Azul
          break;
        case 4:
          rainbow(20); //Chroma
          break;
        case 5:
          rainbowCycle(20); //Chroma 2
          break;
      }
    }
  }
}

void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { 
    strip.setPixelColor(i, color);        
    strip.show();                         
    delay(wait);                          
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<768; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}


void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}


uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
