#include <boarddefs.h>
#include <IRremote.h>
#include <IRremoteInt.h>
#include <ir_Lego_PF_BitStreamEncoder.h>

int ikPin = A0;
IRrecv irrecv(ikPin);
decode_results results;

int Rled = 9; 
int Gled = 10; 
int Bled = 11;
int mode = 0;
int lastMode = 0;

void off() {
  analogWrite(Rled, 0); 
  analogWrite(Gled, 0); 
  analogWrite(Bled, 0);
}
void white() {
  analogWrite(Rled, 255); 
  analogWrite(Gled, 255); 
  analogWrite(Bled, 255);
}
void red() {
  analogWrite(Rled, 255); 
  analogWrite(Gled, 0); 
  analogWrite(Bled, 0);
}
void yellow() {
  analogWrite(Rled, 255); 
  analogWrite(Gled, 20); 
  analogWrite(Bled, 0);
}
void green() {
  analogWrite(Rled, 0); 
  analogWrite(Gled, 255); 
  analogWrite(Bled, 0);
}
void cyan() {
  analogWrite(Rled, 0); 
  analogWrite(Gled, 255); 
  analogWrite(Bled, 255);
}
void blue() {
  analogWrite(Rled, 0); 
  analogWrite(Gled, 0); 
  analogWrite(Bled, 255);
}
void magneta() {
  analogWrite(Rled, 255); 
  analogWrite(Gled, 0); 
  analogWrite(Bled, 255);
}

void takeMode(int mode) {
  if (mode == 0)
  off();
  
  else if (mode == 1)
  red();
  
  else if (mode == 2)
  yellow();
  
  else if (mode == 3)
  green();

  else if (mode == 4)
  cyan();

  else if (mode == 5)
  blue();

  else if (mode == 6)
  magneta();
  else if (mode == 7)
  white();
}

void setup() {
 pinMode(Bled, OUTPUT); 
 pinMode(Gled, OUTPUT); 
 pinMode(Rled, OUTPUT);

randomSeed(analogRead(1));

lastMode = random(1, 7);

 irrecv.enableIRIn(); // Start the receiver

 Serial.begin(9600);
 Serial.println("IR_RGB_0");
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    Serial.println(mode);
    Serial.println(lastMode);
    Serial.println();
    
    //CH
    if (results.value == 0xFF629D && mode != 0) {
      lastMode = mode;
      mode = 0;
    }
    else if (results.value == 0xFF629D && mode == 0) {
      mode = lastMode;
    }
    //CH-
    else if (results.value == 0xFFA25D && mode > 1 && mode < 7) {
      mode -= 1;
    }
    else if (results.value == 0xFFA25D && mode == 1) {
      mode = 6;
    }
    else if (results.value == 0xFFA25D && mode == 7) {
      mode = random(1, 7);
    }
    //CH+
    else if (results.value == 0xFFE21D && 0 < mode && mode < 6) {
      mode += 1;
    }
    else if (results.value == 0xFFE21D && mode == 6) {
      mode = 1;
    }
    else if (results.value == 0xFFE21D && mode == 7) {
      mode = random(1, 7);
    }
    //0
    if (results.value == 0xFF6897) {
      mode = 7;
    }
    else if (results.value == 0xFF6897 && mode == 0) {
      mode = lastMode;
    }
    //1
    else if (results.value == 0xFF30CF) 
    mode = 1;
    //2
    else if (results.value == 0xFF18E7) 
    mode = 2;
    //3
    else if (results.value == 0xFF7A85) 
    mode = 3;
    //4
    else if (results.value == 0xFF10EF) 
    mode = 4;
    //5
    else if (results.value == 0xFF38C7) 
    mode = 5;
    //6
    else if (results.value == 0xFF5AA5) 
    mode = 6;

    takeMode(mode);
    
    irrecv.resume();
  }
}
