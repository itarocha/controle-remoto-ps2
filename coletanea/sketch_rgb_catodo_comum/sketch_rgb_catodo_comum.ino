#include <VirtualWire.h>

// ARDUINO UNO
//#define PIN_R 9
//#define PIN_G 10
//#define PIN_B 11

// ATTINY 85
#define PIN_R 0 // pino 5
#define PIN_G 1 // pino 6
//#define PIN_B 2 // pino 7
#define PIN_B 5 // pino 0

int r = 0;
int g = 0;
int b = 0;


struct rgb {
  byte r, g, b;  
};

const rgb RED = {255, 0, 0};
const rgb GREEN = {0, 255, 0};
const rgb BLUE = {0, 0, 255};
const rgb ORANGE = { 255, 165, 0 }; 
const rgb YELLOW = { 255, 255, 0 };
const rgb PURPLE = { 148, 0, 211 };
const rgb INDIGO = { 75, 0, 130 };
//const rgb VIOLET = { 238, 130, 238 };
//const rgb CHOCOLATE = {210, 105, 30 };

const rgb WHITE = { 255, 255, 255 };
const rgb AQUA = { 0, 180, 180 };
const rgb OFF = { 0, 0, 0 };

void setup() {
  //Serial.begin(9600);

  pinMode(PIN_R, OUTPUT);
  pinMode(PIN_G, OUTPUT);
  pinMode(PIN_B, OUTPUT);

  analogWrite(PIN_R, 0);
  analogWrite(PIN_G, 0);
  analogWrite(PIN_B, 0);
}

void loop() {
  //Serial.println("RED");
  smooth(RED);
  
  //Serial.println("ORANGE");
  smooth(ORANGE);
  
  //Serial.println("YELLOW");
  smooth(YELLOW);
  
  //Serial.println("GREEN");
  smooth(GREEN);

  //Serial.println("AQUA");
  smooth(AQUA);

  //Serial.println("BLUE");
  smooth(BLUE);

  //Serial.println("INDIGO");
  smooth(INDIGO);

  //Serial.println("PURPLE");
  smooth(PURPLE);
}

void smooth(rgb cor){
  while (r != cor.r || g != cor.g || b != cor.b) {
    if (r < cor.r) r += 1;
    if (r > cor.r) r -= 1;

    if (g < cor.g) g += 1;
    if (g > cor.g) g -= 1;

    if (b < cor.b) b += 1;
    if (b > cor.b) b -= 1;
    
    setColor();
    delay(20);
  } 
  delay(2000);
}

void setColor(){
  analogWrite(PIN_R, r);
  analogWrite(PIN_G, g);
  analogWrite(PIN_B, b);
}
