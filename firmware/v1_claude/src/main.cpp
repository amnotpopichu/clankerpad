#include <bluefruit.h>

BLEDis bledis;
BLEHidAdafruit blehid;

// Encoder pins (from schematic: twist1=D0, twist2=D1, r1=D2)
#define ENC_A   0
#define ENC_B   1
#define ENC_SW  2

// 8 key switches: s1-s8 → D3,D4,D5,D6,D7,D8,D9,D10
const int NUM_KEYS = 8;
const int KEY_PINS[NUM_KEYS] = {3, 4, 10, 9, 5, 6, 8, 7};
const uint8_t KEYCODES[NUM_KEYS] = {
  HID_KEY_2, HID_KEY_3, HID_KEY_4, HID_KEY_5,
  HID_KEY_6, HID_KEY_7, HID_KEY_8, HID_KEY_9
};

bool keyState[NUM_KEYS];
bool encSwState;
int  encLastA;

void startAdv();

void setup() {
  Serial.begin(115200);

  for (int i = 0; i < NUM_KEYS; i++) {
    pinMode(KEY_PINS[i], INPUT_PULLUP);
    keyState[i] = HIGH;
  }

  pinMode(ENC_A,  INPUT_PULLUP);
  pinMode(ENC_B,  INPUT_PULLUP);
  pinMode(ENC_SW, INPUT_PULLUP);
  encLastA    = digitalRead(ENC_A);
  encSwState  = HIGH;

  Bluefruit.begin();
  Bluefruit.setName("ClankerPad");
  Bluefruit.setTxPower(4);

  bledis.setManufacturer("Seeed");
  bledis.setModel("XIAO nRF52840");
  bledis.begin();

  blehid.begin();
  startAdv();

  Serial.println("ClankerPad ready");
}

void startAdv() {
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.addAppearance(BLE_APPEARANCE_HID_KEYBOARD);
  Bluefruit.Advertising.addService(blehid);
  Bluefruit.Advertising.addName();
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244);
  Bluefruit.Advertising.setFastTimeout(30);
  Bluefruit.Advertising.start(0);
}

void loop() {
  bool connected = Bluefruit.connected();

  // --- 8 key switches ---
  for (int i = 0; i < NUM_KEYS; i++) {
    bool state = digitalRead(KEY_PINS[i]);
    if (state != keyState[i]) {
      delay(5);
      state = digitalRead(KEY_PINS[i]);
      if (state != keyState[i]) {
        Serial.print("Key "); Serial.print(i + 1);
        Serial.println(state == LOW ? " PRESS" : " RELEASE");
        if (connected) {
          if (state == LOW) {
            uint8_t kc[6] = {KEYCODES[i], 0, 0, 0, 0, 0};
            blehid.keyboardReport(0, kc);
          } else {
            blehid.keyRelease();
          }
        }
        keyState[i] = state;
      }
    }
  }

  // --- Encoder click (D2, active LOW) ---
  bool sw = digitalRead(ENC_SW);
  if (sw != encSwState) {
    delay(5);
    sw = digitalRead(ENC_SW);
    if (sw != encSwState) {
      Serial.println(sw == LOW ? "Encoder CLICK press" : "Encoder CLICK release");
      if (connected) {
        if (sw == LOW) {
          uint8_t kc[6] = {HID_KEY_ENTER, 0, 0, 0, 0, 0};
          blehid.keyboardReport(0, kc);
        } else {
          blehid.keyRelease();
        }
      }
      encSwState = sw;
    }
  }

  // --- Encoder rotation (quadrature on D0/D1) ---
  int a = digitalRead(ENC_A);
  if (a != encLastA) {
    int b = digitalRead(ENC_B);
    if (a == LOW) {
      if (b == HIGH) {
        Serial.println("Encoder CW  → vol up");
        if (connected) {
          blehid.consumerKeyPress(HID_USAGE_CONSUMER_VOLUME_INCREMENT);
          delay(10);
          blehid.consumerKeyRelease();
        }
      } else {
        Serial.println("Encoder CCW → vol down");
        if (connected) {
          blehid.consumerKeyPress(HID_USAGE_CONSUMER_VOLUME_DECREMENT);
          delay(10);
          blehid.consumerKeyRelease();
        }
      }
    }
    encLastA = a;
  }

  delay(5);
}
