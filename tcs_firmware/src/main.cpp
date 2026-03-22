#include <Arduino.h>

const int LED_G = 11, LED_Y = 12, LED_R = 13;
const int BTN_WALK = 2, BTN_DANCE = 3;

void setup() {
  Serial.begin(9600);
  pinMode(LED_G, OUTPUT); pinMode(LED_Y, OUTPUT); pinMode(LED_R, OUTPUT);
  pinMode(BTN_WALK, INPUT_PULLUP); pinMode(BTN_DANCE, INPUT_PULLUP);
}

void runWalkCycle() {
  Serial.println("PEDESTRIAN CYCLE START");
  // Transition to Red
  digitalWrite(LED_G, LOW);
  digitalWrite(LED_Y, HIGH); delay(2000);
  digitalWrite(LED_Y, LOW);
  digitalWrite(LED_R, HIGH);

  // Instead of a 7-segment, we blink the Red LED to show "Don't Walk" ending
  for(int i=0; i<10; i++) {
    digitalWrite(LED_R, HIGH); delay(250);
    digitalWrite(LED_R, LOW);  delay(250);
  }
  Serial.println("PEDESTRIAN CYCLE END");
}

void dot() { digitalWrite(LED_Y, HIGH); delay(200); digitalWrite(LED_Y, LOW); delay(200); }
void dash() { digitalWrite(LED_G, HIGH); delay(600); digitalWrite(LED_G, LOW); delay(200); }
void letterSpace() { delay(400); }

void runPolycompMorse() {
  Serial.println("DANCE MODE: POLYCOMP");
  
  // P: .--.
  dot(); dash(); dash(); dot(); letterSpace();
  // O: ---
  dash(); dash(); dash(); letterSpace();
  // L: .-..
  dot(); dash(); dot(); dot(); letterSpace();
  // Y: -.--
  dash(); dot(); dash(); dash(); letterSpace();
  // C: -.-.
  dash(); dot(); dash(); dot(); letterSpace();
  // O: ---
  dash(); dash(); dash(); letterSpace();
  // M: --
  dash(); dash(); letterSpace();
  // P: .--.
  dot(); dash(); dash(); dot(); 
}

void loop() {
  // Check for Web/Serial Commands
  if (Serial.available() > 0) {
    char cmd = Serial.read();
    if (cmd == 'W') runWalkCycle();
    if (cmd == 'D') runPolycompMorse();
  }

  // Check for Buttons
  if (digitalRead(BTN_WALK) == LOW) runWalkCycle();
  if (digitalRead(BTN_DANCE) == LOW) runPolycompMorse();

  // Default state: Green is ON
  digitalWrite(LED_G, HIGH);
  digitalWrite(LED_R, LOW);
  digitalWrite(LED_Y, LOW);
}