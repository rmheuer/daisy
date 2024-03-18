#include "DaisyDuino.h"

DaisyHardware patch;

void setup() {
  // initialize hardware
  patch = DAISY.init(DAISY_PATCH_SM);
}

void loop() {

  // update inputs
  patch.ProcessAllControls();

  // gate_in_1, B10 input jack
  GateIn gate_in_1 = patch.gateIns[0];
  if (gate_in_1.State()) {
    // gate_out_1, B5 output jack
    digitalWrite(PIN_PATCH_SM_GATE_OUT_1, HIGH);
    // cv_out_2, C1 led on front panel
    digitalWrite(PIN_PATCH_SM_CV_OUT_2, HIGH);
  }
  else {
    digitalWrite(PIN_PATCH_SM_GATE_OUT_1, LOW);
    digitalWrite(PIN_PATCH_SM_CV_OUT_2, LOW);
  }

  // gate_in_2, B9 input jack
  GateIn gate_in_2 = patch.gateIns[1];
  if (gate_in_2.State()) {
    // gate_out_2, B6 output jack
    digitalWrite(PIN_PATCH_SM_GATE_OUT_2, HIGH);
  }
  else {
    digitalWrite(PIN_PATCH_SM_GATE_OUT_2, LOW);
  }
}
