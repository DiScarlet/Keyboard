#include <Arduino.h>
#include <BleKeyboard.h>

const uint8_t rowPins[] = {21, 14, 32, 13};
const uint8_t colPins[] = {26, 25, 34, 39, 36, 4, 5, 18, 19, 16, 17, 22, 23};
const uint8_t rowCount = sizeof(rowPins) / sizeof(rowPins[0]);
const uint8_t colCount = sizeof(colPins) / sizeof(colPins[0]);

const uint8_t keymap[rowCount][colCount] = {
  {KEY_ESC, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '='},
  {KEY_TAB, 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']'},
  {KEY_CAPS_LOCK, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', KEY_RETURN},
  {KEY_LEFT_SHIFT, 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', KEY_SPACE, KEY_BACKSPACE}
};

bool previousState[rowCount][colCount] = {};
BleKeyboard bleKeyboard("Duck Keyboard", "Duck Keyboard", 100);

void setupMatrix() {
  for (uint8_t r = 0; r < rowCount; ++r) {
    pinMode(rowPins[r], OUTPUT);
    digitalWrite(rowPins[r], HIGH);
  }

  for (uint8_t c = 0; c < colCount; ++c) {
    pinMode(colPins[c], INPUT_PULLUP);
  }
}

void scanMatrix(bool matrix[rowCount][colCount]) {
  for (uint8_t r = 0; r < rowCount; ++r) {
    digitalWrite(rowPins[r], LOW);
    delayMicroseconds(30);

    for (uint8_t c = 0; c < colCount; ++c) {
      matrix[r][c] = digitalRead(colPins[c]) == LOW;
    }

    digitalWrite(rowPins[r], HIGH);
  }
}

bool matrixChanged(const bool current[rowCount][colCount]) {
  for (uint8_t r = 0; r < rowCount; ++r) {
    for (uint8_t c = 0; c < colCount; ++c) {
      if (current[r][c] != previousState[r][c]) {
        return true;
      }
    }
  }
  return false;
}

void sendKeys(const bool current[rowCount][colCount]) {
  bleKeyboard.releaseAll();

  for (uint8_t r = 0; r < rowCount; ++r) {
    for (uint8_t c = 0; c < colCount; ++c) {
      if (current[r][c]) {
        bleKeyboard.press(keymap[r][c]);
      }
    }
  }
}

void setup() {
  Serial.begin(115200);
  setupMatrix();
  bleKeyboard.begin();
}

void loop() {
  bool currentState[rowCount][colCount] = {};
  scanMatrix(currentState);

  if (bleKeyboard.isConnected() && matrixChanged(currentState)) {
    sendKeys(currentState);
    memcpy(previousState, currentState, sizeof(previousState));
  } else if (!bleKeyboard.isConnected()) {
    memset(previousState, 0, sizeof(previousState));
  }

  delay(10);
}
