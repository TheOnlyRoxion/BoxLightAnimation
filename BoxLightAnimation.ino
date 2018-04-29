#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 8
int brightnes=255;
const int doorPin =   6;
const int doorPinGND =   7;
const int buttonPin = 4;
const int buttonPinGND = 5;
int i=0;
int state =1;
int Stringled[5][11]={
      {0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10},
      {21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11},
      {22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32},
      {43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33},
      {44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54}
};


// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(55, PIN, NEO_BRG );

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
 Serial.begin(9600);

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
pinMode(doorPin, INPUT);
pinMode(doorPin, INPUT_PULLUP);
pinMode(doorPinGND, OUTPUT);
digitalWrite(doorPinGND, LOW);


randomSeed(analogRead(A2)^2);
strip.setBrightness(brightnes); 

}

void loop() {

   int sensorValue = analogRead(A0);
  Serial.println(sensorValue);

if(digitalRead(doorPin)==HIGH){
  state=0;
}else{
   if(digitalRead(buttonPin)==LOW){
    state++;
   }else{
    state=state;
      
   }
    
}




    switch(state){
    case 0:
      swipe(strip.Color(255,255,255), 100,2,Stringled);
      
    break;
    
    case 1:
   
      swipe(strip.Color(255,255,255), 100,1,Stringled);

    break;
  
    case 2:
      state=0;
    break;
    
    
    
    
    }












}


void swipe(uint32_t c,uint8_t wait, int rotation,int Stringled[][11]){

  switch(rotation){
  case 1:
for(int i=0; i<11; i++) {
for(int j=5; j>=0; j--){
    strip.setPixelColor(Stringled[j][i], c);
  } 
  strip.show();
  delay(wait);
}
break;
  case 2:
for(int j=5; j>=0; j--){
for(int i=0; i<11; i++) {

    strip.setPixelColor(Stringled[j][i], c);
    strip.show();
  } 
  
  delay(wait);
}
break;
case 3:
for(int i=11; i>0; i--){
for(int j=5; j>=0; j--){
strip.setPixelColor(Stringled[j][i], c);
  } 
  strip.show();
  delay(wait);
}
break;
case 4:

for(int j=0; j<5; j++){
for(int i=0; i<11; i++) {

    strip.setPixelColor(Stringled[j][i], c);
  } 
  strip.show();
  delay(wait);
}
break;


  }

}


  





// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
if(digitalRead(doorPin)==HIGH){
  break;
}
    
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    if(digitalRead(doorPin)==HIGH){
  break;
}
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      if(digitalRead(doorPin)==HIGH){
      break;
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      if(digitalRead(doorPin)==HIGH){
        break;
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
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
