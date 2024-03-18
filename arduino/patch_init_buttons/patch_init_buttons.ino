#include "DaisyDuino.h"

DaisyHardware patch;
Switch b7;
Switch b8;

void setup() {

  // initialize hardware
  patch = DAISY.init(DAISY_PATCH_SM);

  // b7, momentary button B7
  b7.Init(1000, true, PIN_PATCH_SM_B7, INPUT_PULLUP);

  // b8, toggle switch
  b8.Init(1000, true, PIN_PATCH_SM_B8, INPUT_PULLUP);

  // led on back panel
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {

  // debounce button and switch
  b7.Debounce();
  b8.Debounce();

  bool b7_pressed = b7.Pressed();
  bool b8_pressed = b8.Pressed();

  // led on back panel
  digitalWrite(LED_BUILTIN, b7_pressed || b8_pressed);

  // cv_out_1, C10 output jack
  float cv_out_1 = 0.0;
  if (b7_pressed && b8_pressed) {
    cv_out_1 = 4.0;
  }
  else if (b7_pressed || b8_pressed) {
    cv_out_1 = 3.0;
  }
  patch.WriteCvOut(PIN_PATCH_SM_CV_OUT_1, cv_out_1);

  // cv_out_2, led on front panel
  float cv_out_2 = 0.0;
  if (b7_pressed && b8_pressed) {
    cv_out_2 = 2.0;
  }
  else if (b7_pressed || b8_pressed) {
    cv_out_2 = 1.0;
  }
  patch.WriteCvOut(PIN_PATCH_SM_CV_OUT_2, cv_out_2);

}

