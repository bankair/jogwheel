#include <Keyboard.h>

#define CLK 2
#define DT 3
#define SW 6

int counter = 0;
int currentStateCLK;
int lastStateCLK;
String currentDir = "";
unsigned long lastButtonPress = 0;

void setup() {
  // Set encoder pins as inputs
  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);
  pinMode(SW, INPUT_PULLUP);

  // Setup Serial Monitor
  Serial.begin(9600);
  Keyboard.begin();

  // Read the initial state of CLK
  lastStateCLK = digitalRead(CLK);
}

void loop() {
  currentStateCLK = digitalRead(CLK);
  if (currentStateCLK != lastStateCLK  && currentStateCLK == 1) {
    if (digitalRead(DT) != currentStateCLK) {
      counter ++;
      currentDir = "CCW";
      Keyboard.press(KEY_RIGHT_ARROW);
      Keyboard.release(KEY_RIGHT_ARROW);
    } else {
      counter --;
      currentDir = "CW";
      Keyboard.press(KEY_LEFT_ARROW);
      Keyboard.release(KEY_LEFT_ARROW);
    }

    Serial.print("Direction: ");
    Serial.print(currentDir);
    Serial.print(" | Counter: ");
    Serial.println(counter);
  }

  lastStateCLK = currentStateCLK;

  int btnState = digitalRead(SW);

  if (btnState == LOW) {
    if (millis() - lastButtonPress > 50) {
      Serial.println("Button pressed!");
      Keyboard.write(' ');
    }
    lastButtonPress = millis();
  }
  delay(1);
}
