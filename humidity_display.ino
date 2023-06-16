//design file:
// https://www.tinkercad.com/things/gbtEyLXFqW7
// author : jelly coding (dsbaek)

#include <Servo.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_LEDBackpack.h>

// C++ code
//
// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN    2

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 12

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);


Adafruit_7segment matrix = Adafruit_7segment();


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

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);

  strip.begin();
  //strip.setBrightness(50);
  //strip.show(); // Initialize all pixels to 'off'
  rainbow(1);
  
  Serial.begin(9600);
  Serial.println("7 Segment Backpack Test");
  
  matrix.begin(0x70);
  
  // print a floating point 
  matrix.print(12.34);
  matrix.writeDisplay();
  delay(200);
  matrix.clear();


  
}

int val;

uint32_t mint = strip.Color(0, 255, 255);

void loop()
{
  float humidity;
  digitalWrite(LED_BUILTIN, HIGH);
  
  //아날로그 신호 읽기(습도센서의 출력 신호 전압 )
  //analogRead 함수의 리턴값은 0에서 1023 사이의 값임
  val = analogRead(A0); 
  
  humidity = (val/1024.0 ) * 100.0;
  
  // print a floating point 
  matrix.print(humidity);
  matrix.writeDisplay();
  delay(100);

  int barGraphVal = int(LED_COUNT*humidity/70.0);
  uint16_t i;
  
  strip.clear();
  for(i=0; i<barGraphVal; i++) {
    strip.setPixelColor(i, mint);
  }
  strip.show();
  
  
 
  digitalWrite(LED_BUILTIN, LOW);
  delay(100); // Wait for 100 millisecond(s)
}
