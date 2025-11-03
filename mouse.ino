#include <Mouse.h>

void setup() {
  Serial.begin(115200);
#if !defined(__MIPSEL__)
  while (!Serial);
#endif
  Mouse.begin();
  Serial.println("Ready to receive movement data (x,y)");
}

void loop() {
  if (!Serial.available()) return;

  String input = Serial.readStringUntil('\n');
  input.trim();
  if (input.length() == 0) return;

  int commaIndex = input.indexOf(',');
  if (commaIndex == -1) {
    Serial.println("Invalid input format. Expected: x,y");
    return;
  }

  int xTarget = input.substring(0, commaIndex).toInt();
  int yTarget = input.substring(commaIndex + 1).toInt();

  xTarget = constrain(xTarget, -1000, 1000);
  yTarget = constrain(yTarget, -1000, 1000);
  // step size
  const int stepSize = 5;
  int steps = max(abs(xTarget), abs(yTarget)) / stepSize;
  if (steps < 1) steps = 1;

  float xStep = (float)xTarget / steps;
  float yStep = (float)yTarget / steps;

  for (int i = 0; i < steps; i++) {
    Mouse.move((int)xStep, (int)yStep, 0);
    delay(5); // change delay number for speed
  }


  Mouse.move(xTarget - (int)(xStep * steps), yTarget - (int)(yStep * steps), 0);
}
